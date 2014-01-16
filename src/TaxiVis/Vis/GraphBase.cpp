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

#include <QtGui/QPainter>

#include "Vis/GraphBase.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphBase::GraphBase(QGraphicsItem *pParentItem)
      : QGraphicsItem(pParentItem)
      , m_rect(QRectF(0,0,50,50))
   {
   }

   // -------------------------------------------------------------------------
   GraphBase::GraphBase(const GraphBase& orig)
      : QGraphicsItem(0)
      , m_rect( orig.getSize() )
   {
   }

   // -------------------------------------------------------------------------
   GraphBase::~GraphBase()
   {
   }


   // =========================================================================
   // Overridden methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QRectF GraphBase::boundingRect() const
   {
      //! @todo The GraphBase boundingRect seems to be off since the scene doesn't
      //!       redraw the items added to the ring map properly.  It might be
      //!       due to the scale that the ring map imposes and the 
      //!       boundingRect not accounting for it.
      return m_rect;
   }
  
   // -------------------------------------------------------------------------
   void GraphBase::paint(
      QPainter *painter,
      const QStyleOptionGraphicsItem *option,
      QWidget *widget)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      painter->drawRect( m_rect );

      QRectF rectQuad1(m_rect.left(), m_rect.top(), m_rect.width()/2.0, m_rect.height()/2.0);
      painter->drawRect( rectQuad1 );

      QRectF rectQuad3(m_rect.center().x(), m_rect.center().y(), m_rect.width()/2.0, m_rect.height()/2.0 );
      painter->drawRect( rectQuad3 );
   }


   // =========================================================================
   // Implementation Methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphBase::setSize( const QRectF& rect )
   {
      m_rect = rect;
   }

   const QRectF& GraphBase::getSize() const
   {
      return m_rect;
   }
   
   // -------------------------------------------------------------------------
   void GraphBase::resize( const QSize& size )
   {
   }


   // =========================================================================
   // Operators
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphBase& GraphBase::operator=( const GraphBase &rhs )
   {
      if( this != &rhs )
      {
         m_rect = rhs.m_rect;
      }

      return *this;
   }

}; //namespace