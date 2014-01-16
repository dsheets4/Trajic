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
#ifndef GraphPcObjWrap_H
#define GraphPcObjWrap_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "Vis/GraphPc.h"
#include "Vis/GraphBaseObjWrap.h"


namespace Vis
{
   class GraphPcObjWrap;
   
   //! Smart pointer definition.
   typedef SHARED_POINTER<GraphPcObjWrap> GraphPcObjWrapPtr;


   //! Wrapper class to wrap Graph objects with a QObject to make them 
   //! accessible with signals and slots for uses such as threading.
   class GraphPcObjWrap : public GraphBaseObjWrap
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphPcObjWrap(QObject *pParent=0);
      GraphPcObjWrap(GraphPc *pGfx, QObject *pParent=0);
      GraphPcObjWrap(const GraphPcObjWrap& orig);
      virtual ~GraphPcObjWrap();

      // ----------------------------------------------------------------------
      GraphPc* getGraphPc() const;
      void setGraphPc( GraphPc* pGfx );
      
      // ----------------------------------------------------------------------
      GraphPcObjWrap& operator=( const GraphPcObjWrap &rhs );

   public slots:
      // ----------------------------------------------------------------------
      void setYMax( double fYMax );
      
      void setYMin( double fYMin );
      
      //! Sets the background color of the Parallel Coordinates graphical item.
      //!
      //! @param sColor        String representing the route line color defined by 
      //!                      http://www.w3.org/TR/SVG/types.html#ColorKeywords
      //!                      Color may also take the form of RGB values in 
      //!                      hex such as "#FF0000" for red or #00FF00 for green.
      //! @param fTransparency Transparency of the line on a scale from 0 to 1 
      //!                      with zero being invisible and one being 
      //!                      completely opaque.
      void setBackgroundColor( QString sColor, qreal fTransparency );
      
      void setCoordinateScale( QString sType );
      void setGain( qreal fGain );
      void setOffset( qreal fOffset );
      
      //! @copydoc GraphPc::addCoordinate
      void addCoordinate( QString sLabel );
      
      //! @copydoc GraphPc::removeCoordinate
      void removeCoordinate( int nIndex );
      
      //! @copydoc GraphPc::removeAllCoordinates
      void removeAllCoordinates();
      
      //! Adds a line to the parallel coordinates graph.  The line must 
      //! contain the same number of points as there are coordinates.  
      //! Therefore, be sure to call addCoordinate for every coordinate that 
      //! is needed before adding the first line.
      //!
      //! @param fListValues   List of points representing a line drawn from 
      //!                      one coordinate to the next.  Size of the list 
      //!                      must match the number of coordinates.
      //! @param sColor        String representing the route line color defined by 
      //!                      http://www.w3.org/TR/SVG/types.html#ColorKeywords
      //!                      Color may also take the form of RGB values in 
      //!                      hex such as "#FF0000" for red or #00FF00 for green.
      void addLine( QVariantList fListValues, QString sColor, qreal fTransparency=1.0 );
      
      //! @copydoc GraphPc::removeAllLines
      void removeAllLines( );
      
   };
}; //namespace


// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Vis::GraphPcObjWrap);
Q_DECLARE_METATYPE(Vis::GraphPcObjWrap*);
Q_DECLARE_METATYPE(Vis::GraphPcObjWrapPtr);
Q_DECLARE_METATYPE(Vis::GraphPcObjWrapPtr*);


#endif // ObjWrapGraphPc_H
