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
#ifndef MapPageScriptProto_H
#define MapPageScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Map/MapPageDispatch.h"


namespace Map
{
   //! Represents a bar MapPageScriptProto.
   class MapPageScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      MapPageScriptProto(QObject *pParent);
      virtual ~MapPageScriptProto();

      
   public slots:
      // ----------------------------------------------------------------------
      void addLayer( ObjectBaseWrapperPtr pLayer );
      void removeLayer( ObjectBaseWrapperPtr pLayer );
      void setMapSettings( ObjectBaseWrapperPtr pSettings );
      void setShowPosZoom( bool bShowPosZoom );


   private:
      // ----------------------------------------------------------------------
      MapPageDispatch* thisDispatch() const;

   };
}; //namespace

#endif // MapPageScriptProto_H
