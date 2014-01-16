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
#include <QtGui/QGraphicsScene>
#include <QtGui/QPainter>

#include "TaxiVisConstants.h"
#include "Vis/GraphMappingLinear.h"
#include "Vis/GraphMappingLog10Y.h"
#include "Vis/GraphPc.h"


// ============================================================================
using namespace std;

namespace Vis
{
   // =========================================================================
   // Constants
   // =========================================================================
   static const qreal fLeftRightMargin = 0.5;

   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPc::GraphPc(QGraphicsItem *pParentItem)
      : GraphBase(pParentItem)
      , m_pMapping(NULL)
      , m_penLine(QBrush(QColor(0,0,0,255)), 1.0)
      , m_penBckgrd(QBrush(QColor(255,255,255,255)), 1.0)
   {
      // Default linear scale.
      setCoordinateScale( CoordinateScale::Linear );
   }

   // -------------------------------------------------------------------------
   GraphPc::~GraphPc()
   {
      delete m_pMapping;
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphPc::paint(
      QPainter *painter,
      const QStyleOptionGraphicsItem *option,
      QWidget *widget)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Class should maintain a valid mapping at all times.
      Q_ASSERT( m_pMapping );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Draw the background using a gradient.
      const int GradDist = 64;
      QColor color = m_penBckgrd.color();
      color.setRed  ( (color.red()>GradDist)
         ? color.red()-GradDist   : color.red()+GradDist );
      color.setGreen( (color.green()>GradDist)
         ? color.green()-GradDist : color.green()+GradDist );
      color.setBlue ( (color.blue()>GradDist)
         ? color.blue()-GradDist  : color.blue()+GradDist );

      QLinearGradient gradient(
         m_pMapping->getRectFull().width()/2.0, 0,
         m_pMapping->getRectFull().width()/2.0, m_pMapping->getRectFull().height() );
      gradient.setColorAt(0, m_penBckgrd.color());
      gradient.setColorAt(1, color);
      painter->setPen( m_penBckgrd );
      painter->setBrush( QBrush(gradient) );
      painter->drawRect( m_pMapping->getRectFull() );
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      //!@todo This draws horizontal axis markers for the parallel 
      //!      coordinates.  Migrate this to its own class for the labels
      //!      and axes.
      QPointF ptLeft;
      QPointF ptRight;      
      qreal fMultiplier = 100000000;
      qreal fValue = 0.0000001;
      qreal fIncrement = 0;
      qreal fDrawValue;
      painter->setPen( Qt::gray );

      //
      for( int i = 1; i < 10; i++ )
      {
         fIncrement = fValue;

         for( int j = 1; j <= 10; j++ )
         {
            fValue = j*fIncrement;
            fDrawValue = fValue*fMultiplier;
            if( fDrawValue > m_pMapping->getMaxPtY() )
            {
               break;
            }
            ptLeft = m_pMapping->mapPoint( m_pMapping->getMinPtX(), fDrawValue );
            ptRight = m_pMapping->mapPoint( m_pMapping->getMaxPtX(), fDrawValue );
            painter->drawLine( ptLeft, ptRight );

            if( (j % 10) == 0 )
            {
	            painter->drawText( ptLeft, QString::number(fValue, 'f') );
            }
         }
      }
   }
   
