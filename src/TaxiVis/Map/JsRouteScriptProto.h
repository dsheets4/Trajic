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
#ifndef JsRouteScriptProto_H
#define JsRouteScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Map/JsRouteDispatch.h"


namespace Map
{
   //! @addtogroup ScriptLang
   //! @{
   

   /**
   Interaction with the route data on the map via the scripting language.

   @code{.js}
   var r = new JsRoute();      // Creates a new JsRoute object
   @endcode
   */
   class JsRouteScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      JsRouteScriptProto(QObject *pParent);
      virtual ~JsRouteScriptProto();


   public slots:
      // ----------------------------------------------------------------------

      //! @copydoc JsRoute::setColor
      void setColor( QString sColor, qreal fTransparency=1.0 );
      
      //! @copydoc JsRoute::setWeight
      void setWeight( int nWeight );
      
      //! @copydoc JsRoute::addPoint
      void addPoint( unsigned long long llTime, qreal lon, qreal lat, qreal hdg, qreal spd );


   private:
      // ----------------------------------------------------------------------
      JsRouteDispatch* thisDispatch() const;

   };

   //!@}

}; //namespace

#endif // JsRouteScriptProto_H
