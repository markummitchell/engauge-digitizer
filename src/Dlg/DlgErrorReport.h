#ifndef DLG_ERROR_REPORT_H
#define DLG_ERROR_REPORT_H

#include <QDialog>

class QPushButton;

/// Dialog for sending error report. Even if it is not sent, the information is available while this dialog
/// is open, as a file in the executable directory
class DlgErrorReport : public QDialog
{
  Q_OBJECT;

 public:
  /// Single constructor
  DlgErrorReport (const QString &xml,
                  QWidget *parent = 0);

  ~DlgErrorReport();

 private slots:
  void slotSend();

 private:
  DlgErrorReport ();

  QString errorFile () const;
  void removeFile () const;
  void saveFile (const QString &xml) const;

  QPushButton *m_btnSend;
  QPushButton *m_btnCancel;
  QString m_xml;
};

#endif // DLG_ERROR_REPORT_H
