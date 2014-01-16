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
#ifndef GraphPc_Coord_H
#define GraphPc_Coord_H

#include <QtGui/QPen>

#include "Vis/GraphMapping.h"
#include "Vis/GraphBase.h"


namespace Vis
{
   //! Represents a bar graph.
   class GraphPc_Coord : public GraphBase
   {		
   public:
      // ----------------------------------------------------------------------
      GraphPc_Coord(const GraphMapping* const & mapping, QGraphicsItem* pParentItem=0);
      ~GraphPc_Coord();


      // ----------------------------------------------------------------------
      // QGraphics Item implementation.
      
      void paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget);


      // ----------------------------------------------------------------------
      // Additional implementation.

      QString getLabel() const;
      void setLabel( QString sLabel );
      
      qreal getCoordNum() const;
      void setCoordNum( qreal fCoordNum );

      //!@todo Add the ability to hide a coordinate so that it's possible to 
      //!      manipulate whether the coordinate is drawn or not.


   protected:
      // ----------------------------------------------------------------------
      const GraphMapping* const & m_pMapping; //!< Maps values to scene coordinates
      
      // ----------------------------------------------------------------------
      QString m_sLabel;       //!< Label associated with the coordinate
      qreal   m_fCoordNum;    //!< X value for the coordinate.

   };
}; //namespace

#endif // GraphPc_Coord_H
