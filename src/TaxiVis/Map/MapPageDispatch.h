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
#ifndef MapPageDispatch_H
#define MapPageDispatch_H

#include <QtCore/QObject>

#include "ObjectBaseWrapper.h"
#include "ObjectBaseDispatch.h"
#include "Map/JsLayer.h"
#include "Map/MapPage.h"


namespace Map
{
   //! Wrapper class to wrap Graph objects with a QObject to make them 
   //! accessible with signals and slots for uses such as threading.
   class MapPageDispatch : public ObjectBaseDispatch
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      MapPageDispatch(QObject *pParent=0);
      MapPageDispatch(const MapPageDispatch& orig);
      virtual ~MapPageDispatch();


   signals:
      // ----------------------------------------------------------------------
      void addLayerSignal( ObjectBaseWrapperPtr pLayer );
      void removeLayerSignal( ObjectBaseWrapperPtr pLayer );
      void setMapSettingsSignal( ObjectBaseWrapperPtr pSettings );
      void setShowPosZoomSignal( bool bShowPosZoom );


   public slots:
      // ----------------------------------------------------------------------
      void addLayer( ObjectBaseWrapperPtr pLayer );
      void removeLayer( ObjectBaseWrapperPtr pLayer );
      void setMapSettings( ObjectBaseWrapperPtr pSettings );
      void setShowPosZoom( bool bShowPosZoom );

      
   private:
      // ----------------------------------------------------------------------
   };
}; //namespace

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Map::MapPageDispatch);
Q_DECLARE_METATYPE(Map::MapPageDispatch*);

#endif // MapPageDispatch_H
