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
#ifndef GraphFactory_H
#define GraphFactory_H

#include "Vis/GraphTypes.h"
#include "Vis/GraphBaseObjWrap.h"
#include "GraphFactoryHandler.h"


namespace Vis
{
   //! Factory for allocating various Graph objects
   class GraphFactory : public QObject
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphFactory(QObject *pParent=0);
      ~GraphFactory();

      static GraphFactory* getInstance();

      GraphBaseObjWrapPtr AllocateGraph( const QString& sGfxType, GraphBase* pParent=0 );


   signals:
      // ----------------------------------------------------------------------
      //! @todo Convert this to use the GraphTypes::Enum instead of QString
      //!       in order to make it a little more efficient.
      void RequestGraph( QString sGfxType, GraphFactoryHandler *hndlr, GraphBase* pParent );


   protected slots:
      // ----------------------------------------------------------------------
      void createGraph( 
         QString sGfxType,
         GraphFactoryHandler *gfxFactHndlr,
         GraphBase* pParent );

   protected:
      bool m_bFactoryGood;  //!< Whether the factory can allocate.
   };

   //! Convenience macro to access the singleton.
   #define GRAPH_FACTORY GraphFactory::getInstance()

}; //namespace

#endif // GraphFactory_H
