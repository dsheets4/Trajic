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

#include "MainViewDispatch.h"


// =========================================================================
// Construction and destruction
// =========================================================================

// -------------------------------------------------------------------------
MainViewDispatch::MainViewDispatch(QObject *pParent)
   : ObjectBaseDispatch( pParent )
{
}
   
// -------------------------------------------------------------------------
MainViewDispatch::MainViewDispatch(MainView* pView, QObject *pParent)
   : ObjectBaseDispatch( pParent )
   , m_pView( pView )
{
}
   
// -------------------------------------------------------------------------
MainViewDispatch::MainViewDispatch(const MainViewDispatch& orig)
   : ObjectBaseDispatch(0)
   , m_pView( orig.m_pView )
{
}

// -------------------------------------------------------------------------
MainViewDispatch::~MainViewDispatch()
{
}

      
// =========================================================================
// Implementation
// =========================================================================
   
// -------------------------------------------------------------------------
MainView* MainViewDispatch::getView() const
{
   return m_pView;
}

void MainViewDispatch::setView( MainView* pView )
{
   m_pView = pView;
}

   
// =========================================================================
// Operators
// =========================================================================

// -------------------------------------------------------------------------
MainViewDispatch& MainViewDispatch::operator=( const MainViewDispatch &rhs )
{
   if( this != &rhs )
   {
      this->m_pView = rhs.m_pView;
   }

   return *this;
}
   

// =========================================================================
// Slots
// =========================================================================

// -------------------------------------------------------------------------
void MainViewDispatch::setTitle( QString sTitle )
{
   emit setTitleSignal( sTitle );
}

// -------------------------------------------------------------------------
void MainViewDispatch::captureScreenShot( QString sImageFile )
{
   emit captureScreenShotSignal( sImageFile );
}

// -------------------------------------------------------------------------
void MainViewDispatch::captureScreenShotPdf( QString sImageFile )
{
   emit captureScreenShotPdfSignal( sImageFile );
}

// -------------------------------------------------------------------------
void MainViewDispatch::fullScreen( Vis::GraphBaseObjWrapPtr pGfxObjWrap )
{
   emit fullScreenSignal( pGfxObjWrap );
}

// -------------------------------------------------------------------------
void MainViewDispatch::restoreView( )
{
   emit restoreViewSignal();
}
