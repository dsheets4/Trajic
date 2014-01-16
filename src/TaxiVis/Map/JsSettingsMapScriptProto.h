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
#ifndef JsSettingsMapScriptProto_H
#define JsSettingsMapScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Map/JsSettingsMapDispatch.h"


namespace Map
{
   //! @addtogroup ScriptLang
   //! @{   

   /**
   Interaction with the route data on the map via the scripting language.

   @code{.js}
   var s = new JsSettingsMap();      // Creates a new object
   @endcode
   */
   class JsSettingsMapScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      JsSettingsMapScriptProto(QObject *pParent);
      virtual ~JsSettingsMapScriptProto();


   public slots:
      // ----------------------------------------------------------------------
   
      //! @copydoc JsSettingsMap::setZoomLevel
      void setZoomLevel(qint32 nZoom);
   
      //! @copydoc JsSettingsMap::setCenterLon
      void setCenterLon(qreal fCenterLon);
   
      //! @copydoc JsSettingsMap::setCenterLat
      void setCenterLat(qreal fCenterLat);
      
      //! @copydoc JsSettingsMap::setExtents
      void setExtents(QVariantList lstExtents);
   
      //! @copydoc JsSettingsMap::setPositionMapByExtents
      void setPositionMapByExtents(bool bPositionByExtents);
      

   private:
      // ----------------------------------------------------------------------
      JsSettingsMapDispatch* thisDispatch() const;

   };

   //! @}

}; //namespace

#endif // JsSettingsMapScriptProto_H
