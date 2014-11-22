#include "CmdMediator.h"
#include "DlgSettingsAbstractBase.h"
#include <QPushButton>
#include <QVBoxLayout>

DlgSettingsAbstractBase::DlgSettingsAbstractBase(const QString &title,
                                                 QWidget *parent) :
  QDialog (parent),
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
  const int NO_STRETCH = 1;

  QVBoxLayout *panelLayout = new QVBoxLayout (this);
  setLayout (panelLayout);

  panelLayout->addWidget (subPanel);

  QWidget *panelButtons = new QWidget (this);
  QHBoxLayout *buttonLayout = new QHBoxLayout (panelButtons);

  QPushButton *btnOk = new QPushButton (tr ("Ok"));
  buttonLayout->addWidget (btnOk);

  QPushButton *btnCancel = new QPushButton (tr ("Cancel"));
  buttonLayout->addWidget (btnCancel);

  panelLayout->addWidget (panelButtons, NO_STRETCH, Qt::AlignCenter);
}

void DlgSettingsAbstractBase::setCmdMediator (CmdMediator &cmdMediator)
{
  m_cmdMediator = &cmdMediator;
}
