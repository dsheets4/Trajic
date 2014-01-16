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

#include "MainScene.h"
#include "MainView.h"
#include "GuiFactory.h"


namespace Gui
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GuiFactory::GuiFactory(QObject *pParent)
      : QObject(pParent)
      , m_bFactoryGood(false)
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Register for the factory to create Graph objects.
      if( 
      connect( 
         this,  SIGNAL(Request(QString,GuiFactoryHandler*,QWidget*)),
         this,  SLOT(create(QString,GuiFactoryHandler*,QWidget*))
         ) )
      {
         m_bFactoryGood = true;
      }
   }

   // -------------------------------------------------------------------------
   GuiFactory::~GuiFactory()
   {

   }

   
   // =========================================================================
   // Factory Methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   GuiFactory* GuiFactory::getInstance()
   {
      static GuiFactory instance;
      return &instance;
   }

   
   // =========================================================================
   // Factory Methods
   // =========================================================================
      
   // -------------------------------------------------------------------------
   void GuiFactory::create( 
      QString sType,
      GuiFactoryHandler *hndlr,
      QWidget* pParent)
   {
      GuiTypes::Enum eType = GuiTypes::ToEnum( sType.toStdString() );

      switch( eType )
      {
      case GuiTypes::MainScene:
         hndlr->setObject( 
            ObjectBaseWrapperPtr(new ObjectBaseWrapper(new MainScene(),0))
            );
         break;
         
      case GuiTypes::MainView:
         hndlr->setObject( 
            ObjectBaseWrapperPtr(new ObjectBaseWrapper(new MainView(NULL,pParent),0))
            );
         break;

      default:
         Q_ASSERT(false); // Unknown type...
         hndlr->setObject( ObjectBaseWrapperPtr(0) );
      }
   }

   
   
   // -------------------------------------------------------------------------
   ObjectBaseWrapperPtr GuiFactory::Allocate( const QString& sType, QWidget* pParent )
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
      GuiFactoryHandler hndlr;
      QEventLoop waitLoop;
      waitLoop.connect( &hndlr, SIGNAL(requestHandled()), SLOT(quit()) );
      emit Request( sType, &hndlr, pParent );
      waitLoop.exec();
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      return hndlr.getObject();
   }


}; //namespace