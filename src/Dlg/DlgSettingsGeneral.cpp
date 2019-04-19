/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdSettingsGeneral.h"
#include "DlgSettingsGeneral.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QComboBox>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <qmath.h>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include "Settings.h"

DlgSettingsGeneral::DlgSettingsGeneral(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("General"),
                           "DlgSettingsGeneral",
                           mainWindow),
  m_modelGeneralBefore (nullptr),
  m_modelGeneralAfter (nullptr)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGeneral::DlgSettingsGeneral";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsGeneral::~DlgSettingsGeneral()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGeneral::~DlgSettingsGeneral";
}

void DlgSettingsGeneral::createControls (QGridLayout *layout,
                                         int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGeneral::createControls";

  QLabel *labelCursorSize = new QLabel (QString ("%1:").arg (tr ("Effective cursor size (pixels)")));
  layout->addWidget (labelCursorSize, row, 1);

  m_spinCursorSize = new QSpinBox;
  m_spinCursorSize->setMinimum (1);
  m_spinCursorSize->setWhatsThis (tr ("Effective Cursor Size\n\n"
                                      "This is the effective width and height of the cursor when clicking on a pixel that is "
                                      "not part of the background.\n\n"
                                      "This parameter is used in the Color Picker and Point Match modes"));
  connect (m_spinCursorSize, SIGNAL (valueChanged (int)), this, SLOT (slotCursorSize (int)));
  layout->addWidget (m_spinCursorSize, row++, 2);

  QLabel *labelExtraPrecision = new QLabel (QString ("%1:").arg (tr ("Extra precision (digits)")));
  layout->addWidget (labelExtraPrecision, row, 1);

  m_spinExtraPrecision = new QSpinBox;
  m_spinExtraPrecision->setMinimum (0);
  m_spinExtraPrecision->setWhatsThis (tr ("Extra Digits of Precision\n\n"
                                          "This is the number of additional digits of precision appended after the significant "
                                          "digits determined by the digitization accuracy at that point. The digitization accuracy "
                                          "at any point equals the change in graph coordinates from moving one pixel in each direction. "
                                          "Appending extra digits does not improve the accuracy of the numbers. More information can "
                                          "be found in discussions of accuracy versus precision.\n\n"
                                          "This parameter is used on the coordinates in the Status Bar and during Export"));
  connect (m_spinExtraPrecision, SIGNAL (valueChanged (int)), this, SLOT (slotExtraPrecision (int)));
  layout->addWidget (m_spinExtraPrecision, row++, 2);
}

void DlgSettingsGeneral::createOptionalSaveDefault (QHBoxLayout *layout)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGeneral::createOptionalSaveDefault";

  m_btnSaveDefault = new QPushButton (tr ("Save As Default"));
  m_btnSaveDefault->setWhatsThis (tr ("Save the settings for use as future defaults, according to the curve name selection."));
  connect (m_btnSaveDefault, SIGNAL (released ()), this, SLOT (slotSaveDefault ()));
  layout->addWidget (m_btnSaveDefault, 0, Qt::AlignLeft);
}

QWidget *DlgSettingsGeneral::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGeneral::createSubPanel";

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

void DlgSettingsGeneral::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGeneral::handleOk";

  CmdSettingsGeneral *cmd = new CmdSettingsGeneral (mainWindow (),
                                                    cmdMediator ().document(),
                                                    *m_modelGeneralBefore,
                                                    *m_modelGeneralAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsGeneral::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGeneral::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  delete m_modelGeneralBefore;
  delete m_modelGeneralAfter;

  // Save new data
  m_modelGeneralBefore = new DocumentModelGeneral (cmdMediator.document());
  m_modelGeneralAfter = new DocumentModelGeneral (cmdMediator.document());

  // Populate controls
  m_spinCursorSize->setValue (m_modelGeneralAfter->cursorSize());
  m_spinExtraPrecision->setValue (m_modelGeneralAfter->extraPrecision());

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
}

void DlgSettingsGeneral::setSmallDialogs(bool /* smallDialogs */)
{
}

void DlgSettingsGeneral::slotCursorSize (int cursorSize)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGeneral::slotCursorSize";

  m_modelGeneralAfter->setCursorSize (cursorSize);
  updateControls();
}

void DlgSettingsGeneral::slotExtraPrecision (int extraPrecision)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGeneral::slotExtraPrecision";

  m_modelGeneralAfter->setExtraPrecision (extraPrecision);
  updateControls();
}

void DlgSettingsGeneral::slotSaveDefault()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGeneral::slotSaveDefault";

  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup (SETTINGS_GROUP_GENERAL);

  settings.setValue (SETTINGS_GENERAL_CURSOR_SIZE,
                     m_modelGeneralAfter->cursorSize());
  settings.setValue (SETTINGS_GENERAL_EXTRA_PRECISION,
                     m_modelGeneralAfter->extraPrecision());
  settings.endGroup ();
}

void DlgSettingsGeneral::updateControls ()
{
  enableOk (true);
}
