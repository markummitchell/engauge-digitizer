#include <QApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QSettings>
#include <QTranslator>
#include "Settings.h"
#include "TranslatorContainer.h"

TranslatorContainer::TranslatorContainer(QApplication & /* app */)
{
  QLocale localeDefault;

  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup(SETTINGS_GROUP_MAIN_WINDOW);

  // Get the locale settings outside of the settings retrieval methods in MainWindow
  QLocale::Language language = static_cast<QLocale::Language> (settings.value (SETTINGS_LOCALE_LANGUAGE,
                                                                               QVariant (localeDefault.language())).toInt());
  QLocale::Country country = static_cast<QLocale::Country> (settings.value (SETTINGS_LOCALE_COUNTRY,
                                                                            QVariant (localeDefault.country())).toInt());
  QLocale locale (language,
                  country);
  
  settings.endGroup();

  // For some reason, some built-in strings get translated into German by the first call to installTranslator,
  // when the locale is english. So we skip translation for unless user has either
  // 1) default language is not english
  // 2) default language and selected language are not the same
  if ((localeDefault.name().toLower() != "en_us") ||
      (localeDefault.name().toLower() != locale.name().toLower())) {

    QString localeName = locale.name().toLower();

    // Basic translators, like buttons in QWizard
    m_translatorGeneric = new QTranslator;
    m_translatorGeneric->load ("qt_" + localeName,
                                QLibraryInfo::location (QLibraryInfo::TranslationsPath));
    QApplication::installTranslator (m_translatorGeneric);

    // Engauge-specific translators. As documented in engauge.pro, the country-specific engauge_XX_YY locale is loaded
    // if available, otherwise engauge_XX is loaded if available
    //
    // In OSX, QDir::currentPath points to /Users/?/Library/Containers/Digitizer/Data and
    // QCoreApplication::applicationDirPath points to ../Engauge Digitizer.app/Contents/MacOS (which we want)
    QString delimiters ("._");
    m_translatorEngauge = new QTranslator;
    // Handle usual translations like es_es
    bool rtn = m_translatorEngauge->load ("engauge_" + localeName,
                                           qmDirectory(),
                                           delimiters);
    if (!rtn) {
      // Handle country-specific translations like fa_IR. Transifex capitalizes the last two characters
      QString localeNameUpper = QString ("%1%2")
          .arg (localeName.left (localeName.length() - 2))
          .arg (localeName.right (2).toUpper ());
      m_translatorEngauge->load ("engauge_" + localeNameUpper,
                                 qmDirectory(),
                                 delimiters);
    }
    QApplication::installTranslator (m_translatorEngauge);
  }
}

QString TranslatorContainer::qmDirectory()
{
#if defined(OSX_DEBUG) || defined(OSX_RELEASE)
    return QCoreApplication::applicationDirPath () + "/../Resources/translations";
#else
    return QCoreApplication::applicationDirPath () + "/translations";
#endif
}
