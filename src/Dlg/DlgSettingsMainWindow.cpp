#include "CmdSettingsMainWindow.h"
#include "DlgSettingsMainWindow.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
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
#include "ZoomControl.h"

DlgSettingsMainWindow::DlgSettingsMainWindow(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("MainWindow",
                           "DlgSettingsMainWindow",
                           mainWindow),
  m_modelMainWindowBefore (0),
  m_modelMainWindowAfter (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::DlgSettingsMainWindow";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsMainWindow::~DlgSettingsMainWindow()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::~DlgSettingsMainWindow";
}

void DlgSettingsMainWindow::createControls (QGridLayout *layout,
                                               int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::createControls";

  QLabel *labelZoomControl = new QLabel ("Zoom control:");
  layout->addWidget (labelZoomControl, row, 1);

  m_cmbZoomControl = new QComboBox;
  m_cmbZoomControl->addItem ("Menu only"                     , QVariant (ZOOM_CONTROL_MENU_ONLY));
  m_cmbZoomControl->addItem ("Menu and mouse wheel"          , QVariant (ZOOM_CONTROL_MENU_WHEEL));
  m_cmbZoomControl->addItem ("Menu and +/- keys"             , QVariant (ZOOM_CONTROL_MENU_PLUSMINUS));
  m_cmbZoomControl->addItem ("Menu, mouse wheel and +/- keys", QVariant (ZOOM_CONTROL_MENU_WHEEL_PLUSMINUS));
  m_cmbZoomControl->setWhatsThis (tr ("Zoom Control\n\n"
                                      "Select which inputs are used to zoom in and out."));
  connect (m_cmbZoomControl, SIGNAL (currentTextChanged (const QString)), this, SLOT (slotZoomControl(const QString)));
  layout->addWidget (m_cmbZoomControl, row++, 2);
}

void DlgSettingsMainWindow::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::createOptionalSaveDefault";
}

QWidget *DlgSettingsMainWindow::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::createSubPanel";

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

void DlgSettingsMainWindow::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::handleOk";

  CmdSettingsMainWindow *cmd = new CmdSettingsMainWindow (mainWindow (),
                                                                cmdMediator ().document(),
                                                                *m_modelMainWindowBefore,
                                                                *m_modelMainWindowAfter);
  cmdMediator ().push (cmd);

  hide ();
}
void DlgSettingsMainWindow::load (CmdMediator & /* cmdMediator */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::load";

  ENGAUGE_ASSERT (false);
}

void DlgSettingsMainWindow::loadMainWindowModel (CmdMediator &cmdMediator,
                                                       const MainWindowModel &modelMainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::loadMainWindowModel";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelMainWindowBefore != 0) {
    delete m_modelMainWindowBefore;
  }
  if (m_modelMainWindowAfter != 0) {
    delete m_modelMainWindowAfter;
  }

  // Save new data
  m_modelMainWindowBefore = new MainWindowModel (modelMainWindow);
  m_modelMainWindowAfter = new MainWindowModel (modelMainWindow);

  // Populate controls
  m_cmbZoomControl->setCurrentIndex (m_modelMainWindowAfter->zoomControl());

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
}

void DlgSettingsMainWindow::slotZoomControl(const QString)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::slotZoomControl";

  m_modelMainWindowAfter->setZoomControl ((ZoomControl) m_cmbZoomControl->currentData().toInt());
  updateControls();
}

void DlgSettingsMainWindow::updateControls ()
{
  enableOk (true);
}
