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

#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QPainter>

#include "TaxiVisGuiConstants.h"
#include "Vis/GraphFactory.h"
#include "Vis/GraphRingItem.h"
#include "Vis/GraphRingMap.h"



// ============================================================================
using namespace std;

namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingMap::GraphRingMap(QGraphicsItem *pParentItem)
      : GraphBase(pParentItem)
      , m_pen(QBrush(QColor(100,100,100,64)), 3.0)
      , m_bDrawQuadrants(false)
      , m_bDrawRingMarkers(false)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      resize(TaxiVisGuiConstants::ChildWindowSizeDefault);
   }
   
   // -------------------------------------------------------------------------
   GraphRingMap::GraphRingMap( const GraphRingMap &orig )
      : GraphBase(0)
      , m_pen(QBrush(QColor(50,50,50,64)), 3.0)
   {
   }

   // -------------------------------------------------------------------------
   GraphRingMap::~GraphRingMap()
   {

   }


   // =========================================================================
   // QGraphicsItem Implementation
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphRingMap::paint(
      QPainter *painter,
      const QStyleOptionGraphicsItem *option,
      QWidget *widget)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      painter->setPen( m_pen );
      painter->drawEllipse( m_rect );
      painter->setPen( QPen(QBrush(QColor(128,128,128,128)), 1.0) );
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Draw several pies that represent the quadrants of the ring map.
      if( m_bDrawQuadrants )
      {
         painter->drawPie(m_rect,   0*16, 0);
         painter->drawPie(m_rect,  90*16, 0);
         painter->drawPie(m_rect, 180*16, 0);
         painter->drawPie(m_rect, 270*16, 0);
      }
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Draw several rings representing 25%, 50%, and 75% of the ring map.
      if( m_bDrawRingMarkers )
      {
         QRectF rect = m_rect;
         rect.setWidth ( m_rect.width()  * 0.25 );
         rect.setHeight( m_rect.height() * 0.25 );
         rect.translate( m_rect.center().x()-rect.center().x(),m_rect.center().y()-rect.center().y() );
         painter->drawEllipse( rect );
         rect.setWidth ( m_rect.width()  * 0.5 );
         rect.setHeight( m_rect.height() * 0.5 );
         rect.translate( m_rect.center().x()-rect.center().x(),m_rect.center().y()-rect.center().y() );
         painter->drawEllipse( rect );
         rect.setWidth ( m_rect.width()  * 0.75 );
         rect.setHeight( m_rect.height() * 0.75 );
         rect.translate( m_rect.center().x()-rect.center().x(),m_rect.center().y()-rect.center().y() );
         painter->drawEllipse( rect );
      }

#if 0
#ifdef _DEBUG

      // For each ring item child, draw the pie representing the area that it
      // has to draw its Graph object.
      QListIterator<QGraphicsItem*> i( this->childItems() );
      while( i.hasNext() )
      {
         GraphRingItem* ri = dynamic_cast<GraphRingItem*>(i.next());
         if( ri )
         {
            //! @todo The rotation to draw the GraphRingItem extents for debugging
            //!       is off, presumably because there are other 
            //!       transformations going on.  How can we account for that?
            //!       At the moment it is accounted for with the +90 but that
            //!       is not properly drawing all the quadrants.
            qreal fRotation = (-ri->getRotation()+90)*16;

            // Draw a center line
            QPen pen(Qt::DashLine);
            pen.setColor( QColor(128,128,128,128) );
            painter->setPen( pen );      
            painter->drawPie(m_rect, fRotation, 0);

            // Draw the extents of the ring item.
            pen.setStyle(Qt::DotLine);
            painter->setPen( pen );
            painter->drawPie(m_rect, 
               fRotation-((ri->getSpan()/2)*16),
               ri->getSpan()*16);
         }
      }
