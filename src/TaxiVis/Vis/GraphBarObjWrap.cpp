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

#include "Vis/GraphBarObjWrap.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphBarObjWrap::GraphBarObjWrap(QObject *pParent)
      : GraphBaseObjWrap( new GraphBar(), pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphBarObjWrap::GraphBarObjWrap(GraphBar* pGfxBar, QObject *pParent)
      : GraphBaseObjWrap( pGfxBar, pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphBarObjWrap::GraphBarObjWrap(const GraphBarObjWrap& orig)
      : GraphBaseObjWrap(orig)
   {
   }

   // -------------------------------------------------------------------------
   GraphBarObjWrap::~GraphBarObjWrap()
   {
   }

      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphBar* GraphBarObjWrap::getGraphBar() const
   {
      return dynamic_cast<GraphBar*>(m_pGfx);
   }

   void GraphBarObjWrap::setGraphBar( GraphBar* pGfxBar )
   {
      m_pGfx = pGfxBar;
   }
   
   // ----------------------------------------------------------------------
   void GraphBarObjWrap::createBar(
      double fValue,
      QString sColor,
      double fTransparency )
   {
      GraphBar* pGfxBar = getGraphBar();
      if( pGfxBar )
      {
         QColor color(sColor);
         color.setAlpha(fTransparency*255);
         pGfxBar->createBar( fValue, color ); 
      }
   }
   
   // =========================================================================
   // Operators
   // =========================================================================
   GraphBarObjWrap& GraphBarObjWrap::operator=( const GraphBarObjWrap &rhs )
   {
      if( this != &rhs )
      {
         GraphBaseObjWrap::operator=( rhs );
      }

      return *this;
   }
   
}; //namespace