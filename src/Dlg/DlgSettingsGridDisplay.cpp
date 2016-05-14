/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdSettingsGridDisplay.h"
#include "DlgSettingsGridDisplay.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleValidator>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "ViewPreview.h"

const int COUNT_MIN = 1;
const int COUNT_MAX = 100;
const int COUNT_DECIMALS = 0;

DlgSettingsGridDisplay::DlgSettingsGridDisplay(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Grid Display"),
                           "DlgSettingsGridDisplay",
                           mainWindow),
  m_scenePreview (0),
  m_viewPreview (0),
  m_modelGridDisplayBefore (0),
  m_modelGridDisplayAfter (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::DlgSettingsGridDisplay";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsGridDisplay::~DlgSettingsGridDisplay()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::~DlgSettingsGridDisplay";
}

void DlgSettingsGridDisplay::createDisplayGridLines (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::createDisplayGridLines";

  createDisplayGridLinesX (layout, row);
  createDisplayGridLinesY (layout, row);
}

void DlgSettingsGridDisplay::createDisplayGridLinesX (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::createDisplayGridLinesX";

  QString titleX = tr ("X Grid Lines");
  if (false) {
    titleX = QString (QChar (0x98, 0x03)) + QString (" %1").arg (tr ("Grid Lines"));
  }
  QGroupBox *groupX = new QGroupBox (titleX);
  layout->addWidget (groupX, row, 2);

  QGridLayout *layoutGroup = new QGridLayout;
  groupX->setLayout (layoutGroup);

  QLabel *labelDisable = new QLabel (tr ("Disable:"));
  layoutGroup->addWidget (labelDisable, 0, 0);

  m_cmbDisableX = new QComboBox;
  m_cmbDisableX->setWhatsThis (tr ("Disabled value.\n\n"
                                   "The X grid lines are specified using only three values at a time. For flexibility, four values "
                                   "are offered so you must chose which value is disabled. Once disabled, that value is simply "
                                   "updated as the other values change"));
  m_cmbDisableX->addItem(gridCoordDisableToString (GRID_COORD_DISABLE_COUNT),
                         QVariant (GRID_COORD_DISABLE_COUNT));
  m_cmbDisableX->addItem(gridCoordDisableToString (GRID_COORD_DISABLE_START),
                         QVariant (GRID_COORD_DISABLE_START));
  m_cmbDisableX->addItem(gridCoordDisableToString (GRID_COORD_DISABLE_STEP),
                         QVariant (GRID_COORD_DISABLE_STEP));
  m_cmbDisableX->addItem(gridCoordDisableToString (GRID_COORD_DISABLE_STOP),
                         QVariant (GRID_COORD_DISABLE_STOP));
  connect (m_cmbDisableX, SIGNAL (activated (const QString &)), this, SLOT (slotDisableX (const QString &))); // activated() ignores code changes
  layoutGroup->addWidget (m_cmbDisableX, 0, 1);

  QLabel *labelCount = new QLabel (tr ("Count:"));
  layoutGroup->addWidget (labelCount, 1, 0);

  m_editCountX = new QLineEdit;
  m_editCountX->setWhatsThis (tr ("Number of X grid lines.\n\n"
                                  "The number of X grid lines must be entered as an integer greater than zero"));
  m_validatorCountX = new QDoubleValidator (COUNT_MIN, COUNT_MAX, COUNT_DECIMALS);
  m_editCountX->setValidator (m_validatorCountX);
  connect (m_editCountX, SIGNAL (textChanged (const QString &)), this, SLOT  (slotCountX (const QString &)));
  layoutGroup->addWidget (m_editCountX, 1, 1);

  QLabel *labelStart = new QLabel (tr ("Start:"));
  layoutGroup->addWidget (labelStart, 2, 0);

  m_editStartX = new QLineEdit;
  m_editStartX->setWhatsThis (tr ("Value of the first X grid line.\n\n"
                                  "The start value cannot be greater than the stop value"));
  m_validatorStartX = new QDoubleValidator;
  m_editStartX->setValidator (m_validatorStartX);
  connect (m_editStartX, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStartX (const QString &)));
  layoutGroup->addWidget (m_editStartX, 2, 1);

  QLabel *labelStep = new QLabel (tr ("Step:"));
  layoutGroup->addWidget (labelStep, 3, 0);

  m_editStepX = new QLineEdit;
  m_editStepX->setWhatsThis (tr ("Difference in value between two successive X grid lines.\n\n"
                                 "The step value must be greater than zero"));
  m_validatorStepX = new QDoubleValidator;
  m_editStepX->setValidator (m_validatorStepX);
  connect (m_editStepX, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStepX (const QString &)));
  layoutGroup->addWidget (m_editStepX, 3, 1);

  QLabel *labelStop = new QLabel (tr ("Stop:"));
  layoutGroup->addWidget (labelStop, 4, 0);

  m_editStopX = new QLineEdit;
  m_editStopX->setWhatsThis (tr ("Value of the last X grid line.\n\n"
                                 "The stop value cannot be less than the start value"));
  m_validatorStopX = new QDoubleValidator;
  m_editStopX->setValidator (m_validatorStopX);
  connect (m_editStopX, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStopX (const QString &)));
  layoutGroup->addWidget (m_editStopX, 4, 1);
}

