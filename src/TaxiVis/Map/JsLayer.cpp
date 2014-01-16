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

#include <sstream>
#include <iostream>

#include <QtCore/QDateTime>

#include <QtWebKit/QWebFrame>

#include "DataAccess/DataRoute.h"
#include "Map/JsQueryRouteHandler.h"
#include "Map/JsLayer.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsLayer::JsLayer(QObject *pParent)
      : MapObject(pParent)
      , m_sName("JsLayer")
      , m_nPos(-1)
      , m_settings(0)
   {
   }

   // -------------------------------------------------------------------------
   JsLayer::~JsLayer()
   {

   }


   // =========================================================================
   // Script exposed
   // =========================================================================

   // -------------------------------------------------------------------------
   QString JsLayer::getName() const
   {
      return m_sName;
   }

   void JsLayer::setName( QString sName )
   {
      m_sName = sName;
   }

   // -------------------------------------------------------------------------
   const JsSettingsLayer& JsLayer::getSettings() const
   {
      return m_settings;
   }

   QObject* JsLayer::getSettings()
   {
      return &m_settings;
   }

   void JsLayer::setSettings( const JsSettingsLayer& settings )
   {
      m_settings = settings;
   }


   // -------------------------------------------------------------------------
   QObjectList JsLayer::getRoutes()
   {
      QObjectList objList;

      JsRoutePtrListIterator i(m_routes);
      while( i.hasNext() )
      {
         objList.append( i.next().get()->getObject() );
      }

      return objList;
   }
   
   // -------------------------------------------------------------------------
   void JsLayer::addRoute( ObjectBaseWrapperPtr pRoute )
   {
      Q_ASSERT( pRoute );
      Q_ASSERT( pRoute.get()->getObject() );

      if( pRoute && pRoute.get()->getObject() )
      {
         JsRoute* route = dynamic_cast<JsRoute*>(pRoute.get()->getObject());
         Q_ASSERT( route );
         if( route )
         {
            m_routes.append( pRoute );
         }
      }
   }

   // -------------------------------------------------------------------------
   void JsLayer::RefreshLayerData()
   {
      emit RefreshData( this );
   }
}; //namespace