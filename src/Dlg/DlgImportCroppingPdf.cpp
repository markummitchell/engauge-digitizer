/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgImportCroppingPdf.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include "PdfCropping.h"
#include "poppler-qt5.h"
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include <QTimer>
#include "Settings.h"
#include "ViewPreview.h"

using namespace Poppler;

int DlgImportCroppingPdf::MINIMUM_DIALOG_WIDTH = 350;
int DlgImportCroppingPdf::MINIMUM_PREVIEW_HEIGHT = 200;
const int X_TOP_LEFT = 0, Y_TOP_LEFT = 0;
const int WIDTH = -1, HEIGHT = -1; // Negative values give full page
const int FIRST_PAGE_1_BASED = 1;
const int SMALLEST_DELAY_MS = 500; // Below 500 triggers "double jump" bug in linux

DlgImportCroppingPdf::DlgImportCroppingPdf(const Poppler::Document &document,
                                           int resolution) :
  m_document (document),
  m_resolution (resolution),
  m_pixmap (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportCroppingPdf::DlgImportCroppingPdf";

  setWindowTitle (tr ("PDF File Import Cropping"));
  setModal (true);

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  int row = 0;

  createTimer ();
  createPageSpinner (layout, row);
  createPreview (layout, row);
  finishPanel (subPanel);
  updatePreview ();

  // Bring the two middle columns together
  layout->setColumnStretch (0, 1);
  layout->setColumnStretch (1, 0);
  layout->setColumnStretch (2, 0);
  layout->setColumnStretch (3, 1);
}

DlgImportCroppingPdf::~DlgImportCroppingPdf()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportCroppingPdf::~DlgImportCroppingPdf";
}

void DlgImportCroppingPdf::createPageSpinner (QGridLayout *layout,
                                              int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportCroppingPdf::createPageSpinner";

  const int MIN_WIDTH_SPINNER = 90;

  QLabel *labelPage = new QLabel (tr ("Page:"));
  layout->addWidget (labelPage, row, 1, 1, 1);

  m_spinPage = new QSpinBox;
  m_spinPage->setMinimumWidth (MIN_WIDTH_SPINNER);
  m_spinPage->setWhatsThis (tr ("Page number that will be imported"));
  m_spinPage->setRange (1, m_document.numPages());
  layout->addWidget (m_spinPage, row++, 2, 1, 1);
  connect (m_spinPage, SIGNAL (valueChanged (int)), this, SLOT (slotPage (int)));
}

void DlgImportCroppingPdf::createPdfCropping ()
{
  // Create frame that shows what will be included, and what will be excluded, during the import
  m_pdfCropping = new PdfCropping (*m_scenePreview,
                                   *m_viewPreview);
}

void DlgImportCroppingPdf::createPreview (QGridLayout *layout,
                                          int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportCroppingPdf::createPreview";

  QLabel *labelPreview = new QLabel (tr ("Preview"));
  layout->addWidget (labelPreview, row++, 0, 1, 1, Qt::AlignLeft);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview,
                                   ViewPreview::VIEW_ASPECT_RATIO_ONE_TO_ONE,
                                   this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows what part of the image will be imported. "
                                   "The image portion inside the rectangular frame will be imported from the currently selected page. "
                                   "The frame can be moved and resized by dragging the corner handles."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);
  layout->addWidget (m_viewPreview, row++, 0, 1, 4);

  // More preview initialization
  initializeFrameGeometryAndPixmap (); // Before first call to updatePreview
  createPdfCropping ();
}

void DlgImportCroppingPdf::createTimer ()
{
  m_timer = new QTimer;
  m_timer->setSingleShot (true);
  connect (m_timer, SIGNAL (timeout ()), this, SLOT (slotTimeout ()));
}

