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

#include <cmath>

#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QPainter>

#include "TaxiVisConstants.h"
#include "Vis/GraphRingItem.h"


// ============================================================================
using namespace std;

namespace Vis
{
   // =========================================================================
   // Construction and destruction
   // =========================================================================

   // -------------------------------------------------------------------------
   GraphRingItem::GraphRingItem(QGraphicsItem *pParentItem)
      : GraphBase(pParentItem)
      , m_fRotation(0)
      , m_fSpan(15)
      , m_fDistPercent(1.0)
      , m_eAlign(AlignOutside)
      , m_bStabilized(false)
   {
   }

   // -------------------------------------------------------------------------
   GraphRingItem::~GraphRingItem()
   {

   }


   // =========================================================================
   // QGraphicsItem Implementation
   // =========================================================================

   // -------------------------------------------------------------------------
   void GraphRingItem::paint(
      QPainter *painter,
      const QStyleOptionGraphicsItem *option,
      QWidget *widget)
   {            
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      //!@todo Draw a circle centered on the center of the ring (parent) to 
      //!      help illustrate the relationships.
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      //! @todo Draw the angle and centerline for the ring item using the ring
      //!       item.  There's an issue with the transform where the way that 
      //!       the ring item is transforming the child Graph that also causes
      //!       the pie slice and centerline to transform.  When drawing these
      //!       items from the ring map they draw perfectly fine...  I think 
      //!       the solution is to setup the drawing but them draw it in the
      //!       parent coordinates.  That is, convert the coordinates set for
      //!       drawing these items but convert them from parent to child 
      //!       coordinates.  Refer to the GraphRing::paint for the code that
      //!       does the drawing referenced here.

      
   }


   // =========================================================================
   // Additional Interface
   // =========================================================================

   void GraphRingItem::updateTransform()
   {
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // If there is no Graph item set then there's nothing to update.
      if( childItems().size() < 1 )
         return;
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Determine the length of the chord subtended by the span.
      // Chord = D * sin( theta / 2 )
      double fDistance    = (m_rect.height()/2.0)*m_fDistPercent;
      double fRadius      = fDistance;
      double fSinAngle    = sin(m_fSpan*TaxiVisConstants::Pi/180);
      double fChordLength = fDistance*fSinAngle;
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Get the rectangle for the child item.
      QGraphicsItem* itemChild = childItems().at(0);
      QRectF rectChild = itemChild->boundingRect();
      
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Set the position and size of the Graph child item to fit with the 
      // the given rotation and span.  Set the position to be above the center
      // of the ring in the x direction and centered in the y.
      qreal fScale = fChordLength/rectChild.width();
            
      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Update the distance based on the desired alignment.
      if( m_eAlign != AlignOutside )
      {
         double fNewDistance    = fDistance + 10;
         double fNewChordLength = fChordLength + 10;
         double fNewScale       = fScale + 10;
         double fHeight;

         switch( m_eAlign )
         {
         case AlignCenter:
            fHeight = rectChild.height()/2.0;
            break;
         case AlignInside:
            fHeight = rectChild.height();
            break;
         default:
            Q_ASSERT(false); // Unknown alignment type.
         }
         
         //!@todo While the loop here that progressively aligns the size and 
         //!      height seems to work pretty well at finding the alignment
         //!      for the graph in the ring item it seems expensive.  Figure 
         //!      out if there is a better way to do this.
         while( fNewDistance > (fDistance+0.5) || fNewDistance < (fDistance-0.5) )
         {
            fDistance    = fNewDistance;
            fChordLength = fNewChordLength;
            fScale       = fNewScale;
            
            fNewDistance     = fRadius - (fHeight*fScale);
            fNewChordLength  = fNewDistance*fSinAngle;
            fNewScale        = fNewChordLength/rectChild.width();
         }
      }

      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
      // Set up the final position and scale as well as the transformation 
      // to translate and rotate the item around the circle.
      itemChild->setScale( fScale );
      itemChild->setPos( -(fChordLength/2.0), -(rectChild.height()*fScale) );
      QTransform trans;
      trans.rotate(m_fRotation);
      trans.translate(0, -(fDistance));
      if( m_bStabilized )
      {
         trans.translate( 0, -rectChild.height()/2*fScale );
         trans.rotate(-m_fRotation);
         trans.translate( 0, rectChild.height()/2*fScale );
      }
      setTransform(trans);
   }

   // -------------------------------------------------------------------------
   void GraphRingItem::addGraph( GraphBase* pGfx )
   {
      Q_ASSERT(pGfx);

      if( pGfx )
      {
         pGfx->setParentItem(this);
         updateTransform();
      }
   }

   void GraphRingItem::removeGraph( GraphBase* pGfx )
   {
      Q_ASSERT(pGfx);

      if( pGfx && pGfx->parentItem() == this )
      {
         pGfx->setParentItem(NULL);
         pGfx->setTransform(QTransform());
         pGfx->setScale(1.0);
      }
   }

   // -------------------------------------------------------------------------
   qreal GraphRingItem::getRotation() const
   {
      return m_fRotation;
   }

   void GraphRingItem::setRotation( qreal fRotation )
   {
      m_fRotation = fRotation;
      updateTransform();
   }

   // -------------------------------------------------------------------------
   qreal GraphRingItem::getSpan() const
   {
      return m_fSpan;
   }

   void GraphRingItem::setSpan( qreal fSpan )
   {
      m_fSpan = fSpan;
      updateTransform();
   }

   // -------------------------------------------------------------------------
   bool GraphRingItem::getDistPercent() const
   {
      return m_fDistPercent;
   }

   void GraphRingItem::setDistPercent( qreal fDistPercent )
   {
      m_fDistPercent = fDistPercent;
      updateTransform();
   }

   // -------------------------------------------------------------------------
   Vis::GraphRingItem::Alignment GraphRingItem::getAlignment() const
   {
      return m_eAlign;
   }

   void GraphRingItem::setAlignment( Vis::GraphRingItem::Alignment eAlignment )
   {
      m_eAlign = eAlignment;
      updateTransform();
   }
   
   // -------------------------------------------------------------------------
   bool GraphRingItem::getStabilized() const
   {
      return m_bStabilized;
   }

   void GraphRingItem::setStabilized( bool bStabilized )
   {
      m_bStabilized = bStabilized;
   }

}; //namespace