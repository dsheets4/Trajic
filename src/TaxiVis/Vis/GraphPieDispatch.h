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
#ifndef GraphPieDispatch_H
#define GraphPieDispatch_H

#include <QtCore/QObject>

#include "Vis/GraphBaseDispatch.h"


namespace Vis
{
   //! Represents a bar GraphPieDispatch.
   class GraphPieDispatch : public GraphBaseDispatch
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphPieDispatch(QObject *pParent);
      virtual ~GraphPieDispatch();
      

   signals:
      // ----------------------------------------------------------------------

      //! Signal is emitted to allow for cross-thread communication.
      void createSliceSignal( double fValue, QString sColor, double fTransparency );


   public slots:
      // ----------------------------------------------------------------------
      
      //! @copydoc GraphPieObjWrap::createSlice(double,QString,double)
      void createSlice( double fValue, QString sColor, double fTransparency );

   };
}; //namespace

#endif // GraphPieDispatch_H