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

#include "Map/JsRouteScriptProto.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsRouteScriptProto::JsRouteScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   JsRouteScriptProto::~JsRouteScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void JsRouteScriptProto::setColor( QString sColor, qreal fTransparency )
   {
      JsRouteDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setColor( sColor, fTransparency );
      }
   }
   
   // -------------------------------------------------------------------------
   void JsRouteScriptProto::setWeight( int nWeight )
   {
      JsRouteDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setWeight( nWeight );
      }
   }
   
   // -------------------------------------------------------------------------
   void JsRouteScriptProto::addPoint( unsigned long long llTime, qreal lon, qreal lat, qreal hdg, qreal spd )
   {
      JsRouteDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->addPoint( llTime, lon, lat, hdg, spd );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   JsRouteDispatch* JsRouteScriptProto::thisDispatch() const
   {
      ObjectBaseDispatchPtr *ptr = qscriptvalue_cast<ObjectBaseDispatchPtr*>(thisObject().data());
      if( ptr )
      {
         return dynamic_cast<JsRouteDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace