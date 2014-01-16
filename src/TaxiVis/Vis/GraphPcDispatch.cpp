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

#include "Vis/GraphPcDispatch.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPcDispatch::GraphPcDispatch(QObject *pParent)
      : GraphBaseDispatch(pParent)
   {
   }

   // -------------------------------------------------------------------------
   GraphPcDispatch::~GraphPcDispatch()
   {
   }


   // =========================================================================
   // Slots
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void GraphPcDispatch::setBackgroundColor( QString sColor, qreal fTransparency )
   {
      emit setBackgroundColorSignal( sColor, fTransparency );
   }

   // -------------------------------------------------------------------------
   void GraphPcDispatch::setCoordinateScale( QString sType )
   {
      emit setCoordinateScaleSignal( sType );
   }
   
   // -------------------------------------------------------------------------
   void GraphPcDispatch::setGain( qreal fGain )
   {
      emit setGainSignal( fGain );
   }
      
   // -------------------------------------------------------------------------
   void GraphPcDispatch::setOffset( qreal fOffset )
   {
      emit setOffsetSignal( fOffset );
   }

   // -------------------------------------------------------------------------
   void GraphPcDispatch::setYMax( double fYMax )
   {
      emit setYMaxSignal( fYMax );
   }
      
   // -------------------------------------------------------------------------
   void GraphPcDispatch::setYMin( double fYMin )
   {
      emit setYMinSignal( fYMin );
   }
   
   // -------------------------------------------------------------------------  
   void GraphPcDispatch::addCoordinate( QString sLabel )
   {
      emit addCoordinateSignal( sLabel );
   }
   
   // -------------------------------------------------------------------------
   void GraphPcDispatch::removeCoordinate( int nIndex )
   {
      emit removeCoordinateSignal( nIndex );
   }
   
   // -------------------------------------------------------------------------
   void GraphPcDispatch::removeAllCoordinates()
   {
      emit removeAllCoordinatesSignal();
   }

   // -------------------------------------------------------------------------  
   void GraphPcDispatch::addLine( QVariantList fListValues, QString sColor, qreal fTransparency )
   {
      emit addLineSignal( fListValues, sColor, fTransparency );
   }
   
   // -------------------------------------------------------------------------
   void GraphPcDispatch::removeAllLines( )
   {
      emit removeAllLinesSignal( );
   }
   
}; //namespace