/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_EDIT_POINT_H
#define DLG_EDIT_POINT_H

#include "CoordUnitsDate.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsPolarTheta.h"
#include "CoordUnitsTime.h"
#include "DocumentAxesPointsRequired.h"
#include <QCursor>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class DigitizeStateAbstractBase;
class DlgValidatorAbstract;
class DocumentModelCoords;
class MainWindow;
class MainWindowModel;
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
                const MainWindowModel &modelMainWindow,
                const QCursor &cursorShape,
                const Transformation &transformation,
                DocumentAxesPointsRequired documentAxesPointsRequired,
                bool isXOnly = false,
                const double *xInitialValue = 0,
                const double *yInitialValue = 0);
  ~DlgEditPoint ();

  /// Return the graph coordinates position specified by the user. Only applies if dialog was accepted
  QPointF posGraph (bool &isXOnly) const;

signals:
  /// Send a signal to trigger the setting of the override cursor.
  void signalSetOverrideCursor (QCursor);

private slots:
  void slotTextChanged (const QString &);

private:
  void createCoords (QVBoxLayout *layoutOuter);
  void createHint (QVBoxLayout *layoutOuter);
  void createOkCancel (QVBoxLayout *layoutOuter);
  void initializeGraphCoordinates (const double *xInitialValue,
                                   const double *yInitialValue,
                                   const Transformation &transformation,
                                   bool isX,
                                   bool isY);
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

  DocumentAxesPointsRequired m_documentAxesPointsRequired;

  const DocumentModelCoords &m_modelCoords;
  const MainWindowModel &m_modelMainWindow;
};

#endif // DLG_EDIT_POINT_H
