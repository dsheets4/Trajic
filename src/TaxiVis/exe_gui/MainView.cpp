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

#include <QtGui/QPrinter>

#include "CommonDefinitions.h"
#include "MainView.h"

#include "Vis/GraphBar.h"
#include "Vis/GraphPie.h"


// ============================================================================
// Construction and destruction
// ============================================================================

// ----------------------------------------------------------------------------
MainView::MainView(MainScene *pScene, QWidget *pParent)
   : QGraphicsView(pScene,pParent)
{
}

// ----------------------------------------------------------------------------
MainView::~MainView()
{
}


// ============================================================================
// Implementation Methods
// ============================================================================

// ----------------------------------------------------------------------------
MainScene* MainView::getMainScene()
{
   MainScene* pScene = dynamic_cast<MainScene*>(scene());
   Q_ASSERT(pScene);
   
   return pScene;
}


// ============================================================================
// Overridden methods
// ============================================================================

// ----------------------------------------------------------------------------
void MainView::resizeEvent( QResizeEvent * evt )
{
   Q_ASSERT(this->parentWidget());

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Resize the contents appropriately. This is called when the main window 
   // is resized. To calculate the new size, account for the size of the 
   // window frame
   QSize size = evt->size();

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   // Make sure the view stays in the intended area.
   setSceneRect( QRectF( QPoint(0,0),size) );

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   //! @todo When the map window is created it is still leaving a scroll bar 
   //!       that gets worse when the MDI sub-window isn't maximized; figure 
   //!       out how to calculate the new size so the map fits within the 
   //!       window. At the moment, the setSceneRect and no scroll bars
   //!       are used to get a pretty good window representation so this is
   //!       low priority.
   getMainScene()->resize(size);
}


// ============================================================================
// Action handlers
// ============================================================================

// ----------------------------------------------------------------------------
void MainView::refresh()
{
   getMainScene()->getMapItem()->reload();
}


// ----------------------------------------------------------------------------
void MainView::captureScreenShot( QString sFileName )
{
   // Create the full path to the image.
   QString sFullName = CommonDefinitions::sImageCaptureDir.c_str();
   sFullName += "/";
   sFileName = sFullName + sFileName;

   // Create a new icon with an image format that supports transparency.
   QImage img( size(), QImage::Format_ARGB32_Premultiplied );

   // Fill the image with a transparent background.
   img.fill(QColor(0,0,0,0).rgba());

   // Setup the painter to paint to the image and render the scene to the image.
   // Note that the image is being limited to only paint the current view of the
   // scene.
   QPainter painter;
   painter.begin(&img);
   scene()->render(&painter, sceneRect(), sceneRect());

   // Save the icon off to a file.
   img.save(sFileName, "PNG");
}

// ----------------------------------------------------------------------------
void MainView::captureScreenShotPdf( QString sFileName )
{
   // Create the full path to the image.
   QString sFullName = CommonDefinitions::sImageCaptureDir.c_str();
   sFullName += "/";
   sFullName += sFileName;
   sFileName = sFullName;

   // Setup a QPrinter that is the size of the window contents.
   QPrinter printer(QPrinter::HighResolution);
   printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setOutputFileName(sFileName);
   printer.setFullPage(true);
   QRect rect = this->geometry();
   printer.setPaperSize(QSizeF(rect.width(),rect.height()),QPrinter::DevicePixel);
   printer.setPageMargins(0,0,0,0,QPrinter::DevicePixel);
   
   // Create a new icon with an image format that supports transparency.
   QImage img( size(), QImage::Format_ARGB32_Premultiplied );

   // Fill the image with a transparent background.
   img.fill(QColor(0,0,0,0).rgba());

   // Setup the painter to paint to the image and render the scene to the image.
   // Note that the image is being limited to only paint the current view of the
   // scene.
   QPainter painter;
   painter.begin(&img);
   scene()->render(&painter, sceneRect(), sceneRect());

   // Setup the painter to render the image to the PDF.
   // Note that the  is being limited to only paint the current view of the
   // scene.
   QPainter painter2;
   painter2.begin(&printer);
   painter2.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
   painter2.drawImage(QPoint(0,0),img);

   // File is saved when the printer is destroyed.
}

// ----------------------------------------------------------------------------
void MainView::fullScreen( Vis::GraphBaseObjWrapPtr pGfxObjWrap )
{
   Q_ASSERT( pGfxObjWrap );
   Q_ASSERT( pGfxObjWrap->getGraph() );

   if( !pGfxObjWrap || !pGfxObjWrap->getGraph() )
      return;

   fitInView( pGfxObjWrap->getGraph() );
}

// ----------------------------------------------------------------------------
void MainView::restoreView()
{
   fitInView( scene()->sceneRect() );
}
