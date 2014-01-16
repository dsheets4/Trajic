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

#include "Vis/GraphMappingLinear.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphMappingLinear::GraphMappingLinear()
      : GraphMapping(CoordinateScale::Linear)
   {
   }
   
   // -------------------------------------------------------------------------
   GraphMappingLinear::GraphMappingLinear( const GraphMapping& orig )
      : GraphMapping(orig, CoordinateScale::Linear)
   {
   }

   // -------------------------------------------------------------------------
   GraphMappingLinear::~GraphMappingLinear()
   {
   }
   

   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   qreal GraphMappingLinear::mapX( qreal fX ) const
   {
      return (fX-m_ptMin.x())/(m_ptMax.x()-m_ptMin.x())*m_rectDraw.width()+m_rectDraw.x();
   }
   
   // -------------------------------------------------------------------------
   qreal GraphMappingLinear::mapY( qreal fY ) const
   {
      return m_rectDraw.height()-(fY-m_ptMin.y())/(m_ptMax.y()-m_ptMin.y())*m_rectDraw.height()+m_rectDraw.y();
   }
      
}; //namespace