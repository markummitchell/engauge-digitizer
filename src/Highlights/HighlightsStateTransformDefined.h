#ifndef HIGHLIGHTS_STATE_TRANSFORM_DEFINED_H
#define HIGHLIGHTS_STATE_TRANSFORM_DEFINED_H

#include "HighlightsPoint.h"
#include "HighlightsStateAbstractBase.h"

/// Class to show highlights since transformation is defined.
class HighlightsStateTransformDefined : public HighlightsStateAbstractBase
{
public:
  /// Single constructor.
  HighlightsStateTransformDefined(HighlightsStateContext &context);

  virtual void begin();
  virtual void end();

private:
  HighlightsStateTransformDefined();

  HighlightsPoint *m_highlightsPoint0;
  HighlightsPoint *m_highlightsPoint1;
  HighlightsPoint *m_highlightsPoint2;
};

#endif // HIGHLIGHTS_STATE_TRANSFORM_DEFINED_H
