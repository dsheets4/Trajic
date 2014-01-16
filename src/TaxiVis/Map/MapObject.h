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
#ifndef MapObject_H
#define MapObject_H

#include <QtCore/QMetaType>
#include <QtCore/QObject>

#include "TaxiVisUtils.h"
#include "Map/MapTypes.h"


namespace Map
{
   //! Wrapper class to wrap Graph objects with a QObject to make them 
   //! accessible with signals and slots for uses such as threading.
   class MapObject : public QObject
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      MapObject(QObject *pParent=0);
      MapObject(const MapObject& orig);
      virtual ~MapObject();
      

      // ----------------------------------------------------------------------
      MapObject& operator=( const MapObject &rhs );
      
   };
}; //namespace


// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Map::MapObject);
Q_DECLARE_METATYPE(Map::MapObject*);

#endif // MapObject_H
