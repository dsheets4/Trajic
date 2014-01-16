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

#include <iostream>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QCoreApplication>

#include <QtScript/QScriptEngine>

#include "Script/ScriptPrompt.h"

#include "CommonDefinitions.h"
#include "Map/MapPage.h"


// ============================================================================
using namespace std;


namespace Script
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   ScriptPrompt::ScriptPrompt()
      : m_bQuit(false)
   {
   }

   // -------------------------------------------------------------------------
   ScriptPrompt::~ScriptPrompt()
   {
   }


   // =========================================================================
   // Implementation Methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   void ScriptPrompt::interactive()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Setup the prompt strings
      QTextStream qin(stdin, QFile::ReadOnly);

      std::string sPrompt = CommonDefinitions::sAppName + "> ";
      std::string sDotPrompt;
      for( std::string::size_type i = 0; i < sPrompt.length()-1; ++i )
      {
         sDotPrompt += ".";
      }
      sDotPrompt += " ";

      std::string *prompt = &sPrompt;

      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      QString code;

      // Begin the prompt loop.
      while( !m_bQuit )
      {
         QString line;

         std::cout << (*prompt);
         fflush(stdout);

         //! @todo Figure out how to interrupt the readLine for the script 
         //!       prompt so that the application can exit properly with the
         //!       graphical exit rather than only from the quit() command.
         line = qin.readLine();
         if (line.isNull())
            break;

         code += line;
         code += QLatin1Char('\n');

         if (line.trimmed().isEmpty())
         {
            // User entered a blank line, nothing to do here.
            continue;
         }
         //!@todo Implement a communication layer for the prompt and the 
         //!      script to communicate and re-enable the multi-line input.
         //!else if (! m_pEng->canEvaluate(code))
         //!{
         //!   // User is entering a multi-line input.
         //!   prompt = &sDotPrompt;
         //!}
         else
         {
            // All input received.  Process the input!
            emit command( code );
            //!@todo What is the benefit of the second argument here?
            //!QScriptValue result = m_pEng->evaluate(code, QLatin1String("typein"));

            code.clear();
            prompt = &sPrompt;
         }
      }
   }

   // -------------------------------------------------------------------------
   void ScriptPrompt::cmdPrompt()
   {      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Go into interactive mode to allow user input.
      interactive();           // This will loop until user exits.
      emit cmdPromptExited();  // When user exits inform listeners.
   }

   
   // =========================================================================
   // Slots
   // =========================================================================

   // -------------------------------------------------------------------------
   void ScriptPrompt::quit()
   {
      m_bQuit = true;
   }

}; //namespace