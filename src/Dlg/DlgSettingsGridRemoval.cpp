#include "CmdMediator.h"
#include "CmdSettingsGridRemoval.h"
#include "DlgSettingsGridRemoval.h"
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

const double CLOSE_DISTANCE_MAX = 64;
const double CLOSE_DISTANCE_MIN = 0;
const int CLOSE_DECIMALS = 1;
const int COUNT_MIN = 1;
const int COUNT_MAX = 100;
const int COUNT_DECIMALS = 0;

DlgSettingsGridRemoval::DlgSettingsGridRemoval(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Grid Removal", mainWindow),
  m_modelGridRemovalBefore (0),
  m_modelGridRemovalAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsGridRemoval::createPreview (QGridLayout *layout, int &row)
{
  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0, 1, 5);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview, this);
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);
  layout->addWidget (m_viewPreview, row++, 0, 1, 5);
}

void DlgSettingsGridRemoval::createRemoveGridLines (QGridLayout *layout, int &row)
{
  m_chkRemoveGridLines = new QCheckBox ("Remove pixels close to grid lines");
  m_chkRemoveGridLines->setWhatsThis ("Check this box to have pixels close to regularly spaced gridlines removed.\n\n"
                                      "This option is only available when the axis points have all been defined.");
  connect (m_chkRemoveGridLines, SIGNAL (stateChanged (int)), this, SLOT (slotRemoveGridLines (int)));
  layout->addWidget (m_chkRemoveGridLines, row++, 1, 1, 3);

  QLabel *labelCloseDistance = new QLabel ("Close distance (pixels):");
  layout->addWidget (labelCloseDistance, row, 2);

  m_editCloseDistance = new QLineEdit;
  m_editCloseDistance->setWhatsThis ("Set closeness distance in pixels.\n\n"
                                     "Pixels that are closer to the regularly spaced gridlines, than this distance, "
                                     "will be removed.\n\n"
                                     "This value cannot be negative. A zero value disables this feature. Decimal values are allowed");
  m_editCloseDistance->setValidator (new QDoubleValidator (CLOSE_DISTANCE_MIN, CLOSE_DISTANCE_MAX, CLOSE_DECIMALS));
  connect (m_editCloseDistance, SIGNAL (textChanged (const QString &)), this, SLOT (slotCloseDistance (const QString &)));
  layout->addWidget (m_editCloseDistance, row++, 3);

  createRemoveGridLinesX (layout, row);
  createRemoveGridLinesY (layout, row);
}

void DlgSettingsGridRemoval::createRemoveGridLinesX (QGridLayout *layout, int &row)
{
  QString titleX = "X Grid Lines";
  if (false) {
    titleX = QString (QChar (0x98, 0x03)) + QString (" Grid Lines");
  }
  QGroupBox *groupX = new QGroupBox (titleX);
  layout->addWidget (groupX, row, 2);

  QGridLayout *layoutGroup = new QGridLayout;
  groupX->setLayout (layoutGroup);

  QLabel *labelDisable = new QLabel ("Disable:");
  layoutGroup->addWidget (labelDisable, 0, 0);

  m_cmbDisableX = new QComboBox;
  m_cmbDisableX->setWhatsThis ("Disabled value.\n\n"
                               "The X grid lines are specified using only three values at a time. For flexibility, four values "
                               "are offered so you must chose which value is disabled. Once disabled, that value is simply "
                               "updated as the other values change");
  connect (m_cmbDisableX, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotDisableX (const QString &)));
  layoutGroup->addWidget (m_cmbDisableX, 0, 1);

  QLabel *labelCount = new QLabel ("Count:");
  layoutGroup->addWidget (labelCount, 1, 0);

  m_editCountX = new QLineEdit;
  m_editCountX->setWhatsThis ("Number of X grid lines.\n\n"
                              "The number of X grid lines must be entered as an integer greater than zero");
  m_editCountX->setValidator (new QDoubleValidator (COUNT_MIN, COUNT_MAX, COUNT_DECIMALS));
  layoutGroup->addWidget (m_editCountX, 1, 1);

  QLabel *labelStart = new QLabel ("Start:");
  layoutGroup->addWidget (labelStart, 2, 0);

  m_editStartX = new QLineEdit;
  m_editStartX->setWhatsThis ("Value of the first X grid line.\n\n"
                              "The start value cannot be greater than the stop value");
  m_editStartX->setValidator (new QDoubleValidator ());
  layoutGroup->addWidget (m_editStartX, 2, 1);

  QLabel *labelStep = new QLabel ("Step:");
  layoutGroup->addWidget (labelStep, 3, 0);

  m_editStepX = new QLineEdit;
  m_editStepX->setWhatsThis ("Difference in value between two successive X grid lines.\n\n"
                             "The step value must be greater than zero");
  m_editStepX->setValidator (new QDoubleValidator ());
  layoutGroup->addWidget (m_editStepX, 3, 1);

  QLabel *labelStop = new QLabel ("Stop:");
  layoutGroup->addWidget (labelStop, 4, 0);

  m_editStopX = new QLineEdit;
  m_editStopX->setWhatsThis ("Value of the last X grid line.\n\n"
                             "The stop value cannot be less than the start value");
  m_editStopX->setValidator (new QDoubleValidator ());
  layoutGroup->addWidget (m_editStopX, 4, 1);
}

