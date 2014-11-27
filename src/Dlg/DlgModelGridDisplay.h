#ifndef DLG_MODEL_GRID_DISPLAY_H
#define DLG_MODEL_GRID_DISPLAY_H

class CmdMediator;

/// Model for DlgSettingsGridDisplay and CmdSettingsGridDisplay.
class DlgModelGridDisplay
{
public:
  /// Default constructor.
  DlgModelGridDisplay();

  /// Initial constructor from Document.
  DlgModelGridDisplay(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DlgModelGridDisplay(const DlgModelGridDisplay &other);

  /// Assignment constructor.
  DlgModelGridDisplay &operator=(const DlgModelGridDisplay &other);

private:


};

#endif // DLG_MODEL_GRID_DISPLAY_H
