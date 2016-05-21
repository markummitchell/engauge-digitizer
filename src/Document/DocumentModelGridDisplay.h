/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_MODEL_GRID_DISPLAY
#define DOCUMENT_MODEL_GRID_DISPLAY

#include "ColorPalette.h"
#include "DocumentModelAbstractBase.h"
#include "GridCoordDisable.h"

class Document;
class QTextStream;

/// Model for DlgSettingsGridDisplay and CmdSettingsGridDisplay.
class DocumentModelGridDisplay : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelGridDisplay();

  /// Initial constructor from Document.
  DocumentModelGridDisplay(const Document &document);

  /// Copy constructor.
  DocumentModelGridDisplay(const DocumentModelGridDisplay &other);

  /// Assignment constructor.
  DocumentModelGridDisplay &operator=(const DocumentModelGridDisplay &other);

  /// Get method for x grid line count.
  unsigned int countX () const;

  /// Get method for y grid line count.
  unsigned int countY () const;

  /// Get method for x grid line disabled variable.
  GridCoordDisable disableX () const;

  /// Get method for y grid line disabled variable.
  GridCoordDisable disableY () const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Get method for color.
  ColorPalette paletteColor() const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for x grid line count.
  void setCountX (unsigned int countX);

  /// Set method for y grid line count.
  void setCountY (unsigned int countY);

  /// Set method for x grid line disabled variable.
  void setDisableX (GridCoordDisable disableX);

  /// Set method for y grid line disabled variable.
  void setDisableY (GridCoordDisable disableY);

  /// Set method for color.
  void setPaletteColor(ColorPalette paletteColor);

  /// Set method for stable flag.
  void setStable (bool stable);

  /// Set method for x grid line lower bound (inclusive).
  void setStartX (double startX);

  /// Set method for y grid line lower bound (inclusive).
  void setStartY (double yStart);

  /// Set method for x grid line increment.
  void setStepX (double stepX);

  /// Set method for y grid line increment.
  void setStepY (double yStep);

  /// Set method for x grid line upper bound (inclusive).
  void setStopX (double stopX);

  /// Set method for y grid line upper bound (inclusive).
  void setStopY (double yStop);

  /// Get method for stable flag. The flag is false to let the settings get automatically updated, until the
  /// user selects settings - at which point the stable flag is set to true
  bool stable() const;

  /// Get method for x grid line lower bound (inclusive).
  double startX () const;

  /// Get method for y grid line lower bound (inclusive).
  double startY () const;

  /// Get method for x grid line increment.
  double stepX () const;

  /// Get method for y grid line increment.
  double stepY () const;

  /// Get method for x grid line upper bound (inclusive).
  double stopX () const;

  /// Get method for y grid line upper bound (inclusive).
  double stopY () const;

private:

  bool m_stable;
  GridCoordDisable m_disableX;
  unsigned int m_countX;
  double m_startX;
  double m_stepX;
  double m_stopX;

  GridCoordDisable m_disableY;
  unsigned int m_countY;
  double m_startY;
  double m_stepY;
  double m_stopY;

  ColorPalette m_paletteColor;
};

#endif // DOCUMENT_MODEL_GRID_DISPLAY
