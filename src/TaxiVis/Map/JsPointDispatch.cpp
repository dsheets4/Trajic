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

#include "Map/JsPointDispatch.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsPointDispatch::JsPointDispatch(QObject *pParent)
      : ObjectBaseDispatch(pParent)
   {
   }
   
   // -------------------------------------------------------------------------
   JsPointDispatch::JsPointDispatch(const JsPointDispatch& orig)
      : ObjectBaseDispatch(0)
   {
   }

   // -------------------------------------------------------------------------
   JsPointDispatch::~JsPointDispatch()
   {
   }
   
   
   // =========================================================================
   // Implementation
   // =========================================================================
   

   // =========================================================================
   // Slots
   // =========================================================================

   // -------------------------------------------------------------------------
   unsigned long long JsPointDispatch::getTime() const
   {
      std::cout << "Not implememented..." << std::endl;
      emit getTimeSignal();
      return 0;
   }

   void JsPointDispatch::setTime(const unsigned long long llTime)
   {
      emit setTimeSignal( llTime );
   }
   
   // -------------------------------------------------------------------------
   double JsPointDispatch::getLon() const
   {
      std::cout << "Not implememented..." << std::endl;
      emit getLonSignal();
      return 0;
   }

   void JsPointDispatch::setLon(const double fLon)
   {
      emit setLonSignal( fLon );
   }
   
   // -------------------------------------------------------------------------
   double JsPointDispatch::getLat() const
   {
      std::cout << "Not implememented..." << std::endl;
      emit getLatSignal();
      return 0;
   }

   void JsPointDispatch::setLat(const double fLat)
   {
      emit setLatSignal( fLat );
   }
   
   // -------------------------------------------------------------------------
   int JsPointDispatch::getAlt() const
   {
      std::cout << "Not implememented..." << std::endl;
      emit getAltSignal();
      return 0;
   }

   void JsPointDispatch::setAlt(const int nAlt)
   {
      emit setAltSignal( nAlt );
   }
   
   // -------------------------------------------------------------------------
   int JsPointDispatch::getHdg() const
   {
      std::cout << "Not implememented..." << std::endl;
      emit getHdgSignal();
      return 0;
   }

   void JsPointDispatch::setHdg(const int nHdg)
   {
      emit setHdgSignal( nHdg );
   }
   
   // -------------------------------------------------------------------------
   int JsPointDispatch::getSpd() const
   {
      std::cout << "Not implememented..." << std::endl;
      emit getSpdSignal();
      return 0;
   }

   void JsPointDispatch::setSpd(const int nSpd)
   {
      emit setSpdSignal( nSpd );
   }
   
}; //namespace