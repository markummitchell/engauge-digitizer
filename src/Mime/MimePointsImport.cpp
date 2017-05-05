/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "MimePointsImport.h"
#include <QApplication>
#include <QClipboard>
#include "Transformation.h"

MimePointsImport::MimePointsImport ()
{
}

MimePointsImport::~MimePointsImport ()
{
}

void MimePointsImport::retrievePoints (const Transformation &transformation,
                                       QList<QPoint> &points,
                                       QList<double> &ordinals) const
{
  // Sanity checking by MimePointsDetector::isMimePointsData has already been done

  const QString TAB_DELIMITER ("\t");

  const QClipboard *clipboard = QApplication::clipboard();
  QString text = clipboard->text ();
  QStringList lines = text.split ("\n");

  // Loop through lines
  int ordinal = 0;
  for (int i = 0; i < lines.count(); i++) {

    QString line = lines.at (i);

    // Skip empty lines
    QStringList fields = line.split (TAB_DELIMITER);
    if (!line.trimmed ().isEmpty () &&
        fields.count () == 2) {

      QString field0 = fields [0];
      QString field1 = fields [1];
      bool ok0, ok1;
      double value0 = field0.toDouble (&ok0);
      double value1 = field1.toDouble (&ok1);
      if (ok0 && ok1) {

        QPointF pointScreen;
        transformation.transformRawGraphToScreen (QPointF (value0, value1),
                                                  pointScreen);

        points.push_back (pointScreen.toPoint ());
        ordinals.push_back (ordinal++);
      }
    }
  }
}
