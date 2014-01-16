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

#include "Vis/GraphBarScriptProto.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphBarScriptProto::GraphBarScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   GraphBarScriptProto::~GraphBarScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphBarScriptProto::createBar(
      double fValue,
      QString sColor,
      double fTransparency )
   {
      GraphBarDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->createBar( fValue, sColor, fTransparency );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   GraphBarDispatch* GraphBarScriptProto::thisDispatch() const
   {
      GraphBaseDispatchPtr *ptr   = qscriptvalue_cast<GraphBaseDispatchPtr*>(thisObject().data());

      if( ptr )
      {
         return dynamic_cast<GraphBarDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace