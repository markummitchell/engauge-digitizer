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
