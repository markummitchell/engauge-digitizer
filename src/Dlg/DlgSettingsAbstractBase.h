/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_ABSTRACT_BASE_H
#define DLG_SETTINGS_ABSTRACT_BASE_H

#include <QDialog>
#include <QObject>

class CmdMediator;
class MainWindow;
class QComboBox;
class QHBoxLayout;

/// Abstract base class for all Settings dialogs.
class DlgSettingsAbstractBase : public QDialog
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsAbstractBase(const QString &title,
                          const QString &dialogName,
                          MainWindow &mainWindow);
  virtual ~DlgSettingsAbstractBase();

protected:
  /// Provide access to Document information wrapped inside CmdMediator.
  CmdMediator &cmdMediator ();

  /// Let subclass define an optional Save As Default button
  virtual void createOptionalSaveDefault (QHBoxLayout *layout) = 0;

  /// Create dialog-specific panel to which base class will add Ok and Cancel buttons.
  virtual QWidget *createSubPanel () = 0;

  /// Let leaf subclass control the Ok button. This method is separate from the subclasses' updateControls, rather than
  /// part of that method since updateControls is not aware of when it is called at startup - at which point the ok
  /// button should ALWAYS be disabled since there are not yet any changes. In other words, we call this method at startup
  /// to override the ok button state that was just set by updateControls
  ///
  /// Note - if this method is called with a constant value of true from updateControls, one of two cases applies:
  /// 1) There are no constraints to worry about (like a required text field cannot be empty)
  /// 2) There are constraints, but they are already handled by validators and/or other constraint logic
  void enableOk (bool enable);

  /// Add Ok and Cancel buttons to subpanel to get the whole dialog.
  void finishPanel (QWidget *subPanel);

  /// Process slotOk.
  virtual void handleOk () = 0;

  /// Dialog layout constant that guarantees every widget has sufficient room
  static int MINIMUM_DIALOG_WIDTH;

  /// Dialog layout constant that guarantees preview has sufficent room
  static int MINIMUM_PREVIEW_HEIGHT;

  /// Load settings from Document.
  virtual void load (CmdMediator &cmdMediator) = 0;

  /// Get method for MainWindow.
  MainWindow &mainWindow ();

  /// Const get method for MainWindow.
  const MainWindow &mainWindow () const;

  /// Add colors in color palette to combobox, without transparent entry at end.
  void populateColorComboWithoutTransparent (QComboBox &combo);

  /// Add colors in color palette to combobox, with transparent entry at end.
  void populateColorComboWithTransparent (QComboBox &combo);

  /// Store CmdMediator for easy access by the leaf class.
  void setCmdMediator (CmdMediator &cmdMediator);

  /// Override the default Ok button behavior applied in showEvent
  void setDisableOkAtStartup(bool disableOkAtStartup);

private slots:
  /// Do preparation before dialog is displayed.
  virtual void showEvent (QShowEvent *event);

  /// Hide dialog.
  void slotCancel();

  /// Save changes entered in dialog.
  void slotOk ();

private:
  DlgSettingsAbstractBase();

  void saveGeometryToSettings ();

  MainWindow &m_mainWindow;
  CmdMediator *m_cmdMediator; // Cannot be const since Document gets a command pushed if dialog is ok'ed
  QPushButton *m_btnCancel;
  QPushButton *m_btnOk;

  const QString m_dialogName;
  bool m_disableOkAtStartup;
};

#endif // DLG_SETTINGS_ABSTRACT_BASE_H
