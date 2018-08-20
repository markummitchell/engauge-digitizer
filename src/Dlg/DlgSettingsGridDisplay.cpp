/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdSettingsGridDisplay.h"
#include "DlgSettingsGridDisplay.h"
#include "EngaugeAssert.h"
#include "GridInitializer.h"
#include "GridLineFactory.h"
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
const int COUNT_DECIMALS = 0;
const int MINIMUM_HEIGHT = 480;

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

void DlgSettingsGridDisplay::createDisplayCommon (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::createDisplayCommon";

  QWidget *widgetCommon = new QWidget;
  layout->addWidget (widgetCommon, row++, 2, 1, 2);

  QGridLayout *layoutCommon = new QGridLayout;
  widgetCommon->setLayout (layoutCommon);
  int rowCommon = 0;

  m_labelLimitWarning = new QLabel;
  m_labelLimitWarning->setStyleSheet ("QLabel { color: red; }");
  layoutCommon->addWidget (m_labelLimitWarning, rowCommon++, 0, 1, 4, Qt::AlignCenter);

  QLabel *labelColor = new QLabel (QString ("%1:").arg (tr ("Color")));
  layoutCommon->addWidget (labelColor, rowCommon, 1);

  m_cmbColor = new QComboBox;
  m_cmbColor->setWhatsThis (tr ("Select a color for the lines"));
  populateColorComboWithoutTransparent (*m_cmbColor);
  connect (m_cmbColor, SIGNAL (activated (const QString &)), this, SLOT (slotColor (const QString &))); // activated() ignores code changes
  layoutCommon->addWidget (m_cmbColor, rowCommon++, 2);

  // Make sure there is an empty column, for padding, on the left and right sides
  layoutCommon->setColumnStretch (0, 1);
  layoutCommon->setColumnStretch (1, 0);
  layoutCommon->setColumnStretch (2, 0);
  layoutCommon->setColumnStretch (3, 1);
}

void DlgSettingsGridDisplay::createDisplayGridLinesX (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::createDisplayGridLinesX";

  m_groupX = new QGroupBox; // Text is added at load time at which point current context is known
  layout->addWidget (m_groupX, row, 2);

  QGridLayout *layoutGroup = new QGridLayout;
  m_groupX->setLayout (layoutGroup);

  QLabel *labelDisable = new QLabel (QString ("%1:").arg (tr ("Disable")));
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

  QLabel *labelCount = new QLabel (QString ("%1:").arg (tr ("Count")));
  layoutGroup->addWidget (labelCount, 1, 0);

  m_editCountX = new QLineEdit;
  m_editCountX->setWhatsThis (tr ("Number of X grid lines.\n\n"
                                  "The number of X grid lines must be entered as an integer greater than zero"));
  m_validatorCountX = new QDoubleValidator;
  m_validatorCountX->setBottom (COUNT_MIN);
  m_validatorCountX->setDecimals (COUNT_DECIMALS);
  m_editCountX->setValidator (m_validatorCountX);
  connect (m_editCountX, SIGNAL (textEdited (const QString &)), this, SLOT  (slotCountX (const QString &)));
  layoutGroup->addWidget (m_editCountX, 1, 1);

  QLabel *labelStart = new QLabel (QString ("%1:").arg (tr ("Start")));
  layoutGroup->addWidget (labelStart, 2, 0);

  m_editStartX = new QLineEdit;
  m_editStartX->setWhatsThis (tr ("Value of the first X grid line.\n\n"
                                  "The start value cannot be greater than the stop value"));
  m_validatorStartX = new QDoubleValidator;
  m_editStartX->setValidator (m_validatorStartX);
  connect (m_editStartX, SIGNAL (textEdited (const QString &)), this, SLOT  (slotStartX (const QString &)));
  layoutGroup->addWidget (m_editStartX, 2, 1);

  QLabel *labelStep = new QLabel (QString ("%1:").arg (tr ("Step")));
  layoutGroup->addWidget (labelStep, 3, 0);

  m_editStepX = new QLineEdit;
  m_editStepX->setWhatsThis (tr ("Difference in value between two successive X grid lines.\n\n"
                                 "The step value must be greater than zero"));
  m_validatorStepX = new QDoubleValidator;
  m_editStepX->setValidator (m_validatorStepX);
  connect (m_editStepX, SIGNAL (textEdited (const QString &)), this, SLOT  (slotStepX (const QString &)));
  layoutGroup->addWidget (m_editStepX, 3, 1);

  QLabel *labelStop = new QLabel (QString ("%1:").arg (tr ("Stop")));
  layoutGroup->addWidget (labelStop, 4, 0);

  m_editStopX = new QLineEdit;
  m_editStopX->setWhatsThis (tr ("Value of the last X grid line.\n\n"
                                 "The stop value cannot be less than the start value"));
  m_validatorStopX = new QDoubleValidator;
  m_editStopX->setValidator (m_validatorStopX);
  connect (m_editStopX, SIGNAL (textEdited (const QString &)), this, SLOT  (slotStopX (const QString &)));
  layoutGroup->addWidget (m_editStopX, 4, 1);
}

