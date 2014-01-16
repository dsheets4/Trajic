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
#include "Map/GraphPageScriptProto.h"
#include "Map/GraphPageScript.h"


namespace Map
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString GraphPageScript::ScriptClassName = "GraphPage";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPageScript::GraphPageScript(QScriptEngine *pEngine)
      : QObject(pEngine), QScriptClass(pEngine)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup the script object.
      m_proto = pEngine->newQObject( new GraphPageScriptProto(this),
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
   GraphPageScript::~GraphPageScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue GraphPageScript::prototype() const
   {
      return m_proto;
   }
   
   // -------------------------------------------------------------------------
   QString GraphPageScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphPageScript::constructor()
   {
      return m_ctor;
   }

   // -------------------------------------------------------------------------
   QScriptValue GraphPageScript::newInstance()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the object.
      ObjectBaseWrapperPtr pMap = MAP_FACTORY->Allocate( ScriptClassName );
      ObjectBaseDispatchPtr pDispatch(new GraphPageDispatch(0));
      pDispatch->setObjWrap(pMap);
      return newInstance(pDispatch);
   }
   
   // -------------------------------------------------------------------------
   QScriptValue GraphPageScript::newInstance(const ObjectBaseDispatchPtr &pDispatch)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      ConnectSignals( pDispatch->getObjWrap(), pDispatch );
      QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
      return engine()->newObject(this, data);
   }
   
   // -------------------------------------------------------------------------
   QScriptValue GraphPageScript::newInstance(const ObjectBaseWrapperPtr &pObj)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      ObjectBaseDispatchPtr pDispatch(new GraphPageDispatch(0));
      pDispatch->setObjWrap(pObj);

      ConnectSignals( pDispatch->getObjWrap(), pDispatch );
      QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
      return engine()->newObject(this, data);
   }

   // -------------------------------------------------------------------------
   void GraphPageScript::ConnectSignals(ObjectBaseWrapperPtr pObj, ObjectBaseDispatchPtr pDispatch)
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
         SIGNAL(setCsvFileSignal(QString)),
         SLOT(setCsvFile(QString)) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setValueThreshSignal(qreal)),
         SLOT(setValueThresh(qreal)) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setTopicThreshSignal(int)),
         SLOT(setTopicThresh(int)) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setTopicColorsSignal(QStringList)),
         SLOT(setTopicColors(QStringList)) );
   }
   
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphPageScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      GraphPageScript *pClass = 
         qscriptvalue_cast<GraphPageScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();

      return pClass->newInstance();
   }
   
}; //namespace