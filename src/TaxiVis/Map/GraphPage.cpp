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
#include "Map/MapPage.h"
#include "Map/GraphPage.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // ------------------------------------------------------------------------
   GraphPage::GraphPage(QObject *pParent)
      : HtmlPage(pParent)
      , m_sCsvFile()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup the web page that creates the OpenLayers map.
      SetUrl( "http://localhost:8888/www/parallel new2new.html" );
      //SetUrl( "parallel new2new.html" );
   }

   // -------------------------------------------------------------------------
   GraphPage::~GraphPage()
   {

   }
   

   // =========================================================================
   // Public Slots exposed to scripting
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QString GraphPage::getCsvFile()
   {
      return m_sCsvFile;
   }
      
   void GraphPage::setCsvFile(const QString& sCsvFile)
   {
      m_sCsvFile = sCsvFile;
   }
   
   // -------------------------------------------------------------------------
   qreal GraphPage::getValueThresh()
   {
      return m_fValueThresh;
   }

   void GraphPage::setValueThresh(qreal fValueThresh)
   {
      m_fValueThresh = fValueThresh;
   }

   // -------------------------------------------------------------------------
   int GraphPage::getTopicThresh()
   {
      return m_nTopicThresh;
   }

   void GraphPage::setTopicThresh(int nTopicThresh)
   {
      m_nTopicThresh = nTopicThresh;
   }

   // -------------------------------------------------------------------------      
   QStringList GraphPage::getTopicColors()
   {
      return m_lstTopicColors;
   }

   void GraphPage::setTopicColors(QStringList lstTopicColors)
   {
      m_lstTopicColors = lstTopicColors;
   }


   // =========================================================================
   // Private/Protected Slots for action handling
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphPage::RegisterJavascriptObjects()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Expose the objects to the JavaScript executing on the page.
      mainFrame()->addToJavaScriptWindowObject( "GraphPage",     this );
   }

}; //namespace
