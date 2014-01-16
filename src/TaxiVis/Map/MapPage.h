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
#ifndef MAPPAGE_H
#define MAPPAGE_H

#include <QtCore/QVariant>

#include <QtWebKit/QWebPage>

#include "ObjectBaseWrapper.h"
#include "DataAccess/QueryRouteCriteria.h"
#include "Map/JsSettingsMap.h"
#include "Map/JsLayer.h"
#include "Map/JsLayerDispatch.h"
#include "Map/JsQueryRouteWrapper.h"

#include "HtmlPage.h"


namespace Map
{
   //! Represents the Map background.
   class MapPage : public HtmlPage
   {
      Q_OBJECT
		
   public:
      // ----------------------------------------------------------------------
      MapPage(QObject *pParent);
      ~MapPage();
   
      // ----------------------------------------------------------------------
      void CreateLayer( 
		  const DataAccess::QueryRouteCriteria& criteria,
		  const Map::JsSettingsLayer& settingsRoute );

      const Map::JsSettingsLayer& GetLayerSettings( int nPos ) const;
      const DataAccess::QueryRouteCriteria& GetLayerCriteria( ) const;

   signals:
      // ----------------------------------------------------------------------
      void newLayer( QObject* pLayer );


   public slots:
      // ----------------------------------------------------------------------
      void addLayer( ObjectBaseWrapperPtr pLayer );
      void removeLayer( ObjectBaseWrapperPtr pLayer );

      QObjectList getLayers();

      //! Sets the settings used to initialize the map view.
      void setMapSettings( ObjectBaseWrapperPtr pSettings );

      //! Sets the settings used to initialize the map view.
      void setShowPosZoom( bool bShowPosZoom );
      bool getShowPosZoom( );
      
      // ----------------------------------------------------------------------
      //! @todo Test code to be removed later. It is used to allow the JavaScript
      //!       to call back into the C++ for debugging (i.e. catch breakpoint).
      void test(int nProgress=-1);
      void test(QString sMessage);


   protected slots:
      // ----------------------------------------------------------------------

      //! Registers the JavaScript objects with the QWebFrame via QtWebKit bridge.
      void RegisterJavascriptObjects();

      void LayerQueryFinished( );
   

   protected:
      // ----------------------------------------------------------------------
      JsSettingsMap m_jsSettingsMap; //!< Settings for the map.
      QVariantList  m_layers;        //!< List of layers for this map.

      //! @todo The JsLayerDispatchPtr and JsQueryRouteWrapper should be 
      //!       associated with the the specific layer they were created for.
      //!       That is, the list of layers should have associated with each 
      //!       layer a route and dispatch.
      JsLayerDispatchPtr  m_pDispatch; //!< Dispatch connecting query to layer
      JsQueryRouteWrapper m_query;     //!< Access to route data
      QThread             m_thread;    //!< Thread so the query doesn't block
      bool                m_bShowPosZoom; //!< Whether position and zoom should appear on the map
   };
}; //namespace

#endif // MAPPAGE_H
