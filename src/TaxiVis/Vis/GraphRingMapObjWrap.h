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
#ifndef ObjWrapGraphRing_H
#define ObjWrapGraphRing_H

#include <QtCore/QObject>

#include "Vis/GraphRingMap.h"
#include "Vis/GraphBaseObjWrap.h"


namespace Vis
{
   class GraphRingMapObjWrap;
   
   //! Smart pointer definition.
   typedef SHARED_POINTER<GraphRingMapObjWrap> GraphRingMapObjWrapPtr;


   //! Wrapper class to wrap Graph objects with a QObject to make them 
   //! accessible with signals and slots for uses such as threading.
   class GraphRingMapObjWrap : public GraphBaseObjWrap
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphRingMapObjWrap(QObject *pParent=0);
      GraphRingMapObjWrap(GraphRingMap *pGfxRing, QObject *pParent=0);
      GraphRingMapObjWrap(const GraphRingMapObjWrap& orig);
      virtual ~GraphRingMapObjWrap();

      // ----------------------------------------------------------------------
      GraphRingMap* getGraphRing() const;
      void setGraphRing( GraphRingMap* pGfx );
      
      // ----------------------------------------------------------------------
      GraphRingMapObjWrap& operator=( const GraphRingMapObjWrap &rhs );

   signals:
      // ----------------------------------------------------------------------
      void addedRingItemSignal( Vis::GraphBaseObjWrapPtr pRingItem );

   public slots:
      // ----------------------------------------------------------------------
      //void addRingItem( 
      //   Vis::ObjWrapGraphPtr pGfx,
      //   qreal                fRotation,
      //   qreal                fSpan,
      //   qreal                fDistPercent=1.0,
      //   bool                 bDrawInverted=false );
      
      //! Adds the given ring item to the ring map.
      //!
      //! @param pGfx  Ring Item to add to the ring map.
      void addRingItem( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! Removes the given ring item from the ring map.
      //!
      //! @param pGfx  Ring Item to remove from the ring map.
      void removeRingItem( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! @copydoc GraphRingMap::setDrawQuadrants
      void setDrawQuadrants( bool bDrawQuadrants );
      
      //! @copydoc GraphRingMap::setDrawRingMarkers
      void setDrawRingMarkers( bool bDrawRingMarkers );
      
   private:
   };
}; //namespace

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Vis::GraphRingMapObjWrap);
Q_DECLARE_METATYPE(Vis::GraphRingMapObjWrap*);
Q_DECLARE_METATYPE(Vis::GraphRingMapObjWrapPtr);

#endif // ObjWrapGraphRing_H
