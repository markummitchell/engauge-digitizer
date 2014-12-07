#include "DlgSpinBoxDouble.h"

DlgSpinBoxDouble::DlgSpinBoxDouble(QWidget *parent) :
  QDoubleSpinBox (parent)
{
}

void DlgSpinBoxDouble::keyReleaseEvent(QKeyEvent * /* event */)
{
  emit textChanged(text());
}
