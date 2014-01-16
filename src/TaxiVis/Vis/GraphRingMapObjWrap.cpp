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
#include "Vis/GraphRingMapObjWrap.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingMapObjWrap::GraphRingMapObjWrap(QObject *pParent)
      : GraphBaseObjWrap( new GraphRingMap(), pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphRingMapObjWrap::GraphRingMapObjWrap(GraphRingMap* pGfxRing, QObject *pParent)
      : GraphBaseObjWrap( pGfxRing, pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphRingMapObjWrap::GraphRingMapObjWrap(const GraphRingMapObjWrap& orig)
      : GraphBaseObjWrap(orig)
   {
   }

   // -------------------------------------------------------------------------
   GraphRingMapObjWrap::~GraphRingMapObjWrap()
   {
   }

      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphRingMap* GraphRingMapObjWrap::getGraphRing() const
   {
      return dynamic_cast<GraphRingMap*>(m_pGfx);
   }

   void GraphRingMapObjWrap::setGraphRing( GraphRingMap* pGfxRing )
   {
      m_pGfx = pGfxRing;
   }
   
   //// ----------------------------------------------------------------------
   //void GraphRingMapObjWrap::addRingItem( 
   //   Vis::GraphBaseObjWrapPtr pGfx,
   //   qreal                    fRotation,
   //   qreal                    fSpan,
   //   qreal                    fDistPercent,
   //   bool                     bDrawInverted )
   //{
   //   Q_ASSERT( pGfx );

   //   GraphRing* pGfxRing = getGraphRing();
   //   if( pGfxRing )
   //   {
   //      //! @todo Should the Object Wrapper call the factory to maintain
   //      //!       consistency in the allocation? Right now it doesn't 
   //      //!       since the factory has thread-safe overhead.
   //      GraphRingItem* pRingItem = pGfxRing->addRingItem(
   //         pGfx.get()->getGraph(),
   //         fRotation, fSpan, fDistPercent, bDrawInverted
   //         );

   //      ObjWrapGraphPtr pRingItemWrapper( new GraphRingItemObjWrap(pRingItem) );

   //      emit addedRingItemSignal( pRingItemWrapper );
   //   }
   //}
   
   // ----------------------------------------------------------------------
   void GraphRingMapObjWrap::addRingItem( Vis::GraphBaseObjWrapPtr pGfx )
   {
      Q_ASSERT( pGfx );

      GraphRingMap* pGfxRing = getGraphRing();
      if( pGfxRing )
      {
         GraphRingItem* ringItem = dynamic_cast<GraphRingItem*>(pGfx.get()->getGraph());
         if( ringItem )
         {
            pGfxRing->addRingItem( ringItem );
         }
      }
   }

   // ----------------------------------------------------------------------
   void GraphRingMapObjWrap::removeRingItem( Vis::GraphBaseObjWrapPtr pGfx )
   {
      Q_ASSERT( pGfx );

      GraphRingMap* pGfxRing = getGraphRing();
      if( pGfxRing )
      {
         pGfxRing->removeRingItem( pGfx.get()->getGraph() );
      }
   }
   
   // ----------------------------------------------------------------------
   void GraphRingMapObjWrap::setDrawQuadrants( bool bDrawQuadrants )
   {
      GraphRingMap* pGfxRing = getGraphRing();
      if( pGfxRing )
      {
         pGfxRing->setDrawQuadrants( bDrawQuadrants );
      }
   }
   
   // ----------------------------------------------------------------------
   void GraphRingMapObjWrap::setDrawRingMarkers( bool bDrawRingMarkers )
   {
      GraphRingMap* pGfxRing = getGraphRing();
      if( pGfxRing )
      {
         pGfxRing->setDrawRingMarkers( bDrawRingMarkers );
      }
   }
   
   // =========================================================================
   // Operators
   // =========================================================================
   GraphRingMapObjWrap& GraphRingMapObjWrap::operator=( const GraphRingMapObjWrap &rhs )
   {
      if( this != &rhs )
      {
         GraphBaseObjWrap::operator=( rhs );
      }

      return *this;
   }
   
}; //namespace