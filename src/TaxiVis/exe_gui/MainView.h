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
#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QtGui/QGraphicsView>

#include "MainScene.h"


//! Represents the Map background.
class MainView : public QGraphicsView
{
   Q_OBJECT
		
public:
   // -------------------------------------------------------------------------
   MainView(MainScene* pScene, QWidget *pParent = 0);
   virtual ~MainView();
   
   // -------------------------------------------------------------------------
   MainScene* getMainScene();


protected:
   // -------------------------------------------------------------------------
   void resizeEvent( QResizeEvent * event );
   	

public slots:
   // -------------------------------------------------------------------------
   void refresh();

   void captureScreenShot( QString sImageFile );
   void captureScreenShotPdf( QString sImageFile );

   //! Zooms the view to fit the given graphic in full screen.
   void fullScreen( Vis::GraphBaseObjWrapPtr pGfxObjWrap );

   //! Restores the view to the full scene.
   void restoreView();

private:
};

#endif // MAINVIEW_H
