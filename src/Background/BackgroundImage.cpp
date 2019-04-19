/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "BackgroundImage.h"

QString backgroundImageToString (BackgroundImage backgroundImage)
{
  QString rtn;

  switch (backgroundImage) {
    case BACKGROUND_IMAGE_NONE:
      rtn = "None";
      break;

    case BACKGROUND_IMAGE_ORIGINAL:
      rtn = "Original";
      break;

    case BACKGROUND_IMAGE_FILTERED:
      rtn = "Filtered";
      break;
  }

  return rtn;
}
