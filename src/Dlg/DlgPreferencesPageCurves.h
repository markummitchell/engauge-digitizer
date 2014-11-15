#ifndef DLG_PREFERENCES_PAGE_CURVES_H
#define DLG_PREFERENCES_PAGE_CURVES_H

#include "DlgPreferencesPageAbstractBase.h"

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

private slots:
  void slotCurveSelectionChanged ();
  void slotNew ();
  void slotRemove ();

private:
  DlgPreferencesPageCurves(QWidget *parent = 0);

  void appendCurveName (const QString &curveName);
  void createButtons (QGridLayout *layout);
  void createListCurves (QGridLayout *layout);
  bool endsWithNumber (const QString &str) const;
  void insertCurveName (int row,
                        const QString &curveName);
  QString nextCurveName () const; // Pick good curve name to go at currentRow()
  int numberAtEnd (const QString &str) const;
  void updateControls ();

  QPushButton *m_btnNew;
  QPushButton *m_btnRemove;
  QPushButton *m_btnRename;

  DlgModelCurves *m_modelCurves; // Model for m_listCurves
  QListView *m_listCurves; // Use QListView instead of QListWidget so validators can be used
};

#endif // DLG_PREFERENCES_PAGE_CURVES_H
