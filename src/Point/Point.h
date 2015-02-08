#ifndef POINT_H
#define POINT_H

#include <QPointF>
#include <QString>

/// Class that represents one digitized point. The screen-to-graph coordinate transformation is always external to this class
class Point
{
public:
  /// Constructor from scratch. The position, in screen coordinates, applies to the center of the Point
  Point (const QString &curveName,
         const QPointF &posScreen,
         const QPointF posGraph = QPointF (0, 0));

  /// Constructor for specified identifier (after redo). The position, in screen coordinates, applies to the center of the Point
  Point (const QString &curveName,
         const QPointF &posScreen,
         const QString &identifier,
         const QPointF posGraph = QPointF (0, 0));

  /// Copy constructor.
  Point (const Point &point);

  /// Assignment constructor.
  Point &operator=(const Point &point);

  /// Parse the curve name from the specified point identifier. This does the opposite of uniqueIdentifierGenerator
  static QString curveNameFromPointIdentifier (const QString &pointIdentifier);

  /// Unique identifier for a specific Point.
  QString identifier () const;

  /// Return the current index for storage in case we need to reset it later while performing a Redo.
  static unsigned int identifierIndex ();

  /// Get method for ordinal.
  int ordinal () const;

  /// Accessor for graph position.
  QPointF posGraph () const;

  /// Accessor for screen position
  QPointF posScreen () const;

  /// Reset the current index while performing a Redo.
  static void setIdentifierIndex (unsigned int identifierIndex);

  /// Set the ordinal used for ordering Points.
  void setOrdinal (int ordinal);

  /// Set method for position in graph coordinates.
  void setPosGraph (const QPointF &posGraph);

  /// Set method for position in screen coordinates.
  void setPosScreen (const QPointF &posScreen);

private:
  Point();

  /// Generate a unique identifier for a Point. This is static so it can be used while a
  /// GraphicsPointAbstractBase-based object is being constructed.
  ///
  /// Identifiers follow sequential counting numbers since those are easier to deal with
  /// than alternatives such as 64-bit guids (like Microsoft)
  static QString uniqueIdentifierGenerator(const QString &curveName);

  QString m_identifier;
  QPointF m_posScreen;
  QPointF m_posGraph;
  int m_ordinal;

  static unsigned int m_identifierIndex; // For generating unique identifiers
};

#endif // POINT_H
