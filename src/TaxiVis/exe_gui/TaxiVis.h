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
#ifndef TAXIVIS_H
#define TAXIVIS_H

#include <QtCore/QThread>

#include <QtGui/QMainWindow>
#include <QtGui/QDockWidget>
#include <QtGui/QGraphicsView>
#include <QtGui/QComboBox>

#include "ui_TaxiVis.h"
#include "MainScene.h"
#include "MainView.h"
#include "Script/ScriptPrompt.h"
#include "Script/ScriptEngine.h"
#include "Map/MapPage.h"


// -------------------------------------------------------------------------
//! Represents the Main Window of the Information TaxiVis application.
class TaxiVis : public QMainWindow
{
   Q_OBJECT
		
public:
   // -------------------------------------------------------------------------
   TaxiVis(QWidget *pParent, Qt::WFlags flags);
   ~TaxiVis();

private:
   // -------------------------------------------------------------------------
   TaxiVis(const TaxiVis& orig);
   TaxiVis& operator=(const TaxiVis& rhs);
   

   // -------------------------------------------------------------------------
   
   //! Starts the command prompt thread if it is not already running.
   void BeginCommandPrompt();


public slots:
   // -------------------------------------------------------------------------
	void createWindow( ObjectBaseWrapperPtr pScene, ObjectBaseWrapperPtr pView );


protected slots:
   // -------------------------------------------------------------------------
   
   void OnSaveAsImage();

   void OnOpenScript();

   void OnRefresh();

   void PrepareForQuit();


private:
   // -------------------------------------------------------------------------
   //! Sets up all the actions for the user interface.
   void SetupUiActions();

   bool executeScript(QString sScriptName);

   bool VerifyActiveSubWindow();
	
   // -------------------------------------------------------------------------
   Ui::TaxiVisClass ui;  //!< Qt generated from the .ui file from Designer
   
   Script::ScriptPrompt m_prompt;     //!< Command prompt object.
   QThread              m_thdPrompt;  //!< Thread for the command prompt.
   Script::ScriptEngine m_engine;     //!< Script engine to execute scripts.
   QThread              m_thdScript;  //!< Thread for script execution.
};

#endif // TAXIVIS_H
