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
#ifndef GraphPcScriptProto_H
#define GraphPcScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Vis/GraphPcDispatch.h"


namespace Vis
{
   //! @addtogroup ScriptLang
   //! @{   

   /**
   Scripting language prototype for a GraphPc (Parallel Coordinates) 
   graphic item.

   @code{.js}
   var gfxPc = new GraphPc();      // Creates a new object
   @endcode
   */
   class GraphPcScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphPcScriptProto(QObject *pParent);
      virtual ~GraphPcScriptProto();


   public slots:
      // ----------------------------------------------------------------------

      //! @copydoc GraphPcObjWrap::setBackgroundColor
      void setBackgroundColor( QString sColor, qreal fTransparency=1.0 );
      
      void setCoordinateScale( QString sType );
      void setGain( double fGain );
      void setOffset( double fOffset );
      
      void setYMax( double fYMax );
      void setYMin( double fYMin );
      
      //! @copydoc GraphPcObjWrap::addCoordinate
      void addCoordinate( QString sLabel );
      
      //! @copydoc GraphPcObjWrap::removeCoordinate
      void removeCoordinate( int nIndex );
      
      //! @copydoc GraphPcObjWrap::removeAllCoordinates
      void removeAllCoordinates();
      
      //! @copydoc GraphPcObjWrap::addLine
      void addLine( QVariantList fListValues, QString sColor="#FF0000", qreal fTransparency=1.0 );
      
      //! @copydoc GraphPcObjWrap::removeAllLines
      void removeAllLines( );

   private:
      // ----------------------------------------------------------------------
      GraphPcDispatch* thisDispatch() const;

   };

   //@}

}; //namespace

#endif // GraphPcScriptProto_H
