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

#include "Vis/GraphPie.h"


namespace Vis
{
   // =========================================================================
   // Private Implementation
   // =========================================================================
   class GraphPieImpl
   {
   public:
      
      // ----------------------------------------------------------------------
      GraphPieImpl()
         : m_fTotal(0)
      {;}
      
      // ----------------------------------------------------------------------
      QMap<double,QColor>  m_mapSlices;
      double               m_fTotal;
   };


   // =========================================================================
   // Construction and Destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPie::GraphPie( QGraphicsItem* pParent )
      : GraphBase(pParent)
      , m_pImpl(new GraphPieImpl)
   {
   }

   // -------------------------------------------------------------------------
   GraphPie::~GraphPie()
   {
      delete m_pImpl;
      m_pImpl = NULL;
   }


   // =========================================================================
   // QGraphicsItem implementation.
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void GraphPie::paint(
      QPainter *painter,
      const QStyleOptionGraphicsItem *option,
      QWidget *widget)
   {
      Q_ASSERT(m_pImpl);

#ifdef IconGen_EXPORTS
      // Note! This is only an issue with the IconGen project.
      //! @todo When a transform is applied it locks shapes into place.  Since
      //!       most of the items drawn use a transform one is added here to 
      //!       maintain alignment.  I need to figure out how to allow the 
      //!       shape to move.
      QTransform trans;
      painter->setTransform(trans);
#endif
      
#ifdef _DEBUG
      painter->drawEllipse(m_rect);
#endif // _DEBUG     

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      const int GradDist = 80;
      QRadialGradient gradient(m_rect.center(), m_rect.width()/2);
   
      double nTotalRotation = 90.0;
      double nCurrentSpan = 0.0;
      QMapIterator<double,QColor> i(m_pImpl->m_mapSlices);
      while( i.hasNext() )
      {
         i.next();

         // Set up a gradient for the pie slices.
         QColor color0(i.value());
         QColor color1(i.value());
         color1.setRed  ( (color1.red()>GradDist)   ? color1.red()-GradDist   : 0 );
         color1.setGreen( (color1.green()>GradDist) ? color1.green()-GradDist : 0 );
         color1.setBlue ( (color1.blue()>GradDist)  ? color1.blue()-GradDist  : 0 );
         gradient.setColorAt(0, color0);
         gradient.setColorAt(1, color1);

         nCurrentSpan = (i.key()/m_pImpl->m_fTotal)*360.0;

         painter->setBrush( QBrush(gradient) );
         painter->drawPie(m_rect, nTotalRotation*16.0, nCurrentSpan*16.0);

         nTotalRotation += nCurrentSpan;
      }
   }

   // -------------------------------------------------------------------------
   void GraphPie::createSlice( double fValue, const QColor& color )
   {
      m_pImpl->m_fTotal += fValue;
      while( m_pImpl->m_mapSlices.contains(fValue) )
      {
         fValue -= 0.0000000001; // Subtract makes repeated values draw after original.
      }
      m_pImpl->m_mapSlices.insert(fValue, color);
   }

   // -------------------------------------------------------------------------
   void GraphPie::clearSlices()
   {
      m_pImpl->m_fTotal = 0.0;
      m_pImpl->m_mapSlices.clear();
   }

}; //namespace