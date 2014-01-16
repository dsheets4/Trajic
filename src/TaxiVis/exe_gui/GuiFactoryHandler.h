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
#ifndef GuiFactoryHandler_H
#define GuiFactoryHandler_H

#include <QtCore/QObject>

#include "ObjectBaseWrapper.h"


namespace Gui
{
   //! GraphFactory handler to use signals and slots for asynchronous factory 
   //! access
   class GuiFactoryHandler : public QObject
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      GuiFactoryHandler(QObject *pParent=0);
      GuiFactoryHandler(const GuiFactoryHandler &orig);
      ~GuiFactoryHandler();
      
      // ----------------------------------------------------------------------
      GuiFactoryHandler& operator=( const GuiFactoryHandler &rhs );

      // ----------------------------------------------------------------------
      ObjectBaseWrapperPtr getObject() const;
      void setObject( ObjectBaseWrapperPtr pObject );

   signals:
      // ----------------------------------------------------------------------
      void requestHandled( );

   protected:
      ObjectBaseWrapperPtr  m_pObject;  //!< Pointer to the allocated object
   };

}; //namespace

// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Gui::GuiFactoryHandler);
Q_DECLARE_METATYPE(Gui::GuiFactoryHandler*);

#endif // GuiFactoryHandler_H
