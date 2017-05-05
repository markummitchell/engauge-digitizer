/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MIME_POINTS_DETECTOR_H
#define MIME_POINTS_DETECTOR_H

#include <QMimeData>
#include <QString>
#include <QStringList>

class QSize;
class Transformation;

/// Detect if text is acceptable for ingestion by MimePoints
class MimePointsDetector
{
public:
  /// Default constructofr
  MimePointsDetector();

  /// Destructor.
  virtual ~MimePointsDetector ();

  /// Returns true if text is acceptable mime data
  bool isMimePointsData (const Transformation &transforation,
                         const QSize &screenSize) const;

};

#endif // MIME_POINTS_DETECTOR_H
