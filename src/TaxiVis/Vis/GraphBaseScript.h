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
#ifndef GraphBaseScript_H
#define GraphBaseScript_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtScript/QScriptClass>
#include <QtScript/QScriptContext>

#include "Vis/GraphBaseDispatch.h"


namespace Vis
{
   //! Represents a GraphBaseScript.
   class GraphBaseScript : public QObject, public QScriptClass
   {
      Q_OBJECT

   public:
      // ----------------------------------------------------------------------
      static const QString ScriptClassName; //!< Name identifying the class.

      // ----------------------------------------------------------------------
      GraphBaseScript(QScriptEngine *pEngine);
      virtual ~GraphBaseScript();
      
      // ----------------------------------------------------------------------
      virtual QScriptValue prototype() const;
      virtual QString name() const;

      // ----------------------------------------------------------------------
      virtual QScriptValue constructor();
      
      virtual QScriptValue newInstance();
      QScriptValue newInstance(const GraphBaseDispatchPtr &pDispatch);
      QScriptValue newInstance(const GraphBaseObjWrapPtr &pGfx);
            

   protected:
      // ----------------------------------------------------------------------
      static QScriptValue construct(
         QScriptContext *pContext, 
         QScriptEngine *pEngine);

      static QScriptValue toScriptValue(QScriptEngine *eng, const GraphBaseDispatchPtr &pDispatch);
      static void fromScriptValue(const QScriptValue &obj, GraphBaseDispatchPtr &pDispatch);

      static QScriptValue toScriptValue(QScriptEngine *eng, const GraphBaseObjWrapPtr &pDispatch);
      static void fromScriptValue(const QScriptValue &obj, GraphBaseObjWrapPtr &pDispatch);
      
      // ----------------------------------------------------------------------
      virtual void ConnectSignals(GraphBaseObjWrapPtr pGfx, GraphBaseDispatchPtr pDispatch);
      
   private:
      // ----------------------------------------------------------------------
      QScriptValue m_protoGraphBase;
      QScriptValue m_ctorGraphBase;
   };
}; //namespace


// ============================================================================
// Integrate Qt to meta system
// ============================================================================
Q_DECLARE_METATYPE(Vis::GraphBaseScript*);


#endif // GraphBaseScript_H
