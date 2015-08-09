#include "BackgroundStateContext.h"
#include "BackgroundStateNone.h"
#include "Logger.h"

BackgroundStateNone::BackgroundStateNone(BackgroundStateContext &context) :
  BackgroundStateAbstractBase(context)
{
}

void BackgroundStateNone::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::begin";
}

void BackgroundStateNone::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateNone::end";
}
