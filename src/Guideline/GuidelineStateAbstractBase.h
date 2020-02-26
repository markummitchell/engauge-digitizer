/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_ABSTRACT_BASE_H
#define GUIDELINE_STATE_ABSTRACT_BASE_H

#include "EllipseParameters.h"
#include "GuidelineState.h"
#include <QColor>
#include <QLineF>
#include <QPointF>
#include <QRectF>
#include <QString>

class GuidelineStateContext;

/// Milliseconds before transition from Appearing state to Active state
const int APPEARING_TIMEOUT = 3000;

/// This class maintains deployed horizontal/vertical state behaviors for the Guideline class
class GuidelineStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineStateAbstractBase (GuidelineStateContext &context);
  virtual ~GuidelineStateAbstractBase();

  /// Transition into state
  virtual void begin () = 0;

  /// Convert single graph coordinate into screen point pair
  virtual QPointF convertGraphCoordinateToScreenPoint (double valueGraph) const = 0;

  /// Convert screen point pair into single graph coordinate
  virtual double convertScreenPointToGraphCoordinate (const QPointF &posScreen) const = 0;

  /// Allow/skip painting of the owner Guideline. This prevents display of selection markings on
  /// otherwise-invisible handle Guideline
  virtual bool doPaint () const = 0;

  /// Transition out of state
  virtual void end () = 0;

  /// DigitizeState change so active status may (or may not) be toggled
  virtual void handleActiveChange (bool active) = 0;

  /// User toggled Guideline visibility and/or locked mode
  virtual void handleGuidelineMode (bool visibility,
                                    bool locked) = 0;

  /// If transparent then make visible when hover starts
  virtual void handleHoverEnterEvent () = 0;

  /// If previously transparent before hover enter then make transparent again
  virtual void handleHoverLeaveEvent () = 0;

  /// At the start of dragging, convert the Guideline into an invisible handle and visible
  /// slaved deployed Guideline
  virtual void handleMousePress (const QPointF &posScene) = 0;
  
  /// At the end of dragging, clone the Guideline that owns the state machine where these states live
  virtual void handleMouseRelease (const QPointF &posScene) = 0;

  /// Handle timeout from Appearing state
  virtual void handleTimeout () = 0;
  
  /// Return ellipse representing constant range, that passes through the specified point
  virtual EllipseParameters pointToEllipse (const QPointF &posScreen) const = 0;

  /// Return line parallel to an axis line, that passes through the specified point
  virtual QLineF pointToLine (const QPointF &posScreen) const = 0;

  /// Name of state as a string for debugging only
  virtual QString stateName () const = 0;

  /// Update given Transformation in GuidelineStateContext
  virtual void updateWithLatestTransformation () = 0;

protected:

  /// Context in charge of the state classes
  GuidelineStateContext &context () const;

  /// Common mouse press handling. This is expected to be used by
  /// every derived leaf class except GUIDELINE_STATE_HANDLE (which this method creates)
  /// and GUIDELINE_STATE_DISCARDED (which is a noop)
  void handleMousePressCommon (const QPointF &posAbsolute,
                               GuidelineState stateHandle,
                               GuidelineState stateDeployed);

  /// Scene rectangle in screen coordinates (=pixels)
  QRectF sceneRect () const;

private:
  GuidelineStateAbstractBase();

  GuidelineStateContext &m_context;
};

#endif // GUIDELINE_STATE_ABSTRACT_BASE_H
