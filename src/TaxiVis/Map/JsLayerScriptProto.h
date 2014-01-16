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
#ifndef JsLayerScriptProto_H
#define JsLayerScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Map/JsLayerDispatch.h"


namespace Map
{
   //! @addtogroup ScriptLang
   //! @{   

   /**
   Interaction with the route data on the map via the scripting language.

   @code{.js}
   var l = new JsLayer();      // Creates a new object
   @endcode
   */
   class JsLayerScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      JsLayerScriptProto(QObject *pParent);
      virtual ~JsLayerScriptProto();


   public slots:
      // ----------------------------------------------------------------------

      //! @copydoc JsLayer::getName
      //!
      //! This method does not currently work.
      QString getName() const;
      
      //! @copydoc JsLayer::setName
      void setName( QString sName );
      
      //! @copydoc JsLayer::addRoute
      void addRoute( ObjectBaseWrapperPtr pRoute );
      

   private:
      // ----------------------------------------------------------------------
      JsLayerDispatch* thisDispatch() const;

   };

   //! @}

}; //namespace

#endif // JsLayerScriptProto_H
