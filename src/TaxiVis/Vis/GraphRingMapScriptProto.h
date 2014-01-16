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
#ifndef GraphRingMapScriptProto_H
#define GraphRingMapScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Vis/GraphRingMapDispatch.h"


namespace Vis
{
   //! @addtogroup ScriptLang
   //! @{   

   /**
   Scripting language prototype for a GraphRingMap graphic item.

   @code{.js}
   var gfxRm = new GraphRingMap();      // Creates a new object
   @endcode
   */
   class GraphRingMapScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphRingMapScriptProto(QObject *pParent);
      virtual ~GraphRingMapScriptProto();


   public slots:
      // ----------------------------------------------------------------------
      //!@todo Implement the convenience function to create ring items.  The
      //!      problem that this is running into is that the returned object 
      //!      isn't what it should be.  It might be just something simple, 
      //!      there are a TON of steps for creating a single method in this
      //!      system here.
      //Vis::GraphBaseObjWrapPtr addRingItem( 
      //   Vis::GraphBaseObjWrapPtr pGfx,
      //   qreal                    fRotation,
      //   qreal                    fSpan,
      //   qreal                    fDistPercent=1.0,
      //   bool                     bDrawInverted=false );
      
      //! @copydoc GraphRingMapObjWrap::addRingItem
      void addRingItem( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! @copydoc GraphRingMapObjWrap::removeRingItem
      void removeRingItem( Vis::GraphBaseObjWrapPtr pGfx );
      
      //! @copydoc GraphRingMap::setDrawQuadrants
      void setDrawQuadrants( bool bDrawQuadrants );
      
      //! @copydoc GraphRingMap::setDrawRingMarkers
      void setDrawRingMarkers( bool bDrawRingMarkers );


   private:
      // ----------------------------------------------------------------------
      GraphRingMapDispatch* thisDispatch() const;

   };

   //@}

}; //namespace

#endif // GraphRingMapScriptProto_H
