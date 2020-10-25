#include "Crc32.h"
#include "Logger.h"
#include <qmath.h>
#include <QTemporaryFile>
#include <QtTest/QtTest>
#include "Test/TestCrc32.h"

QTEST_MAIN (TestCrc32)

unsigned char inBuffer[] = {"abcdef"};
unsigned outExpectedBinary = 3323750366; // From cksum of file containing inBuffer contents without carriage return
unsigned outExpectedText = 773139377; // From cksum of file containing inBuffer contents without carriage return
    
TestCrc32::TestCrc32(QObject *parent) :
  QObject(parent)
{
}

void TestCrc32::cleanupTestCase ()
{
}

void TestCrc32::initTestCase ()
{
  const bool DEBUG_FLAG = false;

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);
}

void TestCrc32::testFileBinary ()
{
  unsigned outGot = 0;
  
  QTemporaryFile temp;
  temp.setAutoRemove (false);
  QString filename;
  if (temp.open ()) {

    // Save file name for reading after writing, closing then calculating
    filename = temp.fileName ();

    int length = sizeof (inBuffer) / sizeof (unsigned char) - 1;
    
    QDataStream str (&temp);
    str.writeBytes ((const char*) inBuffer, length);

    temp.close ();

    // Calculate
    Crc32 crc32;
    outGot = crc32.filecrc (filename);

    QFile::remove (filename);
  }
  
  QVERIFY (outGot == outExpectedBinary);
}

void TestCrc32::testFileText ()
{
  unsigned outGot = 0;
  
  QTemporaryFile temp;
  temp.setAutoRemove (false);
  QString filename;
  if (temp.open ()) {

    // Save file name for reading after writing, closing then calculating
    filename = temp.fileName ();
    
    QTextStream str (&temp);
    str << QString ((const char*) inBuffer);

    temp.close ();

    // Calculate
    Crc32 crc32;
    outGot = crc32.filecrc (filename);

    QFile::remove (filename);    
  }
  
  QVERIFY (outGot == outExpectedText);
}

void TestCrc32::testMemory ()
{
  Crc32 crc32;

  int length = sizeof (inBuffer) / sizeof (unsigned char) - 1;
  
  unsigned outGot = crc32.memcrc (inBuffer,
                                  length);

  QVERIFY (outGot == outExpectedText);
}
