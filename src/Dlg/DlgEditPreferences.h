#ifndef DLG_EDIT_PREFERENCES_H
#define DLG_EDIT_PREFERENCES_H

#include <QDialog>

class CmdMediator;
class QListWidget;
class QListWidgetItem;
class QPushButton;
class QStackedWidget;
class QWidget;

/// Dialog box for editing the application and current-Document settings.
class DlgEditPreferences : public QDialog
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgEditPreferences(CmdMediator &cmdMediator);

private slots:
  void changePage (QListWidgetItem *current, QListWidgetItem *previous);

private:
  DlgEditPreferences();

  void createListWidget();
  void createStackedWidgetPage (QWidget *&widget,
                                const QString &imageFile,
                                const QString &title);
  void createStackedWidgets ();

  CmdMediator &m_cmdMediator;

  QListWidget *m_listWidget;
  QStackedWidget *m_stackedWidget;

  QWidget *m_frameCoords;
  QWidget *m_frameCurves;
  QWidget *m_frameCurveProperties;
  QWidget *m_frameExport;
  QWidget *m_frameFilter;
  QWidget *m_frameGridDisplay;
  QWidget *m_frameGridRemoval;
  QWidget *m_framePointMatch;
  QWidget *m_frameSegments;

  QPushButton *m_btnClose;
};

#endif // DLG_EDIT_PREFERENCES_H
