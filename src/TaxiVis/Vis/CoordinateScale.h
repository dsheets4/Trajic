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
#ifndef CoordinateScale_H
#define CoordinateScale_H

#include "StringEnumeration.h"


namespace Vis
{   
   //! Defines available coordinate types for the charting area and methods to
   //! convert between the enumeration and string values (useful for scripting)
   namespace CoordinateScale
   {
      // ----------------------------------------------------------------------
      //! Available coordinate types.
      enum Enum
      {
         Linear,      //!< Linear scale that linearly distributes points
         Log10X,      //!< Log base 10 scale on the X axis
         Log10Y,      //!< Log base 10 scale on the Y axis
         Log10Log10,  //!< Log base 10 scale on both the X and Y axis

         END_ENUM
      };
      
      // ----------------------------------------------------------------------
      STRING_ENUM_FUNCS_HDR( STRING_ENUM__NO_LIB_EXPORT );
   };

}; //namespace

#endif // CoordinateScale_H