void DlgSettingsGridRemoval::createRemoveGridLinesY (QGridLayout *layout, int &row)
{
  QString titleY = "Y Grid Lines";
  if (false) {
    titleY = QString ("R Grid Lines");
  }
  QGroupBox *groupY = new QGroupBox (titleY);
  layout->addWidget (groupY, row++, 3);

  QGridLayout *layoutGroup = new QGridLayout;
  groupY->setLayout (layoutGroup);

  QLabel *labelDisable = new QLabel ("Disable:");
  layoutGroup->addWidget (labelDisable, 0, 0);

  m_cmbDisableY = new QComboBox;
  m_cmbDisableY->setWhatsThis ("Disabled value.\n\n"
                               "The Y grid lines are specified using only three values at a time. For flexibility, four values "
                               "are offered so you must chose which value is disabled. Once disabled, that value is simply "
                               "updated as the other values change");
  connect (m_cmbDisableY, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotDisableY (const QString &)));
  layoutGroup->addWidget (m_cmbDisableY, 0, 1);

  QLabel *labelCount = new QLabel ("Count:");
  layoutGroup->addWidget (labelCount, 1, 0);

  m_editCountY = new QLineEdit;
  m_editCountY->setWhatsThis ("Number of Y grid lines.\n\n"
                              "The number of Y grid lines must be entered as an integer greater than zero");
  m_editCountY->setValidator (new QDoubleValidator (COUNT_MIN, COUNT_MAX, COUNT_DECIMALS));
  layoutGroup->addWidget (m_editCountY, 1, 1);

  QLabel *labelStart = new QLabel ("Start:");
  layoutGroup->addWidget (labelStart, 2, 0);

  m_editStartY = new QLineEdit;
  m_editStartY->setWhatsThis ("Value of the first Y grid line.\n\n"
                              "The start value cannot be greater than the stop value");
  m_editStartY->setValidator (new QDoubleValidator ());
  layoutGroup->addWidget (m_editStartY, 2, 1);

  QLabel *labelStep = new QLabel ("Step:");
  layoutGroup->addWidget (labelStep, 3, 0);

  m_editStepY = new QLineEdit;
  m_editStepY->setWhatsThis ("Difference in value between two successive Y grid lines.\n\n"
                             "The step value must be greater than zero");
  m_editStepY->setValidator (new QDoubleValidator ());
  layoutGroup->addWidget (m_editStepY, 3, 1);

  QLabel *labelStop = new QLabel ("Stop:");
  layoutGroup->addWidget (labelStop, 4, 0);

  m_editStopY = new QLineEdit;
  m_editStopY->setWhatsThis ("Value of the last Y grid line.\n\n"
                             "The stop value cannot be less than the start value");
  m_editStopY->setValidator (new QDoubleValidator ());
  layoutGroup->addWidget (m_editStopY, 4, 1);
}

