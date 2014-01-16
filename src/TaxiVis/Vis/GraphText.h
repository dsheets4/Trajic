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
#ifndef GraphText_H
#define GraphText_H

#include <QtGui/QPen>

#include "Vis/GraphBase.h"


namespace Vis
{
   //! Represents a bar graph.
   class GraphText : public GraphBase
   {		
   public:
      // ----------------------------------------------------------------------
      GraphText(QGraphicsItem* pParentItem=0);
      ~GraphText();


      // ----------------------------------------------------------------------
      // QGraphics Item implementation.
      
      void paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget);


      // ----------------------------------------------------------------------
      // Additional implementation.

      //! Creates and then adds a bar item to the bar graph.
      QString getText() const;
      
      //! Sets the text to be displayed.  Text will be drawn centered and at
      //! the top of the allocated size.
      //!
      //! @param sText  Text to draw for this graphical item
      void setText( QString sText );
      
      QColor getColor( ) const;
      
      //! Sets the color of the text.
      //!
      //! @param color  Color to make the text
      void setColor( QColor color );
      
      qreal getWidth( ) const;
      
      //! Sets the width of the text.
      //!
      //! @param fWidth  Width of the text.
      void setWidth( qreal fWidth );


   protected:
      // ----------------------------------------------------------------------
      QString m_sText;      //!< Text displayed by this object
      QPen    m_pen;        //!< QPen used to draw the text
   };
}; //namespace

#endif // GraphText_H
