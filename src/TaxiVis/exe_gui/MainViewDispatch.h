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
#ifndef MainViewDispatch_H
#define MainViewDispatch_H

#include <QtCore/QObject>

#include "Vis/GraphBaseObjWrap.h"
#include "ObjectBaseDispatch.h"
#include "MainView.h"


//! Wrapper class to wrap Graph objects with a QObject to make them 
//! accessible with signals and slots for uses such as threading.
class MainViewDispatch : public ObjectBaseDispatch
{
   Q_OBJECT

public:
   // ----------------------------------------------------------------------
   MainViewDispatch(QObject *pParent=0);
   MainViewDispatch(MainView *pView, QObject *pParent=0);
   MainViewDispatch(const MainViewDispatch& orig);
   virtual ~MainViewDispatch();

   // ----------------------------------------------------------------------
   MainView* getView() const;
   void setView( MainView *pView );
      
   // ----------------------------------------------------------------------
   MainViewDispatch& operator=( const MainViewDispatch &rhs );


signals:
   // ----------------------------------------------------------------------
   void captureScreenShotSignal( QString sImageFile );
   void captureScreenShotPdfSignal( QString sImageFile );
   void fullScreenSignal( Vis::GraphBaseObjWrapPtr pGfxObjWrap );
   void restoreViewSignal( );
   void setTitleSignal( QString sTitle );


public slots:
   // ----------------------------------------------------------------------
   void captureScreenShot( QString sImageFile );
   void captureScreenShotPdf( QString sImageFile );
   void fullScreen( Vis::GraphBaseObjWrapPtr pGfxObjWrap );
   void restoreView( );
   void setTitle( QString sTitle );

      
private:
   // ----------------------------------------------------------------------
   MainView* m_pView; //!< The wrapped object
};

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(MainViewDispatch);
Q_DECLARE_METATYPE(MainViewDispatch*);

#endif // MainViewDispatch_H
