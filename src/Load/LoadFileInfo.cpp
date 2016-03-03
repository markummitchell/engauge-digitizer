/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Document.h"
#include "LoadFileInfo.h"
#include "Logger.h"
#include <QUrl>

LoadFileInfo::LoadFileInfo()
{
}

LoadFileInfo::~LoadFileInfo()
{
}

bool LoadFileInfo::loadsAsDigFile (const QString &urlString) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "LoadFileInfo::loadsAsDigFile";

  QString fileName = urlString;

  QUrl url (urlString);
  if (url.isLocalFile ()) {
    fileName = url.toLocalFile();
  }

  Document document (fileName);

  return document.successfulRead();
}
