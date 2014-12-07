#ifndef DLG_SPINBOX_DOUBLE_H
#define DLG_SPINBOX_DOUBLE_H

#include <QDoubleSpinBox>

/// Wrapper around QDoubleSpinBox to catch when the text field is empty.
class DlgSpinBoxDouble : public QDoubleSpinBox
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSpinBoxDouble(QWidget *parent = 0);

  /// Catch the keypresses that would leave the field empty.
  virtual void keyReleaseEvent(QKeyEvent *event);

signals:
  /// Signal any change in the text.
  void textChanged(const QString &);

};

#endif // DLG_SPINBOX_DOUBLE_H
