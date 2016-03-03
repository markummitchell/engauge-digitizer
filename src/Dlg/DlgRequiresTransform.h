/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_REQUIRES_TRANSFORM_H
#define DLG_REQUIRES_TRANSFORM_H

#include <QMessageBox>

/// Dialog to be displayed whenever some operation or processing cannot be performed since the axis points are not defined
class DlgRequiresTransform : public QMessageBox
{
  Q_OBJECT;

 public:
  /// Single constructor
  DlgRequiresTransform(const QString &context);

private:
  DlgRequiresTransform();
};

#endif // DLG_REQUIRES_TRANSFORM_H
