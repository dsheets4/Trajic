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

#include <sstream>
#include <iostream>

#include <QtCore/QDateTime>

#include <QtWebKit/QWebFrame>

#include <QtSql/QSqlDatabase>

#include "Map/JsRoute.h"


namespace Map
{
   
   // =========================================================================
   // =========================================================================
   const DataAccess::PointVector::size_type JsRoute::iStartIteration = static_cast<DataAccess::PointVector::size_type>(-1);


   // =========================================================================
   // =========================================================================
   // Construction and destruction

   // -------------------------------------------------------------------------
   JsRoute::JsRoute(QObject *pParent)
      : MapObject(pParent)
      , m_nPos(iStartIteration)
      , m_pRoute( new DataAccess::Route() )
      , m_color(255,0,0,128)
      , m_nWeight(5)
   {
   }

   // -------------------------------------------------------------------------
   JsRoute::JsRoute(DataAccess::RoutePtr pRoute, QObject *pParent)
      : MapObject(pParent)
      , m_nPos(-1)
      , m_pRoute(pRoute)
      , m_color(255,0,0,128)
      , m_nWeight(5)
   {
   }


   // --------------------------------------------------------------------------
   JsRoute::~JsRoute()
   {

   }

   // --------------------------------------------------------------------------
   void JsRoute::setRoute( DataAccess::RoutePtr pRoute )
   {
      m_pRoute = pRoute;
   }


   // =========================================================================
   // JavaScript exposed
   // =========================================================================
      
   // -------------------------------------------------------------------------
   QObjectList JsRoute::getPoints()
   {
      QObjectList objList;

      const DataAccess::PointVector& route = m_pRoute->GetRoute();
      DataAccess::PointVector::const_iterator i = route.begin();
      for( ; i != route.end(); ++i )
      {
         objList.append( new JsPoint( (*i), this) );
      }

      return objList;
   }
   
   // -------------------------------------------------------------------------
   void JsRoute::addPoint( unsigned long long llTime, qreal lon, qreal lat, qreal hdg, qreal spd )
   {
      DataAccess::Point p;
      p.SetTime(llTime);
      p.SetLon(lon);
      p.SetLat(lat);
      p.SetHdg(hdg);
      p.SetSpd(spd);
      m_pRoute->AddPoint( p );
   }
   
   // -------------------------------------------------------------------------
   QColor JsRoute::getColor()
   {
      return m_color;
   }

   void JsRoute::setColor( const QColor& color )
   {
      m_color = color;
   }
   
   void JsRoute::setColor(QString sColor, qreal fTransparency)
   {
      QColor color(sColor);
      color.setAlphaF(fTransparency);
      setColor( color );
   }

   QString JsRoute::getColorString()
   {
      return m_color.name();
   }

   double JsRoute::getOpacity()
   {
      return m_color.alphaF();
   }

   // -------------------------------------------------------------------------
   int JsRoute::getWeight()
   {
      return m_nWeight;
   }

   void JsRoute::setWeight( int nWeight )
   {
      m_nWeight = nWeight;
   }
}; //namespace