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

#include <QtScript/QScriptEngine>

#include "Vis/GraphPcScriptProto.h"


namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphPcScriptProto::GraphPcScriptProto(QObject *pParent)
      : QObject(pParent)
   {
   }

   // -------------------------------------------------------------------------
   GraphPcScriptProto::~GraphPcScriptProto()
   {
   }


   // =========================================================================
   // Script Accessible methods
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphPcScriptProto::setBackgroundColor( QString sColor, qreal fTransparency )
   {
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setBackgroundColor( sColor, fTransparency );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphPcScriptProto::setCoordinateScale( QString sType )
   {
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setCoordinateScale( sType );
      }
   }

   // -------------------------------------------------------------------------
   void GraphPcScriptProto::setGain( double fGain )
   {
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setGain( fGain );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphPcScriptProto::setOffset( double fOffset )
   {
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setOffset( fOffset );
      }
   }

   // -------------------------------------------------------------------------
   void GraphPcScriptProto::setYMax( double fYMax )
   {
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setYMax( fYMax );
      }
         
   }
      
   // -------------------------------------------------------------------------
   void GraphPcScriptProto::setYMin( double fYMin )
   {
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->setYMin( fYMin );
      }
         
   }
      
   // -------------------------------------------------------------------------
   void GraphPcScriptProto::addCoordinate( QString sLabel )
   {
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->addCoordinate( sLabel );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphPcScriptProto::removeCoordinate( int nIndex )
   {
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->removeCoordinate( nIndex );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphPcScriptProto::removeAllCoordinates()
   {
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->removeAllCoordinates( );
      }
   }
      
   // -------------------------------------------------------------------------
   void GraphPcScriptProto::addLine( QVariantList fListValues, QString sColor, qreal fTransparency )
   {
      //!@todo Add transparency to the Parallel Coordinate lines.  Overall it 
      //!      might not be too useful but it would be an interesting thing to
      //!      play with and see if it offers any insights.
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->addLine( fListValues, sColor, fTransparency );
      }
   }
   
   // -------------------------------------------------------------------------
   void GraphPcScriptProto::removeAllLines( )
   {
      GraphPcDispatch* pDispatch = thisDispatch();

      if( pDispatch )
      {
         pDispatch->removeAllLines( );
      }
   }
   
   
   // =========================================================================
   // Implementation (not script accessible)
   // =========================================================================
   GraphPcDispatch* GraphPcScriptProto::thisDispatch() const
   {
      GraphBaseDispatchPtr *ptr = qscriptvalue_cast<GraphBaseDispatchPtr*>(thisObject().data());

      if( ptr )
      {
         return dynamic_cast<GraphPcDispatch*>(ptr->get());
      }

      return NULL;
   }

}; //namespace