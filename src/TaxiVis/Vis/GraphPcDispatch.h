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
#ifndef GraphPcDispatch_H
#define GraphPcDispatch_H

#include <QtCore/QObject>

#include "Vis/GraphBaseDispatch.h"


namespace Vis
{
   class GraphPcDispatch : public GraphBaseDispatch
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphPcDispatch(QObject *pParent);
      virtual ~GraphPcDispatch();
      

   signals:
      // ----------------------------------------------------------------------
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setBackgroundColorSignal( QString sColor, qreal fTransparency );
      
      void setCoordinateScaleSignal( QString sType );
      void setGainSignal( qreal fGain );
      void setOffsetSignal( qreal fOffset );

      void setYMaxSignal( double fYMax );
      void setYMinSignal( double fYMin );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void addCoordinateSignal( QString sLabel );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void removeCoordinateSignal( int nIndex );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void removeAllCoordinatesSignal();
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void addLineSignal( QVariantList fListValues, QString sColor, qreal fTransparency );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void removeAllLinesSignal( );


   public slots:
      // ----------------------------------------------------------------------

      //! @copydoc GraphPcObjWrap::setBackgroundColor
      void setBackgroundColor( QString sColor, qreal fTransparency );
      
      void setCoordinateScale( QString sType );
      void setGain( qreal fGain );
      void setOffset( qreal fOffset );
      
      void setYMax( double fYMax );
      void setYMin( double fYMin );
      
      //! @copydoc GraphPcObjWrap::addCoordinate
      void addCoordinate( QString sLabel );
      
      //! @copydoc GraphPcObjWrap::removeCoordinate
      void removeCoordinate( int nIndex );
      
      //! @copydoc GraphPcObjWrap::removeAllCoordinates
      void removeAllCoordinates();
      
      //! @copydoc GraphPcObjWrap::addLine
      void addLine( QVariantList fListValues, QString sColor, qreal fTransparency=1.0 );
      
      //! @copydoc GraphPcObjWrap::removeAllLines
      void removeAllLines( );

   };
}; //namespace

#endif // GraphPcDispatch_H
