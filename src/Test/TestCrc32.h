#ifndef TEST_CRC32_H
#define TEST_CRC32_H

#include <QObject>

/// Unit tests of crc32 checksum algorithm
class TestCrc32 : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestCrc32(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testFileBinary ();
  void testFileText ();
  void testMemory ();
  
private:

};

#endif // TEST_CRC32_H
