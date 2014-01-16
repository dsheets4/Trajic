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

#include "Map/MapPageScript.h"
#include "Map/GraphPageScript.h"
#include "Map/JsSettingsMapScript.h"
#include "Map/JsPointScript.h"
#include "Map/JsRouteScript.h"
#include "Map/JsLayerScript.h"
#include "Map/ScriptConfigMap.h"


namespace Map
{   
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   ScriptConfigMap::ScriptConfigMap()
   {
   }

   // -------------------------------------------------------------------------
   ScriptConfigMap::~ScriptConfigMap()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void ScriptConfigMap::Register( QScriptEngine *pEngine )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      MapPageScript *pMapPageScript = new MapPageScript(pEngine);
      pEngine->globalObject().setProperty(
         pMapPageScript->name(),
         pMapPageScript->constructor());
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphPageScript *pGraphPageScript = new GraphPageScript(pEngine);
      pEngine->globalObject().setProperty(
         pGraphPageScript->name(),
         pGraphPageScript->constructor());

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      JsSettingsMapScript *pJsSettingsMapScript = new JsSettingsMapScript(pEngine);
      pEngine->globalObject().setProperty(
         pJsSettingsMapScript->name(),
         pJsSettingsMapScript->constructor());

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      JsPointScript *pJsPointScript = new JsPointScript(pEngine);
      pEngine->globalObject().setProperty(
         pJsPointScript->name(),
         pJsPointScript->constructor());
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      JsRouteScript *pJsRouteScript = new JsRouteScript(pEngine);
      pEngine->globalObject().setProperty(
         pJsRouteScript->name(),
         pJsRouteScript->constructor());
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      JsLayerScript *pJsLayerScript = new JsLayerScript(pEngine);
      pEngine->globalObject().setProperty(
         pJsLayerScript->name(),
         pJsLayerScript->constructor());
   }
   
}; //namespace