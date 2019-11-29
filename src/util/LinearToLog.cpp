/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "LinearToLog.h"
#include <qmath.h>

LinearToLog::LinearToLog()
{
}

double LinearToLog::delinearize (double valueLinear,
                                 bool isLog) const
{
    double valueLinearOrLog = valueLinear;
    if (isLog) {
        valueLinearOrLog = qExp (valueLinear);
    }

    return valueLinearOrLog;
}

double LinearToLog::linearize (double valueLogOrLinear,
                               bool isLog) const
{
    double valueLinear = valueLogOrLinear;
    if (isLog) {
        valueLinear = qLn (valueLogOrLinear);
    }

    return valueLinear;
}
