/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_ABSTRACT_BASE_H
#define GUIDELINE_STATE_ABSTRACT_BASE_H

#include "GuidelineState.h"
#include <QLineF>
#include <QRectF>

class GuidelineStateContext;

/// This class maintains deployed/template horizontal/vertical state behaviors for the Guideline class
class GuidelineStateAbstractBase
{
public:
  /// Single constructor.
  GuidelineStateAbstractBase (GuidelineStateContext &context);
  virtual ~GuidelineStateAbstractBase();

  /// True/false to keep object always visible (typically for deployed/template respectively)
  virtual bool alwaysVisible () const = 0;

  /// Transition into state
  virtual void begin () = 0;

  /// Initial state of clone made from this Guideline
  virtual GuidelineState cloneState () const = 0;

  /// True/false to enable/disable hover events initially for the Guideline
  virtual bool initialHoverEventsEnable () const = 0;

  /// Use this method to distinguish template and cloned guidelines
  virtual bool isTemplate () const = 0;

  /// Transition out of state
  virtual void end () = 0;

  /// Returns the geometry of a template guideline
  virtual QLineF templateHomeLine () const = 0;

protected:

  /// Context in charge of the state classes
  GuidelineStateContext &context () const;
  
  /// Length of diagonal of scene in screen coordinates (pixels)
  double diagonal () const;

  /// Scene rectangle in screen coordinates (=pixels)
  QRectF sceneRect () const;

private:
  GuidelineStateAbstractBase();

  GuidelineStateContext &m_context;
};

#endif // GUIDELINE_STATE_ABSTRACT_BASE_H
