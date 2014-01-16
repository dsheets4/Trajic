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

#include "Map/MapFactory.h"
#include "Map/JsLayer.h"
#include "Map/JsQueryRouteHandler.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsQueryRouteHandler::JsQueryRouteHandler( )
      : m_pDispatch(0)
   {
   }
   
   // -------------------------------------------------------------------------
   JsQueryRouteHandler::JsQueryRouteHandler( ObjectBaseDispatchPtr pDispatch )
      : m_pDispatch(pDispatch)
   {
   }

   // -------------------------------------------------------------------------
   JsQueryRouteHandler::~JsQueryRouteHandler()
   {

   }

   // =========================================================================
   // Overridden methods from QueryRouteHandler
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void JsQueryRouteHandler::QueryRouteBegin()
   {
   }

   // -------------------------------------------------------------------------
   void JsQueryRouteHandler::HandleRoute( DataAccess::RoutePtr route )
   {
      if( m_pDispatch )
      {
         JsLayerDispatch* pDispatch = dynamic_cast<JsLayerDispatch*>(m_pDispatch.get());
         if( pDispatch )
         {
            ObjectBaseWrapperPtr ptr = MAP_FACTORY->Allocate("JsRoute");
            JsRoute* pRoute = dynamic_cast<JsRoute*>(ptr.get()->getObject());
            Q_ASSERT(pRoute);
            pRoute->setRoute( route );
            pDispatch->addRoute( ptr );
         }
      }
   }
   
   // -------------------------------------------------------------------------
   void JsQueryRouteHandler::QueryRouteComplete()
   {
   }


   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------


}; //namespace