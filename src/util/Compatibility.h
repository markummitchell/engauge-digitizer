/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COMPATIBILITY_H
#define COMPATIBILITY_H

#include <QString>
#include <QtGlobal>

class QTextStream;

/// Centralize hacks necessary to support multiple qt versions
class Compatibility
{
 public:
  /// Single default constructor
  Compatibility ();

  /// End of line 
  static QTextStream &endl (QTextStream &stream);

  /// Flush
  static QTextStream &flush (QTextStream &stream);  

  /// SplitBehavior
#if QT_VERSION < QT_VERSION_CHECK (5, 14, 0)
  static QString::SplitBehavior SkipEmptyParts ();
#else
  static Qt::SplitBehavior SkipEmptyParts ();  
#endif
};

#endif // COMPATIBILITY_H
