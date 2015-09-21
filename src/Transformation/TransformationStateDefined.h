#ifndef TRANSFORMATION_STATE_DEFINED_H
#define TRANSFORMATION_STATE_DEFINED_H

#include "Checker.h"
#include <QObject>
#include "Transformation.h"
#include "TransformationStateAbstractBase.h"

class QTimer;

/// Class to show transformation since transformation is defined.
class TransformationStateDefined : public QObject, public TransformationStateAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  TransformationStateDefined(TransformationStateContext &context,
                             QGraphicsScene &scene);

  virtual void begin(CmdMediator &cmdMediator,
                     const Transformation &transformation,
                     const QString &selectedGraphCurve);
  virtual void end(CmdMediator &cmdMediator,
                   const Transformation &transformation);
  virtual void updateAxesChecker (CmdMediator &cmdMediator,
                                  const Transformation &transformation);

private slots:
  void slotTimeout();

private:
  TransformationStateDefined();

  void initializeModelGridRemoval (CmdMediator &cmdMediator,
                                   const Transformation &transformation,
                                   const QString &selectedGraphCurve);
  void startTimer (const DocumentModelAxesChecker &modelAxesChecker);

  // As a QGraphicsItem subclass, the Checker is deleted by the QGraphicsScene so it must be a pointer
  Checker *m_axesChecker;

  QTimer *m_timer;
};

#endif // TRANSFORMATION_STATE_DEFINED_H
