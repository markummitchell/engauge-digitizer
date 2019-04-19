/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef ENGAUGE_ASSERT_H
#define ENGAUGE_ASSERT_H

#include "LoggerUpload.h"
#include <QtGlobal>

// For the replacements below, the qt_noop part prevents 'missing return' compiler warnings at the ends of functions
inline void engauge_noop(bool) {}

/// Drop in replacement for Q_ASSERT
///#if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
///#define ENGAUGE_ASSERT(cond) engauge_noop(cond)
///#else
#define ENGAUGE_ASSERT(cond) ((!(cond)) ? LoggerUpload::loggerAssert(#cond,__FILE__,__LINE__) : engauge_noop(cond))
///#endif

/// Drop in replacement for Q_CHECK_PTR
///#if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
///#define ENGAUGE_CHECK_PTR(ptr) engauge_noop((ptr)==0)
///#else
#define ENGAUGE_CHECK_PTR(ptr) (((ptr)==nullptr) ? LoggerUpload::loggerCheckPtr(#ptr,__FILE__,__LINE__) : engauge_noop((ptr)==nullptr))
///#endif

#endif // ENGAUGE_ASSERT_H
