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
#include "Vis/GraphRingItemScriptProto.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingItemScriptProto::GraphRingItemScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   GraphRingItemScriptProto::~GraphRingItemScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void GraphRingItemScriptProto::addGraph( Vis::GraphBaseObjWrapPtr pGfx )
   {
      GraphRingItemDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->addGraph( pGfx );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphRingItemScriptProto::removeGraph( Vis::GraphBaseObjWrapPtr pGfx )
   {
      GraphRingItemDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->removeGraph( pGfx );
      }
   }

   // -------------------------------------------------------------------------
   void GraphRingItemScriptProto::setRotation( qreal fRotation )
   {
      GraphRingItemDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setRotation( fRotation );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphRingItemScriptProto::setSpan( qreal fSPan )
   {
      GraphRingItemDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setSpan( fSPan );
      }
   }
      
   // -------------------------------------------------------------------------
   void GraphRingItemScriptProto::setDistPercent( qreal fDistPercent )
   {
      GraphRingItemDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setDistPercent( fDistPercent );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphRingItemScriptProto::setAlignment( int nAlignment )
   {
      GraphRingItemDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setAlignment( static_cast<Vis::GraphRingItem::Alignment>(nAlignment) );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphRingItemScriptProto::setStabilized( bool bStabilized )
   {
      GraphRingItemDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setStabilized( bStabilized );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   GraphRingItemDispatch* GraphRingItemScriptProto::thisDispatch() const
   {
      GraphBaseDispatchPtr *ptr   = qscriptvalue_cast<GraphBaseDispatchPtr*>(thisObject().data());

      if( ptr )
      {
         return dynamic_cast<GraphRingItemDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace