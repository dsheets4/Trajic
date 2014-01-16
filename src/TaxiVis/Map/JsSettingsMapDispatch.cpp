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

#include "Map/JsSettingsMapDispatch.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsSettingsMapDispatch::JsSettingsMapDispatch(QObject *pParent)
      : ObjectBaseDispatch(pParent)
   {
   }
   
   // -------------------------------------------------------------------------
   JsSettingsMapDispatch::JsSettingsMapDispatch(const JsSettingsMapDispatch& orig)
      : ObjectBaseDispatch(0)
      , m_pObj( orig.m_pObj )
   {
   }

   // -------------------------------------------------------------------------
   JsSettingsMapDispatch::~JsSettingsMapDispatch()
   {
   }
   
   // =========================================================================
   // Operators
   // =========================================================================
   
   // -------------------------------------------------------------------------
   JsSettingsMapDispatch& JsSettingsMapDispatch::operator=( const JsSettingsMapDispatch& rhs )
   {
      if( this != &rhs )
      {
         m_pObj = rhs.m_pObj;
      }

      return *this;
   }
   
   
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   ObjectBaseWrapperPtr JsSettingsMapDispatch::getObjWrap()
   {
      return m_pObj;
   }

   void JsSettingsMapDispatch::setObjWrap( ObjectBaseWrapperPtr pObj )
   {
      m_pObj = pObj;
   }


   // =========================================================================
   // Slots
   // =========================================================================

   // -------------------------------------------------------------------------   
   void JsSettingsMapDispatch::setZoomLevel( qint32 nZoom )
   {
      emit setZoomLevelSignal(nZoom);
   }
   
   // -------------------------------------------------------------------------
   void JsSettingsMapDispatch::setCenterLon( qreal fLon )
   {
      emit setCenterLonSignal( fLon );
   }
   
   // -------------------------------------------------------------------------
   void JsSettingsMapDispatch::setCenterLat( qreal fLat )
   {
      emit setCenterLatSignal( fLat );
   }
     
   // ------------------------------------------------------------------------- 
   void JsSettingsMapDispatch::setExtents(QVariantList lstExtents)
   {
      emit setExtentsSignal( lstExtents );
   }
   
   // -------------------------------------------------------------------------
   void JsSettingsMapDispatch::setPositionMapByExtents(bool bPositionByExtents)
   {
      emit setPositionMapByExtentsSignal( bPositionByExtents );
   }
   
}; //namespace