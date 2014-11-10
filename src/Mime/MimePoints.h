#ifndef MIME_POINTS_H
#define MIME_POINTS_H

#include <QMimeData>

/// Custom mime type for separate treatment of graph coordinates and, when there is no transform, points coordinates.
class MimePoints : public QMimeData
{
public:
  /// Default constructor. Initial contents are overwritten by other constructors.
  MimePoints();

  /// Constructor when graph coordinates are available because the transformation is defined.
  MimePoints(const QString &csvGraph,
             const QString &htmlGraph);

  /// Constructor when transformation is not defined. This data is not meant to leave this application
  MimePoints (const QString &csvPoints);

  /// Assignment operator.
  MimePoints &operator=(const MimePoints &other);

  /// Destructor.
  virtual ~MimePoints ();

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

#endif // MIME_POINTS_H
