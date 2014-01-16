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
#ifndef QUERYROUTECRITERIA_H
#define QUERYROUTECRITERIA_H

#include <QtCore/QDateTime>

#include "DataAccess/QueryRouteHandler.h"


namespace DataAccess
{
   // -------------------------------------------------------------------------
   //!
   class QueryRouteCriteria
   {
   public:   
      // ----------------------------------------------------------------------
      QueryRouteCriteria();
      ~QueryRouteCriteria();

      // ----------------------------------------------------------------------
   
      const QDateTime& GetTimeStart() const;
      void SetTimeStart( const QDateTime& time );

      const QDateTime& GetTimeEnd() const;
      void SetTimeEnd( const QDateTime& time );

   protected:
      // ----------------------------------------------------------------------
      QDateTime m_dtStart;     //!< Start time for the query
      QDateTime m_dtEnd;       //!< End time for the query
   };
}; //namespace

#endif // QUERYROUTECRITERIA_H
