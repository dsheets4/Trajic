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
#ifndef GRAPHBAR_H
#define GRAPHBAR_H

#include "Vis/GraphBase.h"
#include "Vis/GraphBarItem.h"


namespace Vis
{
   //! Represents a bar graph.
   class GraphBar : public GraphBase
   {		
   public:
      // ----------------------------------------------------------------------
      GraphBar(QGraphicsItem* pParentItem=0);
      ~GraphBar();


      // ----------------------------------------------------------------------
      // QGraphics Item implementation.
      
      void paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget);


      // ----------------------------------------------------------------------
      // Additional implementation.
      
      //! Adds a bar to the bar graph.
      //!
      //! @param fValue        Value associated with this bar.  The bar graph 
      //!                      will scale all the bars according to the 
      //!                      largest value.
      //! @param color         Color to make the bar, including transparency
      void createBar( double fValue, const QColor& color );

      //! Adds the bar item to the bar graph.
      //!
      //! @param barItem  GraphBarItem to add to the bar graph
      void addBarItem( GraphBarItem* barItem );


   protected:
      // ----------------------------------------------------------------------
      QMap<double,GraphBarItem*> m_bars;      //!< Bars that are part of the graph
   };
}; //namespace

#endif // GRAPHBAR_H
