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

#include "Vis/GraphMapping.h"


namespace Vis
{
   // =========================================================================
   // Constants
   // =========================================================================
   const qreal GraphMapping::fDefaultMarginMax = 20.0f;


   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphMapping::GraphMapping( CoordinateScale::Enum eScale )
      : m_rectFull( 0.0f, 0.0f, 1.0f, 1.0f )
      , m_rectDraw( 0.0f, 0.0f, 1.0f, 1.0f )
      , m_ptMax( 0.0f, 0.0f )
      , m_ptMin( 0.0f, 0.0f )
      , m_fMarginPercent( 0.5f )
      , m_fMarginMax( fDefaultMarginMax )
      , m_eCoordScale(eScale)
      , m_fGain( 1.0 )
      , m_fOffset( 0.0 )
   {
   }

   // -------------------------------------------------------------------------
   GraphMapping::GraphMapping( const GraphMapping& orig, CoordinateScale::Enum eScale )
      : m_rectFull( orig.m_rectFull )
      , m_rectDraw( orig.m_rectDraw )
      , m_ptMax( orig.m_ptMax )
      , m_ptMin( orig.m_ptMin )
      , m_fMarginPercent( orig.m_fMarginPercent )
      , m_fMarginMax( orig.m_fMarginMax )
      , m_eCoordScale(eScale)
      , m_fGain( 1.0 )
      , m_fOffset( 0.0 )
   {
   }

   // -------------------------------------------------------------------------
   GraphMapping::GraphMapping( const GraphMapping& orig )
      : m_rectFull( orig.m_rectFull )
      , m_rectDraw( orig.m_rectDraw )
      , m_ptMax( orig.m_ptMax )
      , m_ptMin( orig.m_ptMin )
      , m_fMarginPercent( orig.m_fMarginPercent )
      , m_fMarginMax( orig.m_fMarginMax )
      , m_eCoordScale( orig.m_eCoordScale )
      , m_fGain( orig.m_fGain )
      , m_fOffset( orig.m_fOffset )
   {
   }


   // -------------------------------------------------------------------------
   GraphMapping::~GraphMapping()
   {
   }
   

   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void GraphMapping::setRectFull( const QRectF& rect )
   {
      m_rectFull = rect;
      setMargins( m_fMarginPercent, m_fMarginMax );
   }

   const QRectF& GraphMapping::getRectFull() const
   {
      return m_rectFull;
   }
   
   // -------------------------------------------------------------------------
   const QRectF& GraphMapping::getRectDraw() const
   {
      return m_rectDraw;
   }
   
   // -------------------------------------------------------------------------
   void GraphMapping::setMargins( qreal fPercent, qreal fMax )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Save off the settings.
      m_fMarginPercent = fPercent;
      m_fMarginMax     = fMax;
            
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Calculate the new margins by first setting the draw area to the full
      // area and then calculating the distance for each margin.  Then adjust
      // the draw area rectangle and move it to provide the margins.
      // Negative values are passed to the right and bottom to shrink the area.
      m_rectDraw = m_rectFull;
      qreal fLeftRightMargin = m_rectFull.width()  * m_fMarginPercent;
      qreal fTopBottomMargin = m_rectFull.height() * m_fMarginPercent;
      m_rectDraw.adjust( 
         ((fLeftRightMargin < m_fMarginMax) ?  fLeftRightMargin :  m_fMarginMax),
         ((fTopBottomMargin < m_fMarginMax) ?  fTopBottomMargin :  m_fMarginMax),
         ((fLeftRightMargin < m_fMarginMax) ? -fLeftRightMargin : -m_fMarginMax),
         ((fTopBottomMargin < m_fMarginMax) ? -fTopBottomMargin : -m_fMarginMax));
   }
   
   // -------------------------------------------------------------------------
   void GraphMapping::setMaxPtX( qreal x )
   {
      m_ptMax.setX( x );
   }
   
   qreal GraphMapping::getMaxPtX() const
   {
      return m_ptMax.x();
   }
   
   // -------------------------------------------------------------------------
   void GraphMapping::setMaxPtY( qreal y )
   {
      m_ptMax.setY( y );
   }
   
   qreal GraphMapping::getMaxPtY() const
   {
      return gainOffset(m_ptMax.y());
   }
   
   // -------------------------------------------------------------------------
   void GraphMapping::setMinPtX( qreal x )
   {
      m_ptMin.setX( x );
   }
   
   qreal GraphMapping::getMinPtX() const
   {
      return m_ptMin.x();
   }
   
   // -------------------------------------------------------------------------
   void GraphMapping::setMinPtY( qreal y )
   {
      m_ptMin.setY( y );
   }
   
   qreal GraphMapping::getMinPtY() const
   {
      return gainOffset(m_ptMin.y());
   }
   
   // -------------------------------------------------------------------------
   void GraphMapping::setGain( qreal fGain )
   {
      m_fGain = fGain;
   }
   
   qreal GraphMapping::getGain() const
   {
      return m_fGain;
   }
   
   // -------------------------------------------------------------------------
   void GraphMapping::setOffset( qreal fOffset )
   {
      m_fOffset = fOffset;
   }
   
   qreal GraphMapping::getOffset() const
   {
      return m_fOffset;
   }
   
   // -------------------------------------------------------------------------
   CoordinateScale::Enum GraphMapping::getCoordinateScale() const
   {
      return m_eCoordScale;
   }
      
}; //namespace