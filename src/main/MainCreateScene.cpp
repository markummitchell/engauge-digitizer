/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainCreateScene.h"
#include "MainWindow.h"
#include <QVBoxLayout>

MainCreateScene::MainCreateScene()
{
}

void MainCreateScene::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainCreateScene::create";
  
  mw.m_scene = new GraphicsScene (&mw);
  mw.m_view = new GraphicsView (mw.m_scene, mw);
  mw.m_layout->addWidget (mw.m_view);
}

