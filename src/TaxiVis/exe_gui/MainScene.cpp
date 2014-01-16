// Written by David Sheets
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

#include "Vis/GraphBar.h"
#include "Vis/GraphPie.h"
#include "MainScene.h"


// ============================================================================
// Construction and destruction
// ============================================================================

// ----------------------------------------------------------------------------
MainScene::MainScene(QObject *pParent)
   : QGraphicsScene(pParent)
   , m_pMapItem(new Map::MapView(0))
{
}

// ----------------------------------------------------------------------------
MainScene::~MainScene()
{
}


// ----------------------------------------------------------------------------
void MainScene::resize( const QSize& size )
{
   Q_ASSERT(m_pMapItem);

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   QListIterator<QGraphicsItem*> i( this->items() );
   while( i.hasNext() )
   {
      Vis::GraphBase* pGfx = dynamic_cast<Vis::GraphBase*>(i.next());
      if( pGfx )
      {
         pGfx->resize(size);
      }
   }
   
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   m_pMapItem->resize(size.width(), size.height());
}

// ============================================================================
// Implementation Methods
// ============================================================================

// ----------------------------------------------------------------------------
Map::MapView* MainScene::getMapItem( ) const
{
   return m_pMapItem;
}

void MainScene::setMapPage( ObjectBaseWrapperPtr pMapPage )
{
   if( pMapPage && pMapPage.get()->getObject() )
   {
      //!@todo Create a common page base class that has the shared operations 
      //!      between MapPage and GraphPage.
      Map::MapPage* pMap = dynamic_cast<Map::MapPage*>(pMapPage.get()->getObject());
      if( pMap )
      {
         m_pMapItem->setPage(pMap);
         m_pMapItem->reload();
      }
      else
      {
         Map::GraphPage* pGraph = dynamic_cast<Map::GraphPage*>(pMapPage.get()->getObject());
         m_pMapItem->setPage(pGraph);
         m_pMapItem->reload();
      }
   }
}

// ----------------------------------------------------------------------------
void MainScene::CreateMapBackground()
{
   Q_ASSERT(m_pMapItem);

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Page settings
   QWebSettings* webSettings = QWebSettings::globalSettings();
   webSettings->setAttribute( QWebSettings::OfflineWebApplicationCacheEnabled, true );

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Create a webpage graphics items for the OpenLayers map.
   addItem(m_pMapItem);
}

// ----------------------------------------------------------------------------
 void MainScene::addGraph( Vis::GraphBase* pGfx )
 {
    addItem(pGfx);
 }
 
void MainScene::addGraph( Vis::GraphBaseObjWrapPtr pGfxObjWrap )
{
   Q_ASSERT( pGfxObjWrap );

   addGraph( pGfxObjWrap->getGraph() );
}

// ----------------------------------------------------------------------------
 void MainScene::removeGraph( Vis::GraphBase* pGfx )
 {
    Q_ASSERT( pGfx );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //!@todo Somehow the memory associated with this graph as well as the 
    //!      associated script memory needs to be cleaned up.  I'm not sure 
    //!      how to do that between the threads yet though.

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Only remove the item if it is a top-level scene object.
    if( pGfx->parentItem() == NULL && pGfx->scene() == this )
    {
       removeItem(pGfx);
    }
 }
 
void MainScene::removeGraph( Vis::GraphBaseObjWrapPtr pGfxObjWrap )
{
   Q_ASSERT( pGfxObjWrap );

   removeGraph( pGfxObjWrap->getGraph() );
}
