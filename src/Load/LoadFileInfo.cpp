#include "Document.h"
#include "LoadFileInfo.h"
#include "Logger.h"
#include <QUrl>

LoadFileInfo::LoadFileInfo() {}

LoadFileInfo::~LoadFileInfo() {}

bool LoadFileInfo::loadsAsDigFile(const QString &urlString) const {
  LOG4CPP_INFO_S((*mainCat)) << "LoadFileInfo::loadsAsDigFile";

  QString fileName = urlString;

  QUrl url(urlString);
  if (url.isLocalFile()) {
    fileName = url.toLocalFile();
  }

  Document document(fileName);

  return document.successfulRead();
}
