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
#ifndef JSQUERYROUTEHANDLER_H
#define JSQUERYROUTEHANDLER_H

#include <QtCore/QList>

#include "DataAccess/QueryRouteHandler.h"
#include "Map/JsLayerDispatch.h"
#include "Map/JsLayer.h"
#include "Map/JsRoute.h"


namespace Map
{
   //! Represents a layer in the map and is exposed to the web page's java script.
   class JsQueryRouteHandler : public DataAccess::QueryRouteHandler
   {
   public:
      // ----------------------------------------------------------------------
      JsQueryRouteHandler();
      JsQueryRouteHandler( ObjectBaseDispatchPtr pDispatch );
      ~JsQueryRouteHandler();
   
      // ----------------------------------------------------------------------
      // QueryRouteHandler implementation.

      void HandleRoute( DataAccess::RoutePtr route );
      
      void QueryRouteBegin();

      void QueryRouteComplete();
      

      // ----------------------------------------------------------------------
      // Implementation
      
      
   protected:
      // ----------------------------------------------------------------------
      ObjectBaseDispatchPtr        m_pDispatch; //!< Dispatch to create layer
   };
}; //namespace

#endif // JSQUERYROUTEHANDLER_H
