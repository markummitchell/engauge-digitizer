/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateLoadImage.h"
#include "LoadImageFromUrl.h"
#include "Logger.h"
#include "MainWindow.h"

CreateLoadImage::CreateLoadImage()
{
}

void CreateLoadImage::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateLoadImage::create";
  
#ifdef NETWORKING
  mw.m_loadImageFromUrl = new LoadImageFromUrl (mw);
#endif
}

