/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_MAIN_WINDOW_H
#define DLG_SETTINGS_MAIN_WINDOW_H

#include "DlgSettingsAbstractBase.h"
#include <QLocale>
#include <QString>
#include <QStringList>

class QCheckBox;
class QComboBox;
class QDoubleSpinBox;
class QGridLayout;
class QPushButton;
class QSpinBox;
class MainWindowModel;

/// Dialog for editing main window settings, which are entirely independent of all documents
class DlgSettingsMainWindow : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsMainWindow(MainWindow &mainWindow);
  virtual ~DlgSettingsMainWindow();

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator); // Not used. Use loadMainWindowModel instead

  /// Replaced load method since the main window settings are independent of document, unlike other DlgSettings* classes
  void loadMainWindowModel (CmdMediator &cmdMediator,
                            const MainWindowModel &modelMainWindow);
  virtual void setSmallDialogs (bool smallDialogs);

private slots:
  void slotDragDropExport (bool);
  void slotGuidelineColor (const QString &);
  void slotHighlightOpacity (double);
  void slotImageReplaceRenamesDocument (bool);
  void slotImportCropping (int index);
  void slotLocale (int index);
  void slotMaximumGridLines (int limit);
  void slotPdfResolution (const QString);
  void slotRecentFileClear ();
  void slotSignificantDigits (int);
  void slotSmallDialogs(bool);
  void slotTitleBarFormat(bool);
  void slotZoomControl (const QString);
  void slotZoomFactor (const QString);

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout,
                       int &row);
  QStringList gatherQmFilenames () const;
  void updateControls();

  QComboBox *m_cmbZoomFactor;
  QComboBox *m_cmbZoomControl;
  QComboBox *m_cmbLocale;
  QComboBox *m_cmbImportCropping;
  QPushButton *m_btnRecentClear;
  QCheckBox *m_chkTitleBarFormat;
  QComboBox *m_cmbPdfResolution;
  QSpinBox *m_spinMaximumGridLines;
  QDoubleSpinBox *m_spinHighlightOpacity;
  QCheckBox *m_chkSmallDialogs;
  QCheckBox *m_chkDragDropExport;
  QSpinBox *m_spinSignificantDigits;
  QCheckBox *m_chkImageReplaceRenamesDocument;
  QComboBox *m_cmbGuidelineColor;

  MainWindowModel *m_modelMainWindowBefore;
  MainWindowModel *m_modelMainWindowAfter;
};

#endif // DLG_SETTINGS_MAIN_WINDOW_H
