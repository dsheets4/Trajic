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
#ifndef GraphPieScriptProto_H
#define GraphPieScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Vis/GraphPieDispatch.h"


namespace Vis
{
   //! @addtogroup ScriptLang
   //! @{   

   /**
   Scripting language prototype for a GraphPie graphic item.

   @code{.js}
   var gfxPie = new GraphPie();      // Creates a new object
   @endcode
   */
   class GraphPieScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphPieScriptProto(QObject *pParent);
      virtual ~GraphPieScriptProto();


   public slots:
      // ----------------------------------------------------------------------

      //! @copydoc GraphPieDispatch::createSlice(double,QString,double)
      void createSlice( double fValue, QString sColor, double fTransparency=1.0 );
      

   private:
      // ----------------------------------------------------------------------
      GraphPieDispatch* thisDispatch() const;

   };

   //@}

}; //namespace

#endif // GraphPieScriptProto_H
