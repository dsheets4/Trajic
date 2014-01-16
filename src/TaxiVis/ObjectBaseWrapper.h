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
#ifndef ObjectBaseWrapper_H
#define ObjectBaseWrapper_H

#include <QtCore/QMetaType>
#include <QtCore/QObject>

#include "TaxiVisUtils.h"
#include "Map/MapTypes.h"


//! Smart pointer definition
class ObjectBaseWrapper;   
typedef SHARED_POINTER<ObjectBaseWrapper> ObjectBaseWrapperPtr;


//! Wrapper class to wrap Graph objects with a QObject to make them 
//! accessible with signals and slots for uses such as threading.
class ObjectBaseWrapper : public QObject
{
   Q_OBJECT

public:
   // ----------------------------------------------------------------------
   ObjectBaseWrapper(QObject *pParent=0);
   ObjectBaseWrapper(QObject* pWrapped, QObject *pParent=0);
   ObjectBaseWrapper(const ObjectBaseWrapper& orig);
   virtual ~ObjectBaseWrapper();

   // ----------------------------------------------------------------------
   QObject* getObject() const;
   void setObject( QObject* pWrapped );
      
   // ----------------------------------------------------------------------
   ObjectBaseWrapper& operator=( const ObjectBaseWrapper &rhs );
      
      
protected slots:
   // ----------------------------------------------------------------------
   void wrappedObjDestroyed( QObject* pObj );
      

protected:
   // ----------------------------------------------------------------------
   QObject*         m_pObj;   //!< The wrapped object
};


// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(ObjectBaseWrapper);
Q_DECLARE_METATYPE(ObjectBaseWrapper*);
Q_DECLARE_METATYPE(ObjectBaseWrapperPtr);
Q_DECLARE_METATYPE(ObjectBaseWrapperPtr*);

#endif // ObjectBaseWrapper_H
