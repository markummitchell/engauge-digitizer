#ifndef DLG_SETTINGS_MAIN_WINDOW_H
#define DLG_SETTINGS_MAIN_WINDOW_H

#include "DlgSettingsAbstractBase.h"
#include <QLocale>

class QComboBox;
class QGridLayout;
class QPushButton;
class QSpinBox;
class MainWindowModel;

/// Dialog for editing main window settings, which are entirely independent of
/// all documents
class DlgSettingsMainWindow : public DlgSettingsAbstractBase {
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsMainWindow(MainWindow &mainWindow);
  virtual ~DlgSettingsMainWindow();

  virtual void createOptionalSaveDefault(QHBoxLayout *layout);
  virtual QWidget *createSubPanel();
  virtual void
  load(CmdMediator &cmdMediator); // Not used. Use loadMainWindowModel instead

  /// Replaced load method since the main window settings are independent of
  /// document, unlike other DlgSettings* classes
  void loadMainWindowModel(CmdMediator &cmdMediator,
                           const MainWindowModel &modelMainWindow);

private slots:
  void slotLocale(int index);
  void slotRecentFileClear();
  void slotZoomControl(const QString);
  void slotZoomFactor(const QString);

protected:
  virtual void handleOk();

private:
  void createControls(QGridLayout *layout, int &row);
  QString localeLabel(QLocale::Language lang, QLocale::Country country) const;
  void updateControls();

  QComboBox *m_cmbZoomFactor;
  QComboBox *m_cmbZoomControl;
  QComboBox *m_cmbLocale;
  QPushButton *m_btnRecentClear;

  MainWindowModel *m_modelMainWindowBefore;
  MainWindowModel *m_modelMainWindowAfter;
};

#endif // DLG_SETTINGS_MAIN_WINDOW_H
