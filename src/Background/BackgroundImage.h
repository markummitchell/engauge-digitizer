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
