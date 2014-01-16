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

#include <iostream>

#include <QtCore/QMetaObject>
#include <QtCore/QMutex>
#include <QtCore/QFileInfo>

#include <QtGui/QMdiSubWindow>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QFileDialog>
#include <QtGui/QDesktopServices>
#include <QtGui/QMessageBox>

#include <QtWebKit/QWebView>
#include <QtWebKit/QGraphicsWebView>

#include "CommonDefinitions.h"
#include "DataAccess/QueryRouteCriteria.h"
#include "Map/MapFactory.h"
#include "Map/ScriptConfigMap.h"
#include "Map/JsSettingsLayer.h"
#include "Vis/ScriptConfigVis.h"
#include "Vis/GraphFactory.h"
#include "GuiFactory.h"
#include "ScriptConfigMain.h"
#include "TaxiVisGuiConstants.h"
#include "TaxiVis.h"


// ============================================================================
using namespace std;

// ============================================================================

// ============================================================================
// Construction and destruction
// ============================================================================

// ----------------------------------------------------------------------------
TaxiVis::TaxiVis(QWidget *pParent, Qt::WFlags flags)
   : QMainWindow(pParent, flags)
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Setup the code created by Qt from the .ui file
   ui.setupUi(this);
   resize( TaxiVisGuiConstants::MainWindowSizeDefault );
   SetupUiActions();
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   //!@todo Calling GRAPH_FACTORY here is a kludge that causes the factory to
   //!      be created in the Main Thread first and therefore properly places 
   //!      the factory object in the Main Thread so all the objects it creates
   //!      will also be in the main thread.  Need to figure out a better way
   //!      to do this.
   Vis::GRAPH_FACTORY;
   Map::MAP_FACTORY;
   Gui::GUI_FACTORY;

	
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Connect action to functions.
   connect( ui.actionExit,           SIGNAL(triggered()), SLOT(close()) );
   connect( ui.actionSave_As_Image,  SIGNAL(triggered()), SLOT(OnSaveAsImage()) );
   connect( ui.actionOpen,           SIGNAL(triggered()), SLOT(OnOpenScript()) );
	
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   BeginCommandPrompt();

   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Process command line arguments.  They can only be scripts right now.
   //!@todo This implementation causes problems since the script executes 
   //!      before the main (i.e. GUI) thread had a chance to start.  As a
   //!      work-around, add the run("") commands to a script with all the 
   //!      scripts to execute on start-up and then just run that on the 
   //!      command line.
#if 1
   Q_ASSERT(qApp);
   QStringList args = qApp->arguments();
   QStringListIterator i(args);
   i.next(); // Remove application name from arguments
   while( i.hasNext() )
   {
      executeScript(i.next());
   }
#endif
}

// ----------------------------------------------------------------------------
TaxiVis::TaxiVis(const TaxiVis& orig)
{
}
   
// ----------------------------------------------------------------------------
TaxiVis::~TaxiVis()
{
   // Synchronize with the prompt thread.
   m_thdPrompt.wait(5000);
}


// ============================================================================
// Setup methods
// ============================================================================
TaxiVis& TaxiVis::operator=(const TaxiVis& rhs)
{
   return *this;
}

// ============================================================================
// Helper methods
// ============================================================================

// ----------------------------------------------------------------------------
void TaxiVis::SetupUiActions()
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// Add keyboard shortcuts
	ui.actionRefresh->setShortcut( QKeySequence(QKeySequence::Refresh) );
}

// ----------------------------------------------------------------------------
bool TaxiVis::VerifyActiveSubWindow()
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Verify there is an active sub-window.
   Q_ASSERT(ui.mdiArea);
   Q_ASSERT(ui.mdiArea->activeSubWindow());
   Q_ASSERT(ui.mdiArea->activeSubWindow()->widget());

   if( (ui.mdiArea == NULL)  ||
       (ui.mdiArea->activeSubWindow() == NULL) ||
       (ui.mdiArea->activeSubWindow()->widget() == NULL) )
   {
      QMessageBox msg(
         QMessageBox::Warning,
         "No Active Window",
         "An active window must be selected to capture a screenshot",
         QMessageBox::Ok,
         this);
      msg.exec();

      return false;
   }

   return true;
}

// ----------------------------------------------------------------------------
bool TaxiVis::executeScript(QString sFileName)
{
    QMetaObject::invokeMethod(
       &m_engine,
       "evaluateFile",
       Qt::QueuedConnection,
       Q_ARG(QString, qPrintable(sFileName))
       );

	return true;
}

// ============================================================================
// Action handlers
// ============================================================================

// ----------------------------------------------------------------------------
void TaxiVis::createWindow( ObjectBaseWrapperPtr pScene, ObjectBaseWrapperPtr pView )
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Condition checking to aid debugging.
   Q_ASSERT(pView);
   Q_ASSERT(pView.get()->getObject());
   Q_ASSERT(pScene);
   Q_ASSERT(pScene.get()->getObject());

   if( !pView || !pView.get()->getObject() || !pScene || !pScene.get()->getObject() )
   {
      return;
   }

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Extract the contents of the wrappers.
   MainView*  view  = dynamic_cast<MainView*> ( pView.get()->getObject());
   MainScene* scene = dynamic_cast<MainScene*>(pScene.get()->getObject());
   Q_ASSERT(view);
   Q_ASSERT(scene);
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Connect the view and scene and handle initializations.
   view->setScene(scene);
   scene->CreateMapBackground();

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Add the MDI Window Area.
   QMdiSubWindow* pSubWin = ui.mdiArea->addSubWindow(view);
   pSubWin->setAttribute( Qt::WA_DeleteOnClose );
   pSubWin->resize(TaxiVisGuiConstants::ChildWindowSizeDefault);
   pSubWin->show();
   //pSubWin->showMaximized();
}

