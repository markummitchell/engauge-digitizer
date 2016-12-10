/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgErrorReportAbstractBase.h"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

const QString ERROR_REPORT_FILE ("engauge_error_report.xml");

DlgErrorReportAbstractBase::DlgErrorReportAbstractBase (QWidget *parent) :
  QDialog (parent)
{
}

DlgErrorReportAbstractBase::~DlgErrorReportAbstractBase ()
{
}

QString DlgErrorReportAbstractBase::errorFile () const
{
  return QCoreApplication::applicationDirPath() + "/" + ERROR_REPORT_FILE;
}

void DlgErrorReportAbstractBase::saveFile (const QString &xml) const
{
  QFile file (errorFile());
  if (file.open (QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {

    QTextStream out (&file);
    out << xml;

    file.close();
  }
}
