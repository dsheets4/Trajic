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

#include <QtScript/QScriptEngine>

#include "Vis/GraphBaseDispatch.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphBaseDispatch::GraphBaseDispatch(QObject *pParent)
      : QObject(pParent)
   {
   }
   
   // -------------------------------------------------------------------------
   GraphBaseDispatch::GraphBaseDispatch(const GraphBaseDispatch& orig)
      : QObject(0)
      , m_pGfx(orig.m_pGfx)
   {
   }

   // -------------------------------------------------------------------------
   GraphBaseDispatch::~GraphBaseDispatch()
   {
   }
   
   // =========================================================================
   // Operators
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphBaseDispatch& GraphBaseDispatch::operator=( const GraphBaseDispatch& rhs )
   {
      if( this != &rhs )
      {
         m_pGfx = rhs.m_pGfx;
      }

      return *this;
   }
   
   // =========================================================================
   // Implementation
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphBaseObjWrapPtr GraphBaseDispatch::getGraphObjWrap()
   {
      return m_pGfx;
   }

   void GraphBaseDispatch::setGraphObjWrap( GraphBaseObjWrapPtr pGfx )
   {
      m_pGfx = pGfx;
   }


   // =========================================================================
   // Slots
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphBaseDispatch::setPosition( qreal x, qreal y)
   {
      emit setPositionSignal(x,y);
   }

   void GraphBaseDispatch::setSize( qreal fHeight, qreal fWidth)
   {
      emit setSizeSignal(fHeight, fWidth);
   }
   
}; //namespace