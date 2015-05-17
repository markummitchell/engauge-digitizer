#ifndef ORDINAL_GENERATOR_H
#define ORDINAL_GENERATOR_H

#include <QPointF>
#include <QString>

class Document;
class Transformation;

/// Utility class for generating ordinal numbers. For axis points, the ordinals are arbitrary but
/// must be unique. For curve points, point is inserted according to its position and the CurveStyle settings
class OrdinalGenerator
{
 public:
  OrdinalGenerator();

  /// Select ordinal just for uniqueness, since there is never a curve drawn through the axis points
  double generateAxisPointOrdinal (const Document &document);

  /// Select ordinal so new point curve passes smoothly through existing points
  double generateCurvePointOrdinal (const Document &document,
                                    const Transformation &transformation,
                                    const QPointF &posScreen,
                                    const QString &curveName);

};

#endif // ORDINAL_GENERATOR_H
