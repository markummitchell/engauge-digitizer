#include "DlgErrorReport.h"
#include <QCheckBox>
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

DlgErrorReport::DlgErrorReport(const QString &xmlWithoutDocument,
                               const QString &xmlWithDocument,
                               QWidget *parent) :
  QDialog (parent),
  m_xmlWithoutDocument (xmlWithoutDocument),
  m_xmlWithDocument (xmlWithDocument)
{
  QVBoxLayout *layout = new QVBoxLayout;
  layout->setSizeConstraint (QLayout::SetFixedSize);
  setLayout (layout);

  QCommonStyle style;
  setModal(true);
  setWindowTitle (tr ("Error Report"));
  setWindowIcon(style.standardIcon (QStyle::SP_MessageBoxCritical));

  QLabel *lblPreview = new QLabel (tr ("An unrecoverable error has occurred. Would you like to send an error report to "
                                       "the Engauge developers?\n\n"
                                       "Adding document information to the error report greatly increases the chances of finding "
                                       "and fixing the problems. However, document information should not be included if your document "
                                       "contains any information that should remain private."));
  lblPreview->setWordWrap(true);
  layout->addWidget (lblPreview);

  m_chkWithDocument = new QCheckBox ("Include document information");
  m_chkWithDocument->setChecked (true);
  updateFile ();
  layout->addWidget (m_chkWithDocument);
  connect (m_chkWithDocument, SIGNAL (stateChanged (int)), this, SLOT (slotDocumentCheckboxChanged (int)));

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
  if (file.open (QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {

    QTextStream out (&file);
    out << xml;

    file.close();
  }
}

void DlgErrorReport::slotDocumentCheckboxChanged(int /* state */)
{
  updateFile();
}

void DlgErrorReport::slotSend()
{
  // This is the one path that allows information to be sent to the server
  if (m_chkWithDocument->isChecked()) {
    m_xmlToUpload = m_xmlWithDocument;
  } else {
    m_xmlToUpload = m_xmlWithoutDocument;
  }

  done (QDialog::Accepted);

  close();
}

void DlgErrorReport::updateFile()
{
  if (m_chkWithDocument->isChecked()) {
    saveFile (m_xmlWithDocument);
  } else {
    saveFile (m_xmlWithoutDocument);
  }
}

QString DlgErrorReport::xmlToUpload() const
{
  return m_xmlToUpload;
}
