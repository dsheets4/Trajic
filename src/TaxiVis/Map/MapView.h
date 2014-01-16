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
#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QtWebKit/QGraphicsWebView>


namespace Map
{
   //! Represents the Map background.
   class MapView : public QGraphicsWebView
   {
      Q_OBJECT
		
      // ----------------------------------------------------------------------
   public:
      MapView(QGraphicsItem *pParent);
      ~MapView();
   	
      // ----------------------------------------------------------------------

   protected:
      // ----------------------------------------------------------------------

      //! Overrides the QGraphicsWebView so that the image menu doesn't appear
      //! since that menu only operates on the web page but has been integrated
      //! with other graphics.
      void contextMenuEvent ( QGraphicsSceneContextMenuEvent * event );

   protected slots:
      // ----------------------------------------------------------------------


   private:
   };
}; //namespace

#endif // MAPVIEW_H
