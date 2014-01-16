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
#ifndef GraphTextDispatch_H
#define GraphTextDispatch_H

#include <QtCore/QObject>

#include "Vis/GraphBaseDispatch.h"


namespace Vis
{
   //! Represents a bar GraphTextDispatch.
   class GraphTextDispatch : public GraphBaseDispatch
   {		
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GraphTextDispatch(QObject *pParent);
      virtual ~GraphTextDispatch();

      
   signals:
      // ----------------------------------------------------------------------
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setTextSignal( QString sText );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setColorSignal( QString sColor, qreal fTransparency );
      
      //! Signal is emitted from the slot to allow for cross-thread communication.
      void setWidthSignal( qreal fWidth );


   public slots:
      // ----------------------------------------------------------------------
      
      //! @copydoc GraphText::setText
      void setText( QString sText );
      
      //! @copydoc GraphTextObjWrap::setColor
      void setColor( QString sColor, qreal fTransparency );
      
      //! @copydoc GraphText::setWidth
      void setWidth( qreal fWidth );

   };
}; //namespace

#endif // GraphTextDispatch_H
