#ifndef TUTORIAL_DLG_H
#define TUTORIAL_DLG_H

#include <QDialog>

class MainWindow;
class QGraphicsScene;
class QGraphicsView;
class TutorialStateContext;

/// Tutorial using a strategy like a comic strip with decision points deciding which panels appear.
/// This is implemented as a QGraphicsScene with states in charge of managing the contents of the scene
class TutorialDlg : public QDialog
{
 public:
  /// Single constructor
  TutorialDlg (MainWindow *mainWindow);

  /// Make geometry available for layout
  QSize backgroundSize () const;

  /// Single scene the covers the entire tutorial dialog
  QGraphicsScene &scene();

  /// Single view that displays the single scene
  QGraphicsView &view();

 private:
  TutorialDlg ();

  void createContext ();
  void createSceneAndView();

  TutorialStateContext *m_context;
  QGraphicsScene *m_scene;
  QGraphicsView *m_view;
};

#endif // TUTORIAL_DLG_H
