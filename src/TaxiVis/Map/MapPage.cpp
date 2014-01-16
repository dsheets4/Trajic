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

#include <QtWebKit/QWebFrame>

#include "CommonDefinitions.h"
#include "Map/MapPage.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // ------------------------------------------------------------------------
   MapPage::MapPage(QObject *pParent)
      : HtmlPage(pParent)
      , m_jsSettingsMap(this)
      , m_pDispatch( new JsLayerDispatch(0) )
      , m_query(m_pDispatch, 0)
      , m_bShowPosZoom(false)
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

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup the web page that creates the OpenLayers map.
      QString sIndexHtml;
      sIndexHtml = "";//"file://";
      sIndexHtml += CommonDefinitions::sWwwDir.c_str();
      sIndexHtml += "/index.html";
      mainFrame()->setUrl( QUrl(sIndexHtml) );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Move the query object into the thread.
      m_query.moveToThread(&m_thread);
      // Starting the thread begins the query
      m_query.connect(  &m_thread, SIGNAL(started()), SLOT(executeQuery()) );
      // The query ending exits the thread
      m_thread.connect( &m_query,  SIGNAL(queryComplete()), SLOT(quit()) );
      connect( &m_thread, SIGNAL(finished()), SLOT(LayerQueryFinished()) );
   }

   // -------------------------------------------------------------------------
   MapPage::~MapPage()
   {

   }

   // =========================================================================
   // Implementation
   // =========================================================================

   // -------------------------------------------------------------------------
   void MapPage::CreateLayer( 
      const DataAccess::QueryRouteCriteria& criteria,
      const Map::JsSettingsLayer& settings)
   {
      m_query.setCriteria( criteria );
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Create the new layer
      JsLayer* layer = new JsLayer(this);
      layer->setSettings(settings);
      ObjectBaseWrapperPtr pLayer(new ObjectBaseWrapper(layer,this));
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Completion of the thread will propagate the layer data ready signal
      connect( &m_thread, SIGNAL(finished()), layer, SLOT(RefreshLayerData()) );
      // Connected the dispatch up to the JsLayer being created.
      m_pDispatch->disconnect();
      m_query.setLayer( pLayer );
      layer->connect( 
         m_pDispatch.get(),
         SIGNAL(addRouteSignal(ObjectBaseWrapperPtr)),
         SLOT(addRoute(ObjectBaseWrapperPtr)) );
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      if( !m_thread.isRunning() )
      {
         // Start the threaded query.
         m_thread.start();
      }
   }

   const Map::JsSettingsLayer& MapPage::GetLayerSettings( int nPos ) const
   {
      if( nPos >= 0 && nPos < m_layers.size() )
      {
         //! @todo Rearrange the objects that expose items to JavaScript so that 
         //!       they can return the QObject but on the C++ side they can still
         //!       communicate using the actual types. qMeta
         QVariant v(m_layers.at(nPos));
         ObjectBaseWrapperPtr p = v.value<ObjectBaseWrapperPtr>();
         return dynamic_cast<const Map::JsLayer*>(p.get()->getObject())->getSettings();
      }

      // Default return value.
      static Map::JsSettingsLayer defaultSettings(0);
      return defaultSettings;
   }

   const DataAccess::QueryRouteCriteria& MapPage::GetLayerCriteria( ) const
   {
      return m_query.getCriteria();
   }

   // =========================================================================
   // Action handlers
   // =========================================================================

   // -------------------------------------------------------------------------
   void MapPage::RegisterJavascriptObjects()
   {
      Q_ASSERT(mainFrame());

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Expose the objects to the JavaScript executing on the page.
      mainFrame()->addToJavaScriptWindowObject( "mapPage",     this );
      mainFrame()->addToJavaScriptWindowObject( "mapSettings", &m_jsSettingsMap );
   }
  
   // ------------------------------------------------------------------------- 
   void MapPage::LayerQueryFinished( )
   {
      addLayer( m_query.getLayer() );
   }

   // =========================================================================
   // Slots exposed to scripting
   // =========================================================================

   // -------------------------------------------------------------------------
   QObjectList MapPage::getLayers()
   {
      QObjectList objList;

      QListIterator<QVariant> i(m_layers);
      while( i.hasNext() )
      {
         QVariant v(i.next());
         ObjectBaseWrapperPtr p = v.value<ObjectBaseWrapperPtr>();
         objList.append( p.get()->getObject() );
      }

      return objList;
   }

   // -------------------------------------------------------------------------
   void MapPage::addLayer( ObjectBaseWrapperPtr pLayer )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      Q_ASSERT( pLayer );
      if( !pLayer ) return;
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      Q_ASSERT( pLayer.get()->getObject() );
      if( !(pLayer.get()->getObject()) ) return;
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      JsLayer* layer = dynamic_cast<JsLayer*>(pLayer.get()->getObject());
      if( layer )
      {
         layer->setParent( this );

         QVariant v;
         v.setValue(pLayer);
         m_layers.append( v );
         emit newLayer( layer );
      }
      else
      {
         std::cout << "MapPage::addLayer passed a non-layer object" << std::endl;
      }
   }

   // -------------------------------------------------------------------------
   void MapPage::removeLayer( ObjectBaseWrapperPtr pLayer )
   {
      //!@todo Implement the removeLayer method to delete a layer from the 
      //!      map.
   }

   // -------------------------------------------------------------------------
   void MapPage::setMapSettings( ObjectBaseWrapperPtr pSettings )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      Q_ASSERT( pSettings );
      if( !pSettings ) return;
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      Q_ASSERT( pSettings.get()->getObject() );
      if( !(pSettings.get()->getObject()) ) return;
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      JsSettingsMap* pSettingsMap = dynamic_cast<JsSettingsMap*>(pSettings.get()->getObject());
      if( pSettingsMap )
      {
         m_jsSettingsMap = *pSettingsMap;
      }
      else
      {
         std::cout << "MapPage::SetMapSettings passed a non-JsSettingsMap object" << std::endl;
      }
   }
   
   // -------------------------------------------------------------------------
   void MapPage::setShowPosZoom( bool bShowPosZoom )
   {
      m_bShowPosZoom = bShowPosZoom;
   }

   bool MapPage::getShowPosZoom( )
   {
      return m_bShowPosZoom;
   }


   // -------------------------------------------------------------------------
   void MapPage::test(int nProgress)
   {
      std::cout << "MapPage::test(int)=" << nProgress << std::endl;
   }

   // -------------------------------------------------------------------------
   void MapPage::test(QString sMessage)
   {
      std::cout << "MapPage::test(string)=" << qPrintable(sMessage) << std::endl;
   }

}; //namespace
