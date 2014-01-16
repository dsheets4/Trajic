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

#include "Vis/GraphPcObjWrap.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPcObjWrap::GraphPcObjWrap(QObject *pParent)
      : GraphBaseObjWrap( new GraphPc(), pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphPcObjWrap::GraphPcObjWrap(GraphPc* pGfx, QObject *pParent)
      : GraphBaseObjWrap( pGfx, pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphPcObjWrap::GraphPcObjWrap(const GraphPcObjWrap& orig)
      : GraphBaseObjWrap(orig)
   {
   }

   // -------------------------------------------------------------------------
   GraphPcObjWrap::~GraphPcObjWrap()
   {
   }

      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphPc* GraphPcObjWrap::getGraphPc() const
   {
      return dynamic_cast<GraphPc*>(m_pGfx);
   }

   void GraphPcObjWrap::setGraphPc( GraphPc* pGfx )
   {
      m_pGfx = pGfx;
   }
   

   // =========================================================================
   // Operators
   // =========================================================================
   GraphPcObjWrap& GraphPcObjWrap::operator=( const GraphPcObjWrap &rhs )
   {
      if( this != &rhs )
      {
         GraphBaseObjWrap::operator=( rhs );
      }

      return *this;
   }
   

   // =========================================================================
   // Slots
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void GraphPcObjWrap::setYMax( double fYMax )
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         pGfx->setYMax( fYMax );
      }
   }
      
   // -------------------------------------------------------------------------
   void GraphPcObjWrap::setYMin( double fYMin )
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         pGfx->setYMin( fYMin );
      }
   }
   // -------------------------------------------------------------------------
   void GraphPcObjWrap::setBackgroundColor( QString sColor, qreal fTransparency )
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         QColor color(sColor);
         color.setAlpha(fTransparency*255);
         pGfx->setBackgroundColor( color ); 
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphPcObjWrap::setCoordinateScale( QString sType )
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         pGfx->setCoordinateScale( CoordinateScale::ToEnum(qPrintable(sType)) );
      }
   }

   // -------------------------------------------------------------------------   
   void GraphPcObjWrap::setGain( qreal fGain )
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         pGfx->setGain( fGain );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphPcObjWrap::setOffset( qreal fOffset )
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         pGfx->setOffset( fOffset );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphPcObjWrap::addCoordinate( QString sLabel )
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         pGfx->addCoordinate( sLabel );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphPcObjWrap::removeCoordinate( int nIndex )
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         pGfx->removeCoordinate( nIndex );
      }
   }

   // -------------------------------------------------------------------------
   void GraphPcObjWrap::removeAllCoordinates()
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         pGfx->removeAllCoordinates( );
      }
   }
   
   // -------------------------------------------------------------------------   
   void GraphPcObjWrap::addLine( QVariantList fListValues, QString sColor, qreal fTransparency )
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         QColor color(sColor);
         color.setAlpha(fTransparency*255);
         pGfx->addLine( fListValues, color );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphPcObjWrap::removeAllLines( )
   {
      GraphPc* pGfx = getGraphPc();
      if( pGfx )
      {
         pGfx->removeAllLines( );
      }
   }
   
}; //namespace