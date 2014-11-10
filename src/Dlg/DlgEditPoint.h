#ifndef DLG_EDIT_POINT_H
#define DLG_EDIT_POINT_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class DigitizeStateAbstractBase;
class MainWindow;
class QVBoxLayout;

/// Dialog box for editing the information of one axis point.
class DlgEditPoint : public QDialog
{
  Q_OBJECT;

public:
  /// Constructor for existing point which already has graph coordinates (which may be changed using this dialog).
  DlgEditPoint (MainWindow &mainWindow,
                DigitizeStateAbstractBase &digitizeState,
                Qt::CursorShape cursorShape,
                QString xValue = "",
                QString yValue = "");
  ~DlgEditPoint ();

  /// Return the graph coordinates position specified by the user. Only applies if dialog was accepted
  QPointF posGraph () const;

signals:
  /// Send a signal to trigger the setting of the override cursor.
  void signalSetOverrideCursor (Qt::CursorShape);

private slots:
  void slotTextChanged (const QString &);

private:
  void createCoords (QVBoxLayout *layoutOuter);
  void createOkCancel (QVBoxLayout *layoutOuter);
  void updateControls ();

  Qt::CursorShape m_cursorShape;
  QLineEdit *m_editGraphX;
  QLineEdit *m_editGraphY;
  QPushButton *m_btnOk;
  QPushButton *m_btnCancel;
};

#endif // DLG_EDIT_POINT_H
