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
#ifndef GraphPieObjWrap_H
#define GraphPieObjWrap_H

#include <QtCore/QObject>

#include "Vis/GraphPie.h"
#include "Vis/GraphBaseObjWrap.h"


namespace Vis
{
   class GraphPieObjWrap;
   
   //! Smart pointer definition.
   typedef SHARED_POINTER<GraphPieObjWrap> GraphPieObjWrapPtr;


   //! Wrapper class to wrap Graph objects with a QObject to make them 
   //! accessible with signals and slots for uses such as threading.
   class GraphPieObjWrap : public GraphBaseObjWrap
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphPieObjWrap(QObject *pParent=0);
      GraphPieObjWrap(GraphPie* pGfxPie, QObject *pParent=0);
      GraphPieObjWrap(const GraphPieObjWrap& orig);
      virtual ~GraphPieObjWrap();

      // ----------------------------------------------------------------------
      GraphPie* getGraphPie() const;
      void setGraphPie( GraphPie* pGfx );
      
      // ----------------------------------------------------------------------
      GraphPieObjWrap& operator=( const GraphPieObjWrap &rhs );

   public slots:
      // ----------------------------------------------------------------------
      
      //! Creates a slice in the pie graph.  The values will be cumulated and 
      //! each slice given a proportionate section of the overall pie.
      //!
      //! @param fValue        Value the slice represents.
      //! @param sColor        String representing the route line color defined by 
      //!                      http://www.w3.org/TR/SVG/types.html#ColorKeywords
      //!                      Color may also take the form of RGB values in 
      //!                      hex such as "#FF0000" for red or #00FF00 for green.
      //! @param fTransparency Transparency of the line on a scale from 0 to 1 
      //!                      with zero being invisible and one being 
      //!                      completely opaque.
      void createSlice( double fValue, QString sColor, double fTransparency );
      
   private:
   };
}; //namespace


// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Vis::GraphPieObjWrap);
Q_DECLARE_METATYPE(Vis::GraphPieObjWrap*);
Q_DECLARE_METATYPE(Vis::GraphPieObjWrapPtr);

#endif // GraphPieObjWrap_H
