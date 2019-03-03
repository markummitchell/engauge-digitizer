/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_BOUNDING_HASH_H
#define CALLBACK_BOUNDING_HASH_H

#include "CallbackSearchReturn.h"
#include "DocumentAxesPointsRequired.h"
#include "DocumentHash.h"
#include <QCryptographicHash>
#include <QString>

class Point;

/// Callback for DocumentHash value for a Document
class CallbackDocumentHash
{
public:
  /// Single constructor
  CallbackDocumentHash(DocumentAxesPointsRequired documentAxesPointsRequired);
  virtual ~CallbackDocumentHash ();

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Computed hash value
  DocumentHash hash() const;

private:
  CallbackDocumentHash();

  const DocumentAxesPointsRequired m_documentAxesPointsRequired;
  QCryptographicHash m_documentHash;
};

#endif // CALLBACK_BOUNDING_HASH_H
