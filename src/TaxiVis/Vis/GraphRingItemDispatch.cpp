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

#include <QtScript/QScriptEngine>

#include "Vis/GraphRingItemDispatch.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingItemDispatch::GraphRingItemDispatch(QObject *pParent)
      : GraphBaseDispatch(pParent)
   {
   }

   // -------------------------------------------------------------------------
   GraphRingItemDispatch::~GraphRingItemDispatch()
   {
   }


   // =========================================================================
   // Slots
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void GraphRingItemDispatch::addGraph( Vis::GraphBaseObjWrapPtr pGfx )
   {
      emit addGraphSignal( pGfx );
   }
      
   // -------------------------------------------------------------------------
   void GraphRingItemDispatch::removeGraph( Vis::GraphBaseObjWrapPtr pGfx )
   {
      emit removeGraphSignal( pGfx );
   }

   // -------------------------------------------------------------------------
   void GraphRingItemDispatch::setRotation( qreal fRotation )
   {
      emit setRotationSignal( fRotation );
   }

   // -------------------------------------------------------------------------
   void GraphRingItemDispatch::setSpan( qreal fSpan )
   {
      emit setSpanSignal( fSpan );
   }

   // -------------------------------------------------------------------------
   void GraphRingItemDispatch::setDistPercent( qreal fDistPercent )
   {
      emit setDistPercentSignal( fDistPercent );
   }
   
   // -------------------------------------------------------------------------
   void GraphRingItemDispatch::setAlignment( Vis::GraphRingItem::Alignment eAlignment )
   {
      emit setAlignmentSignal( eAlignment );
   }
   
   // -------------------------------------------------------------------------
   void GraphRingItemDispatch::setStabilized( bool bStabilized )
   {
      emit setStabilizedSignal( bStabilized );
   }
   
}; //namespace