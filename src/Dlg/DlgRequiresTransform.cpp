/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgRequiresTransform.h"
#include "Version.h"

DlgRequiresTransform::DlgRequiresTransform (const QString &context)
{
  setWindowTitle (engaugeWindowTitle());

  QString text = QString ("%1 %2")
                 .arg (context)
                 .arg (tr ("can only be performed after three axis points have been created, "
                           "so the coordinates are defined"));
  setText (text);
}
