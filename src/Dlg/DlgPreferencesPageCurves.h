#ifndef DLG_PREFERENCES_PAGE_CURVES_H
#define DLG_PREFERENCES_PAGE_CURVES_H

#include "DlgPreferencesPageAbstractBase.h"

class QGridLayout;
class QListWidget;
class QListWidgetItem;
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

  QListWidgetItem *appendCurveName (const QString &curveName);
  void createButtons (QGridLayout *layout);
  void createListCurves (QGridLayout *layout);
  bool endsWithNumber (const QString &str) const;
  QListWidgetItem *insertCurveName (int row,
                                    const QString &curveName);
  QString nextCurveName () const; // Pick good curve name to go at currentRow()
  int numberAtEnd (const QString &str) const;
  void updateControls ();

  QPushButton *m_btnNew;
  QPushButton *m_btnRemove;
  QPushButton *m_btnRename;
  QListWidget *m_listCurves;
};

#endif // DLG_PREFERENCES_PAGE_CURVES_H
