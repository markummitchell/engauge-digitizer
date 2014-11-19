#ifndef DLG_PREFERENCES_PAGE_CURVES_H
#define DLG_PREFERENCES_PAGE_CURVES_H

#include "DlgPreferencesPageAbstractBase.h"
#include <QItemSelection>
#include <QModelIndex>

class DlgModelCurves;
class QGridLayout;
class QListView;
class QPushButton;

/// Stacked widget page for editing curves preferences.
class DlgPreferencesPageCurves : public DlgPreferencesPageAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgPreferencesPageCurves(CmdMediator &cmdMediator,
                           QWidget *parent = 0);

  virtual void load ();

private slots:
  void slotDataChanged (const QModelIndex &topLeft,
                        const QModelIndex &bottomRight,
                        const QVector<int> &roles);
  void slotNew ();
  void slotRemove ();
  void slotSelectionChanged (QItemSelection, QItemSelection);

private:
  DlgPreferencesPageCurves(QWidget *parent = 0);

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

  DlgModelCurves *m_modelCurves; // Model for m_listCurves
  QListView *m_listCurves; // Use QListView instead of QListWidget so validators can be used
};

#endif // DLG_PREFERENCES_PAGE_CURVES_H
