#include "BackgroundStateContext.h"
#include "BackgroundStateCurve.h"
#include "Logger.h"

BackgroundStateCurve::BackgroundStateCurve(BackgroundStateContext &context) :
  BackgroundStateAbstractBase(context)
{
}

void BackgroundStateCurve::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::begin";
}

void BackgroundStateCurve::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::end";
}
