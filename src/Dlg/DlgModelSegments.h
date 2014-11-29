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

  /// Get method for fill corners.
  bool fillCorners () const;

  /// Set method for fill corners.
  void setFillCorners (bool fillCorners);

private:

  bool m_fillCorners;
};

#endif // DLG_MODEL_SEGMENTS_H
