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

#include "GuiFactory.h"
#include "MainSceneScriptProto.h"
#include "MainSceneScript.h"


// =========================================================================
// Global configuration and setup
// =========================================================================
const QString MainSceneScript::ScriptClassName = "MainScene";


// =========================================================================
// Construction and destruction
// =========================================================================

// -------------------------------------------------------------------------
MainSceneScript::MainSceneScript(QScriptEngine *pEngine)
   : QObject(pEngine), QScriptClass(pEngine)
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   // Setup the script object.
   m_proto = pEngine->newQObject( new MainSceneScriptProto(this),
      QScriptEngine::QtOwnership,
      QScriptEngine::SkipMethodsInEnumeration
      | QScriptEngine::ExcludeSuperClassMethods
      | QScriptEngine::ExcludeSuperClassProperties);
   QScriptValue global = pEngine->globalObject();
   m_proto.setPrototype(global.property("ObjectBase").property("prototype"));

   m_ctor = pEngine->newFunction(construct, m_proto);
   m_ctor.setData(qScriptValueFromValue(pEngine, this));
}

// -------------------------------------------------------------------------
MainSceneScript::~MainSceneScript()
{
}


// =========================================================================
// Overridden methods
// =========================================================================

// -------------------------------------------------------------------------
QScriptValue MainSceneScript::prototype() const
{
   return m_proto;
}
   
// -------------------------------------------------------------------------
QString MainSceneScript::name() const
{
   return ScriptClassName;
}
      
// =========================================================================
// Implementation
// =========================================================================
   
// -------------------------------------------------------------------------
QScriptValue MainSceneScript::constructor()
{
   return m_ctor;
}

// -------------------------------------------------------------------------
QScriptValue MainSceneScript::newInstance()
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   // Allocate the object.
   ObjectBaseWrapperPtr pMap = Gui::GUI_FACTORY->Allocate( ScriptClassName );
   ObjectBaseDispatchPtr pDispatch(new MainSceneDispatch());
   pDispatch->setObjWrap(pMap);
   return newInstance(pDispatch);
}
   
// -------------------------------------------------------------------------
QScriptValue MainSceneScript::newInstance(const ObjectBaseDispatchPtr &pDispatch)
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   ConnectSignals( pDispatch->getObjWrap(), pDispatch );
   QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
   return engine()->newObject(this, data);
}
   
// -------------------------------------------------------------------------
QScriptValue MainSceneScript::newInstance(const ObjectBaseWrapperPtr &pObj)
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   ObjectBaseDispatchPtr pDispatch(new MainSceneDispatch());
   pDispatch->setObjWrap(pObj);

   ConnectSignals( pDispatch->getObjWrap(), pDispatch );
   QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
   return engine()->newObject(this, data);
}

// -------------------------------------------------------------------------
void MainSceneScript::ConnectSignals(ObjectBaseWrapperPtr pObj, ObjectBaseDispatchPtr pDispatch)
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
   // ----------------------------------------------------------------------
   pObj.get()->getObject()->connect( 
      pDispatch.get(),
      SIGNAL(addGraphSignal(Vis::GraphBaseObjWrapPtr)),
      SLOT(addGraph(Vis::GraphBaseObjWrapPtr)) );
   pObj.get()->getObject()->connect( 
      pDispatch.get(),
      SIGNAL(removeGraphSignal(Vis::GraphBaseObjWrapPtr)),
      SLOT(removeGraph(Vis::GraphBaseObjWrapPtr)) );
   pObj.get()->getObject()->connect( 
      pDispatch.get(),
      SIGNAL(setMapPageSignal(ObjectBaseWrapperPtr)),
      SLOT(setMapPage(ObjectBaseWrapperPtr)) );
}
   
      
// =========================================================================
// Static methods to interact with the scripting language
// =========================================================================
   
// -------------------------------------------------------------------------
QScriptValue MainSceneScript::construct(
   QScriptContext *pContext,
   QScriptEngine *pEngine)
{
   MainSceneScript *pClass = 
      qscriptvalue_cast<MainSceneScript*>(pContext->callee().data());

   if (!pClass)
      return QScriptValue();

   return pClass->newInstance();
}
