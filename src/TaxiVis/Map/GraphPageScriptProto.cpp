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

#include "Map/GraphPageScriptProto.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPageScriptProto::GraphPageScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   GraphPageScriptProto::~GraphPageScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================
      
   // -------------------------------------------------------------------------
   void GraphPageScriptProto::setCsvFile( QString sCsvFile )
   {
      GraphPageDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setCsvFile( sCsvFile );
      }
   }
      
   // -------------------------------------------------------------------------
   void GraphPageScriptProto::setValueThresh( qreal fValueThresh )
   {
      GraphPageDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setValueThresh( fValueThresh );
      }
   }
      
   // -------------------------------------------------------------------------
   void GraphPageScriptProto::setTopicThresh( int nTopicThresh )
   {
      GraphPageDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setTopicThresh( nTopicThresh );
      }
   }
      
   // -------------------------------------------------------------------------
   void GraphPageScriptProto::setTopicColors( QStringList lstTopicColors )
   {
      GraphPageDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setTopicColors( lstTopicColors );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   GraphPageDispatch* GraphPageScriptProto::thisDispatch() const
   {      
      ObjectBaseDispatchPtr *ptr   = qscriptvalue_cast<ObjectBaseDispatchPtr*>(thisObject().data());
      if( ptr )
      {
         return dynamic_cast<GraphPageDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace