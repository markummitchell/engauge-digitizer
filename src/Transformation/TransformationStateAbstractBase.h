#ifndef TRANSFORMATION_STATE_ABSTRACT_BASE_H
#define TRANSFORMATION_STATE_ABSTRACT_BASE_H

class CmdMediator;
class QColor;
class Transformation;
class TransformationStateContext;

/// Set of possible states of axes transformation.
enum TransformationState {
  TRANSFORMATION_STATE_DEFINED,
  TRANSFORMATION_STATE_UNDEFINED,
  NUM_TRANSFORMATION_STATES
};

/// Base class for all transformation states. This serves as an interface to TransformationStateContext
class TransformationStateAbstractBase
{
public:
  /// Single constructor.
  TransformationStateAbstractBase(TransformationStateContext &context);
  virtual ~TransformationStateAbstractBase();

  /// Method that is called at the exact moment a state is entered. Typically called just after end for the previous state
  virtual void begin(CmdMediator &cmdMediator,
                     const Transformation &transformation) = 0;

  /// Method that is called at the exact moment a state is exited. Typically called just before begin for the next state
  virtual void end(CmdMediator &cmdMediator,
                   const Transformation &transformation) = 0;

  /// Set new line color.
  virtual void updateLineColor (const QColor &lineColor) = 0;

protected:
  /// Reference to the TransformationStateContext that contains all the TransformationStateAbstractBase subclasses, without const.
  TransformationStateContext &context ();

private:
  TransformationStateAbstractBase();

  TransformationStateContext &m_context;
};

#endif // TRANSFORMATION_STATE_ABSTRACT_BASE_H
