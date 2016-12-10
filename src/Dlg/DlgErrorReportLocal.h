/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_ERROR_REPORT_LOCAL_H
#define DLG_ERROR_REPORT_LOCAL_H

#include "DlgErrorReportAbstractBase.h"

class QPushButton;

/// Dialog for saving error report to local hard drive
class DlgErrorReportLocal : public DlgErrorReportAbstractBase
{
  Q_OBJECT;

 public:
  /// Single constructor. With the original data, the extra context improves debugging. With anonymization, user privacy is maintained
  DlgErrorReportLocal (const QString &xmlWithImage,
                       QWidget *parent = 0);
  ~DlgErrorReportLocal ();

 private:
  DlgErrorReportLocal ();

  QPushButton *m_btnOk;
  QString m_xmlOriginal;
};

#endif // DLG_ERROR_REPORT_LOCAL_H
