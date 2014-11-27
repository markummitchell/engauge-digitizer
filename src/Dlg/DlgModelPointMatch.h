#ifndef DLG_MODEL_POINT_MATCH_H
#define DLG_MODEL_POINT_MATCH_H

class CmdMediator;

/// Model for DlgSettingsPointMatch and CmdSettingsPointMatch.
class DlgModelPointMatch
{
public:
  /// Default constructor.
  DlgModelPointMatch();

  /// Initial constructor from Document.
  DlgModelPointMatch(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DlgModelPointMatch(const DlgModelPointMatch &other);

  /// Assignment constructor.
  DlgModelPointMatch &operator=(const DlgModelPointMatch &other);

private:


};

#endif // DLG_MODEL_POINT_MATCH_H
