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
#ifndef GraphPc_H
#define GraphPc_H

#include <QtGui/QPen>

#include "Vis/GraphMapping.h"
#include "Vis/GraphBase.h"
#include "Vis/GraphPc_Coord.h"
#include "Vis/GraphPc_Line.h"


namespace Vis
{
   //! Represents a bar graph.
   class GraphPc : public GraphBase
   {		
   public:
      // ----------------------------------------------------------------------
      GraphPc(QGraphicsItem* pParentItem=0);
      ~GraphPc();


      // ----------------------------------------------------------------------
      // QGraphics Item implementation.
      
      void paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget);
      

      // ----------------------------------------------------------------------
      // GraphBase overrides
      void setSize( const QRectF& rect );
   
      void resize( const QSize& size );


      // ----------------------------------------------------------------------
      // Additional implementation.
      QColor getBackgroundColor() const;
      void setBackgroundColor( QColor color );
      
      void setCoordinateScale( CoordinateScale::Enum eCoordScale );
      void setGain( double fGain );
      void setOffset( double fOffset );

      
      void setYMax( double fYMax );
      
      void setYMin( double fYMin );
      
      //! Adds a new parallel coordinate to the graph.  The coordinates are the 
      //! vertical bars that represent a parameter.
      //!
      //! @param sLabel Label associated with the coordinate.  Note that if the 
      //!               available space is limited the label will be omitted to
      //!               make more room for the actual polylines.
      void addCoordinate( QString sLabel );
      
      //! Removes a specific coordinated associated with the index from the 
      //! graph.  The index maps to the zero-based order in which the 
      //! coordinates are drawn.  The point associated with this coordinate
      //! will also be removed.
      //!
      //! @param nIndex  Zero-based index in the draw order representing the 
      //!                coordinate to remove.
      void removeCoordinate( int nIndex );
      
      //! Removes all coordinates from the parallel coordinates graph.  
      //! By extension this will also remove all the lines.
      void removeAllCoordinates();
      
      //! Adds a line to the parallel coordinates graph.  The line must 
      //! contain the same number of points as there are coordinates.  
      //! Therefore, be sure to call addCoordinate for every coordinate that 
      //! is needed before adding the first line.
      //!
      //! @param fListValues   List of points representing a line drawn from 
      //!                      one coordinate to the next.  Size of the list 
      //!                      must match the number of coordinates.
      //! @param color         Color for the line, including transparency.
      void addLine( QVariantList fListValues, QColor color );
      
      //! Removes all lines from the parallel coordinates.
      void removeAllLines( );

      //!@todo Add the ability to order the coordinates so that they can be
      //!      reorganized to find various patterns in the data.


   protected:      
      // ----------------------------------------------------------------------
      GraphMapping*  m_pMapping;  //!< Maps values to scene coordinates

      // ----------------------------------------------------------------------
	   QList<GraphPc_Coord*> m_lstCoords; //!< Coordinates for the graph
	   QList<GraphPc_Line*>  m_lstLines;  //!< Lines in the graph
      
      // ----------------------------------------------------------------------
      QPen   m_penLine;    //!< Pen used to draw the lines
      QPen   m_penBckgrd;  //!< Pen used to draw the background
   };
}; //namespace

#endif // GraphPc_H
