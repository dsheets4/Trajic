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
#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <vector>


namespace DataAccess
{
   class Point;

   // -------------------------------------------------------------------------
   typedef std::vector<Point>    PointVector;

   // -------------------------------------------------------------------------
   //! Represents a point on the map.
   class Point
   {
   public:
      // ----------------------------------------------------------------------
      Point();
      ~Point();
   
      // ----------------------------------------------------------------------
      unsigned long long GetTime() const;
      void SetTime(const unsigned long long llTime);

      double GetLon() const;
      void SetLon(const double fLon);

      double GetLat() const;
      void SetLat(const double fLat);

      int GetAlt() const;
      void SetAlt(const int nAlt);

      int GetHdg() const;
      void SetHdg(const int nHdg);

      int GetSpd() const;
      void SetSpd(const int nSpd);

   protected:
      // ----------------------------------------------------------------------
      unsigned long long m_llTime; //!< Time in ms since midnight Jan 1, 1970
      double             m_fLon;   //!< Decimal longitude
      double             m_fLat;   //!< Decimal latitude
      int                m_nAlt;   //!< Altitude of the point
      int                m_nHdg;   //!< Heading data for the point
      int                m_nSpd;   //!< Speed of the point
   };
}; //namespace

#endif // DATAPOINT_H
