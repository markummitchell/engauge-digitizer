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
                     const Transformation &transformation,
                     const QString &selectedGraphCurve);
  virtual void end(CmdMediator &cmdMediator,
                   const Transformation &transformation);
  virtual void updateAxesChecker (CmdMediator &cmdMediator,
                                  const Transformation &transformation);

private:
  TransformationStateUndefined();
};

#endif // TRANSFORMATION_STATE_UNDEFINED_H
