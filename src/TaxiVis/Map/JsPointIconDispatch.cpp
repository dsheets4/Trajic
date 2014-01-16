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

#include "Map/JsPointIconDispatch.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsPointIconDispatch::JsPointIconDispatch(QObject *pParent)
      : ObjectBaseDispatch(pParent)
   {
   }
   
   // -------------------------------------------------------------------------
   JsPointIconDispatch::JsPointIconDispatch(const JsPointIconDispatch& orig)
      : ObjectBaseDispatch(0)
      , m_pObj( orig.m_pObj )
   {
   }

   // -------------------------------------------------------------------------
   JsPointIconDispatch::~JsPointIconDispatch()
   {
   }
   
   // =========================================================================
   // Operators
   // =========================================================================
   
   // -------------------------------------------------------------------------
   JsPointIconDispatch& JsPointIconDispatch::operator=( const JsPointIconDispatch& rhs )
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
   ObjectBaseWrapperPtr JsPointIconDispatch::getObjWrap()
   {
      return m_pObj;
   }

   void JsPointIconDispatch::setObjWrap( ObjectBaseWrapperPtr pObj )
   {
      m_pObj = pObj;
   }


   // =========================================================================
   // Slots
   // =========================================================================

   // -------------------------------------------------------------------------
   void JsPointIconDispatch::setColor( QString sColor, qreal fTransparency )
   {
      emit setColorSignal( sColor, fTransparency );
   }

   // -------------------------------------------------------------------------
   void JsPointIconDispatch::setWeight( int nWeight )
   {
      emit setWeightSignal( nWeight );
   }
   
   // -------------------------------------------------------------------------
   void JsPointIconDispatch::addPoint( unsigned long long llTime, qreal lon, qreal lat, qreal hdg, qreal spd )
   {
      emit addPointSignal( llTime, lon, lat, hdg, spd );
   }
   
}; //namespace