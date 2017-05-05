/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "MimePointsDetector.h"
#include <QApplication>
#include <QClipboard>
#include <QSize>
#include <QStringList>
#include "Transformation.h"

MimePointsDetector::MimePointsDetector ()
{
}

MimePointsDetector::~MimePointsDetector ()
{
}

bool MimePointsDetector::isMimePointsData (const Transformation &transformation,
                                           const QSize &screenSize) const
{
  // A major goal is for this to return as quickly as possible so user interface is not visibly slowed down
  //
  // Expected format is:
  //   x Curve1
  //   # #
  //   # #
  //   x Curve 2
  //   # #
  //
  // Tests are, ordered from fastest/easiest to slowest/hardest are:
  // 1) Transformation must be defined
  // 2) Need at least two lines (one header plus one data point)
  // 3) Always two tab-delimited columns
  // 4) Skip lines that have other than 2 numbers
  // 5) Skip if numbers correspond to points outside of the X/Y coordinates since user will never be able to see them

  const QString TAB_DELIMITER ("\t");

  if (!transformation.transformIsDefined()) {
    return false;
  }

  const QClipboard *clipboard = QApplication::clipboard();
  QString text = clipboard->text ();
  QStringList lines = text.split ("\n");
  int i;

  // Check for two lines
  if (lines.count () < 2) {
    return false;
  }

  // Check for two columns
  for (i = 0; i < lines.count(); i++) {

    // Skip empty lines
    QString line = lines.at (i);
    if (!line.trimmed ().isEmpty ()) {

      QStringList fields = line.split (TAB_DELIMITER);
      if (fields.count () != 2) {
        return false;
      }
    }
  }

  // Check for numbers outside of the legal range
  for (i = 0; i < lines.count (); i++) {

    // Skip empty lines
    QString line = lines.at (i);
    if (!line.trimmed ().isEmpty ()) {

      QStringList fields = line.split (TAB_DELIMITER);
      QString field0 = fields [0];
      QString field1 = fields [1];
      bool ok0, ok1;
      double value0 = field0.toDouble (&ok0);
      double value1 = field1.toDouble (&ok1);
      if (ok0 && ok1) {

        // This is a data point. Check against legal range
        QPointF pointScreen;
        transformation.transformRawGraphToScreen (QPointF (value0, value1),
                                                  pointScreen);
        if (pointScreen.x() < 0 ||
            pointScreen.y() < 0 ||
            pointScreen.x() > screenSize.width() ||
            pointScreen.y() > screenSize.height ()) {

          return false;
        }
      }
    }
  }

  return true;
}
