#ifndef TRANSLATOR_CONTAINER_H
#define TRANSLATOR_CONTAINER_H

class QTranslator;

/// Class that stores QTranslator objects for the duration of application execution
class TranslatorContainer
{
 public:
  /// Single constructor
  TranslatorContainer();

 private:

  // Translator for generic strings, like buttons in QWizard pages (which are inaccessible through *.tm files
  QTranslator *m_translatorGeneric;

  // Translator for Engauge-specific strings, which are accessible through *.tm files
  QTranslator *m_translatorEngauge;
};

#endif // TRANSLATOR_CONTAINER_H
