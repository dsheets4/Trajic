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
#include "Map/JsPointIconScriptProto.h"
#include "Map/JsPointIconScript.h"


namespace Map
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString JsPointIconScript::ScriptClassName = "JsPointIcon";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsPointIconScript::JsPointIconScript(QScriptEngine *pEngine)
      : Script::ObjectBaseScript(pEngine)
   {
      m_proto = pEngine->newQObject( new JsPointIconScriptProto(this),
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
   JsPointIconScript::~JsPointIconScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue JsPointIconScript::prototype() const
   {
      return m_proto;
   }
   
   // -------------------------------------------------------------------------
   QString JsPointIconScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue JsPointIconScript::constructor()
   {
      return m_ctor;
   }

   // -------------------------------------------------------------------------
   QScriptValue JsPointIconScript::newInstance()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the object.
      ObjectBaseWrapperPtr pMap = MAP_FACTORY->Allocate( ScriptClassName );
      ObjectBaseDispatchPtr pDispatch(new JsPointIconDispatch(0));
      pDispatch->setObjWrap(pMap);
      return ObjectBaseScript::newInstance(pDispatch);
   }
   
   // -------------------------------------------------------------------------
   void JsPointIconScript::ConnectSignals(ObjectBaseWrapperPtr pObj, ObjectBaseDispatchPtr pDispatch)
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
         SIGNAL(setColorSignal(QString,qreal)),
         SLOT(setColor(QString,qreal)) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setWeightSignal(int)),
         SLOT(setWeight(int)) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(addPointSignal(unsigned long long,qreal,qreal,qreal,qreal)),
         SLOT(addPoint(unsigned long long,qreal,qreal,qreal,qreal)) );
   }
   
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue JsPointIconScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      JsPointIconScript *pClass = 
         qscriptvalue_cast<JsPointIconScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();

      return pClass->newInstance();
   }
   
}; //namespace