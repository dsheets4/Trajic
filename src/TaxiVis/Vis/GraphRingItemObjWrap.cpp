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

#include "Vis/GraphRingItemObjWrap.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingItemObjWrap::GraphRingItemObjWrap(QObject *pParent)
      : GraphBaseObjWrap( new GraphRingItem(), pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphRingItemObjWrap::GraphRingItemObjWrap(GraphRingItem* pGfxRingItem, QObject *pParent)
      : GraphBaseObjWrap( pGfxRingItem, pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphRingItemObjWrap::GraphRingItemObjWrap(const GraphRingItemObjWrap& orig)
      : GraphBaseObjWrap(orig)
   {
   }

   // -------------------------------------------------------------------------
   GraphRingItemObjWrap::~GraphRingItemObjWrap()
   {
   }

      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphRingItem* GraphRingItemObjWrap::getGraphRingItem() const
   {
      return dynamic_cast<GraphRingItem*>(m_pGfx);
   }

   void GraphRingItemObjWrap::setGraphRingItem( GraphRingItem* pGfxRingItem )
   {
      m_pGfx = pGfxRingItem;
   }
   
   // =========================================================================
   // Slots
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphRingItemObjWrap::addGraph( Vis::GraphBaseObjWrapPtr pGfx )
   {
      GraphRingItem* pGfxRingItem = getGraphRingItem();
      if( pGfxRingItem && pGfx.get() )
      {
         pGfxRingItem->addGraph( pGfx.get()->getGraph() );
      }
   }

   // -------------------------------------------------------------------------
   void GraphRingItemObjWrap::removeGraph( Vis::GraphBaseObjWrapPtr pGfx )
   {
      GraphRingItem* pGfxRingItem = getGraphRingItem();
      if( pGfxRingItem && pGfx.get() )
      {
         pGfxRingItem->removeGraph( pGfx.get()->getGraph() );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphRingItemObjWrap::setRotation( qreal fRotation )
   {
      GraphRingItem* pGfxRingItem = getGraphRingItem();
      if( pGfxRingItem )
      {
         pGfxRingItem->setRotation( fRotation );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphRingItemObjWrap::setSpan( qreal fSpan )
   {
      GraphRingItem* pGfxRingItem = getGraphRingItem();
      if( pGfxRingItem )
      {
         pGfxRingItem->setSpan( fSpan );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphRingItemObjWrap::setDistPercent( qreal fDistPercent )
   {
      GraphRingItem* pGfxRingItem = getGraphRingItem();
      if( pGfxRingItem )
      {
         pGfxRingItem->setDistPercent( fDistPercent );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphRingItemObjWrap::setAlignment( Vis::GraphRingItem::Alignment eAlignment )
   {
      GraphRingItem* pGfxRingItem = getGraphRingItem();
      if( pGfxRingItem )
      {
         pGfxRingItem->setAlignment( eAlignment );
      }
   }
   
   void GraphRingItemObjWrap::setStabilized( bool bStabilized )
   {
      GraphRingItem* pGfxRingItem = getGraphRingItem();
      if( pGfxRingItem )
      {
         pGfxRingItem->setStabilized( bStabilized );
      }
   }
   
   // =========================================================================
   // Operators
   // =========================================================================
   GraphRingItemObjWrap& GraphRingItemObjWrap::operator=( const GraphRingItemObjWrap &rhs )
   {
      if( this != &rhs )
      {
         GraphBaseObjWrap::operator=( rhs );
      }

      return *this;
   }
   
}; //namespace