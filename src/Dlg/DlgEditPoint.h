#ifndef DLG_EDIT_POINT_H
#define DLG_EDIT_POINT_H

#include <QCursor>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class DigitizeStateAbstractBase;
class DocumentModelCoords;
class MainWindow;
class QDoubleValidator;
class QVBoxLayout;

/// Dialog box for editing the information of one axis point.
class DlgEditPoint : public QDialog
{
  Q_OBJECT;

public:
  /// Constructor for existing point which already has graph coordinates (which may be changed using this dialog).
  DlgEditPoint (MainWindow &mainWindow,
                DigitizeStateAbstractBase &digitizeState,
                const DocumentModelCoords &modelCoords,
                const QCursor &cursorShape,
                QString xValue = "",
                QString yValue = "");
  ~DlgEditPoint ();

  /// Return the graph coordinates position specified by the user. Only applies if dialog was accepted
  QPointF posGraph () const;

signals:
  /// Send a signal to trigger the setting of the override cursor.
  void signalSetOverrideCursor (QCursor);

private slots:
  void slotTextChanged (const QString &);

private:
  void createCoords (QVBoxLayout *layoutOuter,
                     const DocumentModelCoords &modelCoords);
  void createOkCancel (QVBoxLayout *layoutOuter);
  void updateControls ();

  QCursor m_cursorShape;
  QLineEdit *m_editGraphX;
  QDoubleValidator *m_validatorGraphX;
  QLineEdit *m_editGraphY;
  QDoubleValidator *m_validatorGraphY;
  QPushButton *m_btnOk;
  QPushButton *m_btnCancel;
};

#endif // DLG_EDIT_POINT_H
