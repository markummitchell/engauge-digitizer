#ifndef DIGITIZE_STATE_EMPTY_H
#define DIGITIZE_STATE_EMPTY_H

#include "DigitizeStateAbstractBase.h"

/// Digitizing state before a Document has been created. In this state, the
/// cursor is Qt::ArrowCursor.
class DigitizeStateEmpty : public DigitizeStateAbstractBase {
public:
  /// Single constructor.
  DigitizeStateEmpty(DigitizeStateContext &context);
  virtual ~DigitizeStateEmpty();

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
  DigitizeStateEmpty();
};

#endif // DIGITIZE_STATE_EMPTY_H
