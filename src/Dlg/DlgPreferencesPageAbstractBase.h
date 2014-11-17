#ifndef DLG_PREFERENCES_PAGE_ABSTRACT_BASE_H
#define DLG_PREFERENCES_PAGE_ABSTRACT_BASE_H

#include <QWidget>

class CmdMediator;

/// Abstract base class for all Preferences pages.
class DlgPreferencesPageAbstractBase : public QWidget
{
public:
  /// Single constructor.
  DlgPreferencesPageAbstractBase(CmdMediator &cmdMediator,
                                 QWidget *parent);
  virtual ~DlgPreferencesPageAbstractBase();

  /// Load the pages with the up-to-date information. This is called just before the preferences dialog appears
  virtual void load () = 0;

protected:
  /// Provide access to Document information wrapped inside CmdMediator.
  CmdMediator &cmdMediator ();

private:
  DlgPreferencesPageAbstractBase();

  CmdMediator &m_cmdMediator;
};

#endif // DLG_PREFERENCES_PAGE_ABSTRACT_BASE_H
