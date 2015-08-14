#include "FormatConstants.h"

/// Default precision for QString::number. Precision is important for cases like
/// where latitude and longitude range have precisions of 0.00# degree per pixel, as
/// compared to total values of ###.#### and ##.#### respectively
const int DEFAULT_PRECISION = 9;
