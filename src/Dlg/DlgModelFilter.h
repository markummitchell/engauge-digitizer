#ifndef DLG_MODEL_FILTER_H
#define DLG_MODEL_FILTER_H

#include "Filter/FilterParameter.h"

class CmdMediator;

/// Model for DlgSettingsFilter and CmdSettingsFilter.
class DlgModelFilter
{
public:
  /// Default constructor.
  DlgModelFilter();

  /// Initial constructor from Document.
  DlgModelFilter(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DlgModelFilter(const DlgModelFilter &other);

  /// Assignment constructor.
  DlgModelFilter &operator=(const DlgModelFilter &other);

  /// Get method for filter parameter.
  FilterParameter filterParameter() const;

  /// Set method for filter parameter.
  void setFilterParameter(FilterParameter filterParameter);

private:

  FilterParameter m_filterParameter;
};

#endif // DLG_MODEL_FILTER_H
