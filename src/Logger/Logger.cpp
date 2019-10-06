/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include "Logger.h"
#include <log4cpp/RollingFileAppender.hh>
#include <QString>

log4cpp::Category *mainCat;

const QString INDENTATION_PAST_TIMESTAMP ("             ");
const QString INDENTATION_DELTA ("  ");

using namespace log4cpp;

void initializeLogging (const QString &name,
                        const QString &filename,
                        bool isDebug)
{
  LayoutAppender *appender = nullptr;

  const size_t MAX_FILE_SIZE_BYTES = 6 * 1024 * 1024; // Size that should satisfy most email servers
  const unsigned int MAX_BACKUP_INDEX = 2;
  const bool APPEND_TO_PREVIOUS_FILE = false;

  // Log to file for development
  appender = dynamic_cast<LayoutAppender*> (new RollingFileAppender (name.toStdString (),
                                                                     filename.toStdString (),
                                                                     MAX_FILE_SIZE_BYTES,
                                                                     MAX_BACKUP_INDEX,
                                                                     APPEND_TO_PREVIOUS_FILE));
                                           
  PatternLayout *layout = new PatternLayout ();
  // With date:    %d{%H:%M:%S.%l} %-5p %c - %m%n
  // Without date:                 %-5p %c - %m%n
  layout->setConversionPattern ("%-5p %c - %m%n");
  appender->setLayout (layout);

  mainCat = &Category::getRoot ();

  // Levels are EMERG, FATAL, ALERT, CRIT, ERROR, WARN, NOTICE, INFO, DEBUG.
  //
  // Most trace logging is at INFO level, but methods that are called extremely often (like mouse
  // moves and status bar updates) are at the lower DEBUG level so they are rarely seen
  if (isDebug) {
    mainCat->setPriority (Priority::DEBUG);
  } else {
    mainCat->setPriority (Priority::INFO);
  }

  mainCat->addAppender (appender);
}