   // =========================================================================
   // GraphBase overrides
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphPc::setSize( const QRectF& rect )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Class should maintain a valid mapping at all times.
      Q_ASSERT( m_pMapping );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphBase::setSize( rect );
      m_pMapping->setRectFull( m_rect );
   }
   
   // -------------------------------------------------------------------------
   void GraphPc::setCoordinateScale( CoordinateScale::Enum eCoordScale )
   {
      //! @todo The approach to swapping out the GraphMapping is causing 
      //!        crashes on Linux.  Change the approach so that it 
      //!        does something more robust than using a pointer reference...

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // First, check to see if the requested scale is the current scale.
      if( m_pMapping && m_pMapping->getCoordinateScale() == eCoordScale )
         return;
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Release any current mapping object.
      GraphMapping* pPrevious = m_pMapping;
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Allocate the new GraphMapping related to the new scale.
      switch( eCoordScale )
      {
      case CoordinateScale::Log10Y:
         if( pPrevious )
            m_pMapping = new GraphMappingLog10Y(*pPrevious);
         else
            m_pMapping = new GraphMappingLog10Y();
         break;

      case CoordinateScale::Linear:
      default:
         if( pPrevious )
            m_pMapping = new GraphMappingLinear(*pPrevious);
         else
            m_pMapping = new GraphMappingLinear();
      }
      delete pPrevious;
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Minimum x point is always zero.
      m_pMapping->setMinPtX( 0 );
   }
   
   // -------------------------------------------------------------------------
   void GraphPc::setGain( double fGain )
   {
      m_pMapping->setGain( fGain );
   }

   // -------------------------------------------------------------------------
   void GraphPc::setOffset( double fOffset )
   {
      m_pMapping->setOffset( fOffset );
   }
   
   // -------------------------------------------------------------------------
   void GraphPc::resize( const QSize& size )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Class should maintain a valid mapping at all times.
      Q_ASSERT( m_pMapping );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Update the mapping area so things resize.
      m_pMapping->setRectFull( m_rect );
   }


   // =========================================================================
   // Implementation Methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void GraphPc::setYMax( double fYMax )
   {
      if( m_pMapping->getMinPtY() < fYMax )
      {
         m_pMapping->setMaxPtY( fYMax );
      }
   }
      
   // -------------------------------------------------------------------------
   void GraphPc::setYMin( double fYMin )
   {
      if( m_pMapping->getMaxPtY() > fYMin )
      {
         m_pMapping->setMinPtY( fYMin );
      }
   }

   // -------------------------------------------------------------------------
   QColor GraphPc::getBackgroundColor( ) const
   {
      return m_penBckgrd.color();
   }

   void GraphPc::setBackgroundColor( QColor color )
   {
      m_penBckgrd.setColor( color );
   }
      
   // -------------------------------------------------------------------------
   void GraphPc::addCoordinate( QString sLabel )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Class should maintain a valid mapping at all times.
      Q_ASSERT( m_pMapping );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      GraphPc_Coord *pCoord = new GraphPc_Coord(m_pMapping, this);
      
      pCoord->setZValue(1);  // Coordinates draw on top.
      pCoord->setLabel( sLabel );

      m_lstCoords.append( pCoord );
      pCoord->setCoordNum( m_pMapping->getMaxPtX()+fLeftRightMargin );
      m_pMapping->setMaxPtX( m_pMapping->getMaxPtX()+fLeftRightMargin*2 );
   }
   
   // -------------------------------------------------------------------------
   void GraphPc::removeCoordinate( int nIndex )
   {
      //!@todo Implement the parallel coordinates function to remove a 
      //!      coordinate.
   }
  
   // -------------------------------------------------------------------------
   void GraphPc::removeAllCoordinates()
   {
      removeAllLines();

      QListIterator<QGraphicsItem*> i( this->childItems() );
      while( i.hasNext() )
      {
         QGraphicsItem *item = i.next();

         item->setParentItem(NULL);
         scene()->removeItem(item);
      }
   }
      
   // -------------------------------------------------------------------------
   void GraphPc::addLine( QVariantList fListValues, QColor color )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Class should maintain a valid mapping at all times.
      Q_ASSERT( m_pMapping );

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // If the number of values and coordinates don't match, there's an 
      // issue with the setup.  Remember to create coordinates first.
      //!@todo Since addLine is exposed to the scripting language the assert
      //!      test isn't really valid.  This method needs to have an actual
      //!      test and the ability to provide feedback to the scripting
      //!      language.  While non-ideal, if the script prototype implemented
      //!      the check that might work as well.
      Q_ASSERT( fListValues.size() == m_lstCoords.size() );
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      //! @todo Use the Chart Mapping here by expanding the min and max of the 
      //!       X coordinate so that zero maps to the first coordinate, one to
      //!       the second coordinate, and so on.  The coordinate mapping will
      //!       then have a min and max value to map the values into screen
      //!       coordinates.  A similar concept will apply to the lines.  This
      //!       way all of the logic to determine the screen coordinates can be
      //!       done by the class drawing the particular line rather than 
      //!       propagating up to this level to be coordinated.
      QList<QPointF> lstPoints;
      QPointF p(-fLeftRightMargin,0); // Subtract since points add them in double.
      GraphPc_Line *pLine = new GraphPc_Line(m_pMapping,this);
      QListIterator<QVariant> i(fListValues);
      int iCoord = 0;
      while( i.hasNext() )
      {
         const QVariant& v = i.next();

         p.setX( p.x()+fLeftRightMargin*2 );
         p.setY( v.toReal() );
         
         if( m_pMapping->getMaxPtY() < v.toReal() )
         {
            m_pMapping->setMaxPtY( v.toReal() );
         }
         if( m_pMapping->getMinPtY() > v.toReal() )
         {
            m_pMapping->setMinPtY( v.toReal() );
         }
         
         lstPoints.append( p );

         iCoord++;
      }

      pLine->setPoints( lstPoints );
      pLine->setColor( color );

      m_lstLines.append( pLine );
   }
   
   // -------------------------------------------------------------------------
   void GraphPc::removeAllLines( )
   {
      //!@todo Implement the parallel coordinates method to remove all lines.
   }

}; //namespace