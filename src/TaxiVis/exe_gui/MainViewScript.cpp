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
#include "MainViewScriptProto.h"
#include "MainViewScript.h"


// =========================================================================
// Global configuration and setup
// =========================================================================
const QString MainViewScript::ScriptClassName = "MainView";


// =========================================================================
// Construction and destruction
// =========================================================================

// -------------------------------------------------------------------------
MainViewScript::MainViewScript(QScriptEngine *pEngine)
   : QObject(pEngine), QScriptClass(pEngine)
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   // Setup the script object.
   m_proto = pEngine->newQObject( new MainViewScriptProto(this),
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
MainViewScript::~MainViewScript()
{
}


// =========================================================================
// Overridden methods
// =========================================================================

// -------------------------------------------------------------------------
QScriptValue MainViewScript::prototype() const
{
   return m_proto;
}
   
// -------------------------------------------------------------------------
QString MainViewScript::name() const
{
   return ScriptClassName;
}
      
// =========================================================================
// Implementation
// =========================================================================
   
// -------------------------------------------------------------------------
QScriptValue MainViewScript::constructor()
{
   return m_ctor;
}

// -------------------------------------------------------------------------
QScriptValue MainViewScript::newInstance()
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   // Allocate the object.
   ObjectBaseWrapperPtr pMap = Gui::GUI_FACTORY->Allocate( ScriptClassName );
   ObjectBaseDispatchPtr pDispatch(new MainViewDispatch());
   pDispatch->setObjWrap(pMap);
   return newInstance(pDispatch);
}
   
// -------------------------------------------------------------------------
QScriptValue MainViewScript::newInstance(const ObjectBaseDispatchPtr &pDispatch)
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   ConnectSignals( pDispatch->getObjWrap(), pDispatch );
   QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
   return engine()->newObject(this, data);
}
   
// -------------------------------------------------------------------------
QScriptValue MainViewScript::newInstance(const ObjectBaseWrapperPtr &pObj)
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   ObjectBaseDispatchPtr pDispatch(new MainViewDispatch());
   pDispatch->setObjWrap(pObj);

   ConnectSignals( pDispatch->getObjWrap(), pDispatch );
   QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
   return engine()->newObject(this, data);
}

// -------------------------------------------------------------------------
void MainViewScript::ConnectSignals(ObjectBaseWrapperPtr pObj, ObjectBaseDispatchPtr pDispatch)
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
      SIGNAL(captureScreenShotSignal(QString)),
      SLOT(captureScreenShot(QString)) );
   pObj.get()->getObject()->connect( 
      pDispatch.get(),
      SIGNAL(captureScreenShotPdfSignal(QString)),
      SLOT(captureScreenShotPdf(QString)) );
   pObj.get()->getObject()->connect( 
      pDispatch.get(),
      SIGNAL(fullScreenSignal(Vis::GraphBaseObjWrapPtr)),
      SLOT(fullScreen(Vis::GraphBaseObjWrapPtr)) );
   pObj.get()->getObject()->connect( 
      pDispatch.get(),
      SIGNAL(restoreViewSignal()),
      SLOT(restoreView()) );
   pObj.get()->getObject()->connect( 
      pDispatch.get(),
      SIGNAL(setTitleSignal(QString)),
      SLOT(setWindowTitle(QString)) );
}
   
      
// =========================================================================
// Static methods to interact with the scripting language
// =========================================================================
   
// -------------------------------------------------------------------------
QScriptValue MainViewScript::construct(
   QScriptContext *pContext,
   QScriptEngine *pEngine)
{
   MainViewScript *pClass = 
      qscriptvalue_cast<MainViewScript*>(pContext->callee().data());

   if (!pClass)
      return QScriptValue();

   return pClass->newInstance();
}
