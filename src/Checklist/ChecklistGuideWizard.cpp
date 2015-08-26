#include "ChecklistGuideWizard.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

const int TRANSPARENT_ALPHA = 0;

ChecklistGuideWizard::ChecklistGuideWizard (MainWindow &mainWindow) :
  m_mainWindow (mainWindow),
  m_dialogName ("ChecklistGuide")
{
  setWindowTitle (tr ("Checklist Guide Wizard"));
  setModal (true);
  QPixmap splash (":/engauge/img/SpreadsheetsForDoc.png");
  setPixmap (QWizard::WatermarkPixmap, splash); // For ClassicStyle and ModernStyle
  setPixmap (QWizard::BackgroundPixmap, splash); // For MacStyle

  addPage(createPageIntroduction());
  addPage(createPageStrategy());
  addPage(createPageCurveNames());
}

QWizardPage *ChecklistGuideWizard::createPageCurveNames() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::createPageCurveNames";

  QWizardPage *page = new QWizardPage;

  page->setTitle ("Select curve names");

  return page;
}

QWizardPage *ChecklistGuideWizard::createPageIntroduction() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::createPageIntroduction";

  QWizardPage *page = new QWizardPage;

  page->setTitle ("Introduction");

  QTextEdit *edit = new QTextEdit(page);
  edit->setReadOnly (true);

  QPalette palette = edit->palette ();
  palette.setColor (QPalette::Base, QColor (0, 0, 0, TRANSPARENT_ALPHA));
  edit->setPalette (palette);
  edit->setFrameStyle (QFrame::NoFrame);

  edit->setText ("<b>Test</b> html");

  QGridLayout *layout = new QGridLayout;
  page->setLayout (layout);
  layout->addWidget (edit);

  return page;
}

QWizardPage *ChecklistGuideWizard::createPageStrategy() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::createPageStrategy";

  QWizardPage *page = new QWizardPage;

//  QTextEdit *edit = new QTextEdit(page);
  page->setTitle ("Select a strategy");

  return page;
}

void ChecklistGuideWizard::handleOk()
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::handleOk";
}

void ChecklistGuideWizard::slotCancel()
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::slotCancel";

  hide();
}

void ChecklistGuideWizard::slotOk()
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::slotOk";

  handleOk();
}