void DlgSettingsGridDisplay::createDisplayGridLinesY (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::createDisplayGridLinesY";

  QString titleY = tr ("Y Grid Lines");
  if (false) {
    titleY = QString (tr ("R Grid Lines"));
  }
  QGroupBox *groupY = new QGroupBox (titleY);
  layout->addWidget (groupY, row++, 3);

  QGridLayout *layoutGroup = new QGridLayout;
  groupY->setLayout (layoutGroup);

  QLabel *labelDisable = new QLabel (tr ("Disable:"));
  layoutGroup->addWidget (labelDisable, 0, 0);

  m_cmbDisableY = new QComboBox;
  m_cmbDisableY->setWhatsThis (tr ("Disabled value.\n\n"
                                   "The Y grid lines are specified using only three values at a time. For flexibility, four values "
                                   "are offered so you must chose which value is disabled. Once disabled, that value is simply "
                                   "updated as the other values change"));
  m_cmbDisableY->addItem(gridCoordDisableToString (GRID_COORD_DISABLE_COUNT),
                         QVariant (GRID_COORD_DISABLE_COUNT));
  m_cmbDisableY->addItem(gridCoordDisableToString (GRID_COORD_DISABLE_START),
                         QVariant (GRID_COORD_DISABLE_START));
  m_cmbDisableY->addItem(gridCoordDisableToString (GRID_COORD_DISABLE_STEP),
                         QVariant (GRID_COORD_DISABLE_STEP));
  m_cmbDisableY->addItem(gridCoordDisableToString (GRID_COORD_DISABLE_STOP),
                         QVariant (GRID_COORD_DISABLE_STOP));
  connect (m_cmbDisableY, SIGNAL (activated (const QString &)), this, SLOT (slotDisableY (const QString &))); // activated() ignores code changes
  layoutGroup->addWidget (m_cmbDisableY, 0, 1);

  QLabel *labelCount = new QLabel (tr ("Count:"));
  layoutGroup->addWidget (labelCount, 1, 0);

  m_editCountY = new QLineEdit;
  m_editCountY->setWhatsThis (tr ("Number of Y grid lines.\n\n"
                                  "The number of Y grid lines must be entered as an integer greater than zero"));
  m_validatorCountY = new QDoubleValidator (COUNT_MIN, COUNT_MAX, COUNT_DECIMALS);
  m_editCountY->setValidator (m_validatorCountY);
  connect (m_editCountY, SIGNAL (textChanged (const QString &)), this, SLOT  (slotCountY (const QString &)));
  layoutGroup->addWidget (m_editCountY, 1, 1);

  QLabel *labelStart = new QLabel (tr ("Start:"));
  layoutGroup->addWidget (labelStart, 2, 0);

  m_editStartY = new QLineEdit;
  m_editStartY->setWhatsThis (tr ("Value of the first Y grid line.\n\n"
                                  "The start value cannot be greater than the stop value"));
  m_validatorStartY = new QDoubleValidator;
  m_editStartY->setValidator (m_validatorStartY);
  connect (m_editStartY, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStartY (const QString &)));
  layoutGroup->addWidget (m_editStartY, 2, 1);

  QLabel *labelStep = new QLabel (tr ("Step:"));
  layoutGroup->addWidget (labelStep, 3, 0);

  m_editStepY = new QLineEdit;
  m_editStepY->setWhatsThis (tr ("Difference in value between two successive Y grid lines.\n\n"
                                 "The step value must be greater than zero"));
  m_validatorStepY = new QDoubleValidator;
  m_editStepY->setValidator (m_validatorStepY);
  connect (m_editStepY, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStepY (const QString &)));
  layoutGroup->addWidget (m_editStepY, 3, 1);

  QLabel *labelStop = new QLabel (tr ("Stop:"));
  layoutGroup->addWidget (labelStop, 4, 0);

  m_editStopY = new QLineEdit;
  m_editStopY->setWhatsThis (tr ("Value of the last Y grid line.\n\n"
                                 "The stop value cannot be less than the start value"));
  m_validatorStopY = new QDoubleValidator;
  m_editStopY->setValidator (m_validatorStopY);
  connect (m_editStopY, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStopY (const QString &)));
  layoutGroup->addWidget (m_editStopY, 4, 1);
}

