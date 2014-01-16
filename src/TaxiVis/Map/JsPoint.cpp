// Written by David Sheets
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

#include <sstream>
#include <iostream>

#include <QtCore/QDateTime>

#include <QtWebKit/QWebFrame>

#include "CommonDefinitions.h"
#include "TaxiVisUtils.h"
#include "DataAccess/DataPoint.h"
#include "Map/JsPoint.h"


namespace Map
{
   // =========================================================================
   // =========================================================================
   // Construction and destruction

   // -------------------------------------------------------------------------
   JsPoint::JsPoint(QObject *pParent)
      : MapObject(pParent)
      , m_color(255,0,0,128)
      , m_nWeight(5)
   {
   }

   // -------------------------------------------------------------------------
   JsPoint::JsPoint(const DataAccess::Point& point, QObject *pParent)
      : MapObject(pParent)
      , m_point(point)
      , m_color(255,0,0,128)
      , m_nWeight(5)
   {
   }


   // -------------------------------------------------------------------------
   JsPoint::~JsPoint()
   {

   }

   // =========================================================================
   // Overridden methods
   // =========================================================================


   // =========================================================================
   // Overridden methods
   // =========================================================================
   

   // =========================================================================
   // Script exposed
   // =========================================================================
   
   // -------------------------------------------------------------------------
   unsigned long long JsPoint::getTime() const
   {
      return m_point.GetTime();
   }

   void JsPoint::setTime(const unsigned long long llTime)
   {
      m_point.SetTime(llTime);
   }
   
   // -------------------------------------------------------------------------
   double JsPoint::getLon() const
   {
      return m_point.GetLon();
   }

   void JsPoint::setLon(const double fLon)
   {
      m_point.SetLon(fLon);
   }
   
   // -------------------------------------------------------------------------
   double JsPoint::getLat() const
   {
      return m_point.GetLat();
   }

   void JsPoint::setLat(const double fLat)
   {
      m_point.SetLat(fLat);
   }
   
   // -------------------------------------------------------------------------
   int JsPoint::getAlt() const
   {
      return m_point.GetAlt();
   }

   void JsPoint::setAlt(const int nAlt)
   {
      m_point.SetAlt(nAlt);
   }
   
   // -------------------------------------------------------------------------
   int JsPoint::getHdg() const
   {
      return m_point.GetHdg();
   }

   void JsPoint::setHdg(const int nHdg)
   {
      m_point.SetHdg(nHdg);
   }
   
   // -------------------------------------------------------------------------
   int JsPoint::getSpd() const
   {
      return m_point.GetSpd();
   }

   void JsPoint::setSpd(const int nSpd)
   {
      m_point.SetSpd(nSpd);
   }

}; //namespace