#ifndef HELP_BROWSER_H
#define HELP_BROWSER_H

#include <QTextBrowser>

class QHelpEngine;

/// Text browser with resource loading enhanced for use as help text browser 
class HelpBrowser : public QTextBrowser
{
 public:
  /// Single constructor
  HelpBrowser (QHelpEngine *engine,
               QWidget *parent = 0);

  /// Load resources
  QVariant loadResource (int type, const QUrl &url);

 private:
  HelpBrowser ();

  QHelpEngine *m_engine;
};

#endif // HELP_BROWSER_H
