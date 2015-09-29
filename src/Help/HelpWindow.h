#ifndef HELP_WINDOW_H
#define HELP_WINDOW_H

#include <QDockWidget>

/// Dockable help window
class HelpWindow : public QDockWidget
{
 public:
  /// Single constructor
  HelpWindow (QWidget *parent);

 private:
  HelpWindow ();

  QString helpPath() const;

};

#endif // HELP_WINDOW_H
