/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgErrorReportLocal.h"
#include <QCommonStyle>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextStream>
#include <QVBoxLayout>

const int MAX_BTN_WIDTH = 80;

DlgErrorReportLocal::DlgErrorReportLocal(const QString &xml,
                                         QWidget *parent) :
  DlgErrorReportAbstractBase (parent),
  m_xmlOriginal (xml)
{
  QVBoxLayout *layout = new QVBoxLayout;
  layout->setSizeConstraint (QLayout::SetFixedSize);
  setLayout (layout);

  QCommonStyle style;
  setModal(true);
  setWindowTitle (tr ("Error Report"));
  setWindowIcon(style.standardIcon (QStyle::SP_MessageBoxCritical));

  QLabel *lblMessage = new QLabel (tr ("An unrecoverable error has occurred. Quitting."));
  lblMessage->setWordWrap(true);
  layout->addWidget (lblMessage);

  QHBoxLayout *layoutButtons = new QHBoxLayout;

  QWidget *panelButtons = new QWidget;
  panelButtons->setLayout (layoutButtons);
  layout->addWidget (panelButtons);

  m_btnOk = new QPushButton(tr ("Ok"));
  m_btnOk->setMaximumWidth (MAX_BTN_WIDTH);
  layoutButtons->addWidget (m_btnOk);
  connect (m_btnOk, SIGNAL (released ()), this, SLOT (accept ()));
}

DlgErrorReportLocal::~DlgErrorReportLocal()
{
}

