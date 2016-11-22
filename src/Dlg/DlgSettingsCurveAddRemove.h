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
#include <QString>

class CurveNameList;
class QGridLayout;
class QListView;
class QPushButton;
class QStandardItemModel;
class QTableView;
class QTextStream;

/// Dialog for editing curve names settings.
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

public slots:
  /// Cleanup after rows have been removed in the model. We remove the corresponding rows in the QListView
  void slotRowsAboutToBeRemoved (const QModelIndex &parent, int rowFirst, int rowLast);

private slots:
  void slotDataChanged (const QModelIndex &topLeft,
                        const QModelIndex &bottomRight,
                        const QVector<int> &roles);
  void slotNew ();
  void slotRemove ();
  void slotResetDefault();
  void slotSaveDefault();

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
  int newRowFromSelection () const;
  QString nextCurveName () const; // Pick good curve name to go at currentRow()
  int numberAtEnd (const QString &str) const;
  unsigned int numPointsForSelectedCurves () const;
  void printStream (QTextStream &str) const; // Debugging method
  void removeSelectedCurves();
  void selectCurveName (const QString &curveWanted);
  void updateControls ();

  CurveNameList *m_curveNameList; // Model for m_listCurves

  QListView *m_listCurves; // Use QListView instead of QListWidget so validators can be used

  QPushButton *m_btnAdd;
  QPushButton *m_btnRemove;
  QPushButton *m_btnRename;

  QPushButton *m_btnResetDefault;
  QPushButton *m_btnSaveDefault;

};

#endif // DLG_SETTINGS_CURVE_ADD_REMOVE_H
