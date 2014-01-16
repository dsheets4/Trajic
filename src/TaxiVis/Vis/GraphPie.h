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

#ifndef GRAPHPIE_H
#define GRAPHPIE_H

#include "Vis/GraphBase.h"


namespace Vis
{
   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // Forward declaration to remove dependencies.
   class GraphPieImpl;


   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   class GraphPie : public GraphBase
   {
   public:
      GraphPie( QGraphicsItem* pParent=0 );
      virtual ~GraphPie();


      // -------------------------------------------------------------------------
      // QGraphics Item implementation.

      void paint(
         QPainter *painter,
         const QStyleOptionGraphicsItem *option,
         QWidget *widget);

   
      // -------------------------------------------------------------------------
      // Additional Interface
      
      //! Creates a slice in the pie graph.  The values will be cumulated and 
      //! each slice given a proportionate section of the overall pie.
      //!
      //! @param fValue  Value the slice represents.
      //! @param color   Color representing the slice, including transparency.
      void createSlice( double fValue, const QColor& color );
      void clearSlices();


   protected:
      // -------------------------------------------------------------------------
      GraphPieImpl* m_pImpl;
   };
}; //namespace


#endif // GRAPHPIE_H