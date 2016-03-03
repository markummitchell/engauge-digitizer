/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_ERROR_REPORT_H
#define DLG_ERROR_REPORT_H

#include <QDialog>

class QCheckBox;
class QPushButton;

/// Dialog for sending error report. Even if it is not sent, the information is available while this dialog
/// is open, as a file in the executable directory
class DlgErrorReport : public QDialog
{
  Q_OBJECT;

 public:
  /// Single constructor. With the original data, the extra context improves debugging. With anonymization, user privacy is maintained
  DlgErrorReport (const QString &xmlWithImage,
                  QWidget *parent = 0);

  ~DlgErrorReport();

  /// Xml to be uploaded. Includes document if user has approved
  QString xmlToUpload() const;

 private slots:
  void slotDocumentCheckboxChanged(int);
  void slotSend();

 private:
  DlgErrorReport ();

  QString errorFile () const;
  void removeFile () const;
  void saveFile (const QString &xml) const;
  void updateFile();

  QCheckBox *m_chkOriginal;
  QPushButton *m_btnSend;
  QPushButton *m_btnCancel;
  QString m_xmlOriginal;
  QString m_xmlAnonymized;
  QString m_xmlToUpload; // Either m_xmlWithoutDocument or m_xmlWithDocument
};

#endif // DLG_ERROR_REPORT_H
