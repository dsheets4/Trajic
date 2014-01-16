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
#ifndef GraphMappingLinear_H
#define GraphMappingLinear_H

#include "GraphMapping.h"


namespace Vis
{
   //! Defines the mapping of the plot area in a graph element so that 
   //! separate components can be coordinate on the same scale with less
   //! coupling.
   class GraphMappingLinear : public GraphMapping
   {
   public:
      // ----------------------------------------------------------------------

      //! Constructs an object with the given rectArea as the paintable area.
      //!
      //! @param rectArea  Total area applicable to the Graph.
      GraphMappingLinear();
      GraphMappingLinear( const GraphMapping& orig );
      ~GraphMappingLinear();
      
      
      // ----------------------------------------------------------------------
      
      //! @copydoc GraphMapping::mapY     
      virtual qreal mapX( qreal fX ) const;
      
      //! @copydoc GraphMapping::mapY
      virtual qreal mapY( qreal fY ) const;
      
   };

}; //namespace

#endif // GraphMappingLinear_H
