#ifndef DLG_MODEL_FILTER_H
#define DLG_MODEL_FILTER_H

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

private:


};

#endif // DLG_MODEL_FILTER_H
