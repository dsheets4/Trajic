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
#include <cmath>

#include "Vis/GraphMappingLog10Y.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphMappingLog10Y::GraphMappingLog10Y()
      : GraphMapping(CoordinateScale::Log10Y)
   {
   }
   
   // -------------------------------------------------------------------------
   GraphMappingLog10Y::GraphMappingLog10Y( const GraphMapping& orig )
      : GraphMapping(orig, CoordinateScale::Log10Y)
   {
   }

   // -------------------------------------------------------------------------
   GraphMappingLog10Y::~GraphMappingLog10Y()
   {
   }
   

   // =========================================================================
   // Implementation
   // =========================================================================
 
   // -------------------------------------------------------------------------
   qreal GraphMappingLog10Y::mapX( qreal fX ) const
   {
      return (fX-m_ptMin.x())/(m_ptMax.x()-m_ptMin.x())*m_rectDraw.width()+m_rectDraw.x();
   }

   // -------------------------------------------------------------------------
   qreal GraphMappingLog10Y::mapY( qreal fY ) const
   {
      return m_rectDraw.height()-log10(fY-m_ptMin.y()+1)/log10(m_ptMax.y()-m_ptMin.y()+1)*m_rectDraw.height()+m_rectDraw.y();
   }
      
}; //namespace
