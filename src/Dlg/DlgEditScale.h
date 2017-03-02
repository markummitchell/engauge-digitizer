/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_EDIT_SCALE_H
#define DLG_EDIT_SCALE_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class DlgValidatorAbstract;
class DocumentModelCoords;
class DocumentModelGeneral;
class MainWindow;
class MainWindowModel;
class QVBoxLayout;

/// Dialog box for editing the information of the map scale
class DlgEditScale : public QDialog
{
  Q_OBJECT;

public:
  /// Single constructor
  DlgEditScale (MainWindow &mainWindow,
                const DocumentModelCoords &modelCoords,
                const DocumentModelGeneral &modelGeneral,
                const MainWindowModel &modelMainWindow,
                const double *scaleLength = 0);
  ~DlgEditScale ();

  /// Return the scale bar length specified by the user. Only applies if dialog was accepted
  double scaleLength () const;

private slots:
  void slotTextChanged (const QString &);

private:
  void createHint (QVBoxLayout *layoutOuter);
  void createOkCancel (QVBoxLayout *layoutOuter);
  void createScaleLength (QVBoxLayout *layoutOuter);
  void initializeScaleLength (const double *scaleLength);
  void updateControls ();

  QLineEdit *m_editScaleLength;
  DlgValidatorAbstract *m_validatorScaleLength;
  QPushButton *m_btnOk;
  QPushButton *m_btnCancel;

  const DocumentModelCoords &m_modelCoords;
  const DocumentModelGeneral &m_modelGeneral;
  const MainWindowModel &m_modelMainWindow;
};

#endif // DLG_EDIT_SCALE_H
