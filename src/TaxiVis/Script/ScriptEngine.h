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
#ifndef ScriptEngine_H
#define ScriptEngine_H

#include <QtCore/QObject>

#include "Script/ScriptConfig.h"


namespace Script
{
   //! Defines the script engine, which executes scripts.
   class ScriptEngine : public QObject
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      ScriptEngine();
      ~ScriptEngine();
      

      // ----------------------------------------------------------------------
      QScriptEngine* getEngine();


   signals:
      // ----------------------------------------------------------------------
      void terminated();

      
   public slots:
      // ----------------------------------------------------------------------
      void evaluateFile( QString sScriptFile );
      void evaluateString( QString sScriptString );
      
      //! Lists out all the objects currently available in the scripting.  It is
      //! useful to determine available functions in the scripting language, 
      //! specifically in conjunction with show.
      //!
      //! @sa show
      void list();
      
      //! Lists the properties and the functions available on the given object.
      //!
      //! @param value  Script object to show functions and properties.
      void show(const QScriptValue& value);
      
      //! Loads a script file that can contain reusable function definitions
      //! into the scripting language.
      //!
      //! @param sExtension  Path to the file containing the extension to load.
      //! 
      //! @retval "undefined"       If the extension is imported successfully.
      //! @retval "Exception Value" If the extension is not imported successfully.
      QScriptValue importExtension(QString sExtension);

      //! Initiates shutdown of the application
      void quit();


   protected:
      // ----------------------------------------------------------------------
      QScriptValue evaluate( QString sScriptFile );


      // ----------------------------------------------------------------------
      QScriptEngine* m_pEng;  //!< Pointer to the Script Engine.
   };
}; //namespace

#endif // ScriptEngine_H
