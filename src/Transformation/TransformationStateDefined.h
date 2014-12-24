#ifndef TRANSFORMATION_STATE_DEFINED_H
#define TRANSFORMATION_STATE_DEFINED_H

#include "Checker.h"
#include "Transformation.h"
#include "TransformationStateAbstractBase.h"

/// Class to show transformation since transformation is defined.
class TransformationStateDefined : public TransformationStateAbstractBase
{
public:
  /// Single constructor.
  TransformationStateDefined(TransformationStateContext &context);

  virtual void begin(CmdMediator &cmdMediator,
                     const Transformation &transformation);
  virtual void end(CmdMediator &cmdMediator,
                   const Transformation &transformation);

private:
  TransformationStateDefined();

  Checker m_axesChecker;
};

#endif // TRANSFORMATION_STATE_DEFINED_H