void DlgSettingsGridDisplay::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
}

void DlgSettingsGridDisplay::createPreview (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::createPreview";

  QLabel *labelPreview = new QLabel (tr ("Preview"));
  layout->addWidget (labelPreview, row++, 0, 1, 5);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview,
                                   ViewPreview::VIEW_ASPECT_RATIO_VARIABLE,
                                   this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect grid display"));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);
  layout->addWidget (m_viewPreview, row++, 0, 1, 5);
}

QWidget *DlgSettingsGridDisplay::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::createSubPanel";

  const int COLUMN_CHECKBOX_WIDTH = 60;

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // Checkbox part of "section" checkboxes. In other rows this has empty space as indentation
  layout->setColumnMinimumWidth(1, COLUMN_CHECKBOX_WIDTH);
  layout->setColumnStretch(2, 0); // X
  layout->setColumnStretch(3, 0); // Y
  layout->setColumnStretch(4, 1); // Empty last column

  int row = 0;
  createDisplayGridLines (layout, row);
  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsGridDisplay::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::handleOk";

  // Set the initialized flag
  m_modelGridDisplayAfter->setStable (true);

  CmdSettingsGridDisplay *cmd = new CmdSettingsGridDisplay (mainWindow (),
                                                            cmdMediator ().document(),
                                                            *m_modelGridDisplayBefore,
                                                            *m_modelGridDisplayAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsGridDisplay::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelGridDisplayBefore != 0) {
    delete m_modelGridDisplayBefore;
  }
  if (m_modelGridDisplayAfter != 0) {
    delete m_modelGridDisplayAfter;
  }

  // Save new data
  m_modelGridDisplayBefore = new DocumentModelGridDisplay (cmdMediator.document());
  m_modelGridDisplayAfter = new DocumentModelGridDisplay (cmdMediator.document());

  // Populate controls
  int indexDisableX = m_cmbDisableX->findData (QVariant (m_modelGridDisplayAfter->disableX()));
  m_cmbDisableX->setCurrentIndex (indexDisableX);

  m_editCountX->setText(QString::number(m_modelGridDisplayAfter->countX()));
  m_editStartX->setText(QString::number(m_modelGridDisplayAfter->startX()));
  m_editStepX->setText(QString::number(m_modelGridDisplayAfter->stepX()));
  m_editStopX->setText(QString::number(m_modelGridDisplayAfter->stopX()));

  int indexDisableY = m_cmbDisableY->findData (QVariant (m_modelGridDisplayAfter->disableY()));
  m_cmbDisableY->setCurrentIndex (indexDisableY);

  m_editCountY->setText(QString::number(m_modelGridDisplayAfter->countY()));
  m_editStartY->setText(QString::number(m_modelGridDisplayAfter->startY()));
  m_editStepY->setText(QString::number(m_modelGridDisplayAfter->stepY()));
  m_editStopY->setText(QString::number(m_modelGridDisplayAfter->stopY()));

  m_scenePreview->clear();
  m_scenePreview->addPixmap (cmdMediator.document().pixmap());

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsGridDisplay::slotCountX(const QString &count)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotCountX";

  m_modelGridDisplayAfter->setCountX(count.toInt());
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotCountY(const QString &count)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotCountY";

  m_modelGridDisplayAfter->setCountY(count.toInt());
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotDisableX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotDisableX";

  GridCoordDisable gridCoordDisable = (GridCoordDisable) m_cmbDisableX->currentData().toInt();
  m_modelGridDisplayAfter->setDisableX(gridCoordDisable);
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotDisableY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotDisableY";

  GridCoordDisable gridCoordDisable = (GridCoordDisable) m_cmbDisableY->currentData().toInt();
  m_modelGridDisplayAfter->setDisableY(gridCoordDisable);
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStartX(const QString &startX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStartX";

  m_modelGridDisplayAfter->setStartX(startX.toDouble());
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStartY(const QString &startY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStartY";

  m_modelGridDisplayAfter->setStartY(startY.toDouble());
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStepX(const QString &stepX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStepX";

  m_modelGridDisplayAfter->setStepX(stepX.toDouble());
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStepY(const QString &stepY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStepY";

  m_modelGridDisplayAfter->setStepY(stepY.toDouble());
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStopX(const QString &stopX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStopX";

  m_modelGridDisplayAfter->setStopX(stopX.toDouble());
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStopY(const QString &stopY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStopY";

  m_modelGridDisplayAfter->setStopY(stopY.toDouble());
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::updateControls ()
{
  GridCoordDisable disableX = (GridCoordDisable) m_cmbDisableX->currentData().toInt();
  m_editCountX->setEnabled (disableX != GRID_COORD_DISABLE_COUNT);
  m_editStartX->setEnabled (disableX != GRID_COORD_DISABLE_START);
  m_editStepX->setEnabled (disableX != GRID_COORD_DISABLE_STEP);
  m_editStopX->setEnabled (disableX != GRID_COORD_DISABLE_STOP);

  GridCoordDisable disableY = (GridCoordDisable) m_cmbDisableY->currentData().toInt();
  m_editCountY->setEnabled (disableY != GRID_COORD_DISABLE_COUNT);
  m_editStartY->setEnabled (disableY != GRID_COORD_DISABLE_START);
  m_editStepY->setEnabled (disableY != GRID_COORD_DISABLE_STEP);
  m_editStopY->setEnabled (disableY != GRID_COORD_DISABLE_STOP);

  QString textCountX = m_editCountX->text();
  QString textStartX = m_editStartX->text();
  QString textStepX = m_editStepX->text();
  QString textStopX = m_editStopX->text();
  QString textCountY = m_editCountY->text();
  QString textStartY = m_editStartY->text();
  QString textStepY = m_editStepY->text();
  QString textStopY = m_editStopY->text();

  int pos;
  bool isOk = (m_validatorCountX->validate (textCountX, pos) == QValidator::Acceptable) &&
              (m_validatorStartX->validate (textStartX, pos) == QValidator::Acceptable) &&
              (m_validatorStepX->validate (textStepX, pos) == QValidator::Acceptable) &&
              (m_validatorStopX->validate (textStopX, pos) == QValidator::Acceptable) &&
              (m_validatorCountY->validate (textCountY, pos) == QValidator::Acceptable) &&
              (m_validatorStartY->validate (textStartY, pos) == QValidator::Acceptable) &&
              (m_validatorStepY->validate (textStepY, pos) == QValidator::Acceptable) &&
              (m_validatorStopY->validate (textStopY, pos) == QValidator::Acceptable);
  enableOk (isOk);
}

void DlgSettingsGridDisplay::updatePreview ()
{

}
