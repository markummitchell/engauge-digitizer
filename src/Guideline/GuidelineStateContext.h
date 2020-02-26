/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_CONTEXT_H
#define GUIDELINE_STATE_CONTEXT_H

#include "ColorPalette.h"
#include "EllipseParameters.h"
#include "GuidelineState.h"
#include "GuidelineStateAbstractBase.h"
#include <QLineF>
#include <QObject>
#include <QPointF>
#include <QString>
#include <QVector>

class GuidelineAbstract;
class Guidelines;
class Transformation;

/// Context class for state machine that belongs to the Guideline class. The GuidelineAbstract
/// class owns an instance of this class. The base class for all guideline states is
/// GuidelineStateAbstractBase.
///
/// While dragging, the Guideline appears to follow a constant-coordinate isocontour during the dragging. The
/// isocontour is along X or Y for cartesian coordinates, or T or R for polar coordinates.
/// This effect is achieved using three GuidelineAbstract instances:
/// - The <b>dragged Guideline</b> that is initially visible and clicked on by the user. It immediately becomes
///   invisible since it cannot be redrawn while being dragged (a constraint of the Qt framework). The
///   state of this Guideline is Handle.
/// - The <b>visible Guideline</b> that is created as soon as the dragged Guideline is made invisible. The
///   visible Guideline is moved along with the cursor during the dragging. It starts out looking just
///   like the dragged Guideline, but changes to follow the relevant isocontours during the dragging.
///   The user will think he/she is dragging the visible Guideline directly, but this is an illusion.
///   The state of this Guideline is Deployed.
/// - The <b>replacement Guideline</b> that replaces both the dragged and visible Guideline instances when the 
///   mouse is released. This Guideline is off the stack when the mouse is released and therefore can be the
///   target of a new CmdGuidelineMoveXT or CmdGuidelineMoveYR which wants to move something as soons as its
///   redo method is called. The state of this Guideline is Deployed.
///
/// The state machine graph for dragging a Guideline is below:
/// 
/// \dot
/// digraph guidelines {
///   rankdir = LR;
///
///   Start -> DeployedConstantRAppearing [label = BtnGuidelineR];
///   DeployedConstantRAppearing -> DeployedConstantRActive [label = Timeout];
///
///   Start -> DeployedConstantTAppearing [label = BtnGuidelineT];
///   DeployedConstantTAppearing -> DeployedConstantTActive [label = Timeout];
///
///   Start -> DeployedConstantXAppearing [label = BtnGuidelineX];
///   DeployedConstantXAppearing -> DeployedConstantXActive [label = Timeout];
///
///   Start -> DeployedConstantYAppearing [label = BtnGuidelineY];
///   DeployedConstantYAppearing -> DeployedConstantYActive [label = Timeout];
///
///   DeployedConstantRHover -> DeployedConstantRActive [label = HoverLeave];
///   DeployedConstantRHover -> HandleR [label = MouseClick];
///   DeployedConstantRActive -> Discarded [label = DragOffscreen];
///   DeployedConstantRActive -> Discarded [label = TransformLoss];
///   DeployedConstantRActive -> DeployedConstantRHide [label = TurnedOff];
///   DeployedConstantRHide -> DeployedConstantRActive [label = TurnedOn];
///   DeployedConstantRActive -> DeployedConstantRHover [label = HoverEnter];
///   DeployedConstantRActive -> DeployedConstantRLocked [label = LeaveSelectMode];
///   DeployedConstantRLocked -> DeployedConstantRActive [label = EnterSelectMode];
///
///   DeployedConstantTHover -> DeployedConstantTActive [label = HoverLeave];
///   DeployedConstantTHover -> HandleT [label = MouseClick];
///   DeployedConstantTActive -> Discarded [label = DragOffscreen];
///   DeployedConstantTActive -> Discarded [label = TransformLoss];
///   DeployedConstantTActive -> DeployedConstantTHide [label = TurnedOff];
///   DeployedConstantTHide -> DeployedConstantTActive [label = TurnedOn];
///   DeployedConstantTActive -> DeployedConstantTHover [label = HoverEnter];
///   DeployedConstantTActive -> DeployedConstantTLocked [label = LeaveSelectMode];
///   DeployedConstantTLocked -> DeployedConstantTActive [label = EnterSelectMode];
///
///   DeployedConstantXHover -> DeployedConstantXActive [label = HoverLeave];
///   DeployedConstantXHover -> HandleX [label = MouseClick];
///   DeployedConstantXActive -> Discarded [label = DragOffscreen];
///   DeployedConstantXActive -> Discarded [label = TransformLoss];
///   DeployedConstantXActive -> DeployedConstantXHide [label = TurnedOff];
///   DeployedConstantXHide -> DeployedConstantXActive [label = TurnedOn];
///   DeployedConstantXActive -> DeployedConstantXHover [label = HoverEnter];
///   DeployedConstantXActive -> DeployedConstantXLocked [label = LeaveSelectMode];
///   DeployedConstantXLocked -> DeployedConstantXActive [label = EnterSelectMode];
///
///   DeployedConstantYHover -> DeployedConstantYActive [label = HoverLeave];
///   DeployedConstantYHover -> HandleY [label = MouseClick];
///   DeployedConstantYActive -> Discarded [label = DragOffscreen];
///   DeployedConstantYActive -> Discarded [label = TransformLoss];
///   DeployedConstantYActive -> DeployedConstantYHide [label = TurnedOff];
///   DeployedConstantYHide -> DeployedConstantYActive [label = TurnedOn];
///   DeployedConstantYActive -> DeployedConstantYHover [label = HoverEnter];
///   DeployedConstantYActive -> DeployedConstantYLocked [label = LeaveSelectMode];
///   DeployedConstantYLocked -> DeployedConstantYActive [label = EnterSelectMode];
///
///   HandleR -> Discarded [label = MouseRelease];
///   HandleT -> Discarded [label = MouseRelease];
///   HandleX -> Discarded [label = MouseRelease];
///   HandleY -> Discarded [label = MouseRelease];
///
/// }
/// \enddot
///
/// This class derives from QObject so it can receive timeouts from the Appearing state,
/// and then perform a state transition after each timeout. If the states received those
/// timeouts then they would not be able to (singlehandedly) take themselves off the stack
class GuidelineStateContext : public QObject
{
  Q_OBJECT;

public:
  /// Single constructor.
  GuidelineStateContext (GuidelineAbstract &guideline,
                         Guidelines &guidelines,
                         GuidelineState guidelineStateInitial);
  virtual ~GuidelineStateContext();

