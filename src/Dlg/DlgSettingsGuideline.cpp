/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ButtonWhatsThis.h"
#include "CmdSettingsGuideline.h"
#include "DlgSettingsGuideline.h"
#include "DocumentModelGuideline.h"
#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "ImportCropping.h"
#include "ImportCroppingUtilBase.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDir>
#include <QDoubleSpinBox>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <qmath.h>
#include <QPushButton>
#include <QSpinBox>
#include "QtToString.h"
#include <QWhatsThis>
#include "TranslatorContainer.h"
#include "ViewPreview.h"

const int MINIMUM_HEIGHT = 300;
const int MINIMUM_DIALOG_WIDTH_GUIDELINES = 500;
const int MINIMUM_PREVIEW_WIDTH = 200;

DlgSettingsGuideline::DlgSettingsGuideline(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Guidelines"),
                           "DlgSettingsGuideline",
                           mainWindow),
  m_scenePreviewActive (nullptr),
  m_viewPreviewActive (nullptr),
  m_scenePreviewInactive (nullptr),
  m_viewPreviewInactive (nullptr),
  m_itemGuidelineXTActive (nullptr),
  m_itemGuidelineYRActive (nullptr),
  m_itemCircleActive (nullptr),
  m_itemCentipedeXTActive (nullptr),
  m_itemCentipdedYRActive (nullptr),
  m_itemGuidelineXTInactive (nullptr),
  m_itemGuidelineYRInactive (nullptr),
  m_itemCircleInactive (nullptr),
  m_itemCentipedeXTInactive (nullptr),
  m_itemCentipdedYRInactive (nullptr),
  m_modelGuidelineBefore (nullptr),
  m_modelGuidelineAfter (nullptr)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::DlgSettingsGuideline";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel,
               MINIMUM_DIALOG_WIDTH_GUIDELINES);
}

DlgSettingsGuideline::~DlgSettingsGuideline()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::~DlgSettingsGuideline";
}

void DlgSettingsGuideline::createControls (QGridLayout *layout,
                                            int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::createControls";
  
  createWhatsThis (layout,
                   m_btnWhatsThis,
                   row++,
                   3);

  QLabel *labelPointRadius = new QLabel (QString ("%1:").arg (tr ("Creation circle radius")));
  layout->addWidget (labelPointRadius, row, 1);

  m_spinCreationCircleRadius = new QSpinBox;
  m_spinCreationCircleRadius->setWhatsThis (tr ("Select a radius, in pixels, for the points"));
  m_spinCreationCircleRadius->setMinimum (1);
  connect (m_spinCreationCircleRadius, SIGNAL (valueChanged (int)), this, SLOT (slotCreationCircleRadius (int)));
  layout->addWidget (m_spinCreationCircleRadius, row++, 2);

  QLabel *labelGuidelineColor = new QLabel (QString ("%1:").arg (tr ("Guideline color")));
  layout->addWidget (labelGuidelineColor, row, 1);

  m_lineColor = new QComboBox;
  m_lineColor->setWhatsThis (tr ("Guidelines Color\n\n"
                                  "Set the color of the guidelines that can be dragged from the edges of the scene, and used "
                                  "to align points"));
  populateColorComboWithoutTransparent (*m_lineColor);
  connect (m_lineColor, SIGNAL (activated (const QString &)), this, SLOT (slotLineColor (const QString &))); // activated() ignores code changes
  layout->addWidget (m_lineColor, row++, 2);

  QLabel *labelLineWidthActive = new QLabel(QString ("%1:").arg (tr ("Active Line width")));
  layout->addWidget (labelLineWidthActive, row, 1);

  m_spinLineWidthActive = new QSpinBox;
  m_spinLineWidthActive->setWhatsThis (tr ("Select a size for the guidelines when active"));
  m_spinLineWidthActive->setMinimum(1);
  connect (m_spinLineWidthActive, SIGNAL (valueChanged (int)), this, SLOT (slotLineWidthActive (int)));
  layout->addWidget (m_spinLineWidthActive, row++, 2);

  QLabel *labelLineWidthInactive = new QLabel(QString ("%1:").arg (tr ("Inactive Line width")));
  layout->addWidget (labelLineWidthInactive, row, 1);

  m_spinLineWidthInactive = new QSpinBox;
  m_spinLineWidthInactive->setWhatsThis (tr ("Select a size for the guidelines when inactive"));
  m_spinLineWidthInactive->setMinimum(1);
  connect (m_spinLineWidthInactive, SIGNAL (valueChanged (int)), this, SLOT (slotLineWidthInactive (int)));
  layout->addWidget (m_spinLineWidthInactive, row++, 2);  
}

