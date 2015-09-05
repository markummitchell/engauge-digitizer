#ifndef TUTORIAL_ABSTRACT_H
#define TUTORIAL_ABSTRACT_H

#include <QDialog>

class MainWindow;

/// Base class for tutorial windows
class TutorialAbstract : public QDialog
{
 public:
  /// Single constructor
  TutorialAbstract (MainWindow *mainWindow);

};

#endif // TUTORIAL_ABSTRACT_H
