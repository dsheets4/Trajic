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

#include "Map/MapPageDispatch.h"
#include "MainViewDispatch.h"
#include "MainSceneDispatch.h"
#include "TaxiVisDispatch.h"
#include "MainSceneScript.h"
#include "MainViewScript.h"
#include "ScriptConfigMain.h"


// =========================================================================
// Construction and destruction
// =========================================================================

// -------------------------------------------------------------------------
ScriptConfigMain::ScriptConfigMain()
{
}

// -------------------------------------------------------------------------
ScriptConfigMain::~ScriptConfigMain()
{
}


// =========================================================================
// Overridden methods
// =========================================================================

// -------------------------------------------------------------------------
void ScriptConfigMain::Register( QScriptEngine *pEngine )
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   // Expose the view to scripting so it's possible to manipulate the 
   // visualization.
   if( m_pApp )
   {
      TaxiVisDispatch* pAppDispatch = new TaxiVisDispatch(m_pApp);
      m_pApp->connect(
         pAppDispatch,
         SIGNAL(createWindowSignal(ObjectBaseWrapperPtr,ObjectBaseWrapperPtr)),
         SLOT(createWindow(ObjectBaseWrapperPtr,ObjectBaseWrapperPtr)) );
      
      QScriptValue valueView = pEngine->newQObject(
         pAppDispatch, QScriptEngine::ScriptOwnership);
      pEngine->globalObject().setProperty("app", valueView);
   }
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   MainViewScript *pMainViewScript = new MainViewScript(pEngine);
   pEngine->globalObject().setProperty(
      pMainViewScript->name(),
      pMainViewScript->constructor());
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   MainSceneScript *pMainSceneScript = new MainSceneScript(pEngine);
   pEngine->globalObject().setProperty(
      pMainSceneScript->name(),
      pMainSceneScript->constructor());
}

// =========================================================================
// Implementation
// =========================================================================

// -------------------------------------------------------------------------
void ScriptConfigMain::setApp( QObject *pApp )
{
   m_pApp = pApp;
}