void DlgSettingsGridRemoval::createRemoveParallel (QGridLayout *layout, int &row)
{
  m_chkRemoveParallel = new QCheckBox ("Remove thin lines parallel to the axes");
  m_chkRemoveParallel->setWhatsThis ("Check this box to remove thin lines that are parallel to the axes.\n\n"
                                     "This option is only available when the axis points have all been defined.\n\n"
                                     "This option works especially well if the gridlines in the original image are thinner "
                                     "than the curve lines");
  connect (m_chkRemoveParallel, SIGNAL (stateChanged (int)), this, SLOT (slotRemoveParallel (int)));
  layout->addWidget (m_chkRemoveParallel, row++, 1, 1, 3);
}

QWidget *DlgSettingsGridRemoval::createSubPanel ()
{
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
  createRemoveGridLines (layout, row);
  createRemoveParallel (layout, row);
  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsGridRemoval::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::handleOk";

  CmdSettingsGridRemoval *cmd = new CmdSettingsGridRemoval (mainWindow (),
                                                            cmdMediator ().document(),
                                                            *m_modelGridRemovalBefore,
                                                            *m_modelGridRemovalAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsGridRemoval::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::load";

  setCmdMediator (cmdMediator);

  m_modelGridRemovalBefore = new DlgModelGridRemoval (cmdMediator);
  m_modelGridRemovalAfter = new DlgModelGridRemoval (cmdMediator);
}

void DlgSettingsGridRemoval::slotCloseDistance(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotCloseDistance";

  enableOk (true);
}

void DlgSettingsGridRemoval::slotCountX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotCountX";

  enableOk (true);
}

void DlgSettingsGridRemoval::slotCountY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotCountY";

  enableOk (true);
}

void DlgSettingsGridRemoval::slotDisableX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotDisableX";

  enableOk (true);
}

void DlgSettingsGridRemoval::slotDisableY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotDisableY";

  enableOk (true);
}

void DlgSettingsGridRemoval::slotRemoveGridLines (int /* state */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotRemoveGridLines";

  enableOk (true);
  updateControls();
}

void DlgSettingsGridRemoval::slotRemoveParallel (int /* state */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotRemoveParallel";

  enableOk (true);
  updateControls();
}

void DlgSettingsGridRemoval::slotStartX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotStartX";

  enableOk (true);
}

void DlgSettingsGridRemoval::slotStartY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotStartY";

  enableOk (true);
}

void DlgSettingsGridRemoval::slotStepX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotStepX";

  enableOk (true);
}

void DlgSettingsGridRemoval::slotStepY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotStepY";

  enableOk (true);
}

void DlgSettingsGridRemoval::slotStopX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotStopX";

  enableOk (true);
}

void DlgSettingsGridRemoval::slotStopY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridRemoval::slotStopY";

  enableOk (true);
}

void DlgSettingsGridRemoval::updateControls ()
{
  m_editCloseDistance->setEnabled (m_chkRemoveGridLines->isChecked ());
  m_cmbDisableX->setEnabled (m_chkRemoveGridLines->isChecked ());
  m_editCountX->setEnabled (m_chkRemoveGridLines->isChecked ());
  m_editStartX->setEnabled (m_chkRemoveGridLines->isChecked ());
  m_editStepX->setEnabled (m_chkRemoveGridLines->isChecked ());
  m_editStopX->setEnabled (m_chkRemoveGridLines->isChecked ());
  m_cmbDisableY->setEnabled (m_chkRemoveGridLines->isChecked ());
  m_editCountY->setEnabled (m_chkRemoveGridLines->isChecked ());
  m_editStartY->setEnabled (m_chkRemoveGridLines->isChecked ());
  m_editStepY->setEnabled (m_chkRemoveGridLines->isChecked ());
  m_editStopY->setEnabled (m_chkRemoveGridLines->isChecked ());
}
