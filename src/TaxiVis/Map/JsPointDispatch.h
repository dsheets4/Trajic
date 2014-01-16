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
#ifndef JsPointDispatch_H
#define JsPointDispatch_H

#include <QtCore/QObject>

#include "TaxiVisUtils.h"
#include "ObjectBaseWrapper.h"
#include "ObjectBaseDispatch.h"


namespace Map
{
   class JsPointDispatch : public ObjectBaseDispatch
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      JsPointDispatch(QObject *pParent=0);
      JsPointDispatch(const JsPointDispatch& orig);
      virtual ~JsPointDispatch();
      

   signals:
      // ----------------------------------------------------------------------
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      unsigned long long getTimeSignal() const;
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setTimeSignal(const unsigned long long llTime);
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      double getLonSignal() const;
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setLonSignal(const double fLon);
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      double getLatSignal() const;
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setLatSignal(const double fLat);
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      int getAltSignal() const;
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setAltSignal(const int nAlt);
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      int getHdgSignal() const;
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setHdgSignal(const int nHdg);
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      int getSpdSignal() const;
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setSpdSignal(const int nSpd);


   public slots:
      // ----------------------------------------------------------------------
      unsigned long long getTime() const;
      void setTime(const unsigned long long llTime);

      double getLon() const;
      void setLon(const double fLon);

      double getLat() const;
      void setLat(const double fLat);

      int getAlt() const;
      void setAlt(const int nAlt);

      int getHdg() const;
      void setHdg(const int nHdg);

      int getSpd() const;
      void setSpd(const int nSpd);

   };
}; //namespace

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Map::JsPointDispatch);
Q_DECLARE_METATYPE(Map::JsPointDispatch*);

#endif // JsPointDispatch_H
