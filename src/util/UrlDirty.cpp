/******************************************************************************************************
 * (C) 2021 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "UrlDirty.h"

UrlDirty::UrlDirty ()
{
}

UrlDirty::UrlDirty (const QUrl &other) :
  QUrl (other)
{
}

QString UrlDirty::toLocalFile () const
{
  QString dirty = QUrl::toLocalFile ();
  return dirty.replace ("\r", "").replace ("\n", "");
}
