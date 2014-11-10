#ifndef DLG_PREFERENCES_PAGE_CURVES_H
#define DLG_PREFERENCES_PAGE_CURVES_H

#include <QWidget>

class CmdMediator;
class QGridLayout;
class QListWidget;
class QPushButton;

/// Stacked widget page for editing curves preferences.
class DlgPreferencesPageCurves : public QWidget
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgPreferencesPageCurves(CmdMediator &cmdMediator,
                           QWidget *parent = 0);

private slots:
  void slotMoveDown ();
  void slotMoveUp ();
  void slotNew ();
  void slotRemove ();
  void slotRename ();

private:
  DlgPreferencesPageCurves(QWidget *parent = 0);

  void createButtons (QGridLayout *layout);
  void createListCurves (QGridLayout *layout);

  QPushButton *m_btnNew;
  QPushButton *m_btnRemove;
  QPushButton *m_btnMoveUp;
  QPushButton *m_btnMoveDown;
  QPushButton *m_btnRename;
  QListWidget *m_listCurves;
};

#endif // DLG_PREFERENCES_PAGE_CURVES_H
