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
#ifndef GraphRingItemObjWrap_H
#define GraphRingItemObjWrap_H

#include <QtCore/QObject>

#include "TaxiVisUtils.h"
#include "Vis/GraphRingItem.h"
#include "Vis/GraphBaseObjWrap.h"


namespace Vis
{
   class GraphRingItemObjWrap;
   
   //! Smart pointer definition.
   typedef SHARED_POINTER<GraphRingItemObjWrap> GraphRingItemObjWrapPtr;


   //! Wrapper class to wrap Graph objects with a QObject to make them 
   //! accessible with signals and slots for uses such as threading.
   class GraphRingItemObjWrap : public GraphBaseObjWrap
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphRingItemObjWrap(QObject *pParent=0);
      GraphRingItemObjWrap(GraphRingItem *pGfxRingItem, QObject *pParent=0);
      GraphRingItemObjWrap(const GraphRingItemObjWrap& orig);
      virtual ~GraphRingItemObjWrap();

      // ----------------------------------------------------------------------
      GraphRingItem* getGraphRingItem() const;
      void setGraphRingItem( GraphRingItem* pGfx );
      
      // ----------------------------------------------------------------------
      GraphRingItemObjWrap& operator=( const GraphRingItemObjWrap &rhs );

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

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Vis::GraphRingItemObjWrap);
Q_DECLARE_METATYPE(Vis::GraphRingItemObjWrap*);
Q_DECLARE_METATYPE(Vis::GraphRingItemObjWrapPtr);
Q_DECLARE_METATYPE(Vis::GraphRingItem::Alignment);

#endif // GraphRingItemObjWrap_H
