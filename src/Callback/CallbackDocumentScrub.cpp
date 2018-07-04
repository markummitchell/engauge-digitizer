/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackDocumentScrub.h"
#include "CallbackSearchReturn.h"
#include "Point.h"
#include <QStringList>

extern const QString AXIS_CURVE_NAME;

CallbackDocumentScrub::CallbackDocumentScrub () :
  m_success (true)
{
}

QString CallbackDocumentScrub::badPointName () const
{
  return m_badPointName;
}

CallbackSearchReturn CallbackDocumentScrub::callback (const QString & /* curveName */,
                                                      const Point &point)
{
  QString identifier = point.identifier ();

  QStringList fields = identifier.split (POINT_IDENTIFIER_DELIMITER_SAFE);

  bool successBefore = m_success;

  // Required format is defined by Point::temporaryPointIdentifier and Point::uniqueIdentifierGenerator
  if (fields.size () == 2) {

    // Temporary point
    bool isLastNumeric = true;
    fields [1].toInt (&isLastNumeric);
    if (fields [0] != AXIS_CURVE_NAME ||
        !isLastNumeric) {

      m_success = false;

    }

  } else if (fields.size () == 3) {

    // Regular point
    bool isLastNumeric = true;
    fields [2].toInt (&isLastNumeric);
    if (!isLastNumeric) {

      m_success = false;

    }

  } else {

    // Unexpected number of arguments
    m_success = false;

  }

  if (!m_success && successBefore) {
    m_badPointName = point.identifier ();
  }

  return (m_success ? CALLBACK_SEARCH_RETURN_CONTINUE :
                      CALLBACK_SEARCH_RETURN_INTERRUPT);
}

bool CallbackDocumentScrub::success () const
{
  return m_success;
}
