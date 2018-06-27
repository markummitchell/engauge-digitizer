/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_DOCUMENT_SCRUB_H
#define CALLBACK_DOCUMENT_SCRUB_H

class Point;

#include "CallbackSearchReturn.h"
#include <QString>

/// Callback for scrubbing Document. Any state error will be caught
class CallbackDocumentScrub
{
public:
  /// Single constructor
  CallbackDocumentScrub ();

  /// Scrub result details. Applies when unsuccessful
  QString badPointName () const;

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Scrub overall result
  bool success () const;

private:

  bool m_success;
  QString m_badPointName;
};

#endif // CALLBACK_DOCUMENT_SCRUB_H
