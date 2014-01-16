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

//!@todo Remove the iostream used to report errors in the 
//!      DataAccess::ExecuteQuery function when the QueryHandler is provided
//!      and able to propagate the error message.  This will allow the SQL
//!      implementation to more seamlessly integrate with output to locations
//!      other than STDERR.
#include <iostream>

#include <QtSql/QSqlError>

#include "DataAccess/QueryFunctions.h"


namespace DataAccess
{
   
   // -------------------------------------------------------------------------
   bool ExecuteQuery( QSqlQuery& q, const QString& sQuery )
   {
      if( !q.exec(sQuery) )
      {
	      QSqlError err = q.lastError();
	      std::cerr << "Error executing query: " << std::endl;
         std::cerr << "    Query: " << qPrintable(sQuery) << std::endl;
         std::cerr << "    Error: " << qPrintable( err.text() ) << std::endl;
         return true;
      }

      return false; // Success!
   }

}; // namespace