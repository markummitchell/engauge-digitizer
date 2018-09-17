/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "BackgroundStateContext.h"
#include "CreateStateContexts.h"
#include "DigitizeStateContext.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "TransformationStateContext.h"

CreateStateContexts::CreateStateContexts()
{
}

void CreateStateContexts::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateStateContexts::create";

  mw.m_backgroundStateContext = new BackgroundStateContext (mw);
  mw.m_digitizeStateContext = new DigitizeStateContext (mw,
                                                        *(mw.m_view),
                                                        mw.m_isGnuplot);
  mw.m_transformationStateContext = new TransformationStateContext (*(mw.m_scene),
                                                                    mw.m_isGnuplot);
}
