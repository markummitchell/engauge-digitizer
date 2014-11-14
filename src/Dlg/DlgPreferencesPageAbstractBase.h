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

protected:
  CmdMediator &cmdMediator ();

private:
  DlgPreferencesPageAbstractBase();

  CmdMediator &m_cmdMediator;
};

#endif // DLG_PREFERENCES_PAGE_ABSTRACT_BASE_H
