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
#ifndef DATAROUTE_H
#define DATAROUTE_H

#include <vector>

#include <QtCore/QString>
#include <QtCore/QList>

#include "TaxiVisUtils.h"
#include "DataAccess/DataPoint.h"


namespace DataAccess
{
   // -------------------------------------------------------------------------
   //

   // Forward declaration of the class to allow defining the smart pointer type.
   class Route;

   //! Smart pointer definition used for passing around Route pointers.
   typedef SHARED_POINTER<Route> RoutePtr;

   //! Vector of route pointers.
   typedef std::vector<RoutePtr> RoutePtrVector;

   // -------------------------------------------------------------------------
   //!
   class Route
   {
   public:
      // ----------------------------------------------------------------------
      static const unsigned int InvalidTaxiId;
   
      // ----------------------------------------------------------------------
      Route();
      ~Route();

   
      // ----------------------------------------------------------------------
      const QString GetTaxiPlate() const;
      void SetTaxiPlate(const QString sTaxiPlate);

      unsigned int GetTaxiId() const;
      void SetTaxiId(const unsigned int nTaxiId);

      unsigned int GetRouteId() const;
      void SetRouteId(const unsigned int nRouteId);
   
      // ----------------------------------------------------------------------
      const PointVector& GetRoute() const;

      void AddPoint(const Point& p);

      void ClearRoute();

   protected:
      // ----------------------------------------------------------------------
      QString        m_sTaxiPlate; //!< Taxi license plate
      unsigned int   m_nTaxiId;    //!< Id of the taxi
      unsigned int   m_nRouteId;   //!< Id of the route
      PointVector    m_vRoute;     //!< Point comprising the route
   };
}; //namespace

#endif // DATAROUTE_H
