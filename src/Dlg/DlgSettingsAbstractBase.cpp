#include "CmdMediator.h"
#include "DlgSettingsAbstractBase.h"

DlgSettingsAbstractBase::DlgSettingsAbstractBase(CmdMediator &cmdMediator,
                                                 QWidget *parent) :
  QDialog (parent),
  m_cmdMediator (cmdMediator)
{
}

DlgSettingsAbstractBase::~DlgSettingsAbstractBase()
{
}

CmdMediator &DlgSettingsAbstractBase::cmdMediator ()
{
  return m_cmdMediator;
}
