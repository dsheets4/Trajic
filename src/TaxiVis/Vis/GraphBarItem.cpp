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

#include <iostream>

#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QGraphicsLineItem>
#include <QtGui/QPainter>

#include "TaxiVisConstants.h"
#include "Vis/GraphBarItem.h"


// ============================================================================
using namespace std;

namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphBarItem::GraphBarItem(QGraphicsItem *pParentItem)
      : GraphBase(pParentItem)
      , m_offset(0,0)
      , m_pen(QBrush(QColor(0,50,230,128)), 1.0)
      , m_color1(QColor(220,20,60,255))
      , m_color2(QColor(255,215,0,255))
   {   
   }

   // -------------------------------------------------------------------------
   GraphBarItem::~GraphBarItem()
   {

   }


   // =========================================================================
   // Overridden methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void GraphBarItem::paint(
      QPainter *painter,
      const QStyleOptionGraphicsItem *option,
      QWidget *widget)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      painter->setPen( m_pen );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      //! @todo The GraphPie calculates a gradient automatically.  Add that 
      //!       to the GraphBar so that we have less items to request on the
      //!       interface.
      QLinearGradient gradient(
         0, 0,
         m_rect.width(), m_rect.height() );
      gradient.setColorAt(0, m_color1);
      gradient.setColorAt(1, m_color2);
      painter->setBrush( QBrush(gradient) );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Calculate the circle radius and offsets for the bounding rect.
      // Create the directional tick.
      QPolygonF tick;
      tick 
         << QPointF( 0,              m_rect.height() )
         << QPointF( m_rect.width(), m_rect.height() )
         << QPointF( m_rect.width(), 0 )
         << QPointF( 0,              0 );

      
      QTransform trans;
      trans.translate( m_offset.x(), m_offset.y() );
      painter->setTransform( trans, true );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      painter->drawPolygon(tick);
   }

   // =========================================================================
   // Action handlers
   // =========================================================================

   // -------------------------------------------------------------------------



   // =========================================================================
   // Implementation Methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphBarItem::setValue( double fValue )
   {
      m_rect.setHeight(-fValue);
   }

   // -------------------------------------------------------------------------
   void GraphBarItem::setPen( const QPen& pen )
   {
      m_pen = pen;
   }

   // -------------------------------------------------------------------------
   void GraphBarItem::setFillGradient( const QColor& color1, const QColor& color2 )
   {
      m_color1 = color1;
      m_color2 = color2;
   }

   void GraphBarItem::setColor( const QColor& color )
   {
      const int GradDist = 128;

      m_color1 = color;
      m_color2 = color;
      m_color1.setRed  ( (m_color1.red()>GradDist)   ? m_color1.red()-GradDist   : 0 );
      m_color1.setGreen( (m_color1.green()>GradDist) ? m_color1.green()-GradDist : 0 );
      m_color1.setBlue ( (m_color1.blue()>GradDist)  ? m_color1.blue()-GradDist  : 0 );
   }
   
   // -------------------------------------------------------------------------
	void GraphBarItem::setOffsetPoint( const QPointF& p )
   {
      m_offset = p;
   }

}; //namespace