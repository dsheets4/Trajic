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
#include <QtScript/QScriptContext>

#include "Vis/GraphFactory.h"
#include "Vis/GraphBaseScriptProto.h"
#include "Vis/GraphBaseScript.h"


namespace Vis
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString GraphBaseScript::ScriptClassName = "Graph";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphBaseScript::GraphBaseScript(QScriptEngine *pEngine)
      : QObject(pEngine), QScriptClass(pEngine)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup the script object.
      qScriptRegisterMetaType<GraphBaseDispatchPtr>(pEngine, toScriptValue, fromScriptValue);
      qScriptRegisterMetaType<GraphBaseObjWrapPtr>(pEngine, toScriptValue, fromScriptValue);

      m_protoGraphBase = pEngine->newQObject( new GraphBaseScriptProto(this),
         QScriptEngine::QtOwnership,
         QScriptEngine::SkipMethodsInEnumeration
         | QScriptEngine::ExcludeSuperClassMethods
         | QScriptEngine::ExcludeSuperClassProperties);
      QScriptValue global = pEngine->globalObject();
      m_protoGraphBase.setPrototype(global.property("Object").property("prototype"));

      m_ctorGraphBase = pEngine->newFunction(construct, m_protoGraphBase);
      m_ctorGraphBase.setData(qScriptValueFromValue(pEngine, this));
   }

   // -------------------------------------------------------------------------
   GraphBaseScript::~GraphBaseScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue GraphBaseScript::prototype() const
   {
      return m_protoGraphBase;
   }
   
   // -------------------------------------------------------------------------
   QString GraphBaseScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphBaseScript::constructor()
   {
      return m_ctorGraphBase;
   }

   // -------------------------------------------------------------------------
   QScriptValue GraphBaseScript::newInstance( )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the object.
      GraphBaseObjWrapPtr pGfx = GRAPH_FACTORY->AllocateGraph( ScriptClassName );
      GraphBaseDispatchPtr pDispatch(new GraphBaseDispatch(0));
      pDispatch->setGraphObjWrap(pGfx);
      return newInstance(pDispatch);
   }
   
   // -------------------------------------------------------------------------
   QScriptValue GraphBaseScript::newInstance(const GraphBaseDispatchPtr &pDispatch)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      ConnectSignals( pDispatch->getGraphObjWrap(), pDispatch );
      QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
      return engine()->newObject(this, data);
   }
   
   // -------------------------------------------------------------------------
   QScriptValue GraphBaseScript::newInstance(const GraphBaseObjWrapPtr &pGfx)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphBaseDispatchPtr pDispatch(new GraphBaseDispatch(0));
      pDispatch->setGraphObjWrap(pGfx);

      ConnectSignals( pDispatch->getGraphObjWrap(), pDispatch );
      QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
      return engine()->newObject(this, data);
   }

   // -------------------------------------------------------------------------
   void GraphBaseScript::ConnectSignals(GraphBaseObjWrapPtr pGfx, GraphBaseDispatchPtr pDispatch)
   {
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
         SIGNAL(setPositionSignal(qreal,qreal)),
         SLOT(setPosition(qreal,qreal)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setSizeSignal(qreal,qreal)),
         SLOT(setSize(qreal,qreal)) );
   }
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphBaseScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      GraphBaseScript *pClass = 
         qscriptvalue_cast<GraphBaseScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();

      return pClass->newInstance( );
   }
   
   // -------------------------------------------------------------------------
   QScriptValue GraphBaseScript::toScriptValue(
      QScriptEngine *eng,
      const GraphBaseDispatchPtr &pGfx)
   {
      QScriptValue ctor = eng->globalObject().property(ScriptClassName);
      GraphBaseScript *pClass = qscriptvalue_cast<GraphBaseScript*>(ctor.data());

      if (!pClass)
         return eng->newVariant(qVariantFromValue(pGfx));

      return pClass->newInstance(pGfx);
   }
   
   // -------------------------------------------------------------------------
   void GraphBaseScript::fromScriptValue(
      const QScriptValue &proto,
      GraphBaseDispatchPtr &pGfx)
   {
      pGfx = qvariant_cast<GraphBaseDispatchPtr>(proto.data().toVariant());
   }
   
   // -------------------------------------------------------------------------
   QScriptValue GraphBaseScript::toScriptValue(
      QScriptEngine *eng,
      const GraphBaseObjWrapPtr &pGfx)
   {
      QScriptValue ctor = eng->globalObject().property(ScriptClassName);
      GraphBaseScript *pClass = qscriptvalue_cast<GraphBaseScript*>(ctor.data());

      if (!pClass)
         return eng->newVariant(qVariantFromValue(pGfx));

      return pClass->newInstance(pGfx);
   }
   
   // -------------------------------------------------------------------------
   void GraphBaseScript::fromScriptValue(
      const QScriptValue &proto,
      GraphBaseObjWrapPtr &pGfx)
   {
      GraphBaseDispatchPtr pDispatch = qvariant_cast<GraphBaseDispatchPtr>(proto.data().toVariant());
      if( pDispatch )
      {
         pGfx = pDispatch->getGraphObjWrap();
      }
   }
   
}; //namespace