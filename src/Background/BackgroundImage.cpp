#include "BackgroundImage.h"

QString backgroundImageToString (BackgroundImage backgroundImage)
{
  switch (backgroundImage) {
    case BACKGROUND_IMAGE_NONE:
      return "None";
      break;

    case BACKGROUND_IMAGE_ORIGINAL:
      return "Original";
      break;

    case BACKGROUND_IMAGE_FILTERED:
      return "Filtered";
      break;

    default:
      return "Unknown";
  }
}
