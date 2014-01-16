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

#include <QtCore/QEventLoop>

#include <QtScript/QScriptEngine>

#include "Vis/GraphRingMapDispatch.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingMapDispatch::GraphRingMapDispatch(QObject *pParent)
      : GraphBaseDispatch(pParent)
   {
   }

   // -------------------------------------------------------------------------
   GraphRingMapDispatch::~GraphRingMapDispatch()
   {
   }


   // =========================================================================
   // Slots
   // =========================================================================

   //// -------------------------------------------------------------------------
   //Vis::GraphBaseObjWrapPtr GraphRingMapDispatch::addRingItem( 
   //   Vis::GraphBaseObjWrapPtr pGfx,
   //   qreal                    fRotation,
   //   qreal                    fSpan,
   //   qreal                    fDistPercent,
   //   bool                     bDrawInverted )
   //{      
   //   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   //   // Need to synchronize the call and wait for the return value.
   //   QEventLoop waitLoop;
   //   waitLoop.connect( m_pGfx.get(), SIGNAL(addedRingItemSignal(Vis::GraphBaseObjWrapPtr)), SLOT(quit()) );
   //   emit addRingItemSignal( pGfx, fRotation, fSpan, fDistPercent, bDrawInverted );
   //   waitLoop.exec();
   //   
   //   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   //   return m_pAddedRingItem;
   //}
   
   // -------------------------------------------------------------------------
   void GraphRingMapDispatch::addedRingItem( Vis::GraphBaseObjWrapPtr pRingItem )
   {
      m_pAddedRingItem = pRingItem;
   }
   
   // -------------------------------------------------------------------------
   void GraphRingMapDispatch::addRingItem( Vis::GraphBaseObjWrapPtr pGfx )
   {
      emit addRingItemSignal( pGfx );
   }
   
   // -------------------------------------------------------------------------
   void GraphRingMapDispatch::removeRingItem( Vis::GraphBaseObjWrapPtr pGfx )
   {
      emit removeRingItemSignal( pGfx );
   }
   
   // -------------------------------------------------------------------------
   void GraphRingMapDispatch::setDrawQuadrants( bool bDrawQuadrants )
   {
      emit setDrawQuadrantsSignal( bDrawQuadrants );
   }
   
   // -------------------------------------------------------------------------
   void GraphRingMapDispatch::setDrawRingMarkers( bool bDrawRingMarkers )
   {
      emit setDrawRingMarkersSignal( bDrawRingMarkers );
   }
   
}; //namespace