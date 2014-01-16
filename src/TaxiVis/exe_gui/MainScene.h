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
#ifndef MainScene_H
#define MainScene_H

#include <QtGui/QGraphicsScene>

#include "Map/MapPage.h"
#include "Map/GraphPage.h"
#include "Map/MapView.h"
#include "Vis/GraphBase.h"
#include "Vis/GraphBaseObjWrap.h"
#include "Vis/GraphRingMap.h"


//! Represents the graphical scene.
class MainScene : public QGraphicsScene
{
   Q_OBJECT
		
public:
   // -------------------------------------------------------------------------
   MainScene(QObject *pParent=0);
   ~MainScene();
   
   // -------------------------------------------------------------------------

	//! Setups up the Map background in the scene.
	void CreateMapBackground();
   
   Map::MapView* getMapItem( ) const;

   //! @todo The MainScene should not have a resize option.  Instead, the view 
   //!       should draw the scene to a specific scale.
   void resize( const QSize& size );
   
   void addGraph( Vis::GraphBase* pGfx );
   void removeGraph( Vis::GraphBase* pGfx );
   
public slots:
   // -------------------------------------------------------------------------

   void setMapPage( ObjectBaseWrapperPtr pMapPage );

   void addGraph( Vis::GraphBaseObjWrapPtr pGfxObjWrap );
   void removeGraph( Vis::GraphBaseObjWrapPtr pGfxObjWrap );


private:
   // -------------------------------------------------------------------------
	Map::MapView   *m_pMapItem;  //!< Main scene object containing the map
};

#endif // MainScene_H
