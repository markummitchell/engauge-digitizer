/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include "TutorialDlg.h"
#include "TutorialStateContext.h"

const int SCENE_WIDTH = 580;
const int SCENE_HEIGHT = 480;

TutorialDlg::TutorialDlg (MainWindow *mainWindow) :
  QDialog (mainWindow),
  m_context (nullptr),
  m_scene (nullptr),
  m_view (nullptr)
{
  setWindowTitle ("Engauge Digitizer Tutorial");

  // Dialog size is determined by scene size
  QVBoxLayout *layout = new QVBoxLayout;
  layout->setSizeConstraint (QLayout::SetMinimumSize);
  setLayout (layout);

  createSceneAndView();
  createContext();
}

TutorialDlg::~TutorialDlg ()
{
  delete m_view;
  delete m_scene;
  delete m_context;
}

QSize TutorialDlg::backgroundSize () const
{
  return QSize (SCENE_WIDTH,
                SCENE_HEIGHT);
}
void TutorialDlg::createContext ()
{
  m_context = new TutorialStateContext(*this);
}

void TutorialDlg::createSceneAndView ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialDlg::createSceneAndView";

  m_scene = new QGraphicsScene (this);

  m_view = new QGraphicsView (m_scene, this);
  m_view->setMouseTracking (true);
  layout ()->addWidget(m_view);

  // Spacer is used to ensure view is the desired size. Directly setting the size of the view
  // is ineffective since the view then get resized to the smallest rectangle fitting the added items
  QGraphicsRectItem *spacer = new QGraphicsRectItem (0,
                                                     0,
                                                     backgroundSize().width (),
                                                     backgroundSize().height ());
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
