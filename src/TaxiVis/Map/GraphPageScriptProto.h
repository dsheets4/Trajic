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
#ifndef GraphPageScriptProto_H
#define GraphPageScriptProto_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>
#include <QtScript/QScriptEngine>

#include "Map/GraphPageDispatch.h"


namespace Map
{
   //! Represents a bar GraphPageScriptProto.
   class GraphPageScriptProto : public QObject, public QScriptable
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphPageScriptProto(QObject *pParent);
      virtual ~GraphPageScriptProto();

      
   public slots:
      // ----------------------------------------------------------------------
      void setCsvFile( QString sCsvFile );
      void setValueThresh( qreal fValueThresh );
      void setTopicThresh( int nTopicThresh );
      void setTopicColors(QStringList lstTopicColors);


   private:
      // ----------------------------------------------------------------------
      GraphPageDispatch* thisDispatch() const;

   };
}; //namespace

#endif // GraphPageScriptProto_H
