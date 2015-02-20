#ifndef ENGAUGE_ASSERT_H
#define ENGAUGE_ASSERT_H

#include "LoggerUpload.h"
#include <QtGlobal>

// For the replacements below, the qt_noop part prevents 'missing return' compiler warnings at the ends of functions
inline void engauge_noop(void) {}

/// Drop in replacement for Q_ASSERT
#if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
#define ENGAUGE_ASSERT(cond) engauge_noop()
#else
#define ENGAUGE_ASSERT(cond) ((!(cond)) ? LoggerUpload::loggerAssert(#cond,__FILE__,__LINE__) : engauge_noop())
#endif

/// Drop in replacement for Q_CHECK_PTR
#if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
#define ENGAUGE_CHECK_PTR(ptr) engauge_noop()
#else
#define ENGAUGE_CHECK_PTR(ptr) (((ptr)==0) ? LoggerUpload::loggerCheckPtr(#ptr,__FILE__,__LINE__) : engauge_noop())
#endif

#endif // ENGAUGE_ASSERT_H
