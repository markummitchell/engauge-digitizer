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
