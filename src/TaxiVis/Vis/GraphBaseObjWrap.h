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
#ifndef GraphBaseObjWrap_H
#define GraphBaseObjWrap_H

#include <QtCore/QObject>

#include "Vis/GraphTypes.h"
#include "Vis/GraphBase.h"


namespace Vis
{
   class GraphBaseObjWrap;
   
   //! Smart pointer definition
   typedef SHARED_POINTER<GraphBaseObjWrap> GraphBaseObjWrapPtr;


   //! Wrapper class to wrap Graph objects with a QObject to make them 
   //! accessible with signals and slots for uses such as threading.
   class GraphBaseObjWrap : public QObject
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphBaseObjWrap(QObject *pParent=0);
      GraphBaseObjWrap(GraphBase* pGfx, QObject *pParent=0);
      GraphBaseObjWrap(const GraphBaseObjWrap& orig);
      virtual ~GraphBaseObjWrap();

      // ----------------------------------------------------------------------
      GraphBase* getGraph() const;
      void setGraph( GraphBase* pGfx );
      
      // ----------------------------------------------------------------------
      GraphBaseObjWrap& operator=( const GraphBaseObjWrap &rhs );

   public slots:
      // ----------------------------------------------------------------------
      
      //! Sets the position of the upper left corner of the graphic in screen
      //! coordinates.  Using negative numbers will cause the object to be 
      //! placed off screen.
      //!
      //! @param x  Horizontal position to place the object with zero 
      //!           representing the the left edge.
      //! @param y  Vertical position with positive being downward from the 
      //!           top edge of the window.
      void setPosition( qreal x, qreal y);
      
      //! Sets the size of the graphic in screen coordinates.  Using negative
      //! numbers for height will flip the object vertically (i.e. draw it 
      //! upside down).  Negative numbers for width will flip the object 
      //! horizontally (i.e. draw a mirror image).  Also not that negative 
      //! numbers will cause the object to draw above or to the left of the
      //! position for height and width respectively.
      //!
      //! @param fHeight  Height to draw the graphic
      //! @param fWidth   Width to draw the graphic
      void setSize( qreal fHeight, qreal fWidth);

      
   protected:
      // ----------------------------------------------------------------------
      GraphBase*         m_pGfx;   //!< The wrapped graph object
      GraphTypes::Enum   m_eType;  //!< Graph type being wrapped
   };
}; //namespace

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Vis::GraphBaseObjWrap);
Q_DECLARE_METATYPE(Vis::GraphBaseObjWrap*);
Q_DECLARE_METATYPE(Vis::GraphBaseObjWrapPtr);
Q_DECLARE_METATYPE(Vis::GraphBaseObjWrapPtr*);

#endif // GraphBaseObjWrap_H
