#include "CmdMediator.h"
#include "CmdSettingsCommon.h"
#include "DlgSettingsCommon.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>
#include <qmath.h>
#include <QRadioButton>
#include <QSpinBox>

DlgSettingsCommon::DlgSettingsCommon(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Common",
                           "DlgSettingsCommon",
                           mainWindow),
  m_modelCommonBefore (0),
  m_modelCommonAfter (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCommon::DlgSettingsCommon";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsCommon::~DlgSettingsCommon()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCommon::~DlgSettingsCommon";
}

void DlgSettingsCommon::createControls (QGridLayout *layout,
                                        int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCommon::createControls";

  QLabel *labelCursorSize = new QLabel ("Cursor size (pixels):");
  layout->addWidget (labelCursorSize, row, 1);

  m_spinCursorSize = new QSpinBox;
  m_spinCursorSize->setMinimum (1);
  m_spinCursorSize->setWhatsThis (tr ("Effective Cursor Size\n\n"
                                      "This is the effective width and height of the cursor when clicking on a pixel that is "
                                      "not part of the background.\n\n"
                                      "This parameter is used in the Color Picker and Point Match modes"));
  connect (m_spinCursorSize, SIGNAL (valueChanged (int)), this, SLOT (slotCursorSize (int)));
  layout->addWidget (m_spinCursorSize, row++, 2);

  QLabel *labelExtraPrecision = new QLabel ("Extra precision (digits):");
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

QWidget *DlgSettingsCommon::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCommon::createSubPanel";

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

void DlgSettingsCommon::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCommon::handleOk";

  CmdSettingsCommon *cmd = new CmdSettingsCommon (mainWindow (),
                                                  cmdMediator ().document(),
                                                  *m_modelCommonBefore,
                                                  *m_modelCommonAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsCommon::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCommon::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelCommonBefore != 0) {
    delete m_modelCommonBefore;
  }
  if (m_modelCommonAfter != 0) {
    delete m_modelCommonAfter;
  }

  // Save new data
  m_modelCommonBefore = new DocumentModelCommon (cmdMediator.document());
  m_modelCommonAfter = new DocumentModelCommon (cmdMediator.document());

  // Populate controls
  m_spinCursorSize->setValue (m_modelCommonAfter->cursorSize());
  m_spinExtraPrecision->setValue (m_modelCommonAfter->extraPrecision());

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
}

void DlgSettingsCommon::slotCursorSize (int cursorSize)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCommon::slotCursorSize";

  m_modelCommonAfter->setCursorSize (cursorSize);
  updateControls();
}

void DlgSettingsCommon::slotExtraPrecision (int extraPrecision)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCommon::slotExtraPrecision";

  m_modelCommonAfter->setExtraPrecision (extraPrecision);
  updateControls();
}

void DlgSettingsCommon::updateControls ()
{
  enableOk (true);
}
