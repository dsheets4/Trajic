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
#include "Vis/GraphBarScriptProto.h"
#include "Vis/GraphBarScript.h"


namespace Vis
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString GraphBarScript::ScriptClassName = "GraphBar";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphBarScript::GraphBarScript(QScriptEngine *pEngine)
      : GraphBaseScript(pEngine)
   {
      m_proto = pEngine->newQObject( new GraphBarScriptProto(this),
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
   GraphBarScript::~GraphBarScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue GraphBarScript::prototype() const
   {
      return m_proto;
   }
   
   // -------------------------------------------------------------------------
   QString GraphBarScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphBarScript::constructor()
   {
      return m_ctor;
   }

   // -------------------------------------------------------------------------
   QScriptValue GraphBarScript::newInstance()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the object.
      GraphBaseObjWrapPtr pGfx = GRAPH_FACTORY->AllocateGraph( ScriptClassName );
      GraphBaseDispatchPtr pDispatch(new GraphBarDispatch(0));
      pDispatch->setGraphObjWrap(pGfx);
      return GraphBaseScript::newInstance(pDispatch);
   }

   // -------------------------------------------------------------------------
   void GraphBarScript::ConnectSignals(GraphBaseObjWrapPtr pGfx, GraphBaseDispatchPtr pDispatch)
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
         SIGNAL(createBarSignal(double,QString,double)),
         SLOT(createBar(double,QString,double)) );
   }
   
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphBarScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      GraphBarScript *pClass = 
         qscriptvalue_cast<GraphBarScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();

      return pClass->newInstance();
   }
   
}; //namespace