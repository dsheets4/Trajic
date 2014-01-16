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
#include "Map/JsPointScriptProto.h"
#include "Map/JsPointScript.h"


namespace Map
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString JsPointScript::ScriptClassName = "JsPoint";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsPointScript::JsPointScript(QScriptEngine *pEngine)
      : Script::ObjectBaseScript(pEngine)
   {
      m_proto = pEngine->newQObject( new JsPointScriptProto(this),
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
   JsPointScript::~JsPointScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue JsPointScript::prototype() const
   {
      return m_proto;
   }
   
   // -------------------------------------------------------------------------
   QString JsPointScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue JsPointScript::constructor()
   {
      return m_ctor;
   }

   // -------------------------------------------------------------------------
   QScriptValue JsPointScript::newInstance()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the object.
      ObjectBaseWrapperPtr pMap = MAP_FACTORY->Allocate( ScriptClassName );
      ObjectBaseDispatchPtr pDispatch(new JsPointDispatch(0));
      pDispatch->setObjWrap(pMap);
      return ObjectBaseScript::newInstance(pDispatch);
   }

   // -------------------------------------------------------------------------
   void JsPointScript::ConnectSignals(ObjectBaseWrapperPtr pObj, ObjectBaseDispatchPtr pDispatch)
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
         SIGNAL(getTimeSignal()),
         SLOT(getTime()) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setTimeSignal(const unsigned long long)),
         SLOT(setTime(const unsigned long long)) );
      
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(getLonSignal()),
         SLOT(getLon()) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setLonSignal(const double)),
         SLOT(setLon(const double)) );
      
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(getLatSignal()),
         SLOT(getLat()) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setLatSignal(const double)),
         SLOT(setLat(const double)) );
      
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(getAltSignal()),
         SLOT(getAlt()) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setAltSignal(const int)),
         SLOT(setAlt(const int)) );
      
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(getHdgSignal()),
         SLOT(getHdg()) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setHdgSignal(const int)),
         SLOT(setHdg(const int)) );
      
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(getSpdSignal()),
         SLOT(getSpd()) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setSpdSignal(const int)),
         SLOT(setSpd(const int)) );
   }
   
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue JsPointScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      JsPointScript *pClass = 
         qscriptvalue_cast<JsPointScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();

      return pClass->newInstance();
   }
   
}; //namespace