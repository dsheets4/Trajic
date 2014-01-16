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

#include "GraphPageDispatch.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPageDispatch::GraphPageDispatch(QObject *pParent)
      : ObjectBaseDispatch( pParent )
   {
   }
   
   // -------------------------------------------------------------------------
   GraphPageDispatch::GraphPageDispatch(const GraphPageDispatch& orig)
      : ObjectBaseDispatch(0)
   {
   }

   // -------------------------------------------------------------------------
   GraphPageDispatch::~GraphPageDispatch()
   {
   }

      
   // =========================================================================
   // Implementation
   // =========================================================================
   
   
   // =========================================================================
   // Operators
   // =========================================================================
      

   // =========================================================================
   // Slots
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphPageDispatch::setCsvFile( QString sCsvFile )
   {
      emit setCsvFileSignal( sCsvFile );
   }
   
   // -------------------------------------------------------------------------
   void GraphPageDispatch::setValueThresh( qreal fValueThresh )
   {
      emit setValueThreshSignal( fValueThresh );
   }
   
   // -------------------------------------------------------------------------
   void GraphPageDispatch::setTopicThresh( int nTopicThresh )
   {
      emit setTopicThreshSignal( nTopicThresh );
   }
   
   // -------------------------------------------------------------------------
   void GraphPageDispatch::setTopicColors( QStringList nTopicColors )
   {
      emit setTopicColorsSignal( nTopicColors );
   }
};