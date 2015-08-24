#include "ChecklistGuideWizard.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>

ChecklistGuideWizard::ChecklistGuideWizard (MainWindow &mainWindow) :
  m_mainWindow (mainWindow),
  m_dialogName ("ChecklistGuide")
{
  setWindowTitle (tr ("Checklist Guide Wizard"));
  setModal (true);

  addPage(createPageLinesOrPoints());
  addPage(createPageCurveNames());
}

QWizardPage *ChecklistGuideWizard::createPageCurveNames() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::createPageCurveNames";

  QWizardPage *page = new QWizardPage;

  return page;
}

QWizardPage *ChecklistGuideWizard::createPageLinesOrPoints() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::createPageLinesOrPoints";

  QWizardPage *page = new QWizardPage;

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
