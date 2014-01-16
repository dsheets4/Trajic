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
#ifndef JSLAYER_H
#define JSLAYER_H

#include <QtCore/QObject>
#include <QtCore/QList>

#include "ObjectBaseWrapper.h"
#include "DataAccess/QueryRouteCriteria.h"
#include "Map/JsRoute.h"
#include "Map/JsSettingsLayer.h"


typedef QList<ObjectBaseWrapperPtr>              JsRoutePtrList;
typedef QListIterator<ObjectBaseWrapperPtr>      JsRoutePtrListIterator;
typedef QList<DataAccess::Route>                 DataRouteList;
typedef QListIterator<DataAccess::Route>         DataRouteListIterator;

namespace Map
{
   //! Represents a layer in the map and is exposed to the web page's java script.
   class JsLayer : public MapObject
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      JsLayer(QObject *pParent);
      ~JsLayer();

      // ----------------------------------------------------------------------

      //! Returns the settings object for the layer.  Note that QObject* must 
      //! be returned for it to function in the JavaScript.
      const JsSettingsLayer& getSettings() const;


   signals:
      // ----------------------------------------------------------------------
      //! Emitted when this layer has additional data that needs refreshed.
      void RefreshData(QObject* pLayer);


   public slots:
      // ----------------------------------------------------------------------
      
      //! Retrieves the name of the layer.
      QString getName() const;
      
      //! Sets the name of the layer.  This name is used on the map to identify
      //! the layer.
      //!
      //! @param sName  Name to assign the layer.
      void setName( QString sName );

      void setSettings( const JsSettingsLayer& settings );
      //! @todo Is there a better way to allow the script return which 
      //!       apparently isn't const to access the JsLayerSettings data?
      QObject* getSettings();
      
      //! Returns an array of JsRoute objects representing the routes that
      //! comprise this layer.  It's much faster to construct this list than 
      //! to use the iteration style since it greatly reduces the overhead 
      //! of the callbacks.
      QObjectList getRoutes();
      
      //! Adds a route to the layer.
      //!
      //! @param pRoute  Object representing a JsRoute
      void addRoute( ObjectBaseWrapperPtr pRoute );

      //! Prepares for and initiates the event to the JavaScript environment.
      void RefreshLayerData();


   protected:
      // ----------------------------------------------------------------------
      QString             m_sName;      //!< Name of the layer
      int                 m_nPos;       //!< Position of the current route
      JsRoutePtrList      m_routes;     //!< Routes associated with this layer
      JsSettingsLayer     m_settings;   //!< Settings for the route
   };
}; //namespace

#endif // JSLAYER_H