// ----------------------------------------------------------------------------
void TaxiVis::BeginCommandPrompt()
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   m_thdPrompt.setObjectName("Prompt Thread");
   m_thdScript.setObjectName("Script Thread");
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   static QMutex mutex;
   mutex.lock();
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   if( !m_thdPrompt.isRunning() )
   {
      // Register the script commands that should be available for the prompt.
      Map::ScriptConfigMap scMap;
      scMap.Register( m_engine.getEngine() );
      
      Vis::ScriptConfigVis scVis;
      scVis.Register( m_engine.getEngine() );

      ScriptConfigMain scMain;
      scMain.setApp(this);
      scMain.Register( m_engine.getEngine() );

      // Setup the prompt thread to run the command prompt when started.
      m_prompt.connect( 
         &m_thdPrompt, SIGNAL(started()), SLOT(cmdPrompt()) );
      // Setup to quit the application when the user exits the prompt.
      m_thdPrompt.connect(
         &m_prompt, SIGNAL(cmdPromptExited()), SLOT(quit()) );

      // Exit the entire application when the script engine closes.
      connect(
         &m_engine, SIGNAL(terminated()), SLOT(PrepareForQuit()) );
      connect(
         &m_thdScript, SIGNAL(finished()), SLOT(close()) );

      // Connect the engine up to handle command prompt commands but also
      // to block until the command completes.
      m_engine.connect(
         &m_prompt, SIGNAL(command(QString)),
         SLOT(evaluateString(QString)),
         Qt::BlockingQueuedConnection );
      m_thdScript.connect(
         &m_engine, SIGNAL(terminated()), SLOT(quit()) );

      // Setup so the threads are exited when the GUI is closing.
      m_engine.connect(
         qApp, SIGNAL(aboutToQuit()), SLOT(quit()) );
      
      // Put the prompt in the thread and start the threaded prompt.
      m_engine.moveToThread(&m_thdScript);
      m_thdScript.start();

      // Put the prompt in the thread and start the threaded prompt.
      m_prompt.moveToThread(&m_thdPrompt);
      m_thdPrompt.start();
   }
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   mutex.unlock();
}

// ----------------------------------------------------------------------------
void TaxiVis::OnSaveAsImage()
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Verify there is an active sub-window.
   if( !VerifyActiveSubWindow() )
      return;
   
   QMdiSubWindow* pSubWin = ui.mdiArea->activeSubWindow();
   if( pSubWin == NULL )
   {
      return;
   }
   QWidget*       pWidget = pSubWin->widget();
   if( pWidget == NULL )
   {
      return;
   }

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Get a filename from the user to save the screenshot.
   QString sFileName = QFileDialog::getSaveFileName(
      this,
      tr("Save Image"),
      QDesktopServices::storageLocation( QDesktopServices::PicturesLocation ),
      tr("Image Files (*.png)")
      );
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Invoke the method on the active sub-window.
   if( !sFileName.isEmpty() )
   {
      // Since the images are all saved to a specific location we need to strip
      // off the path.
      //!@todo Fix the jibberish where saving a screenshot can't be saved to 
      //       an absolute path but rather the filename is stripped off the 
      //       path and saved to a hard-coded (via CMake) location.
      QFileInfo fileInfo(sFileName);
      QString sMethod = "captureScreenShot";
      if( !QMetaObject::invokeMethod(
         pWidget,
         qPrintable(sMethod),
         Q_ARG(QString, qPrintable(fileInfo.fileName()))) )
      {
         QMessageBox msg(
            QMessageBox::Warning,
            "Method Failed",
            "Failed to execute " + sMethod,
            QMessageBox::Ok,
            this);
         msg.exec();
      }
   }
}

// ----------------------------------------------------------------------------
void TaxiVis::OnOpenScript()
{
	QString sFileName = QFileDialog::getOpenFileName(
			this,
			tr("Open Script"),
			CommonDefinitions::sScriptDir.c_str(), tr("Script Files (*.js)"));

	if( !sFileName.isEmpty() )
	{
		sFileName.replace(CommonDefinitions::sScriptDir.c_str(), "");

		executeScript(sFileName);
	}
}

// ----------------------------------------------------------------------------
void TaxiVis::OnRefresh()
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Verify there is an active sub-window.
   if( !VerifyActiveSubWindow() )
      return;
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Invoke the desired method on the active sub-window.
   QString sMethod = "refresh";
   if( !QMetaObject::invokeMethod(
      ui.mdiArea->activeSubWindow()->widget(),
      qPrintable(sMethod)) )
   {
      QMessageBox msg(
         QMessageBox::Warning,
         "Method Failed",
         "Failed to execute " + sMethod,
         QMessageBox::Ok,
         this);
      msg.exec();
   }
}

// ----------------------------------------------------------------------------
void TaxiVis::PrepareForQuit()
{
   //! @todo Closing stdin will force the input loop of ScriptPrompt to 
   //!       continue past the readline call.  This ultimately exits the
   //!       interactive loop which triggers application exit.  It's not the 
   //!       most elegant solution but works well.  Consider a way to revise
   //!       it so the ScriptPrompt can be turned off and on as needed.
   fclose(stdin);
}
