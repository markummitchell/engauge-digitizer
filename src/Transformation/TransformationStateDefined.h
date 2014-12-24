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
  TransformationStateDefined(TransformationStateContext &context,
                             QGraphicsScene &scene);

  virtual void begin(CmdMediator &cmdMediator,
                     const Transformation &transformation);
  virtual void end(CmdMediator &cmdMediator,
                   const Transformation &transformation);
  virtual void updateLineColor (const QColor &lineColor);

private:
  TransformationStateDefined();

  // As a QGraphicsItem subclass, the Checker is deleted by the QGraphicsScene so it must be a pointer
  Checker *m_axesChecker;
};

#endif // TRANSFORMATION_STATE_DEFINED_H
