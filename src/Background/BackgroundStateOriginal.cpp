#include "BackgroundStateContext.h"
#include "BackgroundStateOriginal.h"
#include "Logger.h"

BackgroundStateOriginal::BackgroundStateOriginal(BackgroundStateContext &context) :
  BackgroundStateAbstractBase(context)
{
}

void BackgroundStateOriginal::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateOriginal::begin";
}

void BackgroundStateOriginal::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateOriginal::end";
}
