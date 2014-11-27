#ifndef DLG_MODEL_GRID_REMOVAL_H
#define DLG_MODEL_GRID_REMOVAL_H

class CmdMediator;

/// Model for DlgSettingsGridRemoval and CmdSettingsGridRemoval.
class DlgModelGridRemoval
{
public:
  /// Default constructor.
  DlgModelGridRemoval();

  /// Initial constructor from Document.
  DlgModelGridRemoval(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DlgModelGridRemoval(const DlgModelGridRemoval &other);

  /// Assignment constructor.
  DlgModelGridRemoval &operator=(const DlgModelGridRemoval &other);

private:


};

#endif // DLG_MODEL_GRID_REMOVAL_H
