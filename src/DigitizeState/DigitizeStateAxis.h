#ifndef DIGITIZE_STATE_AXIS_H
#define DIGITIZE_STATE_AXIS_H

#include "DigitizeStateAbstractBase.h"

class QTimer;

/// Digitizing state for digitizing one axis point at a time. Once three axis
/// points are defined,
/// those points define an affine transformation from pixel screen coordinates
/// to graph coordinates.
class DigitizeStateAxis : public DigitizeStateAbstractBase {
public:
  /// Single constructor.
  DigitizeStateAxis(DigitizeStateContext &context);
  virtual ~DigitizeStateAxis();

  virtual QString activeCurve() const;
  virtual void begin(CmdMediator *cmdMediator, DigitizeState previousState);
  virtual QCursor cursor(CmdMediator *cmdMediator) const;
  virtual void end();
  virtual void handleCurveChange(CmdMediator *cmdMediator);
  virtual void handleKeyPress(CmdMediator *cmdMediator, Qt::Key key,
                              bool atLeastOneSelectedItem);
  virtual void handleMouseMove(CmdMediator *cmdMediator, QPointF posScreen);
  virtual void handleMousePress(CmdMediator *cmdMediator, QPointF posScreen);
  virtual void handleMouseRelease(CmdMediator *cmdMediator, QPointF posScreen);
  virtual QString state() const;
  virtual void updateModelDigitizeCurve(
      CmdMediator *cmdMediator,
      const DocumentModelDigitizeCurve &modelDigitizeCurve);
  virtual void updateModelSegments(const DocumentModelSegments &modelSegments);

private:
  DigitizeStateAxis();

  void createTemporaryPoint(CmdMediator *cmdMediator, const QPointF &posScreen);
};

#endif // DIGITIZE_STATE_AXIS_H
