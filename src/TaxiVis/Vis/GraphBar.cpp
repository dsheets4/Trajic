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
#include "Vis/GraphBar.h"


// ============================================================================
using namespace std;

namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphBar::GraphBar(QGraphicsItem *pParentItem)
      : GraphBase(pParentItem)
   {   
   }

   // -------------------------------------------------------------------------
   GraphBar::~GraphBar()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphBar::paint(
      QPainter *painter,
      const QStyleOptionGraphicsItem *option,
      QWidget *widget)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      double fScale = 100.0; //!< @todo Make scale be a passed in value.

#ifdef _DEBUG
      painter->drawRect(m_rect);
#endif // _DEBUG

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      //
      if( m_bars.size() > 0 )
      {
         QPointF p(0,0);
         QMapIterator<double,GraphBarItem*> i(m_bars);
         double fBarWidth = m_rect.width() / m_bars.size();
         while( i.hasNext() )
         {
            i.next();

            // Shift the bars so they appear side by side.
            i.value()->setOffsetPoint( p );
            p.setX( p.x()+i.value()->boundingRect().width() );

            // Update the width of the bar so they fill the whole space.
            QRectF rect = i.value()->boundingRect();
            rect.setWidth( fBarWidth );
            i.value()->setSize( rect );
         }
      }
   }


   // =========================================================================
   // Implementation Methods
   // =========================================================================

   // -------------------------------------------------------------------------   
   void GraphBar::createBar( double fValue, const QColor& color )
   {
      GraphBarItem* item = new GraphBarItem(this);
      item->setValue( fValue );
      item->setColor( color );

      addBarItem( item );
   }

   // -------------------------------------------------------------------------
   void GraphBar::addBarItem( GraphBarItem* barItem )
   {
      //! @todo Is there a way to use the default QGraphics management to 
      //!       track and update the children?
      m_bars.insert( m_bars.size(), barItem );
      barItem->setParentItem(this);
   }

}; //namespace