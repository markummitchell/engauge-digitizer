#ifndef DLG_EDIT_POINT_H
#define DLG_EDIT_POINT_H

#include "CoordUnitsDate.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsPolarTheta.h"
#include "CoordUnitsTime.h"
#include <QCursor>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class DigitizeStateAbstractBase;
class DlgValidatorAbstract;
class DocumentModelCoords;
class MainWindow;
class QDoubleValidator;
class QVBoxLayout;
class Transformation;

/// Dialog box for editing the information of one axis point.
class DlgEditPoint : public QDialog
{
  Q_OBJECT;

public:
  /// Constructor for existing point which already has graph coordinates (which may be changed using this dialog).
  /// If initial values are unspecified then the value fields will be initially empty
  DlgEditPoint (MainWindow &mainWindow,
                DigitizeStateAbstractBase &digitizeState,
                const DocumentModelCoords &modelCoords,
                const QCursor &cursorShape,
                const Transformation &transformation,
                const double *xInitialValue = 0,
                const double *yInitialValue = 0);
  ~DlgEditPoint ();

  /// Return the graph coordinates position specified by the user. Only applies if dialog was accepted
  QPointF posGraph () const;

signals:
  /// Send a signal to trigger the setting of the override cursor.
  void signalSetOverrideCursor (QCursor);

private slots:
  void slotTextChanged (const QString &);

private:
  void createCoords (QVBoxLayout *layoutOuter);
  void createOkCancel (QVBoxLayout *layoutOuter);
  void initializeGraphCoordinates (const double *xInitialValue,
                                   const double *yInitialValue,
                                   const Transformation &transformation);
  bool isCartesian () const;
  QChar nameXTheta () const;
  QChar nameYRadius () const;
  QString unitsType (bool isXTheta) const;
  void updateControls ();

  QCursor m_cursorShape;
  QLineEdit *m_editGraphX;
  DlgValidatorAbstract *m_validatorGraphX;
  QLineEdit *m_editGraphY;
  DlgValidatorAbstract *m_validatorGraphY;
  QPushButton *m_btnOk;
  QPushButton *m_btnCancel;

  const DocumentModelCoords &m_modelCoords;
};

#endif // DLG_EDIT_POINT_H
