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
#ifndef QUERYFUNCTIONS_H
#define QUERYFUNCTIONS_H

#include <QtCore/QString>

#include <QtSql/QSqlQuery>


namespace DataAccess
{
   
   // -------------------------------------------------------------------------
   //! Helper function for executing queries.
   bool ExecuteQuery( QSqlQuery& q, const QString& sQuery );
   
   // -------------------------------------------------------------------------
   //! Function to handle the last error from the QSql API.
   //! @todo Implement the DataAccess::HandleLastError call. Requires creation 
   //!       of a QueryHandler base class that QueryRouteHandler can inherit.
   //!void HandleLastError( QueryHandler& handler );

}; //namespace

#endif // QUERYFUNCTIONS_H
