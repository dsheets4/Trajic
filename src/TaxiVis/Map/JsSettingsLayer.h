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
#ifndef JsSettingsLayer_H
#define JsSettingsLayer_H

#include <QtCore/QObject>
#include <QtCore/QDateTime>

#include <QtGui/QColor>


namespace Map
{
   //! Map settings object that is exposed to the JavaScript.
   class JsSettingsLayer : public QObject
   {
      Q_OBJECT
		
   public:
      // ----------------------------------------------------------------------
      JsSettingsLayer(QObject *pParent);
      JsSettingsLayer(const JsSettingsLayer& orig);
      ~JsSettingsLayer();

	  
      // ----------------------------------------------------------------------
	  JsSettingsLayer& operator=( const JsSettingsLayer& rhs );
   

   public slots:
   
      // ----------------------------------------------------------------------
   
      //! Get the color of the route.
      QColor getColor() const;

      //! Set the color of the route.
      void setColor(const QColor& color);

      // Get the color string for the route.
      QString getColorString() const;

      double getOpacity() const;
      void setOpacity(double opacity);
   
      //! Get the route weight.
      int getWeight() const;

      //! Set the route weight
      void setWeight(int nWeight);


   protected:
      // ----------------------------------------------------------------------
      QColor    m_color;      //!< Default color to give routes
      int       m_nWeight;    //!< Default weight to give routes
      double    m_fOpacity;   //!< Transparency of the line
   };
}; //namespace

#endif // JsSettingsLayer_H
