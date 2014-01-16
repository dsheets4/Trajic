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
#ifndef ScriptConfigMain_H
#define ScriptConfigMain_H

#include <QtScript/QScriptEngine>

#include "Script/ScriptConfig.h"
#include "MainView.h"
#include "MainScene.h"


//! Represents a bar ScriptConfigMain.
class ScriptConfigMain : public Script::ScriptConfig
{		
public:
   // ----------------------------------------------------------------------
   ScriptConfigMain();
   virtual ~ScriptConfigMain();
      
   // ----------------------------------------------------------------------
   virtual void Register( QScriptEngine *pEngine );
   
   // ----------------------------------------------------------------------
   void setApp( QObject *pApp );


protected:
   // ----------------------------------------------------------------------
   QObject      *m_pApp;       //!< Pointer to the application object.
};

#endif // ScriptConfigMain_H
