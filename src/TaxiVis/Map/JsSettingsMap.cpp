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

#include "Map/JsSettingsMap.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsSettingsMap::JsSettingsMap(QObject *pParent)
      : QObject(pParent)
      , m_fCenterLon(113.999)
      , m_fCenterLat(22.61667)
      , m_nZoom(11)
      , m_bPositionByExtents( false )
   {
   }

   // -------------------------------------------------------------------------
   JsSettingsMap::JsSettingsMap(const JsSettingsMap& orig)
      : QObject(orig.parent())
      , m_fCenterLon        ( orig.m_fCenterLon )
      , m_fCenterLat        ( orig.m_fCenterLat )
      , m_nZoom             ( orig.m_nZoom )
      , m_lstExtents        ( orig.m_lstExtents )
      , m_bPositionByExtents( orig.m_bPositionByExtents )
   {
   }

   // -------------------------------------------------------------------------
   JsSettingsMap::~JsSettingsMap()
   {

   }

   // =========================================================================
   // Implementation
   // =========================================================================

   // -------------------------------------------------------------------------
   JsSettingsMap& JsSettingsMap::operator=( const JsSettingsMap& rhs )
   {
      if( this != &rhs )
      {
         this->m_fCenterLon         = rhs.m_fCenterLon;
         this->m_fCenterLat         = rhs.m_fCenterLat;
         this->m_nZoom              = rhs.m_nZoom;
         this->m_lstExtents         = rhs.m_lstExtents;
         this->m_bPositionByExtents = rhs.m_bPositionByExtents;
      }

      return (*this);
   }

   // =========================================================================
   // Action handlers
   // =========================================================================

   // -------------------------------------------------------------------------
   qint32 JsSettingsMap::getZoomLevel() const
   {
      return m_nZoom;
   }

   void JsSettingsMap::setZoomLevel(qint32 nZoom)
   {
      m_nZoom = nZoom;
   }

   // -------------------------------------------------------------------------
   qreal JsSettingsMap::getCenterLon() const
   {
      return m_fCenterLon;
   }

   void JsSettingsMap::setCenterLon(qreal fCenterLon)
   {
      m_fCenterLon = fCenterLon;
   }

   // -------------------------------------------------------------------------
   qreal JsSettingsMap::getCenterLat() const
   {
      return m_fCenterLat;
   }

   void JsSettingsMap::setCenterLat(qreal fCenterLat)
   {
      m_fCenterLat = fCenterLat;
   }
   
   // -------------------------------------------------------------------------
   QVariantList JsSettingsMap::getExtents() const
   {
      return m_lstExtents;
   }

   void JsSettingsMap::setExtents(QVariantList lstExtents)
   {
      m_lstExtents = lstExtents;
   }
   
   // -------------------------------------------------------------------------
   bool JsSettingsMap::getPositionMapByExtents() const
   {
      return m_bPositionByExtents;
   }

   void JsSettingsMap::setPositionMapByExtents(bool bPositionByExtents)
   {
      m_bPositionByExtents = bPositionByExtents;
   }

}; //namespace