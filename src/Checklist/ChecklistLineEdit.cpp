#include "ChecklistLineEdit.h"
#include "Logger.h"

ChecklistLineEdit::ChecklistLineEdit()
{
}

void ChecklistLineEdit::keyReleaseEvent (QKeyEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistLineEdit::keyReleaseEvent";

  emit signalKeyRelease();
}
