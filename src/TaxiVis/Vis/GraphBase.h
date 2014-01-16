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
#ifndef GraphBase_H
#define GraphBase_H

#include <QtGui/QGraphicsItem>

#include "TaxiVisUtils.h"


namespace Vis
{
   //! Represents a base graph object.
   class GraphBase : public QGraphicsItem
   {
   public:
      // ----------------------------------------------------------------------
      // Construction and Destruction

      GraphBase( QGraphicsItem* pParentItem=0 );
      GraphBase( const GraphBase& orig );
      virtual ~GraphBase();


      // ----------------------------------------------------------------------
      // QGraphicsItem implementation.

      virtual QRectF boundingRect() const;
      
      void paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget);


      // ----------------------------------------------------------------------
      // Additional implementation.
      
      //! Sets the size of the graphic in screen coordinates.  Using negative
      //! numbers for height will flip the object vertically (i.e. draw it 
      //! upside down).  Negative numbers for width will flip the object 
      //! horizontally (i.e. draw a mirror image).  Also not that negative 
      //! numbers will cause the object to draw above or to the left of the
      //! position for height and width respectively.
      //!
      //! @param rect  Rectangle representing the desired height and width
      virtual void setSize( const QRectF& rect );

      virtual const QRectF& getSize() const;

      //! Called when the GraphBase object is being resized.
      //!
      //! @param size  New size (height and width) of the graphical object.
      virtual void resize( const QSize& size );

      
      // ----------------------------------------------------------------------
      // Operators

      GraphBase& operator=( const GraphBase &rhs );


   protected:
      // ----------------------------------------------------------------------
      QRectF     m_rect;   //!< Defines the position of the graph.
   };
}; //namespace

#endif // GraphBase_H
