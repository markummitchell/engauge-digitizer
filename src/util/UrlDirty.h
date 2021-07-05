/******************************************************************************************************
 * (C) 2021 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef URL_DIRTY_H
#define URL_DIRTY_H

#include <QUrl>

/// Adds ability to QUrl to cleanup url path
///
/// Hint for usage - apply where QUrl::toLocalFile is found
class UrlDirty : public QUrl
{
 public:
  /// Default constructor
  UrlDirty ();

  /// Copy constructor
  UrlDirty (const QUrl &other);

  /// Override method to get string value to remove trailing whitepace
  QString toLocalFile () const;
};

#endif // URL_DIRTY_H
