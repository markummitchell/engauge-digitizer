#ifndef HIGHLIGHTS_STATE_ABSTRACT_BASE_H
#define HIGHLIGHTS_STATE_ABSTRACT_BASE_H

class HighlightsStateContext;

/// Set of possible states of axes highlights.
enum HighlightsState {
  HIGHLIGHTS_STATE_TRANSFORM_DEFINED,
  HIGHLIGHTS_STATE_TRANSFORM_UNDEFINED,
  NUM_HIGHLIGHTS_STATES
};

/// Base class for all highlights states. This serves as an interface to HighlightsStateContext
class HighlightsStateAbstractBase
{
public:
  /// Single constructor.
  HighlightsStateAbstractBase(HighlightsStateContext &context);
  virtual ~HighlightsStateAbstractBase();

  /// Method that is called at the exact moment a state is entered. Typically called just after end for the previous state
  virtual void begin() = 0;

  /// Method that is called at the exact moment a state is exited. Typically called just before begin for the next state
  virtual void end() = 0;

protected:
  /// Reference to the HighlightsStateContext that contains all the HighlightsStateAbstractBase subclasses, without const.
  HighlightsStateContext &context ();

private:
  HighlightsStateAbstractBase();

  HighlightsStateContext &m_context;
};

#endif // HIGHLIGHTS_STATE_ABSTRACT_BASE_H
