#ifndef TRANSFORMATION_STATE_UNDEFINED_H
#define TRANSFORMATION_STATE_UNDEFINED_H

#include "TransformationStateAbstractBase.h"

/// Class to not show transformation since transformation is undefined.
class TransformationStateUndefined : public TransformationStateAbstractBase
{
public:
  /// Single constructor.
  TransformationStateUndefined(TransformationStateContext &context,
                               QGraphicsScene &scene);

  virtual void begin(CmdMediator &cmdMediator,
                     const Transformation &transformation);
  virtual void end(CmdMediator &cmdMediator,
                   const Transformation &transformation);
  virtual void updateModelAxesChecker (const DocumentModelAxesChecker &modelAxesChecker);

private:
  TransformationStateUndefined();
};

#endif // TRANSFORMATION_STATE_UNDEFINED_H
