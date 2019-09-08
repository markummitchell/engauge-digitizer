/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_STATE_ABSTRACT_BASE_H
#define GUIDELINE_STATE_ABSTRACT_BASE_H

#include "GuidelineState.h"

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

  /// Transition out of state
  virtual void end () = 0;
  
private:
  GuidelineStateAbstractBase();

  GuidelineStateContext &m_context;
};

#endif // GUIDELINE_STATE_ABSTRACT_BASE_H
