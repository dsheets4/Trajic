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

#include "Vis/GraphRingMapDispatch.h"
#include "Vis/GraphRingItemDispatch.h"
#include "Vis/GraphRingMapScriptProto.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingMapScriptProto::GraphRingMapScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   GraphRingMapScriptProto::~GraphRingMapScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================

   //// -------------------------------------------------------------------------
   //Vis::GraphBaseDispatchPtr GraphRingMapScriptProto::addRingItem( 
   //   Vis::GraphBaseDispatchPtr pGfx,
   //   qreal                fRotation,
   //   qreal                fSpan,
   //   qreal                fDistPercent,
   //   bool                 bDrawInverted )
   //{
   //   GraphRingMapDispatch* pDispatch = thisDispatch();

   //   if( pDispatch )
   //   {
   //      Vis::GraphBaseDispatchPtr pRingItem = pDispatch->addRingItem( 
   //         pGfx, fRotation, fSpan, fDistPercent, bDrawInverted );
   //      
   //      //!@todo Creation of the GraphBaseDispatchPtr isn't connecting the
   //      //!      signals up to connect the ring item properly!!!
   //      GraphBaseDispatchPtr pDispatch(new GraphRingMapDispatchItem(0));
   //      pDispatch->setGraphObjWrap(pRingItem);
   //      return pDispatch;
   //   }

   //   return 0;
   //}
   
   // -------------------------------------------------------------------------
   void GraphRingMapScriptProto::addRingItem( Vis::GraphBaseObjWrapPtr pGfx )
   {
      GraphRingMapDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->addRingItem( pGfx );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphRingMapScriptProto::removeRingItem( Vis::GraphBaseObjWrapPtr pGfx )
   {
      GraphRingMapDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->removeRingItem( pGfx );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphRingMapScriptProto::setDrawQuadrants( bool bDrawQuadrants )
   {
      GraphRingMapDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setDrawQuadrants( bDrawQuadrants );
      }
   }
   
   // ----------------------------------------------------------------------
   void GraphRingMapScriptProto::setDrawRingMarkers( bool bDrawRingMarkers )
   {
      GraphRingMapDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setDrawRingMarkers( bDrawRingMarkers );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   GraphRingMapDispatch* GraphRingMapScriptProto::thisDispatch() const
   {
      GraphBaseDispatchPtr *ptr   = qscriptvalue_cast<GraphBaseDispatchPtr*>(thisObject().data());

      if( ptr )
      {
         return dynamic_cast<GraphRingMapDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace