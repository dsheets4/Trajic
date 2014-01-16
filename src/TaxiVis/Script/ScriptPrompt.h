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
#ifndef ScriptPrompt_H
#define ScriptPrompt_H

#include <QtCore/QObject>

#include "Script/ScriptConfig.h"


namespace Script
{
   //! Defines the underlying core of the script interface.
   class ScriptPrompt : public QObject
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      ScriptPrompt();
      ~ScriptPrompt();
      

   signals:
      // ----------------------------------------------------------------------
      void command( QString sCommand );
      void cmdPromptExited();


   public slots:
      // ----------------------------------------------------------------------
      void cmdPrompt();
      void quit();


   protected:
      // ----------------------------------------------------------------------
      void interactive();
      

      // ----------------------------------------------------------------------
      bool m_bQuit;  //!< Indicates whether to exit the command prompt
   };
}; //namespace

#endif // ScriptPrompt_H
