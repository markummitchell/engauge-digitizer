/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackDocumentHash.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "Point.h"
#include <QCryptographicHash>
#include "QtToString.h"
#include "Transformation.h"

CallbackDocumentHash::CallbackDocumentHash(DocumentAxesPointsRequired documentAxesPointsRequired) :
  m_documentAxesPointsRequired (documentAxesPointsRequired),
  m_documentHash (QCryptographicHash::Md5)
{
}

CallbackSearchReturn CallbackDocumentHash::callback (const QString &curveName,
                                                     const Point &point)
{
  // LOG4CPP_DEBUG_S is below

  // Capture all important information about the point into the hash. A single string representing all of the point's details is
  // created, which can be logged, and then that string is added to the hash

  QString details;

  details += curveName.toLatin1();
  details += " " + point.identifier ();
  details += " " + QPointFToString (point.posScreen());

  if (point.hasOrdinal ()) {
    details += " " + QString::number (point.ordinal ());
  }

  if (point.isAxisPoint()) {

    switch (m_documentAxesPointsRequired) {
    case DOCUMENT_AXES_POINTS_REQUIRED_2:
      // Axis point has same value for both coordinates so we chose one coordinate
      details += " " + QString::number (point.posGraph().x());
      break;

    case DOCUMENT_AXES_POINTS_REQUIRED_3:
      // Axis point has two coordinates
      details += " " + QPointFToString (point.posGraph());
      break;

    case DOCUMENT_AXES_POINTS_REQUIRED_4:
      // Axis point has one coordinate
      if (point.isXOnly()) {

        details += " " + QString::number (point.posGraph().x());

      } else {

        details += " " + QString::number (point.posGraph().y());

      }
      break;

    default:
      ENGAUGE_ASSERT (false);
    }
  }

  LOG4CPP_DEBUG_S ((*mainCat)) << "CallbackDocumentHash::callback details=" << details.toLatin1().data();

  // Add details to hash
  m_documentHash.addData (details.toLatin1());

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

DocumentHash CallbackDocumentHash::hash () const
{
  return m_documentHash.result ();
}
