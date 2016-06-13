/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportImageForRegression.h"
#include <QFile>
#include <QMessageBox>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QTextStream>

ExportImageForRegression::ExportImageForRegression (const QPixmap &pixmap) :
  m_width (pixmap.width ()),
  m_height (pixmap.height ())
{
}

void ExportImageForRegression::fileExport (const QString &filename) const
{
  QFile file (filename);
  if (!file.open (QIODevice::WriteOnly)) {
    QMessageBox::critical (0,
                           QObject::tr ("Export Image"),
                           QObject::tr ("Cannot export file"));
  } else {

    QTextStream str (&file);

    str << m_width << "x" << m_height << "\n";

    file.close ();
  }
}
