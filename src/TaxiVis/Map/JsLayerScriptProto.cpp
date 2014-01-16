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

#include "Map/JsLayerScriptProto.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsLayerScriptProto::JsLayerScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   JsLayerScriptProto::~JsLayerScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QString JsLayerScriptProto::getName() const
   {
      //! @todo Implement the get method paradigm for the scripting language.
      JsLayerDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->getName();
      }

      return QString("Implement Me!");
   }
   
   void JsLayerScriptProto::setName( QString sName )
   {
      JsLayerDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setName( sName );
      }
   }
   
   // -------------------------------------------------------------------------
   void JsLayerScriptProto::addRoute( ObjectBaseWrapperPtr pRoute )
   {
      JsLayerDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->addRoute( pRoute );
      }
   }
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   
   // -------------------------------------------------------------------------
   JsLayerDispatch* JsLayerScriptProto::thisDispatch() const
   {
      ObjectBaseDispatchPtr *ptr   = qscriptvalue_cast<ObjectBaseDispatchPtr*>(thisObject().data());
      if( ptr )
      {
         return dynamic_cast<JsLayerDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace