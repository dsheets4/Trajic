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
#ifndef JsPointIconDispatch_H
#define JsPointIconDispatch_H

#include <QtCore/QObject>

#include "ObjectBaseDispatch.h"


namespace Map
{
   class JsPointIconDispatch : public ObjectBaseDispatch
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      JsPointIconDispatch(QObject *pParent=0);
      JsPointIconDispatch(const JsPointIconDispatch& orig);
      virtual ~JsPointIconDispatch();
      
      // ----------------------------------------------------------------------
      JsPointIconDispatch& operator=( const JsPointIconDispatch& rhs );
      
      // ----------------------------------------------------------------------
      ObjectBaseWrapperPtr getObjWrap();
      void setObjWrap( ObjectBaseWrapperPtr pObj );
      

   signals:
      // ----------------------------------------------------------------------
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setColorSignal( QString sColor, qreal fTransparency );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setWeightSignal( int nWeight );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void addPointSignal( unsigned long long llTime, qreal lon, qreal lat, qreal hdg, qreal spd );


   public slots:
      // ----------------------------------------------------------------------
      
      //! @copydoc JsPointIcon::setColor
      void setColor( QString sColor, qreal fTransparency );
      
      //! @copydoc JsPointIcon::setColor
      void setWeight( int nWeight );
      
      //! @copydoc JsPointIcon::setColor
      void addPoint( unsigned long long llTime, qreal lon, qreal lat, qreal hdg, qreal spd );
      

   protected:
      // ----------------------------------------------------------------------
      ObjectBaseWrapperPtr m_pObj; //!< Object that is connected to this dispatch.

   };
}; //namespace

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Map::JsPointIconDispatch);
Q_DECLARE_METATYPE(Map::JsPointIconDispatch*);

#endif // JsPointIconDispatch_H
