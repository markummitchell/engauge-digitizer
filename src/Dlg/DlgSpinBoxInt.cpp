#include "DlgSpinBoxInt.h"

DlgSpinBoxInt::DlgSpinBoxInt(QWidget *parent) :
  QSpinBox (parent)
{
}

void DlgSpinBoxInt::keyReleaseEvent(QKeyEvent * /* event */)
{
  emit textChanged(text());
}
