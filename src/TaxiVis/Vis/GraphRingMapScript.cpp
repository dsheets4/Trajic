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
#include <QtScript/QScriptContext>

#include "Vis/GraphFactory.h"
#include "Vis/GraphRingMapScriptProto.h"
#include "Vis/GraphRingMapDispatch.h"
#include "Vis/GraphRingMapScript.h"


namespace Vis
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString GraphRingMapScript::ScriptClassName = "GraphRingMap";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingMapScript::GraphRingMapScript(QScriptEngine *pEngine)
      : GraphBaseScript(pEngine)
   {
      m_proto = pEngine->newQObject(new GraphRingMapScriptProto(this),
         QScriptEngine::QtOwnership,
         QScriptEngine::SkipMethodsInEnumeration
         | QScriptEngine::ExcludeSuperClassMethods
         | QScriptEngine::ExcludeSuperClassProperties);
      QScriptValue global = pEngine->globalObject();
      m_proto.setPrototype(global.property("Graph").property("prototype"));

      m_ctor = pEngine->newFunction(construct, m_proto);
      m_ctor.setData(qScriptValueFromValue(pEngine, this));
   }

   // -------------------------------------------------------------------------
   GraphRingMapScript::~GraphRingMapScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue GraphRingMapScript::prototype() const
   {
      return m_proto;
   }
   
   // -------------------------------------------------------------------------
   QString GraphRingMapScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphRingMapScript::constructor()
   {
      return m_ctor;
   }

   // -------------------------------------------------------------------------
   QScriptValue GraphRingMapScript::newInstance()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the object.
      GraphBaseObjWrapPtr pGfx = GRAPH_FACTORY->AllocateGraph( ScriptClassName );
      GraphBaseDispatchPtr pDispatch(new GraphRingMapDispatch(0));
      pDispatch->setGraphObjWrap(pGfx);
      return GraphBaseScript::newInstance(pDispatch);
   }

   // -------------------------------------------------------------------------
   void GraphRingMapScript::ConnectSignals(GraphBaseObjWrapPtr pGfx, GraphBaseDispatchPtr pDispatch)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphBaseScript::ConnectSignals( pGfx, pDispatch );
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      Q_ASSERT( pDispatch );
      Q_ASSERT( pGfx );

      if( !pGfx || !pDispatch )
      {
         return;
      }

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Connect the prototype and the wrapper.
      pDispatch->connect( 
         pGfx.get(),
         SIGNAL(addedRingItemSignal(Vis::GraphBaseObjWrapPtr)),
         SLOT(addedRingItem(Vis::GraphBaseObjWrapPtr)) );
      //pGfx->connect( 
      //   pDispatch.get(),
      //   SIGNAL(addRingItemSignal(Vis::GraphBaseObjWrapPtr,qreal,qreal,qreal,bool)),
      //   SLOT(addRingItem(Vis::GraphBaseObjWrapPtr,qreal,qreal,qreal,bool)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(addRingItemSignal(Vis::GraphBaseObjWrapPtr)),
         SLOT(addRingItem(Vis::GraphBaseObjWrapPtr)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(removeRingItemSignal(Vis::GraphBaseObjWrapPtr)),
         SLOT(removeRingItem(Vis::GraphBaseObjWrapPtr)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setDrawQuadrantsSignal(bool)),
         SLOT(setDrawQuadrants(bool)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setDrawRingMarkersSignal(bool)),
         SLOT(setDrawRingMarkers(bool)) );
   }
   
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphRingMapScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      GraphRingMapScript *pClass = 
         qscriptvalue_cast<GraphRingMapScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();

      return pClass->newInstance();
   }
   
}; //namespace