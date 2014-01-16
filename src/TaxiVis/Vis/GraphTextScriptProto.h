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
#ifndef GraphTextScriptProto_H
#define GraphTextScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Vis/GraphTextDispatch.h"


namespace Vis
{
   //! @addtogroup ScriptLang
   //! @{   

   /**
   Scripting language prototype for a GraphText graphic item.

   @code{.js}
   var gfxText = new GraphText();      // Creates a new object
   @endcode
   */
   class GraphTextScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphTextScriptProto(QObject *pParent);
      virtual ~GraphTextScriptProto();


   public slots:
      // ----------------------------------------------------------------------
      
      //! @copydoc GraphText::setText
      void setText( QString sText );
      
      //! @copydoc GraphTextObjWrap::setColor
      void setColor( QString sColor, qreal fTransparency=1.0 );

      //! @copydoc GraphText::setWidth
      void setWidth( qreal fWidth );


   private:
      // ----------------------------------------------------------------------
      GraphTextDispatch* thisDispatch() const;

   };

   //@}

}; //namespace

#endif // GraphTextScriptProto_H
