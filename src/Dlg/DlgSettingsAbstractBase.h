#ifndef DLG_SETTINGS_ABSTRACT_BASE_H
#define DLG_SETTINGS_ABSTRACT_BASE_H

#include <QDialog>

class CmdMediator;

/// Abstract base class for all Settings dialogs.
class DlgSettingsAbstractBase : public QDialog
{
public:
  /// Single constructor.
  DlgSettingsAbstractBase(CmdMediator &cmdMediator,
                              QWidget *parent);
  virtual ~DlgSettingsAbstractBase();

protected:
  /// Provide access to Document information wrapped inside CmdMediator.
  CmdMediator &cmdMediator ();

  /// Load settings from Document.
  virtual void load () = 0;

private:
  DlgSettingsAbstractBase();

  CmdMediator &m_cmdMediator;
};

#endif // DLG_SETTINGS_ABSTRACT_BASE_H
