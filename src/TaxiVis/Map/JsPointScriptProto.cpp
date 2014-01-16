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

#include <iostream>

#include <QtScript/QScriptEngine>

#include "Map/JsPointScriptProto.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsPointScriptProto::JsPointScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   JsPointScriptProto::~JsPointScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   unsigned long long JsPointScriptProto::getTime() const
   {
      std::cout << "Not implememented..." << std::endl;
      
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->getTime( );
      }
      return 0;
   }

   void JsPointScriptProto::setTime(const unsigned long long llTime)
   {
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setTime( llTime );
      }
   }
   
   // -------------------------------------------------------------------------
   double JsPointScriptProto::getLon() const
   {
      std::cout << "Not implememented..." << std::endl;
      
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->getLon( );
      }
      return 0;
   }

   void JsPointScriptProto::setLon(const double fLon)
   {
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setLon( fLon );
      }
   }
   
   // -------------------------------------------------------------------------
   double JsPointScriptProto::getLat() const
   {
      std::cout << "Not implememented..." << std::endl;
      
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->getLat( );
      }
      return 0;
   }

   void JsPointScriptProto::setLat(const double fLat)
   {
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setLat( fLat );
      }
   }
   
   // -------------------------------------------------------------------------
   int JsPointScriptProto::getAlt() const
   {
      std::cout << "Not implememented..." << std::endl;
      
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->getAlt( );
      }
      return 0;
   }

   void JsPointScriptProto::setAlt(const int nAlt)
   {
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setAlt( nAlt );
      }
   }
   
   // -------------------------------------------------------------------------
   int JsPointScriptProto::getHdg() const
   {
      std::cout << "Not implememented..." << std::endl;
      
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->getHdg( );
      }
      return 0;
   }

   void JsPointScriptProto::setHdg(const int nHdg)
   {
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setHdg( nHdg );
      }
   }
   
   // -------------------------------------------------------------------------
   int JsPointScriptProto::getSpd() const
   {
      std::cout << "Not implememented..." << std::endl;
      
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->getSpd( );
      }
      return 0;
   }

   void JsPointScriptProto::setSpd(const int nSpd)
   {
      JsPointDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setSpd( nSpd );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   JsPointDispatch* JsPointScriptProto::thisDispatch() const
   {
      ObjectBaseDispatchPtr *ptr   = qscriptvalue_cast<ObjectBaseDispatchPtr*>(thisObject().data());
      if( ptr )
      {
         return dynamic_cast<JsPointDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace