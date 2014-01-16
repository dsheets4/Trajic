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

#include <QtScript/QScriptEngine>

#include "MainViewScriptProto.h"


// =========================================================================
// Construction and destruction
// =========================================================================

// -------------------------------------------------------------------------
MainViewScriptProto::MainViewScriptProto(QObject *pParent)
   : QObject(pParent)
{
}

// -------------------------------------------------------------------------
MainViewScriptProto::~MainViewScriptProto()
{
}


// =========================================================================
// Script Accessible methods
// =========================================================================

// -------------------------------------------------------------------------
void MainViewScriptProto::setTitle( QString sTitle )
{
   MainViewDispatch* pDispatch = thisDispatch();

   if( pDispatch )
   {
      pDispatch->setTitle( sTitle );
   }
}

// -------------------------------------------------------------------------
void MainViewScriptProto::captureScreenShot( QString sImageFile )
{
   MainViewDispatch* pDispatch = thisDispatch();

   if( pDispatch )
   {
      pDispatch->captureScreenShot( sImageFile );
   }
}

// -------------------------------------------------------------------------
void MainViewScriptProto::captureScreenShotPdf( QString sImageFile )
{
   MainViewDispatch* pDispatch = thisDispatch();

   if( pDispatch )
   {
      pDispatch->captureScreenShotPdf( sImageFile );
   }
}

// -------------------------------------------------------------------------
void MainViewScriptProto::fullScreen( Vis::GraphBaseObjWrapPtr pGfxObjWrap )
{
   MainViewDispatch* pDispatch = thisDispatch();

   if( pDispatch )
   {
      pDispatch->fullScreen( pGfxObjWrap );
   }
}

// -------------------------------------------------------------------------
void MainViewScriptProto::restoreView( )
{
   MainViewDispatch* pDispatch = thisDispatch();

   if( pDispatch )
   {
      pDispatch->restoreView( );
   }
}
   
   
// =========================================================================
// Implementation (not script accessible)
// =========================================================================
MainViewDispatch* MainViewScriptProto::thisDispatch() const
{      
   ObjectBaseDispatchPtr *ptr   = qscriptvalue_cast<ObjectBaseDispatchPtr*>(thisObject().data());
   if( ptr )
   {
      return dynamic_cast<MainViewDispatch*>(ptr->get());
   }

   return NULL;
}
