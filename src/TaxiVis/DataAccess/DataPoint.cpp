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

#include "DataAccess/DataPoint.h"


namespace DataAccess
{
   // -------------------------------------------------------------------------
   Point::Point()
      : m_llTime(0)
      , m_fLon(0.0)
      , m_fLat(0.0)
      , m_nAlt(0)
      , m_nHdg(-1)
      , m_nSpd(-1)
   {
   }

   // -------------------------------------------------------------------------
   Point::~Point()
   {
   }

   // -------------------------------------------------------------------------
   unsigned long long Point::GetTime() const
   {
      return m_llTime;
   }

   void Point::SetTime(const unsigned long long llTime)
   {
      m_llTime = llTime;
   }

   // -------------------------------------------------------------------------
   double Point::GetLon() const
   {
      return m_fLon;
   }

   void Point::SetLon(const double fLon)
   {
      m_fLon = fLon;
   }

   // -------------------------------------------------------------------------
   double Point::GetLat() const
   {
      return m_fLat;
   }

   void Point::SetLat(const double fLat)
   {
      m_fLat = fLat;
   }

   // -------------------------------------------------------------------------
   int Point::GetAlt() const
   {
      return m_nAlt;
   }

   void Point::SetAlt(const int nAlt)
   {
      m_nAlt = nAlt;
   }

   // -------------------------------------------------------------------------
   int Point::GetHdg() const
   {
      return m_nHdg;
   }

   void Point::SetHdg(const int nHdg)
   {
      m_nHdg = nHdg;
   }

   // -------------------------------------------------------------------------
   int Point::GetSpd() const
   {
      return m_nSpd;
   }

   void Point::SetSpd(const int nSpd)
   {
      m_nSpd = nSpd;
   }
}; //namespace