#endif // _DEBUG
#endif
   }



   // =========================================================================
   // Implementation Methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphRingItem* GraphRingMap::addRingItem( 
      GraphBase *pGfx,
      qreal      fRotation,
      qreal      fSpan,
      qreal      fDistPercent,
      GraphRingItem::Alignment eAlignment )
   {
      if( !pGfx )
         return NULL;
      
      GraphRingItem* pGfxRingItem = new GraphRingItem(this);

      pGfxRingItem->setRotation( fRotation );
      pGfxRingItem->setSpan( fSpan );
      pGfxRingItem->setDistPercent( fDistPercent );
      pGfxRingItem->setAlignment( eAlignment );
      pGfxRingItem->addGraph( pGfx );

      addRingItem( pGfxRingItem );

      return pGfxRingItem;
   }
   
   // -------------------------------------------------------------------------
   void GraphRingMap::addRingItem( GraphRingItem *pGfxRingItem )
   {
      Q_ASSERT( pGfxRingItem );

      pGfxRingItem->setParentItem( this );
      pGfxRingItem->setSize( m_rect );
      pGfxRingItem->updateTransform();
   }
   
   // -------------------------------------------------------------------------
   void GraphRingMap::removeRingItem( GraphBase* pGfx )
   {
      Q_ASSERT(pGfx);

      if( pGfx && pGfx->parentItem() == this )
      {
         pGfx->setParentItem(NULL);
      }
   }
   
   // -------------------------------------------------------------------------
   bool GraphRingMap::getDrawQuadrants()
   {
      return m_bDrawQuadrants;
   }

   void GraphRingMap::setDrawQuadrants(bool bDrawQuadrants )
   {
      m_bDrawQuadrants = bDrawQuadrants;
   }
      
   // -------------------------------------------------------------------------
   bool GraphRingMap::getDrawRingMarkers()
   {
      return m_bDrawRingMarkers;
   }

   void GraphRingMap::setDrawRingMarkers(bool bDrawRingMarkers )
   {
      m_bDrawRingMarkers = bDrawRingMarkers;
   }

   // -------------------------------------------------------------------------
   void GraphRingMap::resize( const QSize& size )
   {
      const double fOuterRingPercent = 0.20;

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Calculate the circle diameter and offsets for the bounding rect.
      double fDiameter;
      double fAdjust;

      // Use the smaller dimension for the circle radius so the circle always fits
      // in the view.  Calculate a percentage adjustment to allow room around the 
      // circle for the graphical items.
      if( size.width() < size.height() )
      {
         fDiameter = size.width();
         fAdjust = size.width() * fOuterRingPercent;
      }
      else
      {
         fDiameter = size.height();
         fAdjust = size.height() * fOuterRingPercent;
      }

      fDiameter -= fAdjust;
      double fRadius = fDiameter/2.0;

      // Determine the offsets from the screen size that center the circle.
      // This point represents the lower right corner, not the center of the
      // circle.
      double fOffsetX = (size.width()  - fDiameter) / 2.0;
      double fOffsetY = (size.height() - fDiameter) / 2.0;
      setPos( fOffsetX+fRadius, fOffsetY+fRadius );

      // The circle is defined by a lower right corner (from the setPos) and 
      // the height and width (it's an ellipse but we make it a circle).
      QRectF rectBounding( -fRadius, -fRadius, fDiameter, fDiameter );
      setSize( rectBounding );

      QListIterator<QGraphicsItem*> i( this->childItems() );
      while( i.hasNext() )
      {
         GraphRingItem* ri = dynamic_cast<GraphRingItem*>(i.next());
         if( ri )
         {
            ri->setSize( rectBounding );
            ri->updateTransform();
         }
      }
   }
   
   // =========================================================================
   // Operators
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingMap& GraphRingMap::operator=( const GraphRingMap &rhs )
   {
      if( this != &rhs )
      {
         GraphBase::operator=( rhs );
         m_pen = rhs.m_pen;
      }

      return *this;
   }

}; //namespace