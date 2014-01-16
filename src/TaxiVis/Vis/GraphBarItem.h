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
#ifndef GRAPHBARITEM_H
#define GRAPHBARITEM_H

#include <QtGui/QPen>

#include "Vis/GraphBase.h"


namespace Vis
{
   //! Represents the Ring Map overlay.
   class GraphBarItem : public GraphBase
   {		
   public:
      // ----------------------------------------------------------------------
      GraphBarItem(QGraphicsItem* pParentItem);
      ~GraphBarItem();


      // ----------------------------------------------------------------------
      // QGraphics Item implementation.
      
      void paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget);


      // ----------------------------------------------------------------------
      // Additional implementation.
      double getValue();
      void setValue(double fValue);

      //! Sets the pen used to draw the bar.
      void setPen( const QPen& pen );

      //! Sets the color used to fill the bar.
      void setFillGradient( const QColor& color1, const QColor& color2 );
      void setColor( const QColor& color );

      void setOffsetPoint( const QPointF& p );
      

   protected:
      // ----------------------------------------------------------------------
      QPointF  m_offset;     //!< Offset driven by the bar graph
      QPen     m_pen;        //!< Pen used to draw this item
      QColor   m_color1;     //!< Gradient color 1
      QColor   m_color2;     //!< Gradient color 2
   };
}; //namespace

#endif // GRAPHBARITEM_H
