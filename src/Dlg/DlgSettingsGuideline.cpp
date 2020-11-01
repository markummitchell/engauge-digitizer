/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsGuideline.h"
#include "DlgSettingsGuideline.h"
#include "EngaugeAssert.h"
#include "ImportCropping.h"
#include "ImportCroppingUtilBase.h"
#include "Logger.h"
#include "MainWindow.h"
#include "DocumentModelGuideline.h"
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDir>
#include <QDoubleSpinBox>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <qmath.h>
#include <QPushButton>
#include <QSpinBox>
#include "QtToString.h"
#include "TranslatorContainer.h"

const int MINIMUM_HEIGHT = 300;
const int MINIMUM_DIALOG_WIDTH_GUIDELINES = 500;

DlgSettingsGuideline::DlgSettingsGuideline(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Guidelines"),
                           "DlgSettingsGuideline",
                           mainWindow),
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

  QLabel *labelLineWidth = new QLabel(QString ("%1:").arg (tr ("Line width")));
  layout->addWidget (labelLineWidth, row, 1);

  m_spinLineWidth = new QSpinBox;
  m_spinLineWidth->setWhatsThis (tr ("Select a size for the guidelines"));
  m_spinLineWidth->setMinimum(1);
  connect (m_spinLineWidth, SIGNAL (valueChanged (int)), this, SLOT (slotLineWidth (int)));
  layout->addWidget (m_spinLineWidth, row++, 2);
}

void DlgSettingsGuideline::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::createOptionalSaveDefault";
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
  m_spinLineWidth->setValue (qFloor (m_modelGuidelineAfter->lineWidth ()));
  
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

void DlgSettingsGuideline::slotLineWidth (int lineWidth)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGuideline::slotLineWidth";

  m_modelGuidelineAfter->setLineWidth (lineWidth);
  updateControls();
  updatePreview();
}                               

void DlgSettingsGuideline::updateControls ()
{
  enableOk (true);
}

void DlgSettingsGuideline::updatePreview()
{
  // Geometry parameters
}
