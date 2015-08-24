#include "DlgChecklistGuideWizard.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>

int DlgChecklistGuideWizard::MINIMUM_DIALOG_WIDTH = 350;

DlgChecklistGuideWizard::DlgChecklistGuideWizard (MainWindow &mainWindow) :
  m_mainWindow (mainWindow),
  m_dialogName ("ChecklistGuide")
{
  setWindowTitle (tr ("Checklist Guide Wizard"));
  setModal (true);

  createWidgets();
}

void DlgChecklistGuideWizard::createWidgets()
{
  const int STRETCH_OFF = 0, STRETCH_ON = 1;

  QVBoxLayout *panelLayout = new QVBoxLayout (this);

  setMinimumWidth (MINIMUM_DIALOG_WIDTH);
  setLayout (panelLayout);

//  panelLayout->addWidget (subPanel);
//  panelLayout->setStretch (panelLayout->count () - 1, STRETCH_ON);

  QWidget *panelButtons = new QWidget (this);
  QHBoxLayout *buttonLayout = new QHBoxLayout (panelButtons);

  m_btnCancel = new QPushButton (tr ("Cancel"));
  buttonLayout->addWidget (m_btnCancel);
  connect (m_btnCancel, SIGNAL (released ()), this, SLOT (slotCancel ()));

  QSpacerItem *spacer = new QSpacerItem (40, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);
  buttonLayout->addItem (spacer);

  m_btnOk = new QPushButton (tr ("Ok"));
  m_btnOk->setEnabled (false); // Nothing to save initially
  buttonLayout->addWidget (m_btnOk);
  connect (m_btnOk, SIGNAL (released ()), this, SLOT (slotOk ()));

  panelLayout->addWidget (panelButtons, STRETCH_ON, Qt::AlignRight);
  panelLayout->setStretch (panelLayout->count () - 1, STRETCH_OFF);
}

void DlgChecklistGuideWizard::handleOk()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgChecklistGuideWizard::handleOk";
}

void DlgChecklistGuideWizard::saveGeometryToSettings ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgChecklistGuideWizard::saveGeometryToSettings";

  // Store the settings for use by showEvent
  QSettings settings;
  settings.setValue (m_dialogName, saveGeometry ());
}

void DlgChecklistGuideWizard::showEvent (QShowEvent * /* event */)
{
  m_btnOk->setEnabled (false);

  QSettings settings;
  if (settings.contains (m_dialogName)) {

    // Restore the settings that were stored by the last call to saveGeometryToSettings
    restoreGeometry (settings.value (m_dialogName).toByteArray ());
  }
}

void DlgChecklistGuideWizard::slotCancel()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgChecklistGuideWizard::slotCancel";

  saveGeometryToSettings();
  hide();
}

void DlgChecklistGuideWizard::slotOk()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgChecklistGuideWizard::slotOk";

  saveGeometryToSettings();
  handleOk();
}
