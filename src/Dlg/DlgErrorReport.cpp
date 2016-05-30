/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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

DlgErrorReport::DlgErrorReport(const QString &xml,
                               QWidget *parent) :
  QDialog (parent),
  m_xmlOriginal (xml),
  m_xmlAnonymized (xml)
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
                                       "The original document can be sent as part of the error report, which increases the "
                                       "chances of finding and fixing the problem(s). However, if any information is private "
                                       "then an anonymized version of the document will be sent."));
  lblPreview->setWordWrap(true);
  layout->addWidget (lblPreview);

  m_chkOriginal = new QCheckBox (tr ("Include original document information, otherwise anonymize the information"));
  m_chkOriginal->setChecked (true);
  updateFile ();
  layout->addWidget (m_chkOriginal);
  connect (m_chkOriginal, SIGNAL (stateChanged (int)), this, SLOT (slotDocumentCheckboxChanged (int)));

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
  if (m_chkOriginal->isChecked()) {
    m_xmlToUpload = m_xmlOriginal;
  } else {
    m_xmlToUpload = m_xmlAnonymized;
  }

  done (QDialog::Accepted);

  close();
}

void DlgErrorReport::updateFile()
{
  if (m_chkOriginal->isChecked()) {
    saveFile (m_xmlOriginal);
  } else {
    saveFile (m_xmlAnonymized);
  }
}

QString DlgErrorReport::xmlToUpload() const
{
  return m_xmlToUpload;
}
