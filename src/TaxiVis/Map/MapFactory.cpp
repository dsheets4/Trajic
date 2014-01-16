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

#include "Map/MapPage.h"
#include "Map/GraphPage.h"
#include "Map/JsSettingsMap.h"
#include "Map/JsPoint.h"
#include "Map/JsRoute.h"
#include "Map/JsLayer.h"
#include "Map/MapFactory.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   MapFactory::MapFactory(QObject *pParent)
      : QObject(pParent)
      , m_bFactoryGood(false)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Register for the factory to create Graph objects.
      if( 
      connect( 
         this,  SIGNAL(Request(QString,MapFactoryHandler*,QObject*)),
         this,  SLOT(create(QString,MapFactoryHandler*,QObject*))
         ) )
      {
         m_bFactoryGood = true;
      }
   }

   // -------------------------------------------------------------------------
   MapFactory::~MapFactory()
   {

   }

   
   // =========================================================================
   // Factory Methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   MapFactory* MapFactory::getInstance()
   {
      static MapFactory instance;
      return &instance;
   }

   
   // =========================================================================
   // Factory Methods
   // =========================================================================
      
   // -------------------------------------------------------------------------
   void MapFactory::create( 
      QString sType,
      MapFactoryHandler *hndlr,
      QObject* pParent)
   {
      MapTypes::Enum eType = MapTypes::ToEnum( sType.toStdString() );

      switch( eType )
      {
      case MapTypes::MapPage:
         hndlr->setObject( 
            ObjectBaseWrapperPtr(new ObjectBaseWrapper(new MapPage(pParent),0))
            );
         break;

      case MapTypes::GraphPage:
         hndlr->setObject( 
            ObjectBaseWrapperPtr(new ObjectBaseWrapper(new GraphPage(pParent),0))
            );
         break;

      case MapTypes::JsSettingsMap:
         hndlr->setObject( 
            ObjectBaseWrapperPtr(new ObjectBaseWrapper(new JsSettingsMap(pParent),0))
            );
         break;

      case MapTypes::JsLayer:
         hndlr->setObject( 
            ObjectBaseWrapperPtr(new ObjectBaseWrapper(new JsLayer(pParent),0))
            );
         break;
         
      case MapTypes::JsRoute:
         hndlr->setObject( 
            ObjectBaseWrapperPtr(new ObjectBaseWrapper(new JsRoute(pParent),0))
            );
         break;
         
      case MapTypes::JsPoint:
         hndlr->setObject( 
            ObjectBaseWrapperPtr(new ObjectBaseWrapper(new JsPoint(pParent),0))
            );
         break;

      default:
         Q_ASSERT(false); // Unknown type...
         hndlr->setObject( ObjectBaseWrapperPtr(0) );
      }
   }

   
   
   // -------------------------------------------------------------------------
   ObjectBaseWrapperPtr MapFactory::Allocate( const QString& sType, QObject* pParent )
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      if( !m_bFactoryGood )
      {
         return ObjectBaseWrapperPtr(NULL);
      }

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup an event loop so that the signal is synchronized.  There isn't 
      // much use in continuing until the object is created.
      //! @todo Setup a QTimer to time out the wait for the Graph object to be
      //!       created.  There won't be much use in using the object but it 
      //!       might prevent freezing if things go wrong.
      MapFactoryHandler hndlr;
      QEventLoop waitLoop;
      waitLoop.connect( &hndlr, SIGNAL(requestHandled()), SLOT(quit()) );
      emit Request( sType, &hndlr, pParent );
      waitLoop.exec();
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      return hndlr.getObject();
   }


}; //namespace