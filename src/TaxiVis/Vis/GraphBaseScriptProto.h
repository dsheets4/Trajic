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
#ifndef GraphBaseScriptProto_H
#define GraphBaseScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Vis/GraphBaseDispatch.h"


namespace Vis
{
   //! @addtogroup ScriptLang
   //! @{

   /**
   Basic graph functionality available on all Graph objects.  ScriptProto
   classes represent the functions that are available in the scripting 
   language.

   @code{.js}
   var g = new GraphBase();    // Creates a new GraphBase object
   g.setPosition( 100, 200 );  // Sets the position to 100 pixels from the 
                               // left edge and 200 pixels down from the top.
   g.setSize( 200, 300 );      // Sets the height of the graph to 200 pixels
                               // and the width to 300 pixels.
   @endcode
   */
   class GraphBaseScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------

      GraphBaseScriptProto(QObject *pParent);
      virtual ~GraphBaseScriptProto();
      

   public slots:
      // ----------------------------------------------------------------------
      
      //! @copydoc GraphBaseObjWrap::setPosition(qreal,qreal)
      void setPosition( qreal x, qreal y);
      
      //! @copydoc GraphBaseObjWrap::setSize(qreal,qreal)
      void setSize( qreal fHeight, qreal fWidth);


   private:
      // ----------------------------------------------------------------------

      //! Extracts a pointer to the underlying dispatch object from the 
      //! script data type in order to implement the script methods.
      GraphBaseDispatchPtr thisDispatch() const;
   };

   //@}

}; //namespace

#endif // GraphBaseScriptProto_H
