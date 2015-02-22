#include "DlgErrorReport.h"
#include <QCommonStyle>
#include <QCoreApplication>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextStream>
#include <QVBoxLayout>

const QString ERROR_REPORT_FILE ("engauge_error_report.xml");
const int MAX_BTN_WIDTH = 80;

DlgErrorReport::DlgErrorReport(const QString &xml,
                               QWidget *parent) :
  QDialog (parent),
  m_xml (xml)
{
  QVBoxLayout *layout = new QVBoxLayout;
  setLayout (layout);

  QCommonStyle style;
  setModal(true);
  setWindowTitle (tr ("Error Report"));
  setWindowIcon(style.standardIcon (QStyle::SP_MessageBoxCritical));

  saveFile (xml);

  QLabel *lblPreview = new QLabel (tr ("An unrecoverable error has occurred. Would you like to send an error report to "
                                       "the Engauge developers?\n\n"
                                       "For your privacy, the error report will not contain your original image or any other"
                                       "information that might be sensitive. Only details of the open Document and your "
                                       "computer's operating system are included."));
  lblPreview->setWordWrap(true);
  layout->addWidget (lblPreview);

  QHBoxLayout *layoutButtons = new QHBoxLayout;

  QWidget *panelButtons = new QWidget;
  panelButtons->setLayout (layoutButtons);
  layout->addWidget (panelButtons);

  m_btnSend = new QPushButton(tr ("Send"));
  m_btnSend->setMaximumWidth (MAX_BTN_WIDTH);
  layoutButtons->addWidget (m_btnSend);
  connect (m_btnSend, SIGNAL (released ()), this, SLOT (slotSend()));

  m_btnCancel = new QPushButton(tr ("Cancel"));
  m_btnCancel->setMaximumWidth (MAX_BTN_WIDTH);
  layoutButtons->addWidget (m_btnCancel);
  connect (m_btnCancel, SIGNAL (released ()), this, SLOT (reject ()));
}

DlgErrorReport::~DlgErrorReport()
{
  removeFile();
}

QString DlgErrorReport::errorFile () const
{
  return QCoreApplication::applicationDirPath() + "/" + ERROR_REPORT_FILE;
}

void DlgErrorReport::removeFile() const
{
  QFile::remove (errorFile ());
}

void DlgErrorReport::saveFile (const QString &xml) const
{
  QFile file (errorFile());
  if (file.open (QIODevice::WriteOnly | QIODevice::Text)) {

    QTextStream out (&file);
    out << xml;

    file.close();
  }
}

void DlgErrorReport::slotSend()
{
  close();
}
