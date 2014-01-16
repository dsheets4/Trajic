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
#ifndef MapFactory_H
#define MapFactory_H

#include "ObjectBaseWrapper.h"
#include "Map/MapTypes.h"
#include "Map/MapFactoryHandler.h"


namespace Map
{

   //! Factory for allocating various objects
   class MapFactory : public QObject
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      MapFactory(QObject *pParent=0);
      ~MapFactory();

      static MapFactory* getInstance();

      ObjectBaseWrapperPtr Allocate( const QString& sType, QObject* pParent=0 );


   signals:
      // ----------------------------------------------------------------------
      //! @todo Convert this to use the MapTypes::Enum instead of QString
      //!       in order to make it a little more efficient.
      void Request( QString sType, MapFactoryHandler *hndlr, QObject* pParent );


   protected slots:
      // ----------------------------------------------------------------------
      void create( 
         QString sGfxType,
         MapFactoryHandler *gfxFactHndlr,
         QObject* pParent );

   protected:
      bool m_bFactoryGood;  //!< Whether the factory can allocate.
   };

   //! Convenience macro to access the singleton.
   #define MAP_FACTORY MapFactory::getInstance()

}; //namespace

#endif // MapFactory_H
