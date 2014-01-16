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

#include <QtScript/QScriptEngine>

#include "Map/JsSettingsMapScriptProto.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsSettingsMapScriptProto::JsSettingsMapScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   JsSettingsMapScriptProto::~JsSettingsMapScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void JsSettingsMapScriptProto::setZoomLevel(qint32 nZoom)
   {
      JsSettingsMapDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setZoomLevel( nZoom );
      }
   }
   
   // -------------------------------------------------------------------------
   void JsSettingsMapScriptProto::setCenterLon(qreal fCenterLon)
   {
      JsSettingsMapDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setCenterLon( fCenterLon );
      }
   }
   
   // -------------------------------------------------------------------------
   void JsSettingsMapScriptProto::setCenterLat(qreal fCenterLat)
   {
      JsSettingsMapDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setCenterLat( fCenterLat );
      }
   }
 
   // -------------------------------------------------------------------------
   void JsSettingsMapScriptProto::setExtents(QVariantList lstExtents)
   {
      JsSettingsMapDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setExtents( lstExtents );
      }
   }
   
   // -------------------------------------------------------------------------
   void JsSettingsMapScriptProto::setPositionMapByExtents(bool bPositionByExtents)
   {
      JsSettingsMapDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setPositionMapByExtents( bPositionByExtents );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   
   // -------------------------------------------------------------------------
   JsSettingsMapDispatch* JsSettingsMapScriptProto::thisDispatch() const
   {
      ObjectBaseDispatchPtr *ptr   = qscriptvalue_cast<ObjectBaseDispatchPtr*>(thisObject().data());
      if( ptr )
      {
         return dynamic_cast<JsSettingsMapDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace