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
#include <QtGui/QTextOption>

#include "TaxiVisConstants.h"
#include "Vis/GraphText.h"


// ============================================================================
using namespace std;

namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphText::GraphText(QGraphicsItem *pParentItem)
      : GraphBase(pParentItem)
      , m_pen(QBrush(QColor(0,0,0,255)), 1.0)
   {   
   }

   // -------------------------------------------------------------------------
   GraphText::~GraphText()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphText::paint(
      QPainter *painter,
      const QStyleOptionGraphicsItem *option,
      QWidget *widget)
   {
#if 0
#ifdef _DEBUG
      painter->save();
      painter->setPen( QPen(QBrush(QColor(0,0,0,128)), 1.0) );
      painter->drawRect( m_rect );
      painter->restore();
#endif
#endif
      
      painter->setPen( m_pen );
      QTextOption textOption;
      textOption.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      painter->drawText( m_rect, m_sText, textOption );
   }


   // =========================================================================
   // Implementation Methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QString GraphText::getText( ) const
   {
      return m_sText;
   }

   void GraphText::setText( QString sText )
   {
      m_sText = sText;
   }
   
   // ------------------------------------------------------------------------- 
   QColor GraphText::getColor( ) const
   {
      return m_pen.color();
   }

   void GraphText::setColor( QColor color )
   {
      m_pen.setColor(color);
   }
   

   // -------------------------------------------------------------------------  
   qreal GraphText::getWidth( ) const
   {
      return m_pen.widthF();
   }

   void GraphText::setWidth( qreal fWidth )
   {
      m_pen.setWidthF( fWidth );
   }

}; //namespace