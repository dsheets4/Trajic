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

#include "Vis/GraphTextScriptProto.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphTextScriptProto::GraphTextScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   GraphTextScriptProto::~GraphTextScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphTextScriptProto::setText( QString sText )
   {
      GraphTextDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setText( sText );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphTextScriptProto::setColor( QString sColor, qreal fTransparency )
   {
      GraphTextDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setColor( sColor, fTransparency );
      }
   }

   // -------------------------------------------------------------------------
   void GraphTextScriptProto::setWidth( qreal fWidth )
   {
      GraphTextDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setWidth( fWidth );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   GraphTextDispatch* GraphTextScriptProto::thisDispatch() const
   {
      GraphBaseDispatchPtr *ptr   = qscriptvalue_cast<GraphBaseDispatchPtr*>(thisObject().data());
      if( ptr )
      {
         return dynamic_cast<GraphTextDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace