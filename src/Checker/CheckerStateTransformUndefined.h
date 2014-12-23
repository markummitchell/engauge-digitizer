#ifndef CHECKER_STATE_TRANSFORM_UNDEFINED_H
#define CHECKER_STATE_TRANSFORM_UNDEFINED_H

#include "CheckerStateAbstractBase.h"

/// Class to not show checker since transformation is undefined.
class CheckerStateTransformUndefined : public CheckerStateAbstractBase
{
public:
  /// Single constructor.
  CheckerStateTransformUndefined(CheckerStateContext &context);

  virtual void begin();
  virtual void end();

private:
  CheckerStateTransformUndefined();
};

#endif // CHECKER_STATE_TRANSFORM_UNDEFINED_H
