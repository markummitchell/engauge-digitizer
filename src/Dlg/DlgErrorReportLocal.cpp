/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgErrorReportLocal.h"
#include <QCheckBox>
#include <QCommonStyle>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextStream>
#include <QVBoxLayout>

const int MAX_BTN_WIDTH = 80;

DlgErrorReportLocal::DlgErrorReportLocal(const QString &xml,
                                         QWidget *parent) :
  DlgErrorReportAbstractBase (parent),
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

  QLabel *lblMessage = new QLabel (tr ("An unrecoverable error has occurred. Would you like to save an error report that can "
                                       "be sent later to the Engauge developers?\n\n"
                                       "The original document can be sent as part of the error report, which increases the "
                                       "chances of finding and fixing the problem(s). However, if any information is private "
                                       "then an anonymized version of the document will be sent."));
  lblMessage->setWordWrap(true);
  layout->addWidget (lblMessage);

  m_chkOriginal = new QCheckBox (tr ("Include original document information, otherwise anonymize the information"));
  m_chkOriginal->setChecked (true);
  updateFile ();
  layout->addWidget (m_chkOriginal);
  connect (m_chkOriginal, SIGNAL (stateChanged (int)), this, SLOT (slotDocumentCheckboxChanged (int)));

  QHBoxLayout *layoutButtons = new QHBoxLayout;

  QWidget *panelButtons = new QWidget;
  panelButtons->setLayout (layoutButtons);
  layout->addWidget (panelButtons);

  m_btnSave = new QPushButton(tr ("Save"));
  m_btnSave->setMaximumWidth (MAX_BTN_WIDTH);
  layoutButtons->addWidget (m_btnSave);
  connect (m_btnSave, SIGNAL (released ()), this, SLOT (slotSave()));

  m_btnCancel = new QPushButton(tr ("Cancel"));
  m_btnCancel->setMaximumWidth (MAX_BTN_WIDTH);
  layoutButtons->addWidget (m_btnCancel);
  connect (m_btnCancel, SIGNAL (released ()), this, SLOT (reject ()));
}

DlgErrorReportLocal::~DlgErrorReportLocal()
{
  removeFile();
}

void DlgErrorReportLocal::removeFile() const
{
  QFile::remove (errorFile ());
}

void DlgErrorReportLocal::slotDocumentCheckboxChanged(int /* state */)
{
  updateFile();
}

void DlgErrorReportLocal::slotSave()
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

void DlgErrorReportLocal::updateFile()
{
  if (m_chkOriginal->isChecked()) {
    saveFile (m_xmlOriginal);
  } else {
    saveFile (m_xmlAnonymized);
  }
}

QString DlgErrorReportLocal::xmlToUpload() const
{
  return m_xmlToUpload;
}
