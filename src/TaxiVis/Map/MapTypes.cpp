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

#include "Map/MapTypes.h"


namespace Map
{
   
   // An enumeration of all the available options of the class.
   namespace MapTypes
   {
      std::string strings[] = {
         "MapPage",
         "GraphPage",
         "JsSettingsMap",
         "JsLayer",
         "JsRoute",
         "JsPoint"
      };

      STRING_ENUM_FUNCS_SRC( STRING_ENUM__NO_LIB_EXPORT );
   };

}; //namespace