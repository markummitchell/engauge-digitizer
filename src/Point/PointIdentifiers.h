#ifndef POINT_IDENTIFIERS_H
#define POINT_IDENTIFIERS_H

#include <QHash>
#include <QString>

class QXmlStreamReader;
class QXmlStreamWriter;

typedef QHash<QString, bool> PointIdentifiersInternal;

/// Hash table class that tracks point identifiers as the key, with a corresponding boolean value
class PointIdentifiers
{
public:
  /// Single constructor
  PointIdentifiers();

  /// True if specified entry exists in the table
  bool contains(const QString &pointIdentifier) const;

  /// Number of entries
  int count() const;

  /// Get key for index. This involves copying of all the keys and is therefore slower than using key lookup, so
  /// should not be used for extremely numerous point sets
  QString getKey (int i) const;

  /// Get value for key
  bool getValue (const QString &pointIdentifier) const;

  /// Load from serialized xml
  void loadXml (QXmlStreamReader &reader);

  /// Serialize table to xml
  void saveXml (QXmlStreamWriter &writer) const;

  /// Set key/value pair
  void setKeyValue (const QString &pointIdentifier,
                    bool value);

private:

  PointIdentifiersInternal m_pointIdentifiers;
};

#endif // POINT_IDENTIFIERS_H
