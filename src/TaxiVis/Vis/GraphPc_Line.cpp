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
#include "Vis/GraphPc_Line.h"


// ============================================================================
using namespace std;

namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPc_Line::GraphPc_Line(const GraphMapping* const & mapping, QGraphicsItem *pParentItem)
      : GraphBase(pParentItem)
      , m_pMapping(mapping)
      , m_pen(QBrush(), 2)
   {   
   }

   // -------------------------------------------------------------------------
   GraphPc_Line::~GraphPc_Line()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphPc_Line::paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Validate the pointer exists.
      Q_ASSERT( m_pMapping );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Draw the line
      painter->setPen( m_pen );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      m_path = QPainterPath(); // Only way to clear the old path.

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      if( !m_lstPoints.isEmpty() )
      {
         QListIterator<QPointF> i(m_lstPoints);
         m_path.moveTo( m_pMapping->mapPoint(i.next()) );
         while( i.hasNext() )
         {
            m_path.lineTo( m_pMapping->mapPoint(i.next()) );
         }
      }

      painter->drawPath( m_path );
   }


   // =========================================================================
   // Implementation Methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphPc_Line::setPoints( QList<QPointF> fListPoints )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Validate the pointer exists.
      Q_ASSERT( m_pMapping );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Save off the points
      m_lstPoints = fListPoints;

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      m_path = QPainterPath(); // Only way to clear the old path.


      std::cout << "Size=" << m_lstPoints.size() << std::endl;

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      if( !fListPoints.isEmpty() )
      {
         QListIterator<QPointF> i(fListPoints);
         m_path.moveTo( m_pMapping->mapPoint(i.next()) );
         while( i.hasNext() )
         {
            m_path.lineTo( m_pMapping->mapPoint(i.next()) );
         }
      }
   }

   // -------------------------------------------------------------------------
   QColor GraphPc_Line::getColor() const
   {
      return m_pen.color();
   }

   void GraphPc_Line::setColor( QColor color )
   {
      m_pen.setColor( color );
   }

}; //namespace
