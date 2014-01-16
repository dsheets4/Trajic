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
#ifndef GraphBarDispatch_H
#define GraphBarDispatch_H

#include <QtCore/QObject>

#include "Vis/GraphBaseDispatch.h"


namespace Vis
{
   class GraphBarDispatch : public GraphBaseDispatch
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphBarDispatch(QObject *pParent);
      virtual ~GraphBarDispatch();

      
   signals:
      // ----------------------------------------------------------------------

      //! Signal is emitted from the slot to allow for cross-thread communication.
      void createBarSignal( double fValue, QString sColor, double fTransparency );


   public slots:
      // ----------------------------------------------------------------------

      //! @copydoc GraphBarObjWrap::createBar(double,QString,double)
      void createBar( double fValue, QString sColor, double fTransparency );

   };
}; //namespace

#endif // GraphBarDispatch_H
