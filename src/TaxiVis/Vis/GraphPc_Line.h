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
#ifndef GraphPc_Line_H
#define GraphPc_Line_H

#include <QtGui/QPen>

#include "Vis/GraphMapping.h"
#include "Vis/GraphBase.h"


namespace Vis
{
   //! Represents a bar graph.
   class GraphPc_Line : public GraphBase
   {		
   public:
      // ----------------------------------------------------------------------
      GraphPc_Line(const GraphMapping* const & mapping, QGraphicsItem* pParentItem=0);
      ~GraphPc_Line();


      // ----------------------------------------------------------------------
      // QGraphics Item implementation.
      
      void paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget);


      // ----------------------------------------------------------------------
      // Additional implementation.

      //! Adds the points corresponding to the coordinates that represent a 
      //! line in the parallel coordinate graph item.
      //!
      //! @param fListValues List with size matching the number of coordinates
      //!                    and containing the desired values for the line.
      void setPoints( QList<QPointF> fListValues );

      QColor getColor() const;
      void setColor( QColor color );


   protected:
      // ----------------------------------------------------------------------
      const GraphMapping* const & m_pMapping; //!< Maps values to scene coordinates
      
      // ----------------------------------------------------------------------
      QList<QPointF>  m_lstPoints;  //!< Points constructing the line

      // ----------------------------------------------------------------------
	   QPainterPath m_path;  //!< Path for this line.
      QPen         m_pen;   //!< Pen used to draw the line.
   };
}; //namespace

#endif // GraphPc_Line_H
