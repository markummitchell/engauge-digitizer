/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ChecklistLineEdit.h"
#include "Logger.h"

ChecklistLineEdit::ChecklistLineEdit()
{
  // Fine tuning of the border which is designed to look good when QLineEdit is all by itself. In our case,
  // the QLineEdits are stacked tightly, so we want the borders between adjacent QLineEdits to look more like
  // spreadsheet cells
  setStyleSheet ("QLineEdit { border-style: solid; border-color: black; border-width: 1px 1px 1px 0;}");
}

void ChecklistLineEdit::keyReleaseEvent (QKeyEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistLineEdit::keyReleaseEvent";

  emit signalKeyRelease();
}
