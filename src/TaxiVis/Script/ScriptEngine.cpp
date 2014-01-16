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
#include <QtScript/QScriptValueIterator>

#include "Script/ScriptEngine.h"

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
   ScriptEngine::ScriptEngine()
      : m_pEng( new QScriptEngine() )
   {      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Register the engine object and create convenience references.
      QScriptValue valueEng = m_pEng->newQObject(this, QScriptEngine::QtOwnership);
      m_pEng->globalObject().setProperty("eng", valueEng);
      evaluate( "quit   = eng.quit" );
      evaluate( "run    = eng.evaluateFile" );
      evaluate( "list   = eng.list" );
      //!@todo Figure out why show and importExtension don't work.  I think 
      //!      it's because of the QScriptValue argument or return value but I 
      //!      could be wrong
      //evaluate( "show   = eng.show" );
      //evaluate( "import = eng.importExtension" );
   }

   // -------------------------------------------------------------------------
   ScriptEngine::~ScriptEngine()
   {
      delete m_pEng;
      m_pEng = NULL;
   }


   // =========================================================================
   // Implementation Methods
   // =========================================================================
   
   // -------------------------------------------------------------------------
   QScriptEngine* ScriptEngine::getEngine()
   {
      return m_pEng;
   }
   
   // =========================================================================
   // Implementation Methods
   // =========================================================================
      
   // -------------------------------------------------------------------------
   void ScriptEngine::evaluateFile( QString sScriptFile )
   {
      // Extract the arguments from the script call.
      QString sFilePath(CommonDefinitions::sScriptDir.c_str());
      QFile file(sFilePath + "/" + sScriptFile);
      if (!file.open(QIODevice::ReadOnly))
      {
         cerr << "Error: Could not open "
            << qPrintable(sScriptFile) << " for reading!" << endl;
      }
      QTextStream ts(&file);
      QString sContents = ts.readAll();
      file.close();

      evaluateString( sContents );
   }
   
   // -------------------------------------------------------------------------
   void ScriptEngine::evaluateString( QString sScriptString )
   {
      Q_ASSERT( m_pEng );

      QScriptValue ret = evaluate( sScriptString );
      if( !m_pEng->hasUncaughtException() && !ret.isUndefined() )
      {
         std::cerr << qPrintable(ret.toString()) << std::endl;
      }
   }
   
   // -------------------------------------------------------------------------
   void ScriptEngine::list()
   {
      show( m_pEng->globalObject() );
   }
   
   // -------------------------------------------------------------------------
   void ScriptEngine::show(const QScriptValue& value)
   {
      //!@todo The ScriptEngine::show method doesn't currently function 
      //!      properly.  It should list out the properties and functions
      //!      on the passed in object.  However, it doesn't list any of
      //!      the properties or methods that are defined in C++.  This is
      //!      at least in part due to the creation of the prototypes and the
      //!      option QScriptEngine::SkipMethodsInEnumeration.
      
      std::cout << "Objects:" << std::endl;
      QScriptValueIterator o(value);
      while( o.hasNext() )
      {
         o.next();

         if( o.value().isObject() )
         {
            std::cout << "   " << qPrintable(o.scriptName().toString()) << std::endl;
         }
      }
      std::cout << "Functions:" << std::endl;
      QScriptValueIterator f(value);
      while( f.hasNext() )
      {
         f.next();

         if( f.value().isFunction() )
         {
            std::cout << "   " << qPrintable(f.scriptName().toString()) << std::endl;
         }
      }
   }
   
   // -------------------------------------------------------------------------
   QScriptValue ScriptEngine::importExtension(QString sExtension)
   {
      //return engine()->importExtension(context()->argument(0).toString());
      return m_pEng->importExtension(sExtension);
   }
   
   // -------------------------------------------------------------------------
   void ScriptEngine::quit()
   {
      emit terminated();
   }
   
   // =========================================================================
   // Private methods
   // =========================================================================

   // -------------------------------------------------------------------------
   QScriptValue ScriptEngine::evaluate( QString sScriptString )
   {
      Q_ASSERT( m_pEng );

      //!@todo The QString "typein" is no longer valid in this context.  Instead
      //!      the evalute function should take in parameter that indicates the
      //!      filename so that proper error reporting can take place.
      QScriptValue ret = m_pEng->evaluate( sScriptString, QLatin1String("typein") );
      if( m_pEng->hasUncaughtException())
      {
         cerr << "Uncaught exception executing script:" << endl;
         cerr << "   Exception: " 
              << qPrintable(m_pEng->uncaughtException().toString()) << endl;
         cerr << "   Line Num: " << m_pEng->uncaughtExceptionLineNumber() << endl;
      }

      return ret;
   }

}; //namespace