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

#include "DataAccess/DataRoute.h"


namespace DataAccess
{
   // -------------------------------------------------------------------------
   const unsigned int Route::InvalidTaxiId = 0xFFFFFFFF;

   // -------------------------------------------------------------------------
   Route::Route()
      : m_sTaxiPlate()
      , m_nTaxiId(InvalidTaxiId)
      , m_nRouteId(0)
      , m_vRoute()
   {
   }

   // -------------------------------------------------------------------------
   Route::~Route()
   {
   }


   // -------------------------------------------------------------------------
   const QString Route::GetTaxiPlate() const
   {
      return m_sTaxiPlate;
   }

   void Route::SetTaxiPlate(const QString sTaxiPlate)
   {
      m_sTaxiPlate = sTaxiPlate;
   }

   // -------------------------------------------------------------------------
   unsigned int Route::GetTaxiId() const
   {
      return m_nTaxiId;
   }

   void Route::SetTaxiId(const unsigned int nTaxiId)
   {
      m_nTaxiId = nTaxiId;
   }

   // -------------------------------------------------------------------------
   unsigned int Route::GetRouteId() const
   {
      return m_nRouteId;
   }

   void Route::SetRouteId(const unsigned int nRouteId)
   {
      m_nRouteId = nRouteId;
   }

   // -------------------------------------------------------------------------
   const PointVector& Route::GetRoute() const
   {
      return m_vRoute;
   }

   // -------------------------------------------------------------------------
   void Route::AddPoint(const Point& p)
   {
      m_vRoute.push_back(p);
   }

   // -------------------------------------------------------------------------
   void Route::ClearRoute()
   {
      m_vRoute.clear();
   }
}; // namespace