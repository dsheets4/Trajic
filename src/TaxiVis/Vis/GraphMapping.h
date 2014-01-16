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
#ifndef GraphMapping_H
#define GraphMapping_H

#include <QtCore/QRectF>
#include <QtCore/QPointF>

#include "CoordinateScale.h"


namespace Vis
{
   //! Defines the mapping of the plot area in a graph element so that 
   //! separate components can be coordinate on the same scale with less
   //! coupling.
   class GraphMapping
   {
   public:
      // ----------------------------------------------------------------------

      //! Default size for the margin.  Used to coordinate the code.
      static const qreal fDefaultMarginMax;


      // ----------------------------------------------------------------------

      //! Constructs an object with the given rectArea as the paintable area.
      //!
      //! @param rectArea  Total area applicable to the Graph.
      GraphMapping( CoordinateScale::Enum eScale );
      GraphMapping( const GraphMapping& orig, CoordinateScale::Enum eScale );
      GraphMapping( const GraphMapping& orig );
      virtual ~GraphMapping();
      

      // ----------------------------------------------------------------------

      void setRectFull( const QRectF& rect );
      const QRectF& getRectFull() const;
      
      const QRectF& getRectDraw() const;

      //! Sets the margin as a percentage of the total size of the graph.  A
      //! maximum size can be set, which is useful for larger graphs.
      //!
      //! @param fPercent  Percentage of the overall graph area to reserve 
      //!                  for margins.
      //! @param fMax      Maximum size for the margin.
      void setMargins( qreal fPercent, qreal fMax=fDefaultMarginMax );
      
      void setMaxPtX( qreal x );
      qreal getMaxPtX() const;

      void setMaxPtY( qreal y );
      qreal getMaxPtY() const;

      void setMinPtX( qreal x );
      qreal getMinPtX() const;

      void setMinPtY( qreal y );
      qreal getMinPtY() const;

      void setGain( qreal fGain );
      qreal getGain() const;

      void setOffset( qreal fOffset );
      qreal getOffset() const;

      CoordinateScale::Enum getCoordinateScale() const;

      
      // ----------------------------------------------------------------------
      
      //! Maps the given real values into screen coordinates for drawing.
      //!
      //! @param fX  Real x value
      //! @param fY  Real y value
      //!
      //! @retval  "Mapped Point"  QPointF of screen coordinates for drawing
      inline QPointF mapPoint( const QPointF& pt ) const
      {
         return QPointF( mapX(pt.x()), mapY(pt.y()) );
      }
      
      //! Maps the given real values into screen coordinates for drawing.
      //!
      //! @param fX  Real x value
      //! @param fY  Real y value
      //!
      //! @retval  "Mapped Point"  QPointF of screen coordinates for drawing
      inline QPointF mapPoint( qreal fX, qreal fY ) const
      {
         return QPointF( mapX(fX), mapY(fY) );
      }

      //! Maps the given real x value into screen coordinates for drawing.
      //!
      //! @param fX  Real x value
      //!
      //! @retval  "Screen mapping"  screen coordinates for drawing
      virtual qreal mapX( qreal fX ) const = 0;
      
      //! Maps the given real y value into screen coordinates for drawing.
      //!
      //! @param fY  Real y value
      //!
      //! @retval  "Screen mapping"  screen coordinates for drawing
      virtual qreal mapY( qreal fY ) const = 0;


   protected:
      // ----------------------------------------------------------------------
      inline qreal gainOffset(qreal fValue) const
      {
         return ((fValue*m_fGain)+m_fOffset);
      }

      // ----------------------------------------------------------------------
      QRectF     m_rectFull;       //!< Full allocated area
      QRectF     m_rectDraw;       //!< Full area minus margins
      QPointF    m_ptMax;          //!< Maximum x and y of graph values
      QPointF    m_ptMin;          //!< Minimum x and y of graph values
      qreal      m_fMarginPercent; //!< Left margin as percentage of draw area
      qreal      m_fMarginMax;     //!< Top margin as percentage of draw area
      qreal      m_fGain;          //!< Gain used in the coordinate mapping process
      qreal      m_fOffset;        //!< Offset used in the coordinate mapping process
      
      // ----------------------------------------------------------------------
      CoordinateScale::Enum  m_eCoordScale; //!< Coordinate scale mapping in use
      
   };

}; //namespace

#endif // GraphMapping_H
