/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef BACKGROUND_IMAGE_H
#define BACKGROUND_IMAGE_H

#include <QString>

/// Background selection.
enum BackgroundImage {
  BACKGROUND_IMAGE_NONE,
  BACKGROUND_IMAGE_ORIGINAL,
  BACKGROUND_IMAGE_FILTERED
};

extern QString backgroundImageToString (BackgroundImage backgroundImage);

#endif // BACKGROUND_IMAGE_H
