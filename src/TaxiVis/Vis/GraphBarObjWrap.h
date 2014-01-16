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
#ifndef GraphBarObjWrap_H
#define GraphBarObjWrap_H

#include <QtCore/QObject>

#include "Vis/GraphBar.h"
#include "Vis/GraphBaseObjWrap.h"


namespace Vis
{
   class GraphBarObjWrap;
   
   //! Smart pointer definition.
   typedef SHARED_POINTER<GraphBarObjWrap> GraphBarObjWrapPtr;


   //! Wrapper class to wrap Graph objects with a QObject to make them 
   //! accessible with signals and slots for uses such as threading.
   class GraphBarObjWrap : public GraphBaseObjWrap
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphBarObjWrap(QObject *pParent=0);
      GraphBarObjWrap(GraphBar *pGfxBar, QObject *pParent=0);
      GraphBarObjWrap(const GraphBarObjWrap& orig);
      virtual ~GraphBarObjWrap();

      // ----------------------------------------------------------------------
      GraphBar* getGraphBar() const;
      void setGraphBar( GraphBar* pGfx );
      
      // ----------------------------------------------------------------------
      GraphBarObjWrap& operator=( const GraphBarObjWrap &rhs );

   public slots:
      // ----------------------------------------------------------------------
      
      //! Adds a bar to the bar graph.
      //!
      //! @param fValue        Value associated with this bar.  The bar graph 
      //!                      will scale all the bars according to the 
      //!                      largest value.
      //! @param sColor        String representing the route line color defined by 
      //!                      http://www.w3.org/TR/SVG/types.html#ColorKeywords
      //!                      Color may also take the form of RGB values in 
      //!                      hex such as "#FF0000" for red or #00FF00 for green.
      //! @param fTransparency Transparency of the line on a scale from 0 to 1 
      //!                      with zero being invisible and one being 
      //!                      completely opaque.
      void createBar( double fValue, QString sColor, double fTransparency );
      
   private:
   };
}; //namespace


// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Vis::GraphBarObjWrap);
Q_DECLARE_METATYPE(Vis::GraphBarObjWrap*);
Q_DECLARE_METATYPE(Vis::GraphBarObjWrapPtr);
Q_DECLARE_METATYPE(Vis::GraphBarObjWrapPtr*);


#endif // ObjWrapGraphBar_H
