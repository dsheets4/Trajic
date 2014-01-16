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
#ifndef JsPointIcon_H
#define JsPointIcon_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>

#include <QtGui/QColor>

#include "TaxiVisUtils.h"
#include "DataAccess/DataRoute.h"
#include "Map/MapObject.h"
#include "Map/JsPoint.h"


namespace Map
{
   // Forward declaration of the class just so the pointer definition isn't
   // hidden at the bottom of the file after the class definition.
   class JsPointIcon;

   //! Smart pointer definition used for passing around JsPointIcon pointers.
   typedef SHARED_POINTER<JsPointIcon> JsPointIconPtr;


   //! Wraps the DataAccess Route so that it can be exposed to JavaScript.
   class JsPointIcon : public MapObject
   {
      Q_OBJECT
		
   public:
      // ----------------------------------------------------------------------
      static const DataAccess::PointVector::size_type iStartIteration;

      // ----------------------------------------------------------------------
      JsPointIcon(QObject *pParent);
      JsPointIcon(DataAccess::RoutePtr pRoute, QObject *pParent);
      ~JsPointIcon();
   
      // ----------------------------------------------------------------------
      void setRoute( DataAccess::RoutePtr pRoute );


   public slots:
      // ----------------------------------------------------------------------
      // Script exposed methods
   
      // ----------------------------------------------------------------------
      
      //! Adds a point to the route.  Route lines are drawn from point to point 
      //! in the order they are added to the route.
      //!
      //! @param llTime Milliseconds since midnight Jan 1, 1970 to the time at 
      //!               which this point was captured.
      //! @param lon    GPS longitiude
      //! @param lat    GPS latitude
      //! @param hdg    True Heading in degrees.  Provides vector direction
      //! @param spd    Km/hr speed of the point to complete the vector.
      void addPoint( unsigned long long llTime, qreal lon, qreal lat, qreal hdg, qreal spd );

      //! Returns an array of JsPoint objects representing the route.
      QObjectList getPoints();
   
      
      // ----------------------------------------------------------------------
      //! Get the color of the route.
      QColor getColor();

      //! Set the color of the route.
      void setColor(const QColor& color);
      
      //! Sets the color of the route and an option transparency.
      //!
      //! @param sColor        String representing the route line color defined by 
      //!                      http://www.w3.org/TR/SVG/types.html#ColorKeywords
      //!                      Color may also take the form of RGB values in 
      //!                      hex such as "#FF0000" for red or #00FF00 for green.
      //! @param fTransparency Transparency of the line on a scale from 0 to 1 
      //!                      with zero being invisible and one being 
      //!                      completely opaque.
      void setColor(QString sColor, qreal fTransparency=1.0);

      // Get the color string for the route.
      QString getColorString();

      //! Get the opacity of the route as a floating points.  Note that opacity
      //! is set with the color.
      double getOpacity();

      //! Get the route weight.
      int getWeight();
      
      //! Sets the weight, or line width of the route line.
      //!
      //! @param nWeight  Width of the route line.
      void setWeight(int nWeight);

   protected:
      // ----------------------------------------------------------------------
      DataAccess::PointVector::size_type m_nPos; //!< Position of the current value.

      DataAccess::RoutePtr   m_pRoute;   //!< Route
      QColor                 m_color;    //!< Color for the route
      int                    m_nWeight;  //!< Weight (e.g. width) of route line
   };
}; //namespace

#endif // JsPointIcon_H
