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
#ifndef QUERYROUTEHANDLER_H
#define QUERYROUTEHANDLER_H

#include "DataAccess/DataRoute.h"


namespace DataAccess
{
   // -------------------------------------------------------------------------
   //! Abstract class used to handle a data query.
   class QueryRouteHandler
   {
   public:   
      // ----------------------------------------------------------------------
      QueryRouteHandler();
      virtual ~QueryRouteHandler();
      
      // ----------------------------------------------------------------------
      //! Called when the query has constructed a new route from the 
      //! underlying data storage.
      //!
      //! @param route  Route compiled from the data storage.
      virtual void HandleRoute( RoutePtr route ) = 0;
      
      //! Called immediately before executing the query.
      virtual void QueryRouteBegin() = 0;

      //! Called when the query has completed
      virtual void QueryRouteComplete() = 0;

   };
}; //namespace

#endif // QUERYROUTEHANDLER_H
