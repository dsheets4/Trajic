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
#ifndef JSQUERYROUTEWRAPPER_H
#define JSQUERYROUTEWRAPPER_H

#include <QtCore/QObject>
#include <QtCore/QThread>

#include "DataAccess/QueryRouteCriteria.h"
#include "Map/JsQueryRouteHandler.h"
#include "Map/JsLayerDispatch.h"


namespace Map
{
   //! Implements QObject so that queries can be threaded.
   class JsQueryRouteWrapper : public QObject
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      JsQueryRouteWrapper(
         JsLayerDispatchPtr  pDispatch,
         QObject* pParent);
      ~JsQueryRouteWrapper();
         
      
      // ----------------------------------------------------------------------
      void getRoutes(JsRoutePtrList& jsRoutes);
      
      const DataAccess::QueryRouteCriteria& getCriteria() const;
      void setCriteria( const DataAccess::QueryRouteCriteria& criteria );
      
      const ObjectBaseWrapperPtr getLayer() const;
      void setLayer( ObjectBaseWrapperPtr pLayer );

   signals:
      //! Sent when the query has completed.  Can be used to terminate 
      //! threaded operations.
      void queryComplete();
      
      //! Sent when the data results of the query are available.
      void routeDataResults();

   public slots:
      
      // ----------------------------------------------------------------------
      void executeQuery();

      
   protected:
      // ----------------------------------------------------------------------
      JsQueryRouteHandler             m_handler;  //!< The wrapped handler
      ObjectBaseWrapperPtr            m_pLayer;   //!< Associated JsLayer
      DataAccess::QueryRouteCriteria  m_criteria; //!< Criteria for querying
   };
}; //namespace

#endif // JSQUERYROUTEWRAPPER_H
