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
#include "Vis/GraphPcScriptProto.h"
#include "Vis/GraphPcScript.h"


namespace Vis
{
   // =========================================================================
   // Global configuration and setup
   // =========================================================================
   const QString GraphPcScript::ScriptClassName = "GraphPc";


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPcScript::GraphPcScript(QScriptEngine *pEngine)
      : GraphBaseScript(pEngine)
   {
      m_proto = pEngine->newQObject( new GraphPcScriptProto(this),
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
   GraphPcScript::~GraphPcScript()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue GraphPcScript::prototype() const
   {
      return m_proto;
   }
   
   // -------------------------------------------------------------------------
   QString GraphPcScript::name() const
   {
      return ScriptClassName;
   }
      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphPcScript::constructor()
   {
      return m_ctor;
   }

   // -------------------------------------------------------------------------
   QScriptValue GraphPcScript::newInstance()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the object.
      GraphBaseObjWrapPtr pGfx = GRAPH_FACTORY->AllocateGraph( ScriptClassName );
      GraphBaseDispatchPtr pDispatch(new GraphPcDispatch(0));
      pDispatch->setGraphObjWrap(pGfx);
      return GraphBaseScript::newInstance(pDispatch);
   }

   // -------------------------------------------------------------------------
   void GraphPcScript::ConnectSignals(GraphBaseObjWrapPtr pGfx, GraphBaseDispatchPtr pDispatch)
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
         SIGNAL(setBackgroundColorSignal(QString,qreal)),
         SLOT(setBackgroundColor(QString,qreal)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setCoordinateScaleSignal(QString)),
         SLOT(setCoordinateScale(QString)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setGainSignal(qreal)),
         SLOT(setGain(qreal)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setOffsetSignal(qreal)),
         SLOT(setOffset(qreal)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setYMaxSignal(double)),
         SLOT(setYMax(double)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(setYMinSignal(double)),
         SLOT(setYMin(double)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(addCoordinateSignal(QString)),
         SLOT(addCoordinate(QString)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(removeCoordinateSignal(int)),
         SLOT(removeCoordinate(int)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(removeAllCoordinatesSignal()),
         SLOT(removeAllCoordinates()) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(addLineSignal(QVariantList,QString,qreal)),
         SLOT(addLine(QVariantList,QString,qreal)) );
      pGfx->connect( 
         pDispatch.get(),
         SIGNAL(removeAllLinesSignal()),
         SLOT(removeAllLines()) );
   }
   
      
   // =========================================================================
   // Static methods to interact with the scripting language
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptValue GraphPcScript::construct(
      QScriptContext *pContext,
      QScriptEngine *pEngine)
   {
      GraphPcScript *pClass = 
         qscriptvalue_cast<GraphPcScript*>(pContext->callee().data());

      if (!pClass)
         return QScriptValue();

      return pClass->newInstance();
   }
   
}; //namespace