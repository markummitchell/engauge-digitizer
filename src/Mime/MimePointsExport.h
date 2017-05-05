/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MIME_POINTS_EXPORT_H
#define MIME_POINTS_EXPORT_H

#include <QMimeData>
#include <QString>
#include <QStringList>

/// Custom mime type for separate treatment of graph coordinates and, when there is no transform, points coordinates.
/// Used for export only.
class MimePointsExport : public QMimeData
{
public:
  /// Default constructor. Initial contents are overwritten by other constructors.
  MimePointsExport();

  /// Constructor when graph coordinates are available because the transformation is defined.
  MimePointsExport(const QString &csvGraph,
                   const QString &htmlGraph);

  /// Constructor when transformation is not defined. This data is not meant to leave this application
  MimePointsExport (const QString &csvPoints);

  /// Assignment operator.
  MimePointsExport &operator=(const MimePointsExport &other);

  /// Destructor.
  virtual ~MimePointsExport ();

  /// Get method for csvGraph.
  QString csvGraph () const;

  /// Get method for csvPoints.
  QString csvPoints () const;

  /// Available formats, which depend on whether or not the transform is defined
  virtual QStringList formats() const;

  /// Get methjod for htmlGraph.
  QString htmlGraph () const;

protected:
  /// Returns a variant with the data for the specified format.
  virtual QVariant retrieveData (const QString &format,
                                 QVariant::Type preferredType) const;

private:
  QString m_csvGraph;
  QString m_csvPoints;
  QString m_htmlGraph;
  QStringList m_formats;
};

#endif // MIME_POINTS_EXPORT_H
