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

#include <QtCore/QEventLoop>

#include "Vis/GraphBar.h"
#include "Vis/GraphBarObjWrap.h"
#include "Vis/GraphBarItem.h"
#include "Vis/GraphPie.h"
#include "Vis/GraphPieObjWrap.h"
#include "Vis/GraphRingMap.h"
#include "Vis/GraphRingMapObjWrap.h"
#include "Vis/GraphRingItem.h"
#include "Vis/GraphRingItemObjWrap.h"
#include "Vis/GraphText.h"
#include "Vis/GraphTextObjWrap.h"
#include "Vis/GraphPc.h"
#include "Vis/GraphPcObjWrap.h"
#include "Vis/GraphRingItem.h"
#include "Vis/GraphFactory.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphFactory::GraphFactory(QObject *pParent)
      : QObject(pParent)
      , m_bFactoryGood(false)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Register for the factory to create Graph objects.
      if( 
      connect( 
         this,  SIGNAL(RequestGraph(QString,GraphFactoryHandler*,GraphBase*)),
         this,  SLOT(createGraph(QString,GraphFactoryHandler*,GraphBase*))
         ) )
      {
         m_bFactoryGood = true;
      }
   }

   // -------------------------------------------------------------------------
   GraphFactory::~GraphFactory()
   {

   }

   
   // =========================================================================
   // Factory Methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GraphFactory* GraphFactory::getInstance()
   {
      static GraphFactory instance;
      return &instance;
   }

   
   // =========================================================================
   // Factory Methods
   // =========================================================================
      
   // -------------------------------------------------------------------------
   void GraphFactory::createGraph( 
      QString sGfxType,
      GraphFactoryHandler *gfxFactHndlr,
      GraphBase* pParent)
   {
      GraphTypes::Enum eGfxType = GraphTypes::ToEnum( sGfxType.toStdString() );

      switch( eGfxType )
      {
      case GraphTypes::Graph:
         gfxFactHndlr->setObjectGraph(
            GraphBaseObjWrapPtr( new GraphBaseObjWrap(new GraphBase(pParent),0) )
            );
         break;

      case GraphTypes::GraphRingMap:
         gfxFactHndlr->setObjectGraph( 
            GraphBaseObjWrapPtr( new GraphRingMapObjWrap(new GraphRingMap(pParent),0) )
            );
         break;

      case GraphTypes::GraphRingItem:
         gfxFactHndlr->setObjectGraph(
            GraphBaseObjWrapPtr( new GraphRingItemObjWrap(new GraphRingItem(pParent),0) )
            );
         break;

      case GraphTypes::GraphBar:
         gfxFactHndlr->setObjectGraph(
            GraphBaseObjWrapPtr( new GraphBarObjWrap(new GraphBar(pParent),0) )
            );
         break;

      case GraphTypes::GraphBarItem:
         gfxFactHndlr->setObjectGraph(
            GraphBaseObjWrapPtr( new GraphBaseObjWrap(new GraphBarItem(pParent),0) )
            );
         break;

      case GraphTypes::GraphPie:
         gfxFactHndlr->setObjectGraph(
            GraphBaseObjWrapPtr( new GraphPieObjWrap(new GraphPie(pParent),0) )
            );
         break;

      case GraphTypes::GraphText:
         gfxFactHndlr->setObjectGraph(
            GraphBaseObjWrapPtr( new GraphTextObjWrap(new GraphText(pParent),0) )
            );
         break;

      case GraphTypes::GraphPc:
         gfxFactHndlr->setObjectGraph(
            GraphBaseObjWrapPtr( new GraphPcObjWrap(new GraphPc(pParent),0) )
            );
         break;

      default:
         Q_ASSERT(false); // Unknown graph type...
         gfxFactHndlr->setObjectGraph( GraphBaseObjWrapPtr() );
      }
   }

   
   
   // -------------------------------------------------------------------------
   GraphBaseObjWrapPtr GraphFactory::AllocateGraph( const QString& sGfxType, GraphBase* pParent )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      if( !m_bFactoryGood )
      {
         return GraphBaseObjWrapPtr(NULL);
      }

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup an event loop so that the signal is synchronized.  There isn't 
      // much use in continuing until the object is created.
      //! @todo Setup a QTimer to time out the wait for the Graph object to be
      //!       created.  There won't be much use in using the object but it 
      //!       might prevent freezing if things go wrong.
      GraphFactoryHandler hndlr;
      QEventLoop waitLoop;
      waitLoop.connect( &hndlr, SIGNAL(requestHandled()), SLOT(quit()) );
      emit RequestGraph( sGfxType, &hndlr, pParent );
      waitLoop.exec();
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      return hndlr.getObjectGraph();
   }


}; //namespace