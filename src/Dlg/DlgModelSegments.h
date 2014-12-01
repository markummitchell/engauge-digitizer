#ifndef DLG_MODEL_SEGMENTS_H
#define DLG_MODEL_SEGMENTS_H

#include "ColorPalette.h"
#include "DocumentModelAbstractBase.h"

class CmdMediator;

/// Model for DlgSettingsSegments and CmdSettingsSegments.
class DlgModelSegments : public DocumentModelAbstractBase
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

  /// Get method for line color.
  ColorPalette lineColor() const;

  /// Get method for line size.
  double lineSize() const;

  /// Get method for min length.
  double minLength() const;

  /// Get method for point separation.
  double pointSeparation() const;

  virtual void saveModel(QXmlStreamWriter &stream) const;

  /// Set method for fill corners.
  void setFillCorners (bool fillCorners);

  /// Set method for line color.
  void setLineColor(ColorPalette lineColor);

  /// Set method for line size.
  void setLineSize (double lineSize);

  /// Set method for min length.
  void setMinLength(double minLength);

  /// Set method for point separation.
  void setPointSeparation(double pointSeparation);

private:

  double m_pointSeparation;
  double m_minLength;
  bool m_fillCorners;
  double m_lineSize;
  ColorPalette m_lineColor;
};

#endif // DLG_MODEL_SEGMENTS_H
