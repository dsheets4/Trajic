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

#include "Vis/GraphBaseScript.h"
#include "Vis/GraphRingMapScript.h"
#include "Vis/GraphRingItemScript.h"
#include "Vis/GraphBarScript.h"
#include "Vis/GraphPieScript.h"
#include "Vis/GraphTextScript.h"
#include "Vis/GraphPcScript.h"
#include "Vis/ScriptConfigVis.h"


namespace Vis
{   
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   ScriptConfigVis::ScriptConfigVis()
   {
   }

   // -------------------------------------------------------------------------
   ScriptConfigVis::~ScriptConfigVis()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void ScriptConfigVis::Register( QScriptEngine *pEngine )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphBaseScript *pGraphBaseScript = new GraphBaseScript(pEngine);
      pEngine->globalObject().setProperty(
         pGraphBaseScript->name(),
         pGraphBaseScript->constructor());
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphRingMapScript *pGraphRingMapScript = new GraphRingMapScript(pEngine);
      pEngine->globalObject().setProperty(
         pGraphRingMapScript->name(),
         pGraphRingMapScript->constructor());
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphRingItemScript *pGraphRingItemScript = new GraphRingItemScript(pEngine);
      pEngine->globalObject().setProperty(
         pGraphRingItemScript->name(),
         pGraphRingItemScript->constructor());
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphBarScript *pGraphBarScript = new GraphBarScript(pEngine);
      pEngine->globalObject().setProperty(
         pGraphBarScript->name(),
         pGraphBarScript->constructor());
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphPieScript *pGraphPieScript = new GraphPieScript(pEngine);
      pEngine->globalObject().setProperty(
         pGraphPieScript->name(),
         pGraphPieScript->constructor());
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphTextScript *pGraphTextScript = new GraphTextScript(pEngine);
      pEngine->globalObject().setProperty(
         pGraphTextScript->name(),
         pGraphTextScript->constructor());
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphPcScript *pGraphPcScript = new GraphPcScript(pEngine);
      pEngine->globalObject().setProperty(
         pGraphPcScript->name(),
         pGraphPcScript->constructor());
   }
   
}; //namespace