void DlgSettingsGridDisplay::createDisplayGridLinesY (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::createDisplayGridLinesY";

  m_groupY = new QGroupBox; // Text is added at load time at which point current context is known
  layout->addWidget (m_groupY, row++, 3);

  QGridLayout *layoutGroup = new QGridLayout;
  m_groupY->setLayout (layoutGroup);

  QLabel *labelDisable = new QLabel (QString ("%1:").arg (tr ("Disable")));
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

  QLabel *labelCount = new QLabel (QString ("%1:").arg (tr ("Count")));
  layoutGroup->addWidget (labelCount, 1, 0);

  m_editCountY = new QLineEdit;
  m_editCountY->setWhatsThis (tr ("Number of Y grid lines.\n\n"
                                  "The number of Y grid lines must be entered as an integer greater than zero"));
  m_validatorCountY = new QDoubleValidator;
  m_validatorCountY->setBottom (COUNT_MIN);
  m_validatorCountY->setDecimals (COUNT_DECIMALS);
  m_editCountY->setValidator (m_validatorCountY);
  connect (m_editCountY, SIGNAL (textEdited (const QString &)), this, SLOT  (slotCountY (const QString &)));
  layoutGroup->addWidget (m_editCountY, 1, 1);

  QLabel *labelStart = new QLabel (QString ("%1:").arg (tr ("Start")));
  layoutGroup->addWidget (labelStart, 2, 0);

  m_editStartY = new QLineEdit;
  m_editStartY->setWhatsThis (tr ("Value of the first Y grid line.\n\n"
                                  "The start value cannot be greater than the stop value"));
  m_validatorStartY = new QDoubleValidator;
  m_editStartY->setValidator (m_validatorStartY);
  connect (m_editStartY, SIGNAL (textEdited (const QString &)), this, SLOT  (slotStartY (const QString &)));
  layoutGroup->addWidget (m_editStartY, 2, 1);

  QLabel *labelStep = new QLabel (QString ("%1:").arg (tr ("Step")));
  layoutGroup->addWidget (labelStep, 3, 0);

  m_editStepY = new QLineEdit;
  m_editStepY->setWhatsThis (tr ("Difference in value between two successive Y grid lines.\n\n"
                                 "The step value must be greater than zero"));
  m_validatorStepY = new QDoubleValidator;
  m_editStepY->setValidator (m_validatorStepY);
  connect (m_editStepY, SIGNAL (textEdited (const QString &)), this, SLOT  (slotStepY (const QString &)));
  layoutGroup->addWidget (m_editStepY, 3, 1);

  QLabel *labelStop = new QLabel (QString ("%1:").arg (tr ("Stop")));
  layoutGroup->addWidget (labelStop, 4, 0);

  m_editStopY = new QLineEdit;
  m_editStopY->setWhatsThis (tr ("Value of the last Y grid line.\n\n"
                                 "The stop value cannot be less than the start value"));
  m_validatorStopY = new QDoubleValidator;
  m_editStopY->setValidator (m_validatorStopY);
  connect (m_editStopY, SIGNAL (textEdited (const QString &)), this, SLOT  (slotStopY (const QString &)));
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

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // Checkbox part of "section" checkboxes. In other rows this has empty space as indentation
  layout->setColumnStretch(2, 0); // X
  layout->setColumnStretch(3, 0); // Y
  layout->setColumnStretch(4, 1); // Empty last column

  int row = 0;
  createDisplayGridLinesX (layout, row);
  createDisplayGridLinesY (layout, row);
  createDisplayCommon (layout, row);
  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsGridDisplay::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::handleOk";

  // Set the stable flag
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
  delete m_modelGridDisplayBefore;
  delete m_modelGridDisplayAfter;

  // Display cartesian or polar headers as appropriate
  QString titleX = tr ("X Grid Lines");
  if (cmdMediator.document ().modelCoords().coordsType() == COORDS_TYPE_POLAR) {
    titleX = QString (QChar (0x98, 0x03)) + QString (" %1").arg (tr ("Grid Lines"));
  }
  m_groupX->setTitle (titleX);

  QString titleY = tr ("Y Grid Lines");
  if (cmdMediator.document ().modelCoords().coordsType() == COORDS_TYPE_POLAR) {
    titleY = QString (tr ("Radius Grid Lines"));
  }
  m_groupY->setTitle (titleY);

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

  int indexColor = m_cmbColor->findData(QVariant(m_modelGridDisplayAfter->paletteColor()));
  ENGAUGE_ASSERT (indexColor >= 0);
  m_cmbColor->setCurrentIndex(indexColor);

  m_scenePreview->addPixmap (cmdMediator.document().pixmap());

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsGridDisplay::setSmallDialogs(bool smallDialogs)
{
  if (!smallDialogs) {
    setMinimumHeight (MINIMUM_HEIGHT);
  }
}

void DlgSettingsGridDisplay::slotColor (QString const &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotColor";

  m_modelGridDisplayAfter->setPaletteColor((ColorPalette) m_cmbColor->currentData().toInt());
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotCountX(const QString &count)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotCountX";

  m_modelGridDisplayAfter->setCountX(count.toInt());
  updateDisplayedVariableX ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotCountY(const QString &count)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotCountY";

  m_modelGridDisplayAfter->setCountY(count.toInt());
  updateDisplayedVariableY ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotDisableX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotDisableX";

  GridCoordDisable gridCoordDisable = (GridCoordDisable) m_cmbDisableX->currentData().toInt();
  m_modelGridDisplayAfter->setDisableX(gridCoordDisable);
  updateDisplayedVariableX ();
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotDisableY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotDisableY";

  GridCoordDisable gridCoordDisable = (GridCoordDisable) m_cmbDisableY->currentData().toInt();
  m_modelGridDisplayAfter->setDisableY(gridCoordDisable);
  updateDisplayedVariableY ();
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStartX(const QString &startX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStartX";

  m_modelGridDisplayAfter->setStartX(startX.toDouble());
  updateDisplayedVariableX ();
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStartY(const QString &startY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStartY";

  m_modelGridDisplayAfter->setStartY(startY.toDouble());
  updateDisplayedVariableY ();
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStepX(const QString &stepX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStepX";

  m_modelGridDisplayAfter->setStepX(stepX.toDouble());
  updateDisplayedVariableX ();
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStepY(const QString &stepY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStepY";

  m_modelGridDisplayAfter->setStepY(stepY.toDouble());
  updateDisplayedVariableY ();
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStopX(const QString &stopX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStopX";

  m_modelGridDisplayAfter->setStopX(stopX.toDouble());
  updateDisplayedVariableX ();
  updateControls();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStopY(const QString &stopY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStopY";

  m_modelGridDisplayAfter->setStopY(stopY.toDouble());
  updateDisplayedVariableY ();
  updateControls();
  updatePreview();
}

bool DlgSettingsGridDisplay::textItemsAreValid () const
{
  QString textCountX = m_editCountX->text();
  QString textCountY = m_editCountY->text();
  QString textStartX = m_editStartX->text();
  QString textStartY = m_editStartY->text();
  QString textStepX = m_editStepX->text();
  QString textStepY = m_editStepY->text();
  QString textStopX = m_editStopX->text();
  QString textStopY = m_editStopY->text();

  // To prevent an infinite loop, skip if either:
  // 1) a field is empty
  // 2) value in a field is malformed
  bool ok = false;
  int pos;
  if (
      !textCountX.isEmpty() &&
      !textCountY.isEmpty() &&
      !textStartX.isEmpty() &&
      !textStartY.isEmpty() &&
      !textStepX.isEmpty() &&
      !textStepY.isEmpty() &&
      !textStopX.isEmpty() &&
      !textStopY.isEmpty() &&
      m_validatorCountX->validate(textCountX, pos) == QValidator::Acceptable &&
      m_validatorCountY->validate(textCountY, pos) == QValidator::Acceptable &&
      m_validatorStartX->validate(textStartX, pos) == QValidator::Acceptable &&
      m_validatorStartY->validate(textStartY, pos) == QValidator::Acceptable &&
      m_validatorStepX->validate(textStepX, pos) == QValidator::Acceptable &&
      m_validatorStepY->validate(textStepY, pos) == QValidator::Acceptable &&
      m_validatorStopX->validate(textStopX, pos) == QValidator::Acceptable &&
      m_validatorStopY->validate(textStopY, pos) == QValidator::Acceptable) {

    // Reject zero steps
    double stepX = textCountX.toDouble ();
    double stepY = textCountY.toDouble ();

    if (stepX != 0 && stepY != 0) {

      ok = true;
    }
  }

  return ok;
}

bool DlgSettingsGridDisplay::textItemsDoNotBreakLineCountLimit ()
{
  if (textItemsAreValid ()) {
    QString textCountX = m_editCountX->text();
    QString textCountY = m_editCountY->text();
    QString textStartX = m_editStartX->text();
    QString textStartY = m_editStartY->text();
    QString textStepX = m_editStepX->text();
    QString textStepY = m_editStepY->text();
    QString textStopX = m_editStopX->text();
    QString textStopY = m_editStopY->text();

    // Given that text fields have good values, now compare grid line counts to limit
    GridInitializer initializer;

    bool linearAxisXTheta = (cmdMediator ().document ().modelCoords ().coordScaleXTheta() == COORD_SCALE_LINEAR);
    bool linearAxisYRadius = (cmdMediator ().document ().modelCoords ().coordScaleYRadius() == COORD_SCALE_LINEAR);

    int countX = textCountX.toInt ();
    if (m_modelGridDisplayAfter->disableX() == GRID_COORD_DISABLE_COUNT) {
      countX = initializer.computeCount (linearAxisXTheta,
                                         textStartX.toDouble (),
                                         textStopX.toDouble (),
                                         textStepX.toDouble ());
    }
    int countY = textCountY.toInt ();
    if (m_modelGridDisplayAfter->disableY() == GRID_COORD_DISABLE_COUNT) {
      countY = initializer.computeCount (linearAxisYRadius,
                                         textStartY.toDouble (),
                                         textStopY.toDouble (),
                                         textStepY.toDouble ());
    }

    return (countX <= mainWindow ().modelMainWindow ().maximumGridLines() &&
            countY <= mainWindow ().modelMainWindow ().maximumGridLines());
  }

  return true;
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

  if (textItemsDoNotBreakLineCountLimit ()) {
    m_labelLimitWarning->setText ("");
  } else {
    m_labelLimitWarning->setText (tr ("Grid line count exceeds limit set by Settings / Main Window."));
  }

  enableOk (textItemsAreValid () && textItemsDoNotBreakLineCountLimit ());
}

void DlgSettingsGridDisplay::updateDisplayedVariableX ()
{
  GridInitializer initializer;

  bool linearAxis = (cmdMediator ().document ().modelCoords ().coordScaleXTheta() == COORD_SCALE_LINEAR);

  switch (m_modelGridDisplayAfter->disableX()) {
    case GRID_COORD_DISABLE_COUNT:
      m_editCountX->setText (QString::number (initializer.computeCount (linearAxis,
                                                                        m_modelGridDisplayAfter->startX (),
                                                                        m_modelGridDisplayAfter->stopX (),
                                                                        m_modelGridDisplayAfter->stepX ())));
      break;

    case GRID_COORD_DISABLE_START:
      m_editStartX->setText (QString::number (initializer.computeStart (linearAxis,
                                                                        m_modelGridDisplayAfter->stopX (),
                                                                        m_modelGridDisplayAfter->stepX (),
                                                                        m_modelGridDisplayAfter->countX ())));
      break;

    case GRID_COORD_DISABLE_STEP:
      m_editStepX->setText (QString::number (initializer.computeStep (linearAxis,
                                                                      m_modelGridDisplayAfter->startX (),
                                                                      m_modelGridDisplayAfter->stopX (),
                                                                      m_modelGridDisplayAfter->countX ())));
      break;

    case GRID_COORD_DISABLE_STOP:
      m_editStopX->setText (QString::number (initializer.computeStop (linearAxis,
                                                                      m_modelGridDisplayAfter->startX (),
                                                                      m_modelGridDisplayAfter->stepX (),
                                                                      m_modelGridDisplayAfter->countX ())));
      break;

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "DlgSettingsGridDisplay::updateDisplayedVariableX";
      break;
  }
}

void DlgSettingsGridDisplay::updateDisplayedVariableY ()
{
  GridInitializer initializer;

  bool linearAxis = (cmdMediator ().document ().modelCoords ().coordScaleYRadius () == COORD_SCALE_LINEAR);

  switch (m_modelGridDisplayAfter->disableY()) {
    case GRID_COORD_DISABLE_COUNT:
      m_editCountY->setText (QString::number (initializer.computeCount (linearAxis,
                                                                        m_modelGridDisplayAfter->startY (),
                                                                        m_modelGridDisplayAfter->stopY (),
                                                                        m_modelGridDisplayAfter->stepY ())));
      break;

    case GRID_COORD_DISABLE_START:
      m_editStartY->setText (QString::number (initializer.computeStart (linearAxis,
                                                                        m_modelGridDisplayAfter->stopY (),
                                                                        m_modelGridDisplayAfter->stepY (),
                                                                        m_modelGridDisplayAfter->countY ())));
      break;

    case GRID_COORD_DISABLE_STEP:
      m_editStepY->setText (QString::number (initializer.computeStep (linearAxis,
                                                                      m_modelGridDisplayAfter->startY (),
                                                                      m_modelGridDisplayAfter->stopY (),
                                                                      m_modelGridDisplayAfter->countY ())));
      break;

    case GRID_COORD_DISABLE_STOP:
      m_editStopY->setText (QString::number (initializer.computeStop (linearAxis,
                                                                      m_modelGridDisplayAfter->startY (),
                                                                      m_modelGridDisplayAfter->stepY (),
                                                                      m_modelGridDisplayAfter->countY ())));
      break;

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "DlgSettingsGridDisplay::updateDisplayedVariableY";
      break;
  }
}

void DlgSettingsGridDisplay::updatePreview ()
{
  m_gridLines.clear ();

  if (textItemsAreValid ()) {

    GridLineFactory factory (*m_scenePreview,
                             cmdMediator ().document ().modelCoords());

    factory.createGridLinesForEvenlySpacedGrid (*m_modelGridDisplayAfter,
                                                cmdMediator ().document (),
                                                mainWindow ().modelMainWindow(),
                                                mainWindow ().transformation(),
                                                m_gridLines);
  }
}
