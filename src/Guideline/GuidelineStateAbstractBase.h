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

/// This class maintains deployed/template horizontal/vertical state behaviors for the Guideline class
class GuidelineStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineStateAbstractBase (GuidelineStateContext &context);
  virtual ~GuidelineStateAbstractBase();

  /// Transition into state
  virtual void begin () = 0;

  /// Allow/skip painting of the owner Guideline. This prevents display of selection markings on
  /// otherwise-invisible handle Guideline
  virtual bool doPaint () const = 0;

  /// Transition out of state
  virtual void end () = 0;

  /// DigitizeState change so active status may (or may not) be toggled
  virtual void handleActiveChange (bool active) = 0;

  /// If transparent then make visible when hover starts
  virtual void handleHoverEnterEvent () = 0;

  /// If previously transparent before hover enter then make transparent again
  virtual void handleHoverLeaveEvent () = 0;

  /// At the start of dragging, convert the template Guideline into an invisible handle and visible
  /// slaved deployed Guideline
  virtual void handleMousePress (const QPointF &posScene) = 0;
  
  /// At the end of dragging, clone the Guideline that owns the state machine where these states live
  virtual void handleMouseRelease (const QPointF &posScene) = 0;

  /// User toggled Guideline visibility
  virtual void handleVisibleChange (bool visibility) = 0;

  /// Return ellipse representing constant range, that passes through the specified point
  virtual EllipseParameters pointToEllipse (const QPointF &posScreen) const = 0;

  /// Return line parallel to an axis line, that passes through the specified point
  virtual QLineF pointToLine (const QPointF &poscreen) const = 0;

  /// State as a string for debugging only
  virtual QString state () const = 0;


  /// Update given Transformation in GuidelineStateContext
  virtual void updateWithLatestTransformation () = 0;

protected:

  /// Context in charge of the state classes
  GuidelineStateContext &context () const;

  /// Common mouse press handling. This is expected to be used by
  /// every derived leaf class except GUIDELINE_STATE_HANDLE (which this method creates)
  /// and GUIDELINE_STATE_DISCARDED (which is a noop)
  void handleMousePressCommon (const QPointF &pos,
                               GuidelineState stateDeployed,
                               GuidelineState stateReplacement);

  /// Scene rectangle in screen coordinates (=pixels)
  QRectF sceneRect () const;

private:
  GuidelineStateAbstractBase();

  GuidelineStateContext &m_context;
};

#endif // GUIDELINE_STATE_ABSTRACT_BASE_H
