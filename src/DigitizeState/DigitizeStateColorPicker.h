#ifndef DIGITIZE_STATE_COLOR_PICKER_H
#define DIGITIZE_STATE_COLOR_PICKER_H

#include "BackgroundImage.h"
#include "DigitizeStateAbstractBase.h"

class DocumentModelFilter;
class QColor;
class QImage;
class QPointF;

/// Digitizing state for selecting a color for DigitizeStateSegment. The basic strategy is that this
/// class acts like a special case of DlgSettingsFilter. Specifically, the pixel just selected by a
/// mouse click is used to change the segment filter for the currently specified curve
class DigitizeStateColorPicker : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateColorPicker(DigitizeStateContext &context);
  virtual ~DigitizeStateColorPicker();

  virtual QString activeCurve () const;
  virtual void begin(DigitizeState previousState);
  virtual QCursor cursor () const;
  virtual void end();
  virtual void handleKeyPress (Qt::Key key);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);

private:
  DigitizeStateColorPicker();

  bool computeFilterFromPixel (const QPointF &posScreen,
                               const QString &curveName,
                               DocumentModelFilter &modelFilterAfter);
  bool findNearestNonBackgroundPixel (const QImage &image,
                                      const QPointF &posScreenPlusHalf,
                                      const QRgb &rgbBackground,
                                      QColor &pixel);
  void saveLowerValueUpperValue (DocumentModelFilter &modelFilterAfter,
                                 const QString &curveName,
                                 double lowerValue,
                                 double upperValue);

  // Save previous state and background for restoring as soon as user selects a valid point
  DigitizeState m_previousDigitizeState;
  BackgroundImage m_previousBackground;
};

#endif // DIGITIZE_STATE_COLOR_PICKER_H
