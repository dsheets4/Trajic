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
#ifndef MainViewScriptProto_H
#define MainViewScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "MainViewDispatch.h"


//! Represents a bar MainViewScriptProto.
class MainViewScriptProto : public QObject, public QScriptable
{		
   Q_OBJECT

public:
   // ----------------------------------------------------------------------
   MainViewScriptProto(QObject *pParent);
   virtual ~MainViewScriptProto();

      
public slots:
   // ----------------------------------------------------------------------
   void captureScreenShot( QString sImageFile );
   void captureScreenShotPdf( QString sImageFile );
   void fullScreen( Vis::GraphBaseObjWrapPtr pGfxObjWrap );
   void restoreView( );
   void setTitle( QString sTitle );


private:
   // ----------------------------------------------------------------------
   MainViewDispatch* thisDispatch() const;

};

#endif // MainViewScriptProto_H
