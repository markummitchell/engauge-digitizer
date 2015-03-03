#ifndef COORD_SCALE_H
#define COORD_SCALE_H

#include <QString>

enum CoordScale {
  COORD_SCALE_LINEAR,
  COORD_SCALE_LOG
};

extern QString coordScaleToString (CoordScale coordScale);

#endif // COORD_SCALE_H
