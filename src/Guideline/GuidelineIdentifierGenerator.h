/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_IDENTIFIER_GENERATOR_H
#define GUIDELINE_IDENTIFIER_GENERATOR_H

#include <QString>

/// Generate unique Guideline identifiers
class GuidelineIdentifierGenerator
{
public:
  /// Single constructor.
  GuidelineIdentifierGenerator();

  /// Create next identifier
  static QString next ();
  
private:

  static int m_count;
};

#endif // GUIDELINE_IDENTIFIER_GENERATOR_H
