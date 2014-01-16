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

#include "MapPageDispatch.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   MapPageDispatch::MapPageDispatch(QObject *pParent)
      : ObjectBaseDispatch( pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   MapPageDispatch::MapPageDispatch(const MapPageDispatch& orig)
      : ObjectBaseDispatch(0)
   {
   }

   // -------------------------------------------------------------------------
   MapPageDispatch::~MapPageDispatch()
   {
   }

      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   
   // =========================================================================
   // Operators
   // =========================================================================
      

   // =========================================================================
   // Slots
   // =========================================================================

   // -------------------------------------------------------------------------
   void MapPageDispatch::addLayer( ObjectBaseWrapperPtr pLayer )
   {
      emit addLayerSignal( pLayer );
   }

   // -------------------------------------------------------------------------
   void MapPageDispatch::removeLayer( ObjectBaseWrapperPtr pLayer )
   {
      emit removeLayerSignal( pLayer );
   }

   // -------------------------------------------------------------------------
   void MapPageDispatch::setMapSettings( ObjectBaseWrapperPtr pSettings )
   {
      emit setMapSettingsSignal( pSettings );
   }
   
   // -------------------------------------------------------------------------
   void MapPageDispatch::setShowPosZoom( bool bShowPosZoom )
   {
      emit setShowPosZoomSignal( bShowPosZoom );
   }
};