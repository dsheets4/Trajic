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

#include <QtCore/QEventLoop>
#include <QtCore/QThread>

#include "Vis/GraphFactory.h"
#include "Vis/GraphBaseObjWrap.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphBaseObjWrap::GraphBaseObjWrap(QObject *pParent)
      : QObject( pParent )
      , m_pGfx( new GraphBase() )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphBaseObjWrap::GraphBaseObjWrap(GraphBase* pGfx, QObject *pParent)
      : QObject( pParent )
      , m_pGfx( pGfx )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphBaseObjWrap::GraphBaseObjWrap(const GraphBaseObjWrap& orig)
      : QObject(0)
      , m_pGfx( orig.m_pGfx )
   {
   }

   // -------------------------------------------------------------------------
   GraphBaseObjWrap::~GraphBaseObjWrap()
   {
      //!@todo There is a memory leak if the wrapped object is created and 
      //!      never assigned a parent object.  This is because the Qt 
      //!      framework doesn't have the object connected in order to free
      //!      the memory.  Until the object is actually used, it needs to be
      //!      managed by the wrapper.  However, the wrapper doesn't know when
      //!      the object it is wrapping is given a parent as the wrapped 
      //!      object may or may not already have a parent when the wrapper is
      //!      created.
      //!      In addition, this class wraps QGraphicItems which aren't 
      //!      parented by QObjects.  Therefore, we can't simply integrated
      //!      with the Qt parent child interaction.
   }

      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphBase* GraphBaseObjWrap::getGraph() const
   {
      return m_pGfx;
   }

   void GraphBaseObjWrap::setGraph( GraphBase* pGfx )
   {      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      m_pGfx = pGfx;
   }
   
   // -------------------------------------------------------------------------
   void GraphBaseObjWrap::setPosition( qreal x, qreal y)
   {      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Set the position of the object but maintain the height and width.
      QRectF fRect = m_pGfx->getSize();
      qreal fHeight = fRect.height();
      qreal fWidth  = fRect.width();
      fRect.setX(x);
      fRect.setY(y);
      fRect.setHeight(fHeight);
      fRect.setWidth(fWidth);
      m_pGfx->setSize(fRect);
   }
      
   // -------------------------------------------------------------------------
   void GraphBaseObjWrap::setSize( qreal fHeight, qreal fWidth)
   {      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      QRectF fRect = m_pGfx->getSize();
      fRect.setHeight(fHeight);
      fRect.setWidth(fWidth);
      m_pGfx->setSize(fRect);
   }
   
   
   // =========================================================================
   // Operators
   // =========================================================================
      
   // -------------------------------------------------------------------------
   GraphBaseObjWrap& GraphBaseObjWrap::operator=( const GraphBaseObjWrap &rhs )
   {
      if( this != &rhs )
      {
         this->m_pGfx = rhs.m_pGfx;
      }

      return *this;
   }
   
}; //namespace