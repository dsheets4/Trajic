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
#ifndef TaxiVisDispatch_H
#define TaxiVisDispatch_H

#include <QtCore/QObject>

#include "Vis/GraphBaseObjWrap.h"
#include "ObjectBaseDispatch.h"
#include "MainView.h"


//! Wrapper class to wrap Graph objects with a QObject to make them 
//! accessible with signals and slots for uses such as threading.
class TaxiVisDispatch : public ObjectBaseDispatch
{
   Q_OBJECT

public:
   // ----------------------------------------------------------------------
   TaxiVisDispatch(QObject *pParent=0);
   TaxiVisDispatch(const TaxiVisDispatch& orig);
   virtual ~TaxiVisDispatch();

   // ----------------------------------------------------------------------
   MainView* getView() const;
   void setView( MainView *pView );
      
   // ----------------------------------------------------------------------
   TaxiVisDispatch& operator=( const TaxiVisDispatch &rhs );


signals:
   // ----------------------------------------------------------------------
   void createWindowSignal( ObjectBaseWrapperPtr pScene, ObjectBaseWrapperPtr pView );


public slots:
   // ----------------------------------------------------------------------
   void createWindow( ObjectBaseWrapperPtr pScene, ObjectBaseWrapperPtr pView );

};

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(TaxiVisDispatch);
Q_DECLARE_METATYPE(TaxiVisDispatch*);

#endif // TaxiVisDispatch_H
