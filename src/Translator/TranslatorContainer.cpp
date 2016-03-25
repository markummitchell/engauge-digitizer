#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include "TranslatorContainer.h"

TranslatorContainer::TranslatorContainer()
{
  QString locale = QLocale::system().name();

  // Basic translators, like buttons in QWizard
  m_translatorGeneric = new QTranslator;
  m_translatorGeneric->load ("qt_" + locale,
                             QLibraryInfo::location (QLibraryInfo::TranslationsPath));
  qApp->installTranslator (m_translatorGeneric);

  // Engauge-specific translators
  m_translatorEngauge = new QTranslator;
  m_translatorEngauge->load ("engauge_" + locale,
                             QCoreApplication::applicationDirPath () + "/translations");
  qApp->installTranslator (m_translatorEngauge);
}
