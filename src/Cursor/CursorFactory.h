/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CURSOR_FACTORY_H
#define CURSOR_FACTORY_H

#include <QCursor>

class DocumentModelDigitizeCurve;

/// Create standard cross cursor, or custom cursor, according to settings
class CursorFactory
{
public:
  /// Single constructor
  CursorFactory();

  /// Factory method to generate standard or custom cursor
  QCursor generate (const DocumentModelDigitizeCurve &modelDigitizeCurve) const;
};

#endif // CURSOR_FACTORY_H