void DlgSettingsGuideline::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::createOptionalSaveDefault";
}

void DlgSettingsGuideline::createPreview (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::createPreview";

  // Need local gridlayout to get nicely even 50/50 split
  int row5050 = 0;
  QGridLayout *layout5050 = new QGridLayout();
  QWidget *widget = new QWidget();
  widget->setLayout (layout5050);

  // Preview panels

  QLabel *labelPreviewActive = new QLabel (tr ("Active Preview"));
  layout5050->addWidget (labelPreviewActive, row5050, 0, 1, 2);

  QLabel *labelPreviewInactive = new QLabel (tr ("Inactive Preview"));
  layout5050->addWidget (labelPreviewInactive, row5050++, 2, 1, 2);

  m_scenePreviewActive = new QGraphicsScene (this);
  m_viewPreviewActive = new ViewPreview (m_scenePreviewActive,
                                         ViewPreview::VIEW_ASPECT_RATIO_VARIABLE,
                                         this);
  m_viewPreviewActive->setWhatsThis (tr ("Preview window that shows how current settings affect the active guidelines."));
  m_viewPreviewActive->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreviewActive->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreviewActive->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);
  m_viewPreviewActive->setMinimumWidth(MINIMUM_PREVIEW_WIDTH);
  m_viewPreviewActive->setRenderHint(QPainter::Antialiasing);

  layout5050->addWidget (m_viewPreviewActive, row5050, 0, 1, 2);

  m_scenePreviewInactive = new QGraphicsScene (this);
  m_viewPreviewInactive = new ViewPreview (m_scenePreviewInactive,
                                           ViewPreview::VIEW_ASPECT_RATIO_VARIABLE,
                                           this);
  m_viewPreviewInactive->setWhatsThis (tr ("Preview window that shows how current settings affect the inactive guidelines."));
  m_viewPreviewInactive->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreviewInactive->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreviewInactive->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);
  m_viewPreviewInactive->setMinimumWidth(MINIMUM_PREVIEW_WIDTH);
  m_viewPreviewInactive->setRenderHint(QPainter::Antialiasing);

  layout5050->addWidget (m_viewPreviewInactive, row5050++, 2, 1, 2);

  layout->addWidget (widget, row++, 0, 1, 4);
}

QWidget *DlgSettingsGuideline::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::createSubPanel";

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // Labels
  layout->setColumnStretch(2, 0); // Values
  layout->setColumnStretch(3, 1); // Empty first column

  int row = 0;
  createControls (layout, row);
  createPreview (layout, row);
  
  return subPanel;
}

void DlgSettingsGuideline::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::handleOk";

  CmdSettingsGuideline *cmd = new CmdSettingsGuideline (mainWindow (),
                                                        cmdMediator().document(),
                                                        *m_modelGuidelineBefore,
                                                        *m_modelGuidelineAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsGuideline::load (CmdMediator &cmdMediator)
{
  LOG4CPP_ERROR_S ((*mainCat)) << "DlgSettingsGuideline::load";
  
  setCmdMediator (cmdMediator);

  // Flush old data
  delete m_modelGuidelineBefore;
  delete m_modelGuidelineAfter;

  // Save new data
  m_modelGuidelineBefore = new DocumentModelGuideline (cmdMediator.document());
  m_modelGuidelineAfter = new DocumentModelGuideline (cmdMediator.document());

  // Populate controls
  m_spinCreationCircleRadius->setValue (qFloor (m_modelGuidelineAfter->creationCircleRadius ()));
  int indexColor = m_lineColor->findData(QVariant(m_modelGuidelineAfter->lineColor()));
  ENGAUGE_ASSERT (indexColor >= 0);
  m_lineColor->setCurrentIndex(indexColor);
  m_spinLineWidthActive->setValue (qFloor (m_modelGuidelineAfter->lineWidthActive ()));
  m_spinLineWidthInactive->setValue (qFloor (m_modelGuidelineAfter->lineWidthInactive ()));  

  m_scenePreviewActive->clear();
  QImage imagePreviewActive = cmdMediator.document().pixmap().toImage();
  m_scenePreviewActive->addPixmap (QPixmap::fromImage (imagePreviewActive));

  m_scenePreviewInactive->clear();
  QImage imagePreviewInactive = cmdMediator.document().pixmap().toImage();
  m_scenePreviewInactive->addPixmap (QPixmap::fromImage (imagePreviewInactive));

  updatePreview();
                             
  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
}

void DlgSettingsGuideline::setSmallDialogs (bool smallDialogs)
{
  if (!smallDialogs) {
    setMinimumHeight (MINIMUM_HEIGHT);
  }
}

void DlgSettingsGuideline::slotCreationCircleRadius (int radius)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::slotCreationCircleRadius";

  m_modelGuidelineAfter->setCreationCircleRadius (radius); 
  updateControls();
  updatePreview();
}

