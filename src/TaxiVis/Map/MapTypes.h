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
#ifndef MapTypes_H
#define MapTypes_H

#include "StringEnumeration.h"


namespace Map
{
   
   //! In a header file define the following.
   namespace MapTypes
   {
      //! Describe the general purpose of the enumeration
      enum Enum
      {
         MapPage,         //!< Page containing OpenLayers with map
         GraphPage,       //!< Page containing graphical items //!@todo GraphPage doesn't belong here
         JsSettingsMap,   //!< JavaScript map settings object
         JsLayer,         //!< JavaScript layer
         JsRoute,         //!< JavaScript route
         JsPoint,         //!< JavaScript point

         END_ENUM
      };

      STRING_ENUM_FUNCS_HDR( STRING_ENUM__NO_LIB_EXPORT );
   };

}; //namespace

#endif // MapTypes_H
