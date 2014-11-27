#ifndef DLG_MODEL_SEGMENTS_H
#define DLG_MODEL_SEGMENTS_H

class CmdMediator;

/// Model for DlgSettingsSegments and CmdSettingsSegments.
class DlgModelSegments
{
public:
  /// Default constructor.
  DlgModelSegments();

  /// Initial constructor from Document.
  DlgModelSegments(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DlgModelSegments(const DlgModelSegments &other);

  /// Assignment constructor.
  DlgModelSegments &operator=(const DlgModelSegments &other);

private:


};

#endif // DLG_MODEL_SEGMENTS_H
