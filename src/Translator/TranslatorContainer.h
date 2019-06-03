#ifndef TRANSLATOR_CONTAINER_H
#define TRANSLATOR_CONTAINER_H

#include <QString>

class QApplication;
class QTranslator;

/// Class that stores QTranslator objects for the duration of application execution
class TranslatorContainer
{
 public:
  /// Single constructor. Argument is needed so object is not optimized away in main() in Windows
  TranslatorContainer(QApplication &app);

  /// Platform dependent directory containing qm translation files
  static QString qmDirectory ();

 private:
  TranslatorContainer();

  // Translator for generic strings, like buttons in QWizard pages (which are inaccessible through *.tm files
  QTranslator *m_translatorGeneric;

  // Translator for Engauge-specific strings, which are accessible through *.tm files
  QTranslator *m_translatorEngauge;
};

#endif // TRANSLATOR_CONTAINER_H
