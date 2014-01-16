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
#ifndef MainSceneDispatch_H
#define MainSceneDispatch_H

#include <QtCore/QObject>

#include "Vis/GraphBaseObjWrap.h"
#include "ObjectBaseDispatch.h"
#include "MainScene.h"


//! Wrapper class to wrap Graph objects with a QObject to make them 
//! accessible with signals and slots for uses such as threading.
class MainSceneDispatch : public ObjectBaseDispatch
{
   Q_OBJECT

public:
   // ----------------------------------------------------------------------
   MainSceneDispatch(QObject *pParent=0);
   MainSceneDispatch(MainScene *pScene, QObject *pParent=0);
   MainSceneDispatch(const MainSceneDispatch& orig);
   virtual ~MainSceneDispatch();

   // ----------------------------------------------------------------------
   MainScene* getScene() const;
   void setScene( MainScene *pScene );
      
   // ----------------------------------------------------------------------
   MainSceneDispatch& operator=( const MainSceneDispatch &rhs );

signals:
   // ----------------------------------------------------------------------
   void addGraphSignal( Vis::GraphBaseObjWrapPtr pGfx );
   void removeGraphSignal( Vis::GraphBaseObjWrapPtr pGfx );
   void setMapPageSignal( ObjectBaseWrapperPtr pPage );

public slots:
   // ----------------------------------------------------------------------
   void addGraph( Vis::GraphBaseObjWrapPtr pGfx );
   void removeGraph( Vis::GraphBaseObjWrapPtr pGfx );
   void setMapPage( ObjectBaseWrapperPtr pPage );

      
private:
   // ----------------------------------------------------------------------
   MainScene* m_pScene; //!< The wrapped object
};

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(MainSceneDispatch);
Q_DECLARE_METATYPE(MainSceneDispatch*);

#endif // MainSceneDispatch_H
