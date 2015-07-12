#include "CallbackNextOrdinal.h"
#include "Logger.h"
#include "Point.h"

CallbackNextOrdinal::CallbackNextOrdinal(const QString &curveName) :
  m_curveName (curveName),
  m_maxOrdinalUsed (0)
{
}

CallbackSearchReturn CallbackNextOrdinal::callback (const QString &curveName,
                                                    const Point &point)
{
  if (curveName == m_curveName) {
    if (point.ordinal() > m_maxOrdinalUsed) {
      m_maxOrdinalUsed = point.ordinal();
    }
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

double CallbackNextOrdinal::nextOrdinal () const
{
  int nextOrdinal = m_maxOrdinalUsed + 1;

  LOG4CPP_INFO_S ((*mainCat)) << "CallbackNextOrdinal::nextOrdinal"
                              << " ordinal=" << nextOrdinal;

  return nextOrdinal;
}
