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

#include <QtCore/QEventLoop>
#include <QtCore/QThread>

#include "ObjectBaseWrapper.h"


// =========================================================================
// Construction and destruction
// =========================================================================

// -------------------------------------------------------------------------
ObjectBaseWrapper::ObjectBaseWrapper(QObject *pParent)
   : QObject( pParent )
   , m_pObj( NULL )
{
}
   
// -------------------------------------------------------------------------
ObjectBaseWrapper::ObjectBaseWrapper(QObject* pWrapped, QObject *pParent)
   : QObject( pParent )
   , m_pObj( NULL )
{
   setObject( pWrapped );
}
   
// -------------------------------------------------------------------------
ObjectBaseWrapper::ObjectBaseWrapper(const ObjectBaseWrapper& orig)
   : QObject(0)
   , m_pObj( orig.m_pObj )
{
}

// -------------------------------------------------------------------------
ObjectBaseWrapper::~ObjectBaseWrapper()
{
   if( m_pObj && !m_pObj->parent() )
   {
      //!@todo Fix the memory deallocation of the object wrapper.  This
      //!      logic deletes the graphics scene placed in the window because
      //!      it doesn't seem to have a parent.  When the scene is deleted
      //!      a crash is inevitably caused.
#define DELETION_CAUSES_CRASHES
#ifndef DELETION_CAUSES_CRASHES
      delete m_pObj;
      m_pObj = NULL;
#endif
   }
}

      
// =========================================================================
// Implementation
// =========================================================================
   
// -------------------------------------------------------------------------
QObject* ObjectBaseWrapper::getObject() const
{
   return m_pObj;
}

void ObjectBaseWrapper::setObject( QObject* pObj )
{
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   // Disconnect from any previous object
   if( m_pObj )
   {
      disconnect( 
         m_pObj, SIGNAL(destroyed(QObject*)), 
         this,   SLOT(wrappedObjDestroyed(QObject*))
         );
   }

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   // Connect to the new object
   m_pObj = pObj;
   connect(
      m_pObj, SIGNAL(destroyed(QObject*)),
      this,   SLOT(wrappedObjDestroyed(QObject*))
      );
}
      
   
// =========================================================================
// Operators
// =========================================================================
      
// -------------------------------------------------------------------------
ObjectBaseWrapper& ObjectBaseWrapper::operator=( const ObjectBaseWrapper &rhs )
{
   if( this != &rhs )
   {
      this->m_pObj = rhs.m_pObj;
   }

   return *this;
}
   

// =========================================================================
// Private slots
// =========================================================================
void ObjectBaseWrapper::wrappedObjDestroyed( QObject* pObj )
{
   if( pObj == m_pObj )
   {
      m_pObj = NULL;
   }
}
