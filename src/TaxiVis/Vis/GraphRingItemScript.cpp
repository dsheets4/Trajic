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
#include "Vis/GraphRingItemScriptProto.h"
#include "Vis/GraphRingItemDispatch.h"
#include "Vis/GraphRingItemScript.h"


namespace Vis
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString GraphRingItemScript::ScriptClassName = "GraphRingItem";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingItemScript::GraphRingItemScript(QScriptEngine *pEngine)
      : GraphBaseScript(pEngine)
   {
      // Allow queued connections containing the Alignment enumeration.
      qRegisterMetaType<Vis::GraphRingItem::Alignment>("Vis::GraphRingItem::Alignment");
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup the prototype and constructor.
      m_proto = pEngine->newQObject(new GraphRingItemScriptProto(this),
         QScriptEngine::QtOwnership,
         QScriptEngine::SkipMethodsInEnumeration
         | QScriptEngine::ExcludeSuperClassMethods
         | QScriptEngine::ExcludeSuperClassProperties);
      QScriptValue global = pEngine->globalObject();
      m_proto.setPrototype(global.property("Graph").property("prototype"));
      
      m_ctor = pEngine->newFunction(construct, m_proto);
      m_ctor.setData(qScriptValueFromValue(pEngine, this));
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      m_ctor.setProperty( "AlignOutside", Vis::GraphRingItem::AlignOutside );
      m_ctor.setProperty( "AlignInside",  Vis::GraphRingItem::AlignInside );
      m_ctor.setProperty( "AlignCenter",  Vis::GraphRingItem::AlignCenter );
      
   }

   // -------------------------------------------------------------------------
   GraphRingItemScript::~GraphRingItemScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue GraphRingItemScript::prototype() const
   {
      return m_proto;
   }
   
   // -------------------------------------------------------------------------
   QString GraphRingItemScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphRingItemScript::constructor()
   {
      return m_ctor;
   }
   
   // -------------------------------------------------------------------------
   GraphBaseDispatchPtr GraphRingItemScript::Allocate()
   {
      GraphBaseObjWrapPtr pGfx = GRAPH_FACTORY->AllocateGraph( ScriptClassName );
      GraphBaseDispatchPtr pDispatch(new GraphRingItemDispatch(0));
      pDispatch->setGraphObjWrap(pGfx);
      return pDispatch;
   }

   // -------------------------------------------------------------------------
   QScriptValue GraphRingItemScript::newInstance()
   {
      return GraphBaseScript::newInstance( Allocate() );
   }
   
   // -------------------------------------------------------------------------
   QScriptValue GraphRingItemScript::newInstance( const Vis::GraphBaseObjWrapPtr& pGfx )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the ring item entourage
      GraphBaseDispatchPtr ptr = Allocate();
      GraphRingItemDispatch* pDispatchRingItem = 
         dynamic_cast<GraphRingItemDispatch*>(ptr.get());

      Q_ASSERT(pDispatchRingItem);
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Call the ScriptGraph::newInstance so signals will be connected
      QScriptValue instance = GraphBaseScript::newInstance( ptr );
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Call the addGraph signal to set the Graph
      pDispatchRingItem->addGraph( pGfx );
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      return instance;
   }

   // -------------------------------------------------------------------------
   void GraphRingItemScript::ConnectSignals(GraphBaseObjWrapPtr pGfx, GraphBaseDispatchPtr pDispatch)
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
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(addGraphSignal(Vis::GraphBaseObjWrapPtr)),
         SLOT(addGraph(Vis::GraphBaseObjWrapPtr)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(removeGraphSignal(Vis::GraphBaseObjWrapPtr)),
         SLOT(removeGraph(Vis::GraphBaseObjWrapPtr)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setRotationSignal(qreal)),
         SLOT(setRotation(qreal)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setSpanSignal(qreal)),
         SLOT(setSpan(qreal)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setDistPercentSignal(qreal)),
         SLOT(setDistPercent(qreal)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setAlignmentSignal(Vis::GraphRingItem::Alignment)),
         SLOT(setAlignment(Vis::GraphRingItem::Alignment)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setStabilizedSignal(bool)),
         SLOT(setStabilized(bool)) );
   }
   
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphRingItemScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphRingItemScript *pClass = 
         qscriptvalue_cast<GraphRingItemScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();


      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      if( pContext->argumentCount() == 1 )
      {
         QScriptValue arg = pContext->argument(0);
         if( arg.isObject() )
         {
            Vis::GraphBaseObjWrapPtr ptr = qscriptvalue_cast<Vis::GraphBaseObjWrapPtr>(arg);
            if( ptr )
            {
               return pClass->newInstance(ptr);
            }
         }
      }

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      return pClass->newInstance();
   }
   
}; //namespace