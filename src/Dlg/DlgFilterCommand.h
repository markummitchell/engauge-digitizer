/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_FILTER_COMMAND_H
#define DLG_FILTER_COMMAND_H

#include "ColorFilterMode.h"

/// Command pattern object for receiving new parameters in DlgFilterWorker from GUI thread.
class DlgFilterCommand
{
public:
  /// Initial constructor.
  DlgFilterCommand(ColorFilterMode colorFilterMode,
                   double low0To1,
                   double high0To1);

  /// Copy constructor.
  DlgFilterCommand(const DlgFilterCommand &other);

  /// Assignment operator.
  DlgFilterCommand &operator=(const DlgFilterCommand &other);

  /// Get method for filter mode.
  ColorFilterMode colorFilterMode() const;

  /// Get method for high value.
  double high0To1 () const;

  /// Get method for low value.
  double low0To1 () const;

private:
  DlgFilterCommand();

  ColorFilterMode m_colorFilterMode;
  double m_low0To1;
  double m_high0To1;
};

#endif // DLG_FILTER_COMMAND_H
