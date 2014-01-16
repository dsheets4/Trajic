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
#ifndef ObjectBaseDispatch_H
#define ObjectBaseDispatch_H

#include <QtCore/QObject>

#include "TaxiVisUtils.h"
#include "ObjectBaseWrapper.h"


//! Smart pointer definition.
class ObjectBaseDispatch;
typedef SHARED_POINTER<ObjectBaseDispatch> ObjectBaseDispatchPtr;


class ObjectBaseDispatch : public QObject
{		
   Q_OBJECT

public:
   // ----------------------------------------------------------------------
   ObjectBaseDispatch(QObject *pParent=0);
   ObjectBaseDispatch(const ObjectBaseDispatch& orig);
   virtual ~ObjectBaseDispatch();
      
   // ----------------------------------------------------------------------
   ObjectBaseDispatch& operator=( const ObjectBaseDispatch& rhs );
      
   // ----------------------------------------------------------------------
   ObjectBaseWrapperPtr getObjWrap();
   void setObjWrap( ObjectBaseWrapperPtr pObj );
      

signals:
   // ----------------------------------------------------------------------

public slots:
   // ----------------------------------------------------------------------
      

protected:
   // ----------------------------------------------------------------------
   ObjectBaseWrapperPtr m_pObj; //!< Object that is connected to this dispatch.

};


// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(ObjectBaseDispatch);
Q_DECLARE_METATYPE(ObjectBaseDispatch*);
Q_DECLARE_METATYPE(ObjectBaseDispatchPtr);
Q_DECLARE_METATYPE(ObjectBaseDispatchPtr*);

#endif // ObjectBaseDispatch_H
