#include "DlgRequiresTransform.h"
#include "Version.h"

DlgRequiresTransform::DlgRequiresTransform (const QString &context)
{
  setWindowTitle (engaugeWindowTitle());

  QString text = QString ("%1 can only be performed after three axis points have been created, "
                          "so the coordinates are defined")
                 .arg (context);
  setText (text);
}
