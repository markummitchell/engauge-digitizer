/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_EDIT_POINT_CURVE_H
#define DLG_EDIT_POINT_CURVE_H

#include <QDialog>
#include <QPointF>
#include <QString>

class DlgValidatorAbstract;
class DocumentModelCoords;
class MainWindow;
class MainWindowModel;
class QLineEdit;
class QPushButton;
class QVBoxLayout;
class Transformation;

/// Dialog box for editing the information of one curve point.
class DlgEditPointCurve : public QDialog
{
  Q_OBJECT;

public:
  /// Constructor for existing point which already has graph coordinates (which may be changed using this dialog).
  /// If initial values are unspecified then the value fields will be initially empty
  DlgEditPointCurve (MainWindow &mainWindow,
                     const DocumentModelCoords &modelCoords,
                     const MainWindowModel &modelMainWindow,
                     const Transformation &transformation,
                     const double *xInitialValue = 0,
                     const double *yInitialValue = 0);
  ~DlgEditPointCurve ();

  /// Return the graph coordinates position specified by the user. Only applies if dialog was accepted
  QPointF posGraph () const;

private slots:
  void slotTextChanged (const QString &);

private:
  DlgEditPointCurve ();

  void createCoords (QVBoxLayout *layoutOuter);
  void createHint (QVBoxLayout *layoutOuter);
  void createOkCancel (QVBoxLayout *layoutOuter);
  void initializeGraphCoordinates (const double *xInitialValue,
                                   const double *yInitialValue,
                                   const Transformation &transformation);
  bool isCartesian () const;
  QChar nameXTheta () const;
  QChar nameYRadius () const;
  QString unitsType (bool isXTheta) const;
  void updateControls ();

  DlgValidatorAbstract *m_validatorGraphX;
  QLineEdit *m_editGraphX;
  DlgValidatorAbstract *m_validatorGraphY;
  QLineEdit *m_editGraphY;
  QPushButton *m_btnOk;
  QPushButton *m_btnCancel;

  // Enable Ok button once text has changed. For simplicity, this is true even when original text is restored
  bool m_changed;

  const DocumentModelCoords &m_modelCoords;
  const MainWindowModel &m_modelMainWindow;
};

#endif // DLG_EDIT_POINT_CURVE_H
