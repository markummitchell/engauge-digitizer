#ifndef TUTORIAL_LINES_H
#define TUTORIAL_LINES_H

#include "TutorialAbstract.h"

class MainWindow;

/// Tutorial dialog for curves with lines
class TutorialLines : public TutorialAbstract
{
 public:
  /// Single constructor
  TutorialLines (MainWindow *mainWindow);

 private:
  TutorialLines ();
};

#endif // TUTORIAL_LINES_H

