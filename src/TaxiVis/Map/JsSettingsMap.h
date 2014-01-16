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
#ifndef JSSETTINGSMAP_H
#define JSSETTINGSMAP_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include <QtGui/QColor>


namespace Map
{
   //! Map settings object that is exposed to the JavaScript.
   class JsSettingsMap : public QObject
   {
      Q_OBJECT
		
   public:
      // ----------------------------------------------------------------------
      JsSettingsMap(QObject *pParent);
      JsSettingsMap(const JsSettingsMap& orig);
      ~JsSettingsMap();

	  
      // ----------------------------------------------------------------------
      JsSettingsMap& operator=( const JsSettingsMap& rhs );
   

   public slots:
      // ----------------------------------------------------------------------
   
      //! Gets the zoom level for the map.
      qint32 getZoomLevel() const;
      void setZoomLevel(qint32 nZoom);
   
      //! Gets the longitude of the set center location.
      qreal getCenterLon() const;
      void setCenterLon(qreal fCenterLon);
   
      //! Gets the latitude of the set center location.
      qreal getCenterLat() const;
      void setCenterLat(qreal fCenterLat);
   
      //! Extents to show on the map.
      QVariantList getExtents() const;
      void setExtents(QVariantList lstExtents);
   
      //! Whether to display the map centered on the center location or
      //! auto-zoom based on extents.
      bool getPositionMapByExtents() const;
      void setPositionMapByExtents(bool bPositionByExtents);

   protected:
      // ----------------------------------------------------------------------
      qreal   m_fCenterLon;      //!< Longitude of the starting location of the map.
      qreal   m_fCenterLat;      //!< Latitude of the starting location of the map.
      qint32  m_nZoom;           //!< Zoom level for the map.

      QVariantList m_lstExtents; //!< Left, Top, Right, Bottom Extents to show.

      bool m_bPositionByExtents; //!< Flag indicating to position map using
                                 //!< extents instead of center and zoom.
   };
}; //namespace

#endif // JSSETTINGSMAP_H
