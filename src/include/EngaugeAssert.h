#ifndef ENGAUGE_ASSERT_H
#define ENGAUGE_ASSERT_H

#include "LoggerUpload.h"

#define ENGAUGE_ASSERT(condition) LoggerUpload::assert(condition,__FILE__,__LINE__);

#endif // ENGAUGE_ASSERT_H
