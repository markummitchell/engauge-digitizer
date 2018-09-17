/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateIcons.h"
#include "img/bannerapp_16.xpm"
#include "img/bannerapp_32.xpm"
#include "img/bannerapp_64.xpm"
#include "img/bannerapp_128.xpm"
#include "img/bannerapp_256.xpm"
#include "Logger.h"
#include "MainWindow.h"

CreateIcons::CreateIcons()
{
}

void CreateIcons::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateIcons::create";

  QIcon icon;
  QPixmap icon16 (bannerapp_16);
  QPixmap icon32 (bannerapp_32);
  QPixmap icon64 (bannerapp_64);
  QPixmap icon128 (bannerapp_128);
  QPixmap icon256 (bannerapp_256);

  icon.addPixmap (icon16);
  icon.addPixmap (icon32);
  icon.addPixmap (icon64);
  icon.addPixmap (icon128);
  icon.addPixmap (icon256);

  mw.setWindowIcon (icon);
}
