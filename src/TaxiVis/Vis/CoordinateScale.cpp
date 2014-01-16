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

#include "Vis/CoordinateScale.h"


namespace Vis
{
   namespace CoordinateScale
   {
      // ----------------------------------------------------------------------
      // The order of the strings must match the enumeration.
      std::string strings[] = {
         "Linear",
         "Log10X",
         "Log10Y",
         "Log10Log10"
      };
      
      // ----------------------------------------------------------------------
      STRING_ENUM_FUNCS_SRC( STRING_ENUM__NO_LIB_EXPORT );
   };

}; //namespace