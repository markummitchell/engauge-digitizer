#ifndef DLG_FILTER_COMMAND_H
#define DLG_FILTER_COMMAND_H

#include "FilterMode.h"

/// Command pattern object for receiving new parameters in DlgFilterWorker from GUI thread.
class DlgFilterCommand
{
public:
  /// Initial constructor.
  DlgFilterCommand(FilterMode filterMode,
                   double low0To1,
                   double high0To1);

  /// Copy constructor.
  DlgFilterCommand(const DlgFilterCommand &other);

  /// Assignment operator.
  DlgFilterCommand &operator=(const DlgFilterCommand &other);

  /// Get method for filter mode.
  FilterMode filterMode() const;

  /// Get method for high value.
  double high0To1 () const;

  /// Get method for low value.
  double low0To1 () const;

private:
  DlgFilterCommand();

  FilterMode m_filterMode;
  double m_low0To1;
  double m_high0To1;
};

#endif // DLG_FILTER_COMMAND_H