  /// True/false if coordinates are cartesian/polar
  bool cartesian() const;

  /// Color to be used for guidelines
  ColorPalette color () const;

  /// Convert single graph coordinate into screen point pair
  QPointF convertGraphCoordinateToScreenPoint (double valueGraph) const;

  /// Convert screen point pair into single graph coordinate
  double convertScreenPointToGraphCoordinate (const QPointF &posScreen) const;

  /// Factory method for creating a new Guideline
  GuidelineAbstract *createGuideline (const QString &identifier,
                                      GuidelineState stateInitial) const;

  /// Allow/skip painting of the owner Guideline. This prevents display of selection markings on
  /// otherwise-invisible handle Guideline
  bool doPaint () const;

  /// Guideline has been dragged off screen so remove it
  void draggedOffScreen ();

  /// Guideline that owns this context class
  GuidelineAbstract &guideline ();

  /// DigitizeState change so active status may (or may not) be toggled
  void handleActiveChange (bool active);

  /// User toggled Guideline visibility and/or locked mode
  void handleGuidelineMode (bool visibile,
                            bool locked);

  /// If transparent then make visible when hover starts
  void handleHoverEnterEvent ();

  /// If previously transparent before hover enter then make transparent again
  void handleHoverLeaveEvent ();

  /// At the start of dragging, convert the original Guideline into an invisible handle and
  /// visible slaved deployed Guideline
  void handleMousePress (const QPointF &posScene);
  
  /// At the end of dragging, clone the Guideline that owns the state machine where these states live
  void handleMouseRelease (const QPointF &posScene);

  /// Return ellipse representing constant range, that passes through the specified point
  EllipseParameters pointToEllipse (const QPointF &posScreen) const;

  /// Return line parallel to an axis line, that passes through the specified point
  QLineF pointToLine (const QPointF &posScreen) const;

  /// Get method for current cursor coordinate when object was last created/dragged
  QPointF posCursorGraph () const;

  /// Request a state transition
  void requestStateTransition (GuidelineState guidelineState);

  /// Pass the current cursor coordinate to the state so it can save the relevant coordinate for
  /// later adjustement when the transformation changes
  void setPosCursorGraph (const QPointF &posGraph);

  /// Dump state for debugging only
  QString stateDump () const;

  /// State as a string for debugging only
  QString stateName () const;

  /// Return copy of transformation owned by MainWindow
  Transformation transformation () const;

  /// Update given Transformation in GuidelineStateContext
  void updateWithLatestTransformation ();

public slots:
  void slotTimeout ();

private:
  GuidelineStateContext();

  /// Transition if requested
  void transitionIfRequested ();
  
  GuidelineAbstract &m_guideline;
  Guidelines &m_guidelines;

  QVector<GuidelineStateAbstractBase*> m_states;
  GuidelineState m_currentState;
  GuidelineState m_nextState;

  QPointF m_posCursorGraph;
};

#endif // GUIDELINE_STATE_CONTEXT_H
