#ifndef DLG_SETTINGS_CURVE_ADD_REMOVE_H
#define DLG_SETTINGS_CURVE_ADD_REMOVE_H

#include "DlgSettingsAbstractBase.h"
#include <QItemSelection>
#include <QModelIndex>

class CurveNameList;
class QGridLayout;
class QListView;
class QPushButton;

/// Dialog for editing curve names settings.
class DlgSettingsCurveAddRemove : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsCurveAddRemove(MainWindow &mainWindow);
  virtual ~DlgSettingsCurveAddRemove();

  virtual QWidget *createSubPanel ();
  void load (CmdMediator &cmdMediator);

private slots:
  void slotDataChanged (const QModelIndex &topLeft,
                        const QModelIndex &bottomRight,
                        const QVector<int> &roles);
  void slotNew ();
  void slotRemove ();
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
  QString nextCurveName () const; // Pick good curve name to go at currentRow()
  int numberAtEnd (const QString &str) const;
  void removeSelectedCurves();
  void updateControls ();

  QPushButton *m_btnNew;
  QPushButton *m_btnRemove;
  QPushButton *m_btnRename;

  CurveNameList *m_curveNameList; // Model for m_listCurves
  QListView *m_listCurves; // Use QListView instead of QListWidget so validators can be used
};

#endif // DLG_SETTINGS_CURVE_ADD_REMOVE_H
