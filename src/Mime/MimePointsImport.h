/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MIME_POINTS_IMPORT_H
#define MIME_POINTS_IMPORT_H

#include <QList>
#include <QPoint>

class Transformation;

/// Import of point data from clipboard
class MimePointsImport
{
public:
  /// Default constructor
  MimePointsImport();

  /// Destructor.
  virtual ~MimePointsImport ();

  /// Retrieve points from clipboard
  void retrievePoints (const Transformation &transformation,
                       QList<QPoint> &points,
                       QList<double> &ordinals) const;
};

#endif // MIME_POINTS_IMPORT_H
