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
#ifndef GRAPHTYPES_H
#define GRAPHTYPES_H

#include "StringEnumeration.h"


namespace Vis
{
   
   //! Defines the types of graphs that are possible in the library.  
   //! The namespace to abstract an enumerated type with string conversions.
   namespace GraphTypes
   {
      // ----------------------------------------------------------------------
      //! Available graph types.
      enum Enum
      {
         Graph,         //!< Generic type, used for early implementation
         GraphPie,      //!< Pie graph type
         GraphBar,      //!< Bar graph type
         GraphBarItem,  //!< Bar graph item type
         GraphRingMap,  //!< Ring map graph type
         GraphRingItem, //!< Ring map item type
         GraphText,     //!< Text
         GraphPc,       //!< Parallel Coordinates

         END_ENUM
      };
      
      // ----------------------------------------------------------------------
      STRING_ENUM_FUNCS_HDR( STRING_ENUM__NO_LIB_EXPORT );
   };

}; //namespace

#endif // GRAPHTYPES_H
