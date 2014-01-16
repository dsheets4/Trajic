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
#ifndef JsLayerDispatch_H
#define JsLayerDispatch_H

#include <QtCore/QObject>

#include "TaxiVisUtils.h"
#include "ObjectBaseDispatch.h"
#include "DataAccess/QueryRouteCriteria.h"


namespace Map
{
   //! Smart pointer definition.
   class JsLayerDispatch;
   typedef SHARED_POINTER<JsLayerDispatch> JsLayerDispatchPtr;


   class JsLayerDispatch : public ObjectBaseDispatch
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      JsLayerDispatch(QObject *pParent=0);
      JsLayerDispatch(const JsLayerDispatch& orig);
      virtual ~JsLayerDispatch();
      
      // ----------------------------------------------------------------------
      JsLayerDispatch& operator=( const JsLayerDispatch& rhs );
      
      // ----------------------------------------------------------------------
      ObjectBaseWrapperPtr getObjWrap();
      void setObjWrap( ObjectBaseWrapperPtr pObj );
      

   signals:
      // ----------------------------------------------------------------------
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      QString getNameSignal() const;   
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setNameSignal( QString sName );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void addRouteSignal( ObjectBaseWrapperPtr pRoute );


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
      

   protected:
      // ----------------------------------------------------------------------
      ObjectBaseWrapperPtr m_pObj; //!< Object that is connected to this dispatch.

   };
}; //namespace

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Map::JsLayerDispatch);
Q_DECLARE_METATYPE(Map::JsLayerDispatch*);

#endif // JsLayerDispatch_H
