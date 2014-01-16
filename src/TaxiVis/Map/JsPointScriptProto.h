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
#ifndef JsPointScriptProto_H
#define JsPointScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Map/JsPointDispatch.h"


namespace Map
{
   //! @addtogroup ScriptLang
   //! @{

   /**
   Interaction with the route data on the map via the scripting language.

   @note JsPoint is not useful in the scripting language.  Use 
         JsRouteScriptProto::addPoint

   @code{.js}
   var p = new JsPoint();      // Creates a new object
   @endcode
   */
   class JsPointScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      JsPointScriptProto(QObject *pParent);
      virtual ~JsPointScriptProto();


   public slots:
      // ----------------------------------------------------------------------
      unsigned long long getTime() const;
      void setTime(const unsigned long long llTime);

      double getLon() const;
      void setLon(const double fLon);

      double getLat() const;
      void setLat(const double fLat);

      int getAlt() const;
      void setAlt(const int nAlt);

      int getHdg() const;
      void setHdg(const int nHdg);

      int getSpd() const;
      void setSpd(const int nSpd);


   private:
      // ----------------------------------------------------------------------
      JsPointDispatch* thisDispatch() const;

   };

   //! @}

}; //namespace

#endif // JsPointScriptProto_H
