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

#include "Vis/GraphTextObjWrap.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphTextObjWrap::GraphTextObjWrap(QObject *pParent)
      : GraphBaseObjWrap( new GraphText(), pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphTextObjWrap::GraphTextObjWrap(GraphText* pGfxText, QObject *pParent)
      : GraphBaseObjWrap( pGfxText, pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphTextObjWrap::GraphTextObjWrap(const GraphTextObjWrap& orig)
      : GraphBaseObjWrap(orig)
   {
   }

   // -------------------------------------------------------------------------
   GraphTextObjWrap::~GraphTextObjWrap()
   {
   }

      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphText* GraphTextObjWrap::getGraphText() const
   {
      return dynamic_cast<GraphText*>(m_pGfx);
   }

   void GraphTextObjWrap::setGraphText( GraphText* pGfxBar )
   {
      m_pGfx = pGfxBar;
   }
   
   // ----------------------------------------------------------------------
   void GraphTextObjWrap::setText( QString sText )
   {
      GraphText* pGfxText = getGraphText();
      if( pGfxText )
      {
         pGfxText->setText( sText ); 
      }
   }
   
   // ----------------------------------------------------------------------
   void GraphTextObjWrap::setColor( QString sColor, qreal fTransparency )
   {
      GraphText* pGfxText = getGraphText();
      if( pGfxText )
      {
         QColor color(sColor);
         color.setAlphaF(fTransparency);
         pGfxText->setColor( color ); 
      }
   }
   
   // ----------------------------------------------------------------------
   void GraphTextObjWrap::setWidth( qreal fWidth )
   {
      GraphText* pGfxText = getGraphText();
      if( pGfxText )
      {
         pGfxText->setWidth( fWidth ); 
      }
   }
   
   // =========================================================================
   // Operators
   // =========================================================================
   GraphTextObjWrap& GraphTextObjWrap::operator=( const GraphTextObjWrap &rhs )
   {
      if( this != &rhs )
      {
         GraphBaseObjWrap::operator=( rhs );
      }

      return *this;
   }
   
}; //namespace