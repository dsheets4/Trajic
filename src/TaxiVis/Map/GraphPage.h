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
#ifndef GraphPage_H
#define GraphPage_H

#include "HtmlPage.h"


namespace Map
{
   //! Represents the Map background.
   class GraphPage : public HtmlPage
   {
      Q_OBJECT
		
   public:
      // ----------------------------------------------------------------------
      GraphPage(QObject *pParent);
      ~GraphPage();

   public slots:
      // ----------------------------------------------------------------------

      QString getCsvFile();
      void setCsvFile(const QString& sCsvFile);
      
      qreal getValueThresh();
      void setValueThresh(qreal fValueThresh);
      
      int getTopicThresh();
      void setTopicThresh(int nTopicThresh);
      
      QStringList getTopicColors();
      void setTopicColors(QStringList lstTopicColors);
   

   protected slots:
      // ----------------------------------------------------------------------

      //! Registers the JavaScript objects with the QWebFrame via QtWebKit bridge.
      void RegisterJavascriptObjects();


   protected:
      // ----------------------------------------------------------------------
      QStringList m_lstTopicColors; //!< List of colors to use for the topics.

      QString m_sCsvFile;      //!< Path to the CSV file
      qreal   m_fValueThresh;  //!< Value that roads must meet/exceed to be viewed
      int     m_nTopicThresh;  //!< Num topics that meet the value threshold for road to be viewed.

   };
}; //namespace

#endif // GraphPage_H
