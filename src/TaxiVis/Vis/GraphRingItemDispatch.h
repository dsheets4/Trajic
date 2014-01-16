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
#ifndef GraphRingItemDispatch_H
#define GraphRingItemDispatch_H

#include <QtCore/QObject>

#include "Vis/GraphRingItem.h"
#include "Vis/GraphBaseDispatch.h"


namespace Vis
{
   //! Represents a bar GraphRingItemDispatch.
   class GraphRingItemDispatch : public GraphBaseDispatch
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphRingItemDispatch(QObject *pParent);
      virtual ~GraphRingItemDispatch();
      

   signals:
      // ----------------------------------------------------------------------
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void addGraphSignal( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void removeGraphSignal( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setRotationSignal( qreal fRotation );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setSpanSignal( qreal fSPan );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setDistPercentSignal( qreal fDistPercent );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setAlignmentSignal( Vis::GraphRingItem::Alignment eAlignment );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setStabilizedSignal( bool bStabilized );


   public slots:
      // ----------------------------------------------------------------------
      
      //! @copydoc GraphRingItem::addGraph
      void addGraph( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! @copydoc GraphRingItem::removeGraph
      void removeGraph( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! @copydoc GraphRingItem::setRotation
      void setRotation( qreal fRotation );
            
      //! @copydoc GraphRingItem::setSpan
      void setSpan( qreal fSpan );
      
      //! @copydoc GraphRingItem::setDistPercent
      void setDistPercent( qreal fDistPercent );
      
      //! @copydoc GraphRingItem::setAlignment
      void setAlignment( Vis::GraphRingItem::Alignment eAlignment );
      
      //! @copydoc GraphRingItem::setStabilized
      void setStabilized( bool bStabilized );

   };
}; //namespace

#endif // GraphRingItemDispatch_H
