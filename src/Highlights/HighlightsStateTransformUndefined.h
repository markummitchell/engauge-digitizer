#ifndef HIGHLIGHTS_STATE_TRANSFORM_UNDEFINED_H
#define HIGHLIGHTS_STATE_TRANSFORM_UNDEFINED_H

#include "HighlightsStateAbstractBase.h"

/// Class to not show highlights since transformation is undefined.
class HighlightsStateTransformUndefined : public HighlightsStateAbstractBase
{
public:
  /// Single constructor.
  HighlightsStateTransformUndefined(HighlightsStateContext &context);

  virtual void begin();
  virtual void end();

private:
  HighlightsStateTransformUndefined();
};

#endif // HIGHLIGHTS_STATE_TRANSFORM_UNDEFINED_H
