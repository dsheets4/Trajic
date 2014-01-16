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

#include "Vis/GraphPieObjWrap.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPieObjWrap::GraphPieObjWrap(QObject *pParent)
      : GraphBaseObjWrap( new GraphPie(), pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphPieObjWrap::GraphPieObjWrap(GraphPie* pGfxPie, QObject *pParent)
      : GraphBaseObjWrap( pGfxPie, pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphPieObjWrap::GraphPieObjWrap(const GraphPieObjWrap& orig)
      : GraphBaseObjWrap(orig)
   {
   }

   // -------------------------------------------------------------------------
   GraphPieObjWrap::~GraphPieObjWrap()
   {
   }

      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphPie* GraphPieObjWrap::getGraphPie() const
   {
      return dynamic_cast<GraphPie*>(m_pGfx);
   }

   void GraphPieObjWrap::setGraphPie( GraphPie* pGfxPie )
   {
      m_pGfx = pGfxPie;
   }
   
   // ----------------------------------------------------------------------
   void GraphPieObjWrap::createSlice(
      double fValue,
      QString sColor,
      double fTransparency )
   {
      GraphPie* pGfxPie = getGraphPie();
      if( pGfxPie )
      {
         QColor color(sColor);
         color.setAlpha(fTransparency*255);
         pGfxPie->createSlice( fValue, color );
      }
   }
   
   // =========================================================================
   // Operators
   // =========================================================================
   GraphPieObjWrap& GraphPieObjWrap::operator=( const GraphPieObjWrap &rhs )
   {
      if( this != &rhs )
      {
         GraphBaseObjWrap::operator=( rhs );
      }

      return *this;
   }
   
}; //namespace