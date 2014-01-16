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
#ifndef GraphRingItem_H
#define GraphRingItem_H

#include "Vis/GraphBase.h"


namespace Vis
{
   //! Represents the Ring Map overlay.
   class GraphRingItem : public GraphBase
   {		
   public:
      // ----------------------------------------------------------------------

      //! Enumeration to define the positioning of the ring item in relation 
      //! to the ring that it is placed on.
      enum Alignment
      {
         AlignOutside,
         AlignInside,
         AlignCenter
      };


      // ----------------------------------------------------------------------
      GraphRingItem(QGraphicsItem* pParentItem=0);
      ~GraphRingItem();

      // ----------------------------------------------------------------------
      // QGraphics Item implementation.

      void paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget);

      // ----------------------------------------------------------------------
      // Additional interface
      
      //! Associates the provided graph with the ring item.  Note that adding
      //! graphs is cumulative.  Remove a graph by calling removeGraph.
      //!
      //! @param pGfx  Any item that inherits from GraphBase to display with 
      //!              the ring item.
      void addGraph( GraphBase* pGfx );
      
      //! Removes the provided graph from the ring item if that item is 
      //! associated with the ring item.
      //!
      //! @param pGfx  Any item that inherits from GraphBase to display with 
      //!              the ring item.
      void removeGraph( GraphBase* pGfx );

      Vis::GraphRingItem::Alignment getAlignment() const;
      
      //! Sets the alignment of the graphic item based on the intersection of 
      //! the centerline of the span and the distance defined by the ring map 
      //! radius and distance percentage.
      //!
      //! @param eAlignment Enumeration defining the alignment.  Possible 
      //!                   values are:
      //!                   @li GraphRingItem.AlignCenter - Center on the rotation centerline and distance.
      //!                   @li GraphRingItem.AlignOutside - Bottom edge is drawn on the rotaion centerline and distance.
      //!                   @li GraphRingItem.AlignInside - Top edge is drawn on the rotaion centerline and distance.
      //!
      //! @sa setDistPercent(qreal), setRotation(qreal)
      void setAlignment( Vis::GraphRingItem::Alignment eAlignment );

      qreal getRotation() const;
      
      //! Sets the rotation of the ring item within the ring map.
      //!
      //! @param fRotation  Rotation in degrees with zero degrees pointing 
      //!                   straight up and rotating clockwise.
      void setRotation( qreal fRotation );
      
      qreal getSpan() const;

      //! Sets the span of the graphical item.  This indirectly sets the width 
      //! of the item.  Width is calculated from the chord that subtends the 
      //! ring map at the given distance percentage.
      //!
      //! @param fSpan  Span in degrees centered on the given rotation.
      //!
      //! @sa setDistPercent(qreal), setRotation(qreal)
      void setSpan( qreal fSpan );

      bool getDistPercent() const;
      
      //! Sets the distance from the center of the ring map that the GraphBase
      //! object will be drawn.  Note that the alignment will also factor in
      //! to the overall distance from the center.
      //!
      //! @param fDistPercent  Percentage of the total radius of the ring map
      //!                      at which the graphic item is drawn.
      //!
      //! @sa setAlignment(int)
      void setDistPercent( qreal fDistPercent );

      bool getStabilized() const;
      
      //! Flag indicating whether the graphical item should rotate as it is 
      //! positioned around the ring map based on the rotation.  By default 
      //! graphical items will rotate with the ring item.  Setting stablized 
      //! to true will result in the graphical item itself not rotating even
      //! though it is still positioned arond the ring map according to the
      //! set rotation.  This is useful for things like text.
      //!
      //! @param bStabilized  When set to true the graphic item associated 
      //!                     with this ring item will be stabilized so it
      //!                     does not rotate around the ring map.
      void setStabilized( bool bStabilized );
      

      void updateTransform();

   protected:
      // ----------------------------------------------------------------------
      qreal     m_fRotation;     //!< Defines the rotation of the bar
      qreal     m_fSpan;         //!< Defines the span of the item on the map.
      qreal     m_fDistPercent;  //!< Percentage of the ring to draw the item at.
      Alignment m_eAlign;        //!< Alignment of the Graph related to the ring.
      bool      m_bStabilized;   //!< Whether Graph should rotate with ring item.
   };
}; //namespace

#endif // GraphRingItem_H
