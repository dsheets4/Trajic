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
#ifndef GraphRingItemScriptProto_H
#define GraphRingItemScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Vis/GraphRingItem.h"
#include "Vis/GraphRingItemDispatch.h"


namespace Vis
{
   //! @addtogroup ScriptLang
   //! @{   

   /**
   Scripting language prototype for a GraphRingItem graphic item.

   @code{.js}
   var gfxRi = new GraphRingItem();      // Creates a new object
   @endcode
   */
   class GraphRingItemScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphRingItemScriptProto(QObject *pParent);
      virtual ~GraphRingItemScriptProto();


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
      void setAlignment( int eAlignment );
      
      //! @copydoc GraphRingItem::setStabilized
      void setStabilized( bool bStabilized );


   private:
      // ----------------------------------------------------------------------
      GraphRingItemDispatch* thisDispatch() const;

   };

   //@}

}; //namespace

#endif // GraphRingItemScriptProto_H
