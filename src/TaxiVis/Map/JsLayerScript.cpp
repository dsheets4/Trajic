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

#include "Map/MapFactory.h"
#include "Map/JsLayerScriptProto.h"
#include "Map/JsLayerScript.h"


namespace Map
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString JsLayerScript::ScriptClassName = "JsLayer";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsLayerScript::JsLayerScript(QScriptEngine *pEngine)
      : Script::ObjectBaseScript(pEngine)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup the script object.
      m_proto = pEngine->newQObject( new JsLayerScriptProto(this),
         QScriptEngine::QtOwnership,
         QScriptEngine::SkipMethodsInEnumeration
         | QScriptEngine::ExcludeSuperClassMethods
         | QScriptEngine::ExcludeSuperClassProperties);
      QScriptValue global = pEngine->globalObject();
      m_proto.setPrototype(global.property("MapObject").property("prototype"));

      m_ctor = pEngine->newFunction(construct, m_proto);
      m_ctor.setData(qScriptValueFromValue(pEngine, this));
   }

   // -------------------------------------------------------------------------
   JsLayerScript::~JsLayerScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue JsLayerScript::prototype() const
   {
      return m_proto;
   }
   
   // -------------------------------------------------------------------------
   QString JsLayerScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue JsLayerScript::constructor()
   {
      return m_ctor;
   }

   // -------------------------------------------------------------------------
   QScriptValue JsLayerScript::newInstance()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the object.
      ObjectBaseWrapperPtr pMap = MAP_FACTORY->Allocate( ScriptClassName );
      ObjectBaseDispatchPtr pDispatch(new JsLayerDispatch(0));
      pDispatch->setObjWrap(pMap);
      return Script::ObjectBaseScript::newInstance(pDispatch);
   }

   // -------------------------------------------------------------------------
   void JsLayerScript::ConnectSignals(ObjectBaseWrapperPtr pObj, ObjectBaseDispatchPtr pDispatch)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      Q_ASSERT( pDispatch );
      Q_ASSERT( pObj );
      Q_ASSERT( pObj.get()->getObject() );

      if( !pObj || !pObj.get()->getObject() || !pDispatch )
      {
         return;
      }

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Connect the dispatch and the wrapper.
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(getNameSignal()),
         SLOT(getName()) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setNameSignal(QString)),
         SLOT(setName(QString)) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(addRouteSignal(ObjectBaseWrapperPtr)),
         SLOT(addRoute(ObjectBaseWrapperPtr)) );
   }
   
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue JsLayerScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      JsLayerScript *pClass = 
         qscriptvalue_cast<JsLayerScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();

      return pClass->newInstance();
   }
   
}; //namespace