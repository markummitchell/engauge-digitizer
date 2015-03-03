#ifndef COORDS_TYPE_H
#define COORDS_TYPE_H

#include <QString>

enum CoordsType {
  COORDS_TYPE_CARTESIAN,
  COORDS_TYPE_POLAR
};

extern QString coordsTypeToString (CoordsType coordsType);

#endif // COORDS_TYPE_H
