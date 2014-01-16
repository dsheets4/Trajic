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
#ifndef MapPageScript_H
#define MapPageScript_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtScript/QScriptClass>
#include <QtScript/QScriptContext>

#include "ObjectBaseDispatch.h"


namespace Map
{
   //! Represents a script constructor object for scripting.
   class MapPageScript : public QObject, public QScriptClass
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      static const QString ScriptClassName; //!< Name identifying the class.

      // ----------------------------------------------------------------------
      MapPageScript(QScriptEngine *pEngine);
      virtual ~MapPageScript();
      
      // ----------------------------------------------------------------------
      virtual QScriptValue prototype() const;
      virtual QString name() const;

      // ----------------------------------------------------------------------
      virtual QScriptValue constructor();
      
      virtual QScriptValue newInstance();
      QScriptValue newInstance(const ObjectBaseDispatchPtr &pDispatch);
      QScriptValue newInstance(const ObjectBaseWrapperPtr &pObj);
      
   protected:
      // ----------------------------------------------------------------------
      static QScriptValue construct(
         QScriptContext *pContext, 
         QScriptEngine *pEngine);
      
      // ----------------------------------------------------------------------
      virtual void ConnectSignals(ObjectBaseWrapperPtr pObj, ObjectBaseDispatchPtr pDispatch);
      
      
   private:
      // ----------------------------------------------------------------------
      QScriptValue m_proto;
      QScriptValue m_ctor;
   };
}; //namespace


// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Map::MapPageScript*);

#endif // MapPageScript_H
