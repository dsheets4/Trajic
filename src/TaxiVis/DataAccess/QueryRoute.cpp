// Written by David Sheets
// TaxiVis product for analyzing trends in taxi trajectories.
// Copyright (C) 2012  David Sheets (dsheets4@kent.edu)
//
// This is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <sstream>

#include <QtCore/QDateTime>
#include <QtCore/QVariant>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>

#include "CommonDefinitions.h"
#include "DataAccess/QueryFunctions.h"
#include "DataAccess/QueryRoute.h"


namespace DataAccess
{
   // =========================================================================
   // =========================================================================
   
   // -------------------------------------------------------------------------
   //! Private implementation of the QueryRoute.
   class QueryRouteImpl
   {
   public:
      QueryRouteImpl()
         : m_sDbName("QueryRoute")
         , m_db(QSqlDatabase::addDatabase("QSQLITE", m_sDbName))
      {
         // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         QString sDbFile = CommonDefinitions::sDataDir.c_str();
         sDbFile += "/taxi2-Medium.db";
         m_db.setDatabaseName(sDbFile);
   
         // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         if( !m_db.open() )
         {
            //std::cerr << "Error connecting to or creating index: " << std::endl;
         }
      }

      ~QueryRouteImpl()
      {
         m_db.close();
		 //m_db.removeDatabase(m_sDbName);
      }

      QString             m_sDbName;    //!< Name of the database connection for this object
      QSqlDatabase        m_db;         //!< Database connection for this class
   };
   
   // =========================================================================
   // =========================================================================

   // -------------------------------------------------------------------------
   QueryRoute::QueryRoute()
      : m_pImpl( new QueryRouteImpl() )
   {
   }

   // -------------------------------------------------------------------------
   QueryRoute::~QueryRoute()
   {
      delete m_pImpl;
      m_pImpl = NULL;
   }


   // -------------------------------------------------------------------------   
   void QueryRoute::QueryTaxiRoute( QueryRouteHandler& handler, QueryRouteCriteria criteria )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      //! @todo The query may not need to be run each time, determine if that can
      //!       be used to optimize the operation here.
      const int iTaxiIdIdx    = 0;
      const int iTimestampIdx = 1;
      const int iLatIdx       = 2;
      const int iLonIdx       = 3;
      const int iStatusIdx    = 4;
      const int iHeadingIdx   = 5;
      const int iSpeedIdx     = 6;
      std::stringstream ss;
      ss << "SELECT Taxi_ID, Timestamp, Lat, Lon, Status, Heading, Speed "
         << "FROM TaxiPoint WHERE ";
      //ss << "(Taxi_ID=34 OR Taxi_ID=27538 OR Taxi_ID=16042) AND ";
      //ss << "(Taxi_ID>=860 ) AND (Taxi_ID<875) AND ";
	  
	  // Taxi_ID has a spike in its route at 0700-0705.
      //ss << "(Taxi_ID=868) AND ";

	  // Apply the time criteria.
      if( !criteria.GetTimeStart().isNull() )
      {
         ss << "Timestamp>=" << criteria.GetTimeStart().toMSecsSinceEpoch() << " AND ";
	  }
      if( !criteria.GetTimeStart().isNull() )
      {
         ss << "Timestamp<"  << criteria.GetTimeEnd().toMSecsSinceEpoch()   << " AND ";
	  }

      ss << "Error=0 ORDER BY Taxi_ID,Timestamp";
   
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      QSqlQuery q(m_pImpl->m_db);
      q.setForwardOnly(true); // Allows for optimized query (if driver supports)
      if( ExecuteQuery(q, ss.str().c_str()) == 0 )
      {
         Point    p;
         RoutePtr route( new Route() );

         // Add any header logic here.  This is after we known the query has 
         // succeeded but before entering the loop to iterate over all the routes
         handler.QueryRouteBegin();
      
         // Prepare for looping over the routes in the query results.
         unsigned int nPointsProcessed = 0;
         unsigned int nRouteId = 0;
         unsigned int nTaxisProcessed = 0;
         bool bInRoute(false);
         while( q.next() )
         {
            QSqlRecord r = q.record();

            if( r.value(iStatusIdx).toUInt() == 1 )
            {
               if( r.value(iTaxiIdIdx).toUInt() != route->GetTaxiId() )
               {
                  // The logic here is run when it is determined that the previous
                  // route has completed and we are now seeing a new route because
                  // this is a new taxi.
                  nTaxisProcessed++;

                  if( bInRoute )
                  {
                     // The current route on the current route has ended as 
                     // denoted by a new taxi starting. 
                     handler.HandleRoute( route );
                  
                     // Prepare for the next route.
                     bInRoute = false;
                     nRouteId++;
                     route.reset( new Route() );
                     route->SetRouteId(nRouteId);
                  }

                  route->SetTaxiId( r.value(iTaxiIdIdx).toUInt() );
               }
      
			   //! @todo The check to make sure that points in the routes are realistic
			   //!       needs updated to do a distance check and use the delta time
			   //!       to determine the feasibility of the points.
			   if( bInRoute == false ||
				   (abs(r.value(iLonIdx).toDouble()-p.GetLon()) < 0.01 &&
				    abs(r.value(iLatIdx).toDouble()-p.GetLat()) < 0.01)    )
			   {
                  p.SetTime( static_cast<unsigned long long>(r.value(iTimestampIdx).toLongLong()) );
                  p.SetLon( r.value(iLonIdx).toDouble() );
                  p.SetLat( r.value(iLatIdx).toDouble() );
                  //p.SetAlt()
                  p.SetHdg( r.value(iHeadingIdx).toInt() );
                  p.SetSpd( r.value(iSpeedIdx).toInt() );
                  route->AddPoint(p);

                  nPointsProcessed++;
			      bInRoute = true;
			   }
            }
            else if( bInRoute )
            {
               // The current route on the current route has ended as denoted by
               // the loaded flag now being false.  Perform logic here to end 
               // the route.
               handler.HandleRoute( route );
            
               // Prepare for the next route.
               bInRoute = false;
               nRouteId++;
               route.reset( new Route() );
               route->SetRouteId(nRouteId);
            }
         }

         if( bInRoute )
         {
            handler.HandleRoute( route );
         }

         // Perform any overall completion of processing a successful query here.
         handler.QueryRouteComplete();
      }
   }

}; // namespace