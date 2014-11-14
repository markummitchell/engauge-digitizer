#include "CmdMediator.h"
#include "DlgPreferencesPageAbstractBase.h"

DlgPreferencesPageAbstractBase::DlgPreferencesPageAbstractBase(CmdMediator &cmdMediator,
                                                               QWidget *parent) :
  QWidget (parent),
  m_cmdMediator (cmdMediator)
{
}

DlgPreferencesPageAbstractBase::~DlgPreferencesPageAbstractBase()
{
}

CmdMediator &DlgPreferencesPageAbstractBase::cmdMediator ()
{
  return m_cmdMediator;
}
