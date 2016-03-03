/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
