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

#include "MainSceneDispatch.h"


// =========================================================================
// Construction and destruction
// =========================================================================

// -------------------------------------------------------------------------
MainSceneDispatch::MainSceneDispatch(QObject *pParent)
   : ObjectBaseDispatch( pParent )
{
}
   
// -------------------------------------------------------------------------
MainSceneDispatch::MainSceneDispatch(MainScene* pScene, QObject *pParent)
   : ObjectBaseDispatch( pParent )
   , m_pScene( pScene )
{
}
   
// -------------------------------------------------------------------------
MainSceneDispatch::MainSceneDispatch(const MainSceneDispatch& orig)
   : ObjectBaseDispatch(0)
   , m_pScene( orig.m_pScene )
{
}

// -------------------------------------------------------------------------
MainSceneDispatch::~MainSceneDispatch()
{
}

      
// =========================================================================
// Implementation
// =========================================================================
   
// -------------------------------------------------------------------------
MainScene* MainSceneDispatch::getScene() const
{
   return m_pScene;
}

void MainSceneDispatch::setScene( MainScene* pScene )
{
   m_pScene = pScene;
}
   
// =========================================================================
// Operators
// =========================================================================

// -------------------------------------------------------------------------
MainSceneDispatch& MainSceneDispatch::operator=( const MainSceneDispatch &rhs )
{
   if( this != &rhs )
   {
      this->m_pScene = rhs.m_pScene;
   }

   return *this;
}
   

// =========================================================================
// Slots
// =========================================================================

// -------------------------------------------------------------------------
void MainSceneDispatch::addGraph( Vis::GraphBaseObjWrapPtr pGfx )
{
   emit addGraphSignal( pGfx );
}

// -------------------------------------------------------------------------
void MainSceneDispatch::removeGraph( Vis::GraphBaseObjWrapPtr pGfx )
{
   emit removeGraphSignal( pGfx );
}

// -------------------------------------------------------------------------
void MainSceneDispatch::setMapPage( ObjectBaseWrapperPtr pPage )
{
   emit setMapPageSignal( pPage );
}