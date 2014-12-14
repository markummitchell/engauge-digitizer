#include "CmdMediator.h"
#include "DlgSettingsAbstractBase.h"
#include "MainWindow.h"
#include <QComboBox>
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
  setModal (true);
}

DlgSettingsAbstractBase::~DlgSettingsAbstractBase()
{
}

CmdMediator &DlgSettingsAbstractBase::cmdMediator ()
{
  Q_ASSERT (m_cmdMediator != 0);

  return *m_cmdMediator;
}

void DlgSettingsAbstractBase::enableOk (bool enable)
{
  m_btnOk->setEnabled (enable);
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

  m_btnCancel = new QPushButton (tr ("Cancel"));
  buttonLayout->addWidget (m_btnCancel);
  connect (m_btnCancel, SIGNAL (released ()), this, SLOT (hide ()));

  QSpacerItem *spacer = new QSpacerItem (40, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);
  buttonLayout->addItem (spacer);

  m_btnOk = new QPushButton (tr ("Ok"));
  m_btnOk->setEnabled (false); // Nothing to save initially
  buttonLayout->addWidget (m_btnOk);
  connect (m_btnOk, SIGNAL (released ()), this, SLOT (slotOk ()));

  panelLayout->addWidget (panelButtons, STRETCH_ON, Qt::AlignRight);
  panelLayout->setStretch (panelLayout->count () - 1, STRETCH_OFF);
}

MainWindow &DlgSettingsAbstractBase::mainWindow ()
{
  return m_mainWindow;
}

void DlgSettingsAbstractBase::populateColorComboWithoutTransparent (QComboBox &combo)
{
  combo.addItem ("Blue", QVariant (COLOR_PALETTE_BLUE));
  combo.addItem ("Red", QVariant (COLOR_PALETTE_RED));
  combo.addItem ("Black", QVariant (COLOR_PALETTE_BLACK));
  combo.addItem ("Cyan", QVariant (COLOR_PALETTE_CYAN));
  combo.addItem ("Gold", QVariant (COLOR_PALETTE_GOLD));
  combo.addItem ("Green", QVariant (COLOR_PALETTE_GREEN));
  combo.addItem ("Magenta", QVariant (COLOR_PALETTE_MAGENTA));
  combo.addItem ("Red", QVariant (COLOR_PALETTE_RED));
  combo.addItem ("Yellow", QVariant (COLOR_PALETTE_YELLOW));
}

void DlgSettingsAbstractBase::populateColorComboWithTransparent (QComboBox &combo)
{
  populateColorComboWithoutTransparent (combo);
  combo.addItem ("Transparent", QVariant (COLOR_PALETTE_TRANSPARENT));
}

void DlgSettingsAbstractBase::setCmdMediator (CmdMediator &cmdMediator)
{
  m_cmdMediator = &cmdMediator;
}

void DlgSettingsAbstractBase::showEvent (QShowEvent * /* event */)
{
  m_btnOk->setEnabled (false);
}

void DlgSettingsAbstractBase::slotOk ()
{
  // Forward to leaf class
  handleOk ();
}