void DlgSettingsGuideline::slotLineColor (QString const &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::slotLineColor";

  m_modelGuidelineAfter->setLineColor(static_cast<ColorPalette> (m_lineColor->currentData().toInt()));
  updateControls();
  updatePreview();
}

void DlgSettingsGuideline::slotLineWidthActive (int lineWidth)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::slotLineWidthActive";

  m_modelGuidelineAfter->setLineWidthActive (lineWidth);
  updateControls();
  updatePreview();
}

void DlgSettingsGuideline::slotLineWidthInactive (int lineWidth)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::slotLineWidthInactive";

  m_modelGuidelineAfter->setLineWidthInactive (lineWidth);
  updateControls();
  updatePreview();
}                               

void DlgSettingsGuideline::slotWhatsThis ()
{
  QWhatsThis::enterWhatsThisMode();
}

void DlgSettingsGuideline::updateControls ()
{
  enableOk (true);
}

void DlgSettingsGuideline::updatePreview()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::updatePreview";

  enableOk (true);

  // Preview widgets
  delete m_itemGuidelineXTActive;
  delete m_itemGuidelineYRActive;
  delete m_itemCircleActive;
  delete m_itemCentipedeXTActive;
  delete m_itemCentipdedYRActive;

  // Screen bounds
  int width = mainWindow().scene().width();
  int height = mainWindow().scene().height();
  QPointF posGraphTL, posGraphTR, posGraphBL, posGraphBR;
  mainWindow().transformation().transformScreenToRawGraph (QPointF (0, 0),
                                                           posGraphTL);
  mainWindow().transformation().transformScreenToRawGraph(QPointF (width, 0),
                                                          posGraphTR);
  mainWindow().transformation().transformScreenToRawGraph (QPointF (0, height),
                                                           posGraphBL);
  mainWindow().transformation().transformScreenToRawGraph(QPointF (width, height),
                                                          posGraphBR);

  if (cmdMediator().document().modelCoords().coordsType() == COORDS_TYPE_CARTESIAN) {

    double xMin = qMin (qMin (qMin (posGraphTL.x(), posGraphTR.x()), posGraphBL.x()), posGraphBR.x());
    double yMin = qMin (qMin (qMin (posGraphTL.y(), posGraphTR.y()), posGraphBL.y()), posGraphBR.y());
    double xMax = qMax (qMax (qMax (posGraphTL.x(), posGraphTR.x()), posGraphBL.x()), posGraphBR.x());
    double yMax = qMax (qMax (qMax (posGraphTL.y(), posGraphTR.y()), posGraphBL.y()), posGraphBR.y());
    double xMid = (xMin + xMax) / 2.0;
    double yMid = (yMin + yMax) / 2.0;

    QPointF posLeft, posRight, posTop, posBottom;
    mainWindow().transformation().transformRawGraphToScreen (QPointF (xMin, yMid),
                                                             posLeft);
    mainWindow().transformation().transformRawGraphToScreen (QPointF (xMax, yMid),
                                                             posRight);
    mainWindow().transformation().transformRawGraphToScreen (QPointF (xMid, yMin),
                                                             posTop);
    mainWindow().transformation().transformRawGraphToScreen (QPointF (xMid, yMax),
                                                             posBottom);

    m_itemGuidelineXTActive = new QGraphicsLineItem (QLineF (posBottom,
                                                             posTop));
    m_itemGuidelineYRActive = new QGraphicsLineItem (QLineF(posLeft,
                                                            posRight));
    m_itemGuidelineXTInactive = new QGraphicsLineItem (QLineF (posBottom,
                                                               posTop));
    m_itemGuidelineYRInactive = new QGraphicsLineItem (QLineF(posLeft,
                                                              posRight));

    m_scenePreviewActive->addItem (m_itemGuidelineXTActive);
    m_scenePreviewActive->addItem (m_itemGuidelineYRActive);
    m_scenePreviewInactive->addItem (m_itemGuidelineXTInactive);
    m_scenePreviewInactive->addItem (m_itemGuidelineYRInactive);

  } else {

  }
}
