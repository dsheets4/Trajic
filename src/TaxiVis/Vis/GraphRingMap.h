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
#ifndef GraphRingMap_H
#define GraphRingMap_H

#include <QtGui/QGraphicsEllipseItem>
#include <QtGui/QPen>

#include "Vis/GraphBase.h"
#include "Vis/GraphRingItem.h"


namespace Vis
{
   //! Represents the Ring Map overlay.
   class GraphRingMap : public GraphBase
   {
   public:
      // ----------------------------------------------------------------------
      GraphRingMap(QGraphicsItem* pParentItem=0);
      GraphRingMap( const GraphRingMap &orig );
      ~GraphRingMap();


      // -------------------------------------------------------------------------
      // QGraphics Item implementation.

      void paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget);

      
      // ----------------------------------------------------------------------
      GraphRingMap& operator=( const GraphRingMap &rhs );

      
      // ----------------------------------------------------------------------

      //! Adds a graphical item to the ring.
      //!
      //! @param pGfx          Pointer to the Graph to add to the ring map
      //! @param fRotation     Rotation from up=0 to place the Graph object
      //! @param fSpan         Span in degrees that will represent the Graph size
      //! @param fDistPercent  % distance from ring center to place the graph (0-1)
      //! @param eAlignment    Where to draw the graph in relation to the ring
      //!
      //! @return GraphRingItem Newly create ring item.
      GraphRingItem* addRingItem( 
         GraphBase* pGfx,
         qreal      fRotation,
         qreal      fSpan,
         qreal      fDistPercent=1.0,
         GraphRingItem::Alignment eAlignment=GraphRingItem::AlignOutside );
      
      //! Adds the given ring item to the ring map.
      //!
      //! @param pGfxRingItem  Ring Item to add to the ring map.
      void addRingItem( GraphRingItem *pGfxRingItem );

      void removeRingItem( GraphBase* pGfx );
      
      bool getDrawQuadrants();
      
      //! Sets a draw flag on whether to draw quadrant lines in the ring map.
      //! Quadrants are represented by lines representing the radius of the 
      //! ring map drawn at 90 degree increments.
      //! 
      //! @param bDrawQuadrants  If set to true, the quadrants are drawn, 
      //!                        otherwise the quadrants are not drawn.
      void setDrawQuadrants(bool bDrawQuadrants );
      
      bool getDrawRingMarkers();
      
      //! Sets a draw flag on whether to draw ring markers that designate 
      //! distance from the center of the ring map.  They are essnentially
      //! concentric circles that represent various distances from the center
      //! of the ring map.
      //! 
      //! @param bDrawRingMarkers  If set to true, the ring markers are drawn, 
      //!                        otherwise they are not drawn.
      void setDrawRingMarkers(bool bDrawRingMarkers );
      
      // ----------------------------------------------------------------------

      void resize( const QSize& size );

   private:
      // ----------------------------------------------------------------------
      QPen     m_pen;              //!< Pen used to draw the ring
      bool     m_bDrawQuadrants;   //!< Whether to draw quadrant markers
      bool     m_bDrawRingMarkers; //!< Whether to draw concentric ring markers
   };
}; //namespace


// ============================================================================
// Integrate to Qt meta system
// ============================================================================
Q_DECLARE_METATYPE(Vis::GraphRingMap)
Q_DECLARE_METATYPE(Vis::GraphRingMap*)


#endif // GraphRingMap_H
