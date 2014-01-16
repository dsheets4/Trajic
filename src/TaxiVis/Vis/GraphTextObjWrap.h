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
#ifndef GraphTextObjWrap_H
#define GraphTextObjWrap_H

#include <QtCore/QObject>

#include "Vis/GraphText.h"
#include "Vis/GraphBaseObjWrap.h"


namespace Vis
{
   class GraphTextObjWrap;
   
   //! Smart pointer definition.
   typedef SHARED_POINTER<GraphTextObjWrap> GraphTextObjWrapPtr;


   //! Wrapper class to wrap Graph objects with a QObject to make them 
   //! accessible with signals and slots for uses such as threading.
   class GraphTextObjWrap : public GraphBaseObjWrap
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphTextObjWrap(QObject *pParent=0);
      GraphTextObjWrap(GraphText *pGfxText, QObject *pParent=0);
      GraphTextObjWrap(const GraphTextObjWrap& orig);
      virtual ~GraphTextObjWrap();

      // ----------------------------------------------------------------------
      GraphText* getGraphText() const;
      void setGraphText( GraphText* pGfx );
      
      // ----------------------------------------------------------------------
      GraphTextObjWrap& operator=( const GraphTextObjWrap &rhs );

   public slots:
      // ----------------------------------------------------------------------
      
      //! @copydoc GraphText::setText
      void setText( QString sText );
      
      //! Sets the color of the text.
      //!
      //! @param sColor        String representing the route line color defined by 
      //!                      http://www.w3.org/TR/SVG/types.html#ColorKeywords
      //!                      Color may also take the form of RGB values in 
      //!                      hex such as "#FF0000" for red or #00FF00 for green.
      //! @param fTransparency Transparency of the line on a scale from 0 to 1 
      //!                      with zero being invisible and one being 
      //!                      completely opaque.
      void setColor( QString sColor, qreal fTransparency );
      
      //! @copydoc GraphText::setWidth
      void setWidth( qreal fWidth );
      
   private:
   };
}; //namespace


// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Vis::GraphTextObjWrap);
Q_DECLARE_METATYPE(Vis::GraphTextObjWrap*);
Q_DECLARE_METATYPE(Vis::GraphTextObjWrapPtr);
Q_DECLARE_METATYPE(Vis::GraphTextObjWrapPtr*);


#endif // GraphTextObjWrap_H
