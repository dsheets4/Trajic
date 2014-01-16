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
#ifndef GraphRingMapDispatch_H
#define GraphRingMapDispatch_H

#include <QtCore/QObject>

#include "Vis/GraphBaseDispatch.h"


namespace Vis
{
   class GraphRingMapDispatch : public GraphBaseDispatch
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphRingMapDispatch(QObject *pParent);
      virtual ~GraphRingMapDispatch();
      

   signals:
      // ----------------------------------------------------------------------
      //void addRingItemSignal( 
      //   Vis::ObjWrapGraphPtr pGfx,
      //   qreal                fRotation,
      //   qreal                fSpan,
      //   qreal                fDistPercent=1.0,
      //   bool                 bDrawInverted=false );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void addRingItemSignal( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void removeRingItemSignal( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setDrawQuadrantsSignal( bool bDrawQuadrants );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setDrawRingMarkersSignal( bool bDrawRingMarkers );


   public slots:
      // ----------------------------------------------------------------------
      //Vis::ObjWrapGraphPtr addRingItem( 
      //   Vis::ObjWrapGraphPtr pGfx,
      //   qreal                fRotation,
      //   qreal                fSpan,
      //   qreal                fDistPercent=1.0,
      //   bool                 bDrawInverted=false );
      
      //! @copydoc GraphRingMapObjWrap::addRingItem
      void addRingItem( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! @copydoc GraphRingMapObjWrap::removeRingItem
      void removeRingItem( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! @copydoc GraphRingMap::setDrawQuadrants
      void setDrawQuadrants( bool bDrawQuadrants );
      
      //! @copydoc GraphRingMap::setDrawRingMarkers
      void setDrawRingMarkers( bool bDrawRingMarkers );
      
      //!@todo The addedRingItem was created as a way to return values
      //!      from the main thread to the script thread.  I'm not sure
      //!      yet if it is a workable approach but implement an approach
      //!      that allows returning values to the scripts.
      void addedRingItem( Vis::GraphBaseObjWrapPtr pRingItem );


   protected:
      GraphBaseObjWrapPtr m_pAddedRingItem;  //!< The addRingItem return value
   };
}; //namespace

#endif // GraphRingMapDispatch_H
