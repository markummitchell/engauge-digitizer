/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_ERROR_REPORT_ABSTRACT_BASE_H
#define DLG_ERROR_REPORT_ABSTRACT_BASE_H

#include <QDialog>

/// Base class for dialogs that handle the error report
class DlgErrorReportAbstractBase : public QDialog
{
 public:
  /// Single constructor
  DlgErrorReportAbstractBase (QWidget *parent = 0);
  ~DlgErrorReportAbstractBase();

 protected:
  /// File name for output file containing error report
  QString errorFile () const;

  /// Save xml into output file named by errorFile
  void saveFile (const QString &xml) const;
  
 private:

};

#endif // DLG_ERROR_REPORT_ABSTRACT_BASE_H
