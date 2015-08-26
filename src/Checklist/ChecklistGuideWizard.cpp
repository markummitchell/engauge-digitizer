#include "ChecklistGuidePage.h"
#include "ChecklistGuideWizard.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

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

  QWizardPage *page = new ChecklistGuidePage ("Select curve names");

  return page;
}

QWizardPage *ChecklistGuideWizard::createPageIntroduction() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::createPageIntroduction";

  QWizardPage *page = new ChecklistGuidePage ("Introduction");

  return page;
}

QWizardPage *ChecklistGuideWizard::createPageStrategy() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::createPageStrategy";

  QWizardPage *page = new ChecklistGuidePage ("Select a strategy");

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
