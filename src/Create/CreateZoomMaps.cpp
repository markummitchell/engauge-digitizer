/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateZoomMaps.h"
#include "Logger.h"
#include "MainWindow.h"

CreateZoomMaps::CreateZoomMaps()
{
}

void CreateZoomMaps::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateZoomMaps::create";

  mw.m_zoomMapFromInitial [ZOOM_INITIAL_16_TO_1] = ZOOM_16_TO_1;
  mw.m_zoomMapFromInitial [ZOOM_INITIAL_8_TO_1] = ZOOM_8_TO_1;
  mw.m_zoomMapFromInitial [ZOOM_INITIAL_4_TO_1] = ZOOM_4_TO_1;
  mw.m_zoomMapFromInitial [ZOOM_INITIAL_2_TO_1] = ZOOM_2_TO_1;
  mw.m_zoomMapFromInitial [ZOOM_INITIAL_1_TO_1] = ZOOM_1_TO_1;
  mw.m_zoomMapFromInitial [ZOOM_INITIAL_1_TO_2] = ZOOM_1_TO_2;
  mw.m_zoomMapFromInitial [ZOOM_INITIAL_1_TO_4] = ZOOM_1_TO_4;
  mw.m_zoomMapFromInitial [ZOOM_INITIAL_1_TO_8] = ZOOM_1_TO_8;
  mw.m_zoomMapFromInitial [ZOOM_INITIAL_1_TO_16] = ZOOM_1_TO_16;
  mw.m_zoomMapFromInitial [ZOOM_INITIAL_FILL] = ZOOM_FILL;

  mw.m_zoomMapToAction [ZOOM_16_TO_1] = mw.m_actionZoom16To1;
  mw.m_zoomMapToAction [ZOOM_16_TO_1_FARTHER] = mw.m_actionZoom16To1Farther;
  mw.m_zoomMapToAction [ZOOM_8_TO_1_CLOSER] = mw.m_actionZoom8To1Closer;
  mw.m_zoomMapToAction [ZOOM_8_TO_1] = mw.m_actionZoom8To1;
  mw.m_zoomMapToAction [ZOOM_8_TO_1_FARTHER] = mw.m_actionZoom8To1Farther;
  mw.m_zoomMapToAction [ZOOM_4_TO_1_CLOSER] = mw.m_actionZoom4To1Closer;
  mw.m_zoomMapToAction [ZOOM_4_TO_1] = mw.m_actionZoom4To1;
  mw.m_zoomMapToAction [ZOOM_4_TO_1_FARTHER] = mw.m_actionZoom4To1Farther;
  mw.m_zoomMapToAction [ZOOM_2_TO_1_CLOSER] = mw.m_actionZoom2To1Closer;
  mw.m_zoomMapToAction [ZOOM_2_TO_1] = mw.m_actionZoom2To1;
  mw.m_zoomMapToAction [ZOOM_2_TO_1_FARTHER] = mw.m_actionZoom2To1Farther;
  mw.m_zoomMapToAction [ZOOM_1_TO_1_CLOSER] = mw.m_actionZoom1To1Closer;
  mw.m_zoomMapToAction [ZOOM_1_TO_1] = mw.m_actionZoom1To1;
  mw.m_zoomMapToAction [ZOOM_1_TO_1_FARTHER] = mw.m_actionZoom1To1Farther;
  mw.m_zoomMapToAction [ZOOM_1_TO_2_CLOSER] = mw.m_actionZoom1To2Closer;
  mw.m_zoomMapToAction [ZOOM_1_TO_2] = mw.m_actionZoom1To2;
  mw.m_zoomMapToAction [ZOOM_1_TO_2_FARTHER] = mw.m_actionZoom1To2Farther;
  mw.m_zoomMapToAction [ZOOM_1_TO_4_CLOSER] = mw.m_actionZoom1To4Closer;
  mw.m_zoomMapToAction [ZOOM_1_TO_4] = mw.m_actionZoom1To4;
  mw.m_zoomMapToAction [ZOOM_1_TO_4_FARTHER] = mw.m_actionZoom1To4Farther;
  mw.m_zoomMapToAction [ZOOM_1_TO_8_CLOSER] = mw.m_actionZoom1To8Closer;
  mw.m_zoomMapToAction [ZOOM_1_TO_8] = mw.m_actionZoom1To8;
  mw.m_zoomMapToAction [ZOOM_1_TO_8_FARTHER] = mw.m_actionZoom1To8Farther;
  mw.m_zoomMapToAction [ZOOM_1_TO_16_CLOSER] = mw.m_actionZoom1To16Closer;
  mw.m_zoomMapToAction [ZOOM_1_TO_16] = mw.m_actionZoom1To16;
  mw.m_zoomMapToAction [ZOOM_FILL] = mw.m_actionZoomFill;
}
