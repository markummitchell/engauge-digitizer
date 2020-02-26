/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_FORMAT_H
#define GUIDELINE_FORMAT_H

#include "ColorPalette.h"
#include <QColor>

/// This class centralizes the formatting information (color, line width, alpha) for the Guidelines
class GuidelineFormat
{
public:
  /// Single constructor.
  GuidelineFormat(ColorPalette color);
  ~GuidelineFormat();

  /// Public enum
  enum HoverOption {
    HOVER_OFF,
    HOVER_ON
  };

  /// Guideline color when hovering
  QColor colorDeployedHover () const;

  /// Guideline color when not hovering
  QColor colorDeployedNonHover () const;

  /// Color when object is transparent but still handling (probably hover) events
  QColor colorHidden () const;

  /// Guideline line width
  double lineWidthHover () const;

  /// Guideline line width for narrow lines
  double lineWidthNonHover () const;
  
private:
  GuidelineFormat();

  QColor m_color;
};

#endif // GUIDELINE_FORMAT_H
