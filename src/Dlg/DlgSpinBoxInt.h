#ifndef DLG_SPINBOX_INT_H
#define DLG_SPINBOX_INT_H

#include <QSpinBox>

/// Wrapper around QSpinBox to catch when the text field is empty.
class DlgSpinBoxInt : public QSpinBox
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSpinBoxInt(QWidget *parent = 0);

  /// Catch the keypresses that would leave the field empty.
  virtual void keyReleaseEvent(QKeyEvent *event);

signals:
  /// Signal any change in the text.
  void textChanged(const QString &);

};

#endif // DLG_SPINBOX_INT_H
