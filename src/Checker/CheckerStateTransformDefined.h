#ifndef CHECKER_STATE_TRANSFORM_DEFINED_H
#define CHECKER_STATE_TRANSFORM_DEFINED_H

#include "Checker.h"
#include "CheckerStateAbstractBase.h"

/// Class to show checker since transformation is defined.
class CheckerStateTransformDefined : public CheckerStateAbstractBase
{
public:
  /// Single constructor.
  CheckerStateTransformDefined(CheckerStateContext &context);

  virtual void begin();
  virtual void end();

private:
  CheckerStateTransformDefined();

  Checker *m_checker;
};

#endif // CHECKER_STATE_TRANSFORM_DEFINED_H
