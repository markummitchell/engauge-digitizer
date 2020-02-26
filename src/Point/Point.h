/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef POINT_H
#define POINT_H

#include <QPointF>
#include <QString>

class QTextStream;
class QXmlStreamReader;
class QXmlStreamWriter;

enum ApplyHasCheck {
  KEEP_HAS_CHECK,
  SKIP_HAS_CHECK
};

extern const QString POINT_IDENTIFIER_DELIMITER_SAFE;

/// Class that represents one digitized point. The screen-to-graph coordinate transformation is always external to this class
class Point
{
public:
  /// Default constructor so this class can be used inside a container
  Point ();

  /// Constructor for Checker temporary points, before real point gets added. The position,
  /// in screen coordinates, applies to the center of the Point
  Point (const QString &curveName,
         const QPointF &posScreen);

  /// Constructor for temporary point used to pre-check transformation points, before real point gets added. The position,
  /// in screen coordinates, applies to the center of the Point
  Point (const QString &curveName,
         const QPointF &posScreen,
         const QPointF &posGraph,
         bool isXOnly);

  /// Constructor for axis points with identifier (after redo). The position, in screen coordinates, applies to the center of the Point
  Point (const QString &curveName,
         const QString &identifier,
         const QPointF &posScreen,
         const QPointF &posGraph,
         double ordinal,
         bool isXOnly);

  /// Constructor for axis points without identifier (after redo). The position, in screen coordinates, applies to the center of the Point
  Point (const QString &curveName,
         const QPointF &posScreen,
         const QPointF &posGraph,
         double ordinal,
         bool isXOnly);

  /// Constructor for graph points with identifier (after redo)
  Point (const QString &curveName,
         const QString &identifier,
         const QPointF &posScreen,
         double ordinal);

  /// Constructor for graph points without identifier (after redo)
  Point (const QString &curveName,
         const QPointF &posScreen,
         double ordinal);

  /// Constructor when loading from serialized xml
  Point (QXmlStreamReader &reader);

  /// Assignment constructor.
  Point &operator=(const Point &point);

  /// Copy constructor.
  Point (const Point &point);

  /// Parse the curve name from the specified point identifier. This does the opposite of uniqueIdentifierGenerator
  static QString curveNameFromPointIdentifier (const QString &pointIdentifier);

  /// True if ordinal is defined.
  bool hasOrdinal () const;

  /// True if graph position is defined.
  bool hasPosGraph () const;

  /// Unique identifier for a specific Point.
  QString identifier () const;

  /// In DOCUMENT_AXES_POINTS_REQUIRED_4 modes, this is true/false if y/x coordinate is undefined
  bool isXOnly() const;

  /// Return the current index for storage in case we need to reset it later while performing a Redo.
  static unsigned int identifierIndex ();

  /// True if point is an axis point. This is used only for sanity checks
  bool isAxisPoint () const;

  /// Get method for ordinal. Skip check if copying one instance to another
  double ordinal (ApplyHasCheck applyHasCheck = KEEP_HAS_CHECK) const;

  /// Accessor for graph position. Skip check if copying one instance to another
  QPointF posGraph (ApplyHasCheck applyHasCheck = KEEP_HAS_CHECK) const;

  /// Accessor for screen position
  QPointF posScreen () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Serialize to stream
  void saveXml(QXmlStreamWriter &writer) const;

  /// Update the point identifier to match the specified curve name
  void setCurveName (const QString &curveName);

  /// Reset the current index while performing a Redo.
  static void setIdentifierIndex (unsigned int identifierIndex);

  /// Set the ordinal used for ordering Points.
  void setOrdinal (double ordinal);

  /// Set method for position in graph coordinates.
  void setPosGraph (const QPointF &posGraph);

  /// Set method for position in screen coordinates.
  void setPosScreen (const QPointF &posScreen);

  /// Point identifier for temporary point that is used by DigitzeStateAxis
  static QString temporaryPointIdentifier ();

  /// Get method for undefined ordinal constant
  static double UNDEFINED_ORDINAL () { return -1.0; }

private:

  /// Version 10.7 was known to have unwanted underscores in points rather than the correct
  /// tabs, in issue #273
  QString fixUnderscores (const QString &identifier) const;

  /// Load from serialized xml
  void loadXml(QXmlStreamReader &reader);

  /// Generate a unique identifier for a Point. This is static so it can be used while a
  /// GraphicsPointAbstractBase-based object is being constructed.
  ///
  /// Identifiers follow sequential counting numbers since those are easier to deal with
  /// than alternatives such as 64-bit guids (like Microsoft)
  static QString uniqueIdentifierGenerator(const QString &curveName);

  bool m_isAxisPoint;
  QString m_identifier;
  QPointF m_posScreen;
  bool m_hasPosGraph;
  QPointF m_posGraph;
  bool m_hasOrdinal;
  double m_ordinal;
  bool m_isXOnly; // For DOCUMENT_AXES_POINTS_REQUIRED_4, true/false when x/y coordinate is undefined

  static unsigned int m_identifierIndex; // For generating unique identifiers
};

#endif // POINT_H
