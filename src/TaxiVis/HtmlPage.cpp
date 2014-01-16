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
#include <iomanip>

#include <QtCore/QDir>
#include <QtWebKit/QWebFrame>

#include "CommonDefinitions.h"
#include "HtmlPage.h"


namespace Map
{
   // =========================================================================


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // ------------------------------------------------------------------------
   HtmlPage::HtmlPage(QObject *pParent)
      : QWebPage(pParent)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Verify object state
      Q_ASSERT(mainFrame());

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Connect the clear of the JavaScript objects to a slot that reregisters
      // them.  Otherwise they are lost when the page reloads.
      connect( 
         mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
         this,        SLOT(RegisterJavascriptObjects())
         );
   }

   // -------------------------------------------------------------------------
   HtmlPage::~HtmlPage()
   {

   }

  
   // =========================================================================
   // QWebPage implementation
   // =========================================================================

   // ------------------------------------------------------------------------- 
   void HtmlPage::javaScriptConsoleMessage(
      const QString & message,
      int lineNumber,
      const QString & sourceID )
   {
//#ifdef _DEBUG
      std::cout
         << "Page::console -   Source= " << qPrintable(sourceID)
         << ":  Line="    << std::setw(6) << lineNumber           
         << ":  Message=" << qPrintable(message)                  << std::endl;
//#endif
   }


   // =========================================================================
   // Public Slots exposed to scripting
   // =========================================================================
  
   // ------------------------------------------------------------------------- 
   void HtmlPage::SetUrl( const QString& sUrl )
   {
      mainFrame()->setUrl( QUrl(sUrl) );
   }


   // =========================================================================
   // Private/Protected Slots for action handling
   // =========================================================================

   // -------------------------------------------------------------------------
   void HtmlPage::RegisterJavascriptObjects()
   {
      Q_ASSERT(mainFrame());

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Expose the objects to the JavaScript executing on the page.
      mainFrame()->addToJavaScriptWindowObject( "HtmlPage",     this );
   }


}; //namespace
