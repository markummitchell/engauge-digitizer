/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_FORMAT_H
#define GUIDELINE_FORMAT_H

#include <QColor>

/// This class centralizes the formatting information (color, line width, alpha) for the Guidelines
class GuidelineFormat
{
public:
  /// Single constructor.
  GuidelineFormat();
  ~GuidelineFormat();

  /// Public enum
  enum HoverOption {
    HOVER_OFF,
    HOVER_ON
  };

  /// Color when cursor is hovering over object
  QColor colorDeployedHover () const;
  
  /// Color when cursor is not hovering over object
  QColor colorDeployedNonHover () const;

  /// Color when object is transparent but still handling (probably hover) events
  QColor colorHidden () const;

  /// Guideline line width for non-templates Guidelines
  double lineWidthHover () const;

  /// Guideline line width of template Guideline as drawn
  double lineWidthNonHover () const;

};

#endif // GUIDELINE_FORMAT_H