void DlgImportCroppingPdf::finishPanel (QWidget *subPanel)
{
  const int STRETCH_OFF = 0, STRETCH_ON = 1;

  QVBoxLayout *panelLayout = new QVBoxLayout (this);

  setMinimumWidth (MINIMUM_DIALOG_WIDTH);
  setLayout (panelLayout);

  panelLayout->addWidget (subPanel);
  panelLayout->setStretch (panelLayout->count () - 1, STRETCH_ON);

  QWidget *panelButtons = new QWidget (this);
  QHBoxLayout *buttonLayout = new QHBoxLayout (panelButtons);

  QHBoxLayout *layoutRightSide = new QHBoxLayout;

  QWidget *widgetRightSide = new QWidget;
  widgetRightSide->setLayout (layoutRightSide);
  buttonLayout->addWidget (widgetRightSide);

  QSpacerItem *spacerExpanding = new QSpacerItem (40, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
  layoutRightSide->addItem (spacerExpanding);

  m_btnOk = new QPushButton (tr ("Ok"));
  layoutRightSide->addWidget (m_btnOk, 0, Qt::AlignRight);
  connect (m_btnOk, SIGNAL (released ()), this, SLOT (slotOk ()));

  QSpacerItem *spacerFixed = new QSpacerItem (40, 5, QSizePolicy::Fixed, QSizePolicy::Fixed);
  layoutRightSide->addItem (spacerFixed);

  m_btnCancel = new QPushButton (tr ("Cancel"));
  layoutRightSide->addWidget (m_btnCancel, 0, Qt::AlignRight);
  connect (m_btnCancel, SIGNAL (released ()), this, SLOT (slotCancel ()));

  panelLayout->addWidget (panelButtons, STRETCH_ON);
  panelLayout->setStretch (panelLayout->count () - 1, STRETCH_OFF);
}

QImage DlgImportCroppingPdf::image () const
{
  // If the entire page was to be returned, then this method would simply return m_image. However, only the framed
  // portion is to be returned
  ENGAUGE_ASSERT (m_pdfCropping != 0);
  QRectF rectFramePixels = m_pdfCropping->frameRect ();

  return m_image.copy (rectFramePixels.toRect ());
}

void DlgImportCroppingPdf::initializeFrameGeometryAndPixmap ()
{
  m_image = loadImage (FIRST_PAGE_1_BASED);
  QGraphicsPixmapItem *pixmap = new QGraphicsPixmapItem (QPixmap::fromImage (m_image));
  m_scenePreview->addItem (pixmap);

  // Force resize so image fills preview area. We do this only once initially for speed
  m_viewPreview->setSceneRect (pixmap->boundingRect ());
}

QImage DlgImportCroppingPdf::loadImage (int page1Based) const
{
  QImage image;

  int page0Based = page1Based - 1;
  Page *page = m_document.page (page0Based);
  if (page != 0) {

    image = page->renderToImage (m_resolution,
                                 m_resolution,
                                 X_TOP_LEFT,
                                 Y_TOP_LEFT,
                                 WIDTH,
                                 HEIGHT);

    delete page;
  }

  return image;
}

void DlgImportCroppingPdf::saveGeometryToSettings()
{
  // Store the settings for use by showEvent
  QSettings settings;
  settings.beginGroup (SETTINGS_GROUP_IMPORT_CROPPING);
  settings.setValue (SETTINGS_IMPORT_CROPPING_POS, saveGeometry ());
  settings.endGroup();
}

void DlgImportCroppingPdf::showEvent (QShowEvent * /* event */)
{
  QSettings settings;
  settings.beginGroup (SETTINGS_GROUP_IMPORT_CROPPING);
  if (settings.contains (SETTINGS_IMPORT_CROPPING_POS)) {

    // Restore the settings that were stored by the last call to saveGeometryToSettings
    restoreGeometry (settings.value (SETTINGS_IMPORT_CROPPING_POS).toByteArray ());
  }
}

void DlgImportCroppingPdf::slotCancel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportCroppingPdf::slotCancel";

  // Restore cursor in case updatePreview has not already completed and then restored it
  QApplication::restoreOverrideCursor ();

  setResult (QDialog::Rejected);
  saveGeometryToSettings();
  hide();
}

void DlgImportCroppingPdf::slotOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportCroppingPdf::slotOk";

  // Restore cursor in case updatePreview has not already completed and then restored it
  QApplication::restoreOverrideCursor ();

  setResult (QDialog::Accepted);
  saveGeometryToSettings();
  hide();
}

void DlgImportCroppingPdf::slotPage (int page)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportCroppingPdf::slotPage"
                              << " page=" << page
                              << " stepBy=" << m_spinPage->singleStep ();

  // Show wait cursor until slow calculations are over
  QApplication::setOverrideCursor (Qt::WaitCursor);

  m_timer->start (SMALLEST_DELAY_MS);
}

void DlgImportCroppingPdf::slotTimeout ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportCroppingPdf::slotTimeout";

  updatePreview ();
}

void DlgImportCroppingPdf::updatePreview ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportCroppingPdf::updatePreview";

  if (m_pixmap != 0) {
    m_scenePreview->removeItem (m_pixmap);
  }

  m_image = loadImage (m_spinPage->value ());
  m_pixmap = new QGraphicsPixmapItem (QPixmap::fromImage (m_image));
  m_scenePreview->addItem (m_pixmap);

  // Calculations for preview updating are now over
  QApplication::restoreOverrideCursor ();
}
