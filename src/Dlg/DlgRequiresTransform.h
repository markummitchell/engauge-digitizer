#ifndef DLG_REQUIRES_TRANSFORM_H
#define DLG_REQUIRES_TRANSFORM_H

#include <QMessageBox>

/// Dialog to be displayed whenever some operation or processing cannot be performed since the axis points are not defined
class DlgRequiresTransform : public QMessageBox
{
 public:
  /// Single constructor
  DlgRequiresTransform(const QString &context);

private:
  DlgRequiresTransform();
};

#endif // DLG_REQUIRES_TRANSFORM_H
