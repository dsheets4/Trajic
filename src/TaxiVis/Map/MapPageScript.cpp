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
#include "Map/MapPageScriptProto.h"
#include "Map/MapPageScript.h"


namespace Map
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString MapPageScript::ScriptClassName = "MapPage";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   MapPageScript::MapPageScript(QScriptEngine *pEngine)
      : QObject(pEngine), QScriptClass(pEngine)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup the script object.
      m_proto = pEngine->newQObject( new MapPageScriptProto(this),
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
   MapPageScript::~MapPageScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue MapPageScript::prototype() const
   {
      return m_proto;
   }
   
   // -------------------------------------------------------------------------
   QString MapPageScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue MapPageScript::constructor()
   {
      return m_ctor;
   }

   // -------------------------------------------------------------------------
   QScriptValue MapPageScript::newInstance()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the object.
      ObjectBaseWrapperPtr pMap = MAP_FACTORY->Allocate( ScriptClassName );
      ObjectBaseDispatchPtr pDispatch(new MapPageDispatch(0));
      pDispatch->setObjWrap(pMap);
      return newInstance(pDispatch);
   }
   
   // -------------------------------------------------------------------------
   QScriptValue MapPageScript::newInstance(const ObjectBaseDispatchPtr &pDispatch)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      ConnectSignals( pDispatch->getObjWrap(), pDispatch );
      QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
      return engine()->newObject(this, data);
   }
   
   // -------------------------------------------------------------------------
   QScriptValue MapPageScript::newInstance(const ObjectBaseWrapperPtr &pObj)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      ObjectBaseDispatchPtr pDispatch(new MapPageDispatch(0));
      pDispatch->setObjWrap(pObj);

      ConnectSignals( pDispatch->getObjWrap(), pDispatch );
      QScriptValue data = engine()->newVariant(qVariantFromValue(pDispatch));
      return engine()->newObject(this, data);
   }

   // -------------------------------------------------------------------------
   void MapPageScript::ConnectSignals(ObjectBaseWrapperPtr pObj, ObjectBaseDispatchPtr pDispatch)
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
         SIGNAL(addLayerSignal(ObjectBaseWrapperPtr)),
         SLOT(addLayer(ObjectBaseWrapperPtr)) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(removeLayerSignal(ObjectBaseWrapperPtr)),
         SLOT(removeLayer(ObjectBaseWrapperPtr)) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setMapSettingsSignal(ObjectBaseWrapperPtr)),
         SLOT(setMapSettings(ObjectBaseWrapperPtr)) );
      pObj.get()->getObject()->connect( 
         pDispatch.get(),
         SIGNAL(setShowPosZoomSignal(bool)),
         SLOT(setShowPosZoom(bool)) );
   }
   
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue MapPageScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      MapPageScript *pClass = 
         qscriptvalue_cast<MapPageScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();

      return pClass->newInstance();
   }
   
}; //namespace