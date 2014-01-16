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
#ifndef GraphBarScriptProto_H
#define GraphBarScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Vis/GraphBarDispatch.h"


namespace Vis
{
   //! @addtogroup ScriptLang
   //! @{   

   /**
   Scripting language prototype for a GraphBar graphic item.

   @code{.js}
   var gfxBar = new GraphBar();      // Creates a new object
   @endcode
   */
   class GraphBarScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphBarScriptProto(QObject *pParent);
      virtual ~GraphBarScriptProto();


   public slots:
      // ----------------------------------------------------------------------

      //! @copydoc GraphBarDispatch::createBar(double,QString,double)
      void createBar( double fValue, QString sColor, double fTransparency=1.0 );


   private:
      // ----------------------------------------------------------------------
      GraphBarDispatch* thisDispatch() const;

   };

   //! @}

}; //namespace

#endif // GraphBarScriptProto_H
