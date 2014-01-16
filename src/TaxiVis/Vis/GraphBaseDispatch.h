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
#ifndef GraphBaseDispatch_H
#define GraphBaseDispatch_H

#include <QtCore/QObject>

#include "TaxiVisUtils.h"
#include "Vis/GraphBaseObjWrap.h"


namespace Vis
{
   //! Smart pointer definition.
   class GraphBaseDispatch;   
   typedef SHARED_POINTER<GraphBaseDispatch> GraphBaseDispatchPtr;


   class GraphBaseDispatch : public QObject
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphBaseDispatch(QObject *pParent=0);
      GraphBaseDispatch(const GraphBaseDispatch& orig);
      virtual ~GraphBaseDispatch();
      
      // ----------------------------------------------------------------------
      GraphBaseObjWrapPtr getGraphObjWrap();
      void setGraphObjWrap( GraphBaseObjWrapPtr pGfx );
      
      GraphBaseDispatch& operator=( const GraphBaseDispatch& rhs );


   signals:
      // ----------------------------------------------------------------------
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setPositionSignal( qreal x, qreal y);
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setSizeSignal( qreal fHeight, qreal fWidth);


   public slots:
      // ----------------------------------------------------------------------

      //! @copydoc GraphBaseObjWrap::setPosition(qreal,qreal)
      void setPosition( qreal x, qreal y);
      
      //! @copydoc GraphBaseObjWrap::setSize(qreal,qreal)
      void setSize( qreal fHeight, qreal fWidth);


   protected:
      // ----------------------------------------------------------------------
      GraphBaseObjWrapPtr m_pGfx; //!< Object that is connected to this dispatch.
   };
}; //namespace

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Vis::GraphBaseDispatch);
Q_DECLARE_METATYPE(Vis::GraphBaseDispatch*);
Q_DECLARE_METATYPE(Vis::GraphBaseDispatchPtr);
Q_DECLARE_METATYPE(Vis::GraphBaseDispatchPtr*);

#endif // GraphBaseDispatch_H
