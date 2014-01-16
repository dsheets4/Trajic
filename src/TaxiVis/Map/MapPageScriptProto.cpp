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

#include "Map/MapPageScriptProto.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   MapPageScriptProto::MapPageScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   MapPageScriptProto::~MapPageScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void MapPageScriptProto::addLayer( ObjectBaseWrapperPtr pLayer )
   {
      MapPageDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->addLayer( pLayer );
      }
   }
   
   // -------------------------------------------------------------------------
   void MapPageScriptProto::removeLayer( ObjectBaseWrapperPtr pLayer )
   {
      MapPageDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->removeLayer( pLayer );
      }
   }
   
   // -------------------------------------------------------------------------
   void MapPageScriptProto::setMapSettings( ObjectBaseWrapperPtr pSettings )
   {
      MapPageDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setMapSettings( pSettings );
      }
   }
   
   // -------------------------------------------------------------------------
   void MapPageScriptProto::setShowPosZoom( bool bShowPosZoom )
   {
      MapPageDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setShowPosZoom( bShowPosZoom );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   MapPageDispatch* MapPageScriptProto::thisDispatch() const
   {      
      ObjectBaseDispatchPtr *ptr   = qscriptvalue_cast<ObjectBaseDispatchPtr*>(thisObject().data());
      if( ptr )
      {
         return dynamic_cast<MapPageDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace