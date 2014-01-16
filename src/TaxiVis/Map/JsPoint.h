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
#ifndef JSPOINT_H
#define JSPOINT_H

#include <QtCore/QObject>

#include <QtGui/QColor>

#include "TaxiVisUtils.h"
#include "DataAccess/DataPoint.h"
#include "Map/MapObject.h"


namespace Map
{
   // Forward declaration of the class just so the pointer definition isn't
   // hidden at the bottom of the file after the class definition.
   class JsPoint;

   //! Smart pointer definition used for passing around JsPoint pointers.
   typedef SHARED_POINTER<JsPoint> JsPointPtr;


   //! Wraps the DataAccess Point so that it can be exposed to JavaScript.
   class JsPoint : public MapObject
   {
      Q_OBJECT
		
   public:
      // ----------------------------------------------------------------------
      JsPoint(QObject *pParent);
      JsPoint(const DataAccess::Point& point, QObject *pParent);
      ~JsPoint();
   

   public slots:
      // ----------------------------------------------------------------------
      // Script exposed methods
   
      unsigned long long getTime() const;
      void setTime(const unsigned long long llTime);

      double getLon() const;
      void setLon(const double fLon);

      double getLat() const;
      void setLat(const double fLat);

      int getAlt() const;
      void setAlt(const int nAlt);

      int getHdg() const;
      void setHdg(const int nHdg);

      int getSpd() const;
      void setSpd(const int nSpd);


   protected:
      // ----------------------------------------------------------------------
      DataAccess::Point      m_point;    //!< Point data being wrapped
      QColor                 m_color;    //!< Color for the point
      int                    m_nWeight;  //!< Weight (e.g. width) of point
   };
}; //namespace

#endif // JSPOINT_H
