#include "EngaugeAssert.h"
#include "MainWindow.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include "TutorialDlg.h"
#include "TutorialStateContext.h"

const int SCENE_WIDTH = 500;
const int SCENE_HEIGHT = 420;

TutorialDlg::TutorialDlg (MainWindow *mainWindow) :
    QDialog (mainWindow)
{
  // Dialog size is determined by scene size
  QVBoxLayout *layout = new QVBoxLayout;
  layout->setSizeConstraint (QLayout::SetFixedSize);
  setLayout (layout);

  createScene();
  createContext();
}

void TutorialDlg::createContext ()
{
  m_context = new TutorialStateContext(*this);
}

void TutorialDlg::createScene ()
{
  m_scene = new QGraphicsScene (this);

  m_view = new QGraphicsView (m_scene, this);
  layout ()->addWidget(m_view);

  // Spacer is used to ensure view is the desired size. Directly setting the size of the view
  // is ineffective since the view then get resized to the smallest rectangle fitting the added items
  QGraphicsRectItem *spacer = new QGraphicsRectItem (0,
                                                     0,
                                                     SCENE_WIDTH,
                                                     SCENE_HEIGHT);
  spacer->setBrush (QBrush (Qt::NoBrush));
  spacer->setPen (QPen (Qt::NoPen));
  spacer->setZValue(-1); // Put behind everything else at the default z of zero
  m_scene->addItem (spacer);
}

QGraphicsScene &TutorialDlg::scene ()
{
  ENGAUGE_CHECK_PTR (m_scene);

  return *m_scene;
}

QGraphicsView &TutorialDlg::view ()
{
  ENGAUGE_CHECK_PTR (m_view);

  return *m_view;
}
