/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_CURVE_ADD_REMOVE_H
#define DLG_SETTINGS_CURVE_ADD_REMOVE_H

#include "DlgSettingsAbstractBase.h"
#include <QItemSelection>
#include <QModelIndex>

class CurveNameList;
class QGridLayout;
class QListView;
class QPushButton;
class QTableView;

/// Dialog for editing curve names settings.
///
/// The debug macro DLG_SETTINGS_DEBUG can be temporarily set to see the hidden columns
class DlgSettingsCurveAddRemove : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsCurveAddRemove(MainWindow &mainWindow);
  virtual ~DlgSettingsCurveAddRemove();

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
  virtual QWidget *createSubPanel ();
  void load (CmdMediator &cmdMediator);
  virtual void setSmallDialogs (bool smallDialogs);

private slots:
  void slotDataChanged (const QModelIndex &topLeft,
                        const QModelIndex &bottomRight,
                        const QVector<int> &roles);
  void slotNew ();
  void slotRemove ();
  void slotResetDefault();
  void slotSaveDefault();
  void slotSelectionChanged (QItemSelection, QItemSelection);

protected:
  virtual void handleOk ();

private:

  void appendCurveName (const QString &curveNameNew,
                        const QString &curveNameOriginal,
                        int numPoints);
  void createButtons (QGridLayout *layout, int &row);
  void createListCurves (QGridLayout *layout, int &row);
  bool endsWithNumber (const QString &str) const;
  void insertCurveName (int row,
                        const QString &curveNameNew,
                        const QString &curveNameOriginal,
                        int numPoints);
  int newIndexFromSelection () const;
  QString nextCurveName () const; // Pick good curve name to go at currentRow()
  int numberAtEnd (const QString &str) const;
  void removeSelectedCurves();
  void selectCurveName (const QString &curveWanted);
  void updateControls ();

  CurveNameList *m_curveNameList; // Model for m_listCurves

#ifdef DLG_SETTINGS_DEBUG
  QTableView *m_listCurves; // While debugging, the 3 columns in each row are visible to make the operations more clear
#else
  QListView *m_listCurves; // Use QListView instead of QListWidget so validators can be used
#endif

  QPushButton *m_btnAdd;
  QPushButton *m_btnRemove;
  QPushButton *m_btnRename;

  QPushButton *m_btnResetDefault;
  QPushButton *m_btnSaveDefault;
};

#endif // DLG_SETTINGS_CURVE_ADD_REMOVE_H
