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

#include "Map/JsPointIconScriptProto.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsPointIconScriptProto::JsPointIconScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   JsPointIconScriptProto::~JsPointIconScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void JsPointIconScriptProto::setColor( QString sColor, qreal fTransparency )
   {
      JsPointIconDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setColor( sColor, fTransparency );
      }
   }
   
   // -------------------------------------------------------------------------
   void JsPointIconScriptProto::setWeight( int nWeight )
   {
      JsPointIconDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setWeight( nWeight );
      }
   }
   
   // -------------------------------------------------------------------------
   void JsPointIconScriptProto::addPoint( unsigned long long llTime, qreal lon, qreal lat, qreal hdg, qreal spd )
   {
      JsPointIconDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->addPoint( llTime, lon, lat, hdg, spd );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   JsPointIconDispatch* JsPointIconScriptProto::thisDispatch() const
   {
      ObjectBaseDispatchPtr *ptr = qscriptvalue_cast<ObjectBaseDispatchPtr*>(thisObject().data());
      if( ptr )
      {
         return dynamic_cast<JsPointIconDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace