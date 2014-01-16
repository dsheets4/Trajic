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
#include <QtGui/QPainter>

#include "TaxiVisConstants.h"
#include "Vis/GraphPc_Coord.h"


// ============================================================================
using namespace std;

namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPc_Coord::GraphPc_Coord(const GraphMapping* const & mapping, QGraphicsItem *pParentItem)
      : GraphBase(pParentItem)
      , m_pMapping(mapping)
      , m_sLabel("Label")
      , m_fCoordNum( 0.0f )
   {
   }

   // -------------------------------------------------------------------------
   GraphPc_Coord::~GraphPc_Coord()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphPc_Coord::paint(
      QPainter *painter,
      const QStyleOptionGraphicsItem *option,
      QWidget *widget)
   {
	   painter->setBrush( Qt::black );
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Draw the coordinate by requesting the min and max points for a 
      // vertical line at this coordinate's x value.
      QPointF ptTop = m_pMapping->mapPoint( m_fCoordNum, m_pMapping->getMinPtY() );
      QPointF ptBot = m_pMapping->mapPoint( m_fCoordNum, m_pMapping->getMaxPtY() );
	   painter->drawLine( ptTop, ptBot );
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Draw the label by calculating a label width distance on either side
      // of this coordinate and drawing the text in between.
      //!@todo Separate the labels into a separate object
      qreal fLabelWidth = m_pMapping->mapX(1) - m_pMapping->mapX(0);
      if( fLabelWidth > 40 )
      {
         QRectF rectLabel( ptTop.x()-(fLabelWidth/2), 0, fLabelWidth, 40 );
	      painter->drawText(rectLabel, Qt::AlignTop | Qt::AlignHCenter, m_sLabel);
      }
   }


   // =========================================================================
   // Implementation Methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QString GraphPc_Coord::getLabel() const
   {
      return m_sLabel;
   }

   void GraphPc_Coord::setLabel( QString sLabel )
   {
      m_sLabel = sLabel;
      setToolTip( sLabel );
   }
      
   // -------------------------------------------------------------------------
   qreal GraphPc_Coord::getCoordNum() const
   {
      return m_fCoordNum;
   }

   void GraphPc_Coord::setCoordNum( qreal fCoordNum )
   {
      m_fCoordNum = fCoordNum;
   }

}; //namespace