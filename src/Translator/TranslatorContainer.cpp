#include <QApplication>
#include <QLibraryInfo>
#include <QSettings>
#include <QTranslator>
#include "Settings.h"
#include "TranslatorContainer.h"

TranslatorContainer::TranslatorContainer(QApplication &app)
{
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup(SETTINGS_GROUP_MAIN_WINDOW);

  // Get the locale settings outside of the settings retrieval methods in MainWindow
  QLocale localeDefault;
  QLocale::Language language = (QLocale::Language) settings.value (SETTINGS_LOCALE_LANGUAGE,
                                                                   QVariant (localeDefault.language())).toInt();
  QLocale::Country country = (QLocale::Country) settings.value (SETTINGS_LOCALE_COUNTRY,
                                                                QVariant (localeDefault.country())).toInt();
  QLocale locale (language,
                  country);

  settings.endGroup();

  // Basic translators, like buttons in QWizard
  m_translatorGeneric = new QTranslator;
  m_translatorGeneric->load ("qt_" + locale.name().toLower(),
                             QLibraryInfo::location (QLibraryInfo::TranslationsPath));
  app.installTranslator (m_translatorGeneric);

  // Engauge-specific translators. As documented in engauge.pro, the country-specific engauge_XX_YY locale is loaded
  // if available, otherwise engauge_XX is loaded if available
  QString delimiters ("._");
  m_translatorEngauge = new QTranslator;
  m_translatorEngauge->load ("engauge_" + locale.name().toLower(),
                             QCoreApplication::applicationDirPath () + "/translations",
                             delimiters);
  app.installTranslator (m_translatorEngauge);
}
