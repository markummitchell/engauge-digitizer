/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgEditPointGraphLineEdit.h"
#include "Logger.h"
#include <QWidget>

DlgEditPointGraphLineEdit::DlgEditPointGraphLineEdit (QWidget *widget) :
  QLineEdit (widget),
  m_hover (false)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgEditPointGraphLineEdit::DlgEditPointGraphLineEdit";
}

DlgEditPointGraphLineEdit::~DlgEditPointGraphLineEdit()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgEditPointGraphLineEdit::~DlgEditPointGraphLineEdit";
}

void DlgEditPointGraphLineEdit::enterEvent(QEvent *)
{
  m_hover = true;
  updateBackground ();
}

void DlgEditPointGraphLineEdit::leaveEvent (QEvent *)
{
  m_hover = false;
  updateBackground ();
}

void DlgEditPointGraphLineEdit::updateBackground ()
{
  QString color = (m_hover || !text().isEmpty() ? QString ("white") : QString ("#d3d3d3"));
  QString style = QString ("QLineEdit { background-color: %1; }").arg (color);
  setStyleSheet (style);
}
