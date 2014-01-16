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

#include "Map/JsSettingsLayer.h"


namespace Map
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   JsSettingsLayer::JsSettingsLayer(QObject *pParent)
      : QObject(pParent)
      , m_color( QColor(255,0,0) )
      , m_nWeight(3)
      , m_fOpacity(0.3)
   {
   }

   // -------------------------------------------------------------------------
   JsSettingsLayer::JsSettingsLayer( const JsSettingsLayer& orig )
      : QObject(orig.parent())
      , m_color( orig.getColor() )
      , m_nWeight( orig.getWeight() )
      , m_fOpacity(orig.getOpacity())
   {
   }

   // -------------------------------------------------------------------------
   JsSettingsLayer::~JsSettingsLayer()
   {

   }

   // =========================================================================
   // Implementation
   // =========================================================================

   // -------------------------------------------------------------------------
   JsSettingsLayer& JsSettingsLayer::operator=( const JsSettingsLayer& rhs )
   {
      if( this != &rhs )
      {
         this->m_color    = rhs.m_color;
         this->m_nWeight  = rhs.m_nWeight;
         this->m_fOpacity = rhs.m_fOpacity;
      }

      return (*this);
   }


   // =========================================================================
   // Action handlers
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QColor JsSettingsLayer::getColor() const
   {
      return m_color;
   }

   void JsSettingsLayer::setColor( const QColor& color )
   {
      m_color = color;
   }

   QString JsSettingsLayer::getColorString() const
   {
      return m_color.name();
   }

   // -------------------------------------------------------------------------
   double JsSettingsLayer::getOpacity() const
   {
      return m_fOpacity;
   }

   void JsSettingsLayer::setOpacity(double opacity)
   {
      m_fOpacity = opacity;
   }

   // -------------------------------------------------------------------------
   int JsSettingsLayer::getWeight() const
   {
      return m_nWeight;
   }

   void JsSettingsLayer::setWeight( int nWeight )
   {
      m_nWeight = nWeight;
   }

}; //namespace