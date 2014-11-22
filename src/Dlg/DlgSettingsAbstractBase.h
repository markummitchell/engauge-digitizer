#ifndef DLG_SETTINGS_ABSTRACT_BASE_H
#define DLG_SETTINGS_ABSTRACT_BASE_H

#include <QDialog>

class CmdMediator;

/// Abstract base class for all Settings dialogs.
class DlgSettingsAbstractBase : public QDialog
{
public:
  /// Single constructor.
  DlgSettingsAbstractBase(const QString &title,
                          QWidget *parent);
  virtual ~DlgSettingsAbstractBase();

protected:
  /// Provide access to Document information wrapped inside CmdMediator.
  CmdMediator &cmdMediator ();

  /// Create dialog-specific panel to which base class will add Ok and Cancel buttons.
  virtual QWidget *createSubPanel () = 0;

  /// Add Ok and Cancel buttons to subpanel to get the whole dialog.
  void finishPanel (QWidget *subPanel);

  /// Load settings from Document.
  virtual void load (CmdMediator &cmdMediator) = 0;

  /// Store CmdMediator for easy access by the leaf class.
  void setCmdMediator (CmdMediator &cmdMediator);

private:
  DlgSettingsAbstractBase();

  CmdMediator *m_cmdMediator;
};

#endif // DLG_SETTINGS_ABSTRACT_BASE_H
