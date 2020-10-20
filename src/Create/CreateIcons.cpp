/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateIcons.h"
#include "Logger.h"
#include "MainWindow.h"

CreateIcons::CreateIcons()
{
}

void CreateIcons::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateIcons::create";

  QIcon icon;

  // We use png files here since Qt xpm import code gives gratuitous qWarning messages,
  // but keep the original xpm files which are easy to work with. ImageMagick 'convert'
  // converts xpm to png
  QPixmap icon16 (":/engauge/img/bannerapp_16.png");
  QPixmap icon32 (":/engauge/img/bannerapp_32.png");
  QPixmap icon64 (":/engauge/img/bannerapp_64.png");
  QPixmap icon128 (":/engauge/img/bannerapp_128.png");
  QPixmap icon256 (":/engauge/img/bannerapp_256.png");

  icon.addPixmap (icon16);
  icon.addPixmap (icon32);
  icon.addPixmap (icon64);
  icon.addPixmap (icon128);
  icon.addPixmap (icon256);

  mw.setWindowIcon (icon);
}
