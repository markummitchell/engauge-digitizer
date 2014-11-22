#include "CmdMediator.h"
#include "DlgSettingsAbstractBase.h"
#include "MainWindow.h"
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

DlgSettingsAbstractBase::DlgSettingsAbstractBase(const QString &title,
                                                 MainWindow &mainWindow) :
  QDialog (&mainWindow),
  m_mainWindow (mainWindow),
  m_cmdMediator (0)
{
  setWindowTitle (title);
}

DlgSettingsAbstractBase::~DlgSettingsAbstractBase()
{
}

CmdMediator &DlgSettingsAbstractBase::cmdMediator ()
{
  Q_ASSERT (m_cmdMediator != 0);

  return *m_cmdMediator;
}

void DlgSettingsAbstractBase::finishPanel (QWidget *subPanel)
{
  const int STRETCH_OFF = 0, STRETCH_ON = 1;

  QVBoxLayout *panelLayout = new QVBoxLayout (this);

  setMinimumWidth (MINIMUM_DIALOG_WIDTH);
  setLayout (panelLayout);

  panelLayout->addWidget (subPanel);
  panelLayout->setStretch (panelLayout->count () - 1, STRETCH_ON);

  QWidget *panelButtons = new QWidget (this);
  QHBoxLayout *buttonLayout = new QHBoxLayout (panelButtons);

  QPushButton *btnCancel = new QPushButton (tr ("Cancel"));
  buttonLayout->addWidget (btnCancel);
  connect (btnCancel, SIGNAL (pressed ()), this, SLOT (hide ()));

  QSpacerItem *spacer = new QSpacerItem (40, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);
  buttonLayout->addItem (spacer);

  QPushButton *btnOk = new QPushButton (tr ("Ok"));
  buttonLayout->addWidget (btnOk);
  connect (btnOk, SIGNAL (pressed ()), this, SLOT (slotOk ()));

  panelLayout->addWidget (panelButtons, STRETCH_ON, Qt::AlignRight);
  panelLayout->setStretch (panelLayout->count () - 1, STRETCH_OFF);
}

MainWindow &DlgSettingsAbstractBase::mainWindow ()
{
  return m_mainWindow;
}

void DlgSettingsAbstractBase::setCmdMediator (CmdMediator &cmdMediator)
{
  m_cmdMediator = &cmdMediator;
}

void DlgSettingsAbstractBase::slotOk ()
{
  // Forward to leaf class
  handleOk ();
}
