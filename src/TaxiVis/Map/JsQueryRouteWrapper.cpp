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

#include "DataAccess/QueryRoute.h"
#include "Map/JsQueryRouteWrapper.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsQueryRouteWrapper::JsQueryRouteWrapper( 
      JsLayerDispatchPtr  pDispatch,
      QObject* pParent )
      : QObject(pParent)
      , m_handler(pDispatch)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      //! @todo Only create new layers when requested.  During the initial 
      //!       implementation I'm creating a layer by default so it needs
      //!       some default arguments.
      m_criteria.SetTimeStart( QDateTime::fromString("2010-04-01T07:00:00", Qt::ISODate) );
      m_criteria.SetTimeEnd  ( QDateTime::fromString("2010-04-01T07:05:00", Qt::ISODate) );
   }

   // -------------------------------------------------------------------------
   JsQueryRouteWrapper::~JsQueryRouteWrapper()
   {

   }


   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   const DataAccess::QueryRouteCriteria& JsQueryRouteWrapper::getCriteria() const
   {
      return m_criteria;
   }

   void JsQueryRouteWrapper::setCriteria( const DataAccess::QueryRouteCriteria& criteria )
   {
      m_criteria = criteria;
   }
   
   // -------------------------------------------------------------------------
   const ObjectBaseWrapperPtr JsQueryRouteWrapper::getLayer() const
   {
      return m_pLayer;
   }

   void JsQueryRouteWrapper::setLayer( ObjectBaseWrapperPtr pLayer )
   {
      m_pLayer = pLayer;
   }

   // =========================================================================
   // Slots
   // =========================================================================

   // -------------------------------------------------------------------------
   void JsQueryRouteWrapper::executeQuery()
   {
      DataAccess::QueryRoute query;
      query.QueryTaxiRoute( m_handler, m_criteria );
      
      emit queryComplete();
      emit routeDataResults();
   }

}; //namespace