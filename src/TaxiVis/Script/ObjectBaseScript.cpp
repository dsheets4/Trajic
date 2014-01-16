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
#include "Script/ObjectBaseScriptProto.h"
#include "Script/ObjectBaseScript.h"


namespace Script
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString ObjectBaseScript::ScriptClassName = "ObjectBase";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   ObjectBaseScript::ObjectBaseScript(QScriptEngine *pEngine)
      : QObject(pEngine), QScriptClass(pEngine)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup the script object.
      qScriptRegisterMetaType<ObjectBaseWrapperPtr>(pEngine, toScriptValue, fromScriptValue);
      qScriptRegisterMetaType<ObjectBaseDispatchPtr>(pEngine, toScriptValue, fromScriptValue);
   }

   // -------------------------------------------------------------------------
   ObjectBaseScript::~ObjectBaseScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue ObjectBaseScript::prototype() const
   {
      return m_proto;
   }
   
   // -------------------------------------------------------------------------
   QString ObjectBaseScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue ObjectBaseScript::constructor()
   {
      return m_ctor;
   }
   
   // -------------------------------------------------------------------------
   QScriptValue ObjectBaseScript::newInstance(const ObjectBaseDispatchPtr &pDispatch)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      ConnectSignals( pDispatch->getObjWrap(), pDispatch );
      QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
      return engine()->newObject(this, data);
   }
   
   // -------------------------------------------------------------------------
   QScriptValue ObjectBaseScript::newInstance(const ObjectBaseWrapperPtr &pObj)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      ObjectBaseDispatchPtr pDispatch(new ObjectBaseDispatch(0));
      pDispatch->setObjWrap(pObj);

      ConnectSignals( pDispatch->getObjWrap(), pDispatch );
      QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
      return engine()->newObject(this, data);
   }

   // -------------------------------------------------------------------------
   void ObjectBaseScript::ConnectSignals(ObjectBaseWrapperPtr pObj, ObjectBaseDispatchPtr pDispatch)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Connect the dispatch and the wrapper.
      //pObj->connect( 
      //   pDispatch.get(),
      //   SIGNAL(createBarSignal(double,QString,double)),
      //   SLOT(createBar(double,QString,double)) );
   }
   
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue ObjectBaseScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      ObjectBaseScript *pClass = 
         qscriptvalue_cast<ObjectBaseScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();

      return pClass->newInstance();
   }
   
   // -------------------------------------------------------------------------
   QScriptValue ObjectBaseScript::toScriptValue(
      QScriptEngine *eng,
      const ObjectBaseDispatchPtr &pDispatch)
   {
      QScriptValue ctor = eng->globalObject().property(ScriptClassName);
      ObjectBaseScript *pClass = qscriptvalue_cast<ObjectBaseScript*>(ctor.data());

      if (!pClass)
         return eng->newVariant(qVariantFromValue(pDispatch));

      return pClass->newInstance(pDispatch);
   }
   
   // -------------------------------------------------------------------------
   void ObjectBaseScript::fromScriptValue(
      const QScriptValue &proto,
      ObjectBaseDispatchPtr &pDispatch)
   {
      pDispatch = qvariant_cast<ObjectBaseDispatchPtr>(proto.data().toVariant());
   }
   
   // -------------------------------------------------------------------------
   QScriptValue ObjectBaseScript::toScriptValue(
      QScriptEngine *eng,
      const ObjectBaseWrapperPtr &pObj)
   {
      QScriptValue ctor = eng->globalObject().property(ScriptClassName);
      ObjectBaseScript *pClass = qscriptvalue_cast<ObjectBaseScript*>(ctor.data());

      if (!pClass)
         return eng->newVariant(qVariantFromValue(pObj));

      return pClass->newInstance(pObj);
   }
   
   // -------------------------------------------------------------------------
   void ObjectBaseScript::fromScriptValue(
      const QScriptValue &proto,
      ObjectBaseWrapperPtr &pObj)
   {
      ObjectBaseDispatchPtr pDispatch = qvariant_cast<ObjectBaseDispatchPtr>(proto.data().toVariant());
      if( pDispatch )
      {
         pObj = pDispatch->getObjWrap();
      }
   }
   
}; //namespace