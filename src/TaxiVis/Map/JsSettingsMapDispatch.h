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
#ifndef JsSettingsMapDispatch_H
#define JsSettingsMapDispatch_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "TaxiVisUtils.h"
#include "ObjectBaseDispatch.h"
#include "DataAccess/QueryRouteCriteria.h"


namespace Map
{
   //! Smart pointer definition.
   class JsSettingsMapDispatch;
   typedef SHARED_POINTER<JsSettingsMapDispatch> JsSettingsMapDispatchPtr;


   class JsSettingsMapDispatch : public ObjectBaseDispatch
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      JsSettingsMapDispatch(QObject *pParent=0);
      JsSettingsMapDispatch(const JsSettingsMapDispatch& orig);
      virtual ~JsSettingsMapDispatch();
      
      // ----------------------------------------------------------------------
      JsSettingsMapDispatch& operator=( const JsSettingsMapDispatch& rhs );
      
      // ----------------------------------------------------------------------
      ObjectBaseWrapperPtr getObjWrap();
      void setObjWrap( ObjectBaseWrapperPtr pObj );
      

   signals:
      // ----------------------------------------------------------------------
      
      //! @copydoc JsSettingsMap::setZoomLevel
      void setZoomLevelSignal(qint32 nZoom);
   
      //! @copydoc JsSettingsMap::setCenterLon
      void setCenterLonSignal(qreal fCenterLon);
   
      //! @copydoc JsSettingsMap::setCenterLat
      void setCenterLatSignal(qreal fCenterLat);
      
      //! @copydoc JsSettingsMap::setExtents
      void setExtentsSignal(QVariantList lstExtents);
   
      //! @copydoc JsSettingsMap::setPositionMapByExtents
      void setPositionMapByExtentsSignal(bool bPositionByExtents);


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

   protected:
      // ----------------------------------------------------------------------
      ObjectBaseWrapperPtr m_pObj; //!< Object that is connected to this dispatch.

   };
}; //namespace

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Map::JsSettingsMapDispatch);
Q_DECLARE_METATYPE(Map::JsSettingsMapDispatch*);

#endif // JsSettingsMapDispatch_H
