#ifndef CHECKLIST_GUIDE_WIZARD_H
#define CHECKLIST_GUIDE_WIZARD_H

#include <QStringList>
#include <QWizard>

class ChecklistGuidePageConclusion;
class ChecklistGuidePageCurves;
class ChecklistGuidePageIntro;
class MainWindow;
class QPushButton;

/// Wizard for setting up the checklist guide
class ChecklistGuideWizard : public QWizard
{
 public:
  /// Single constructor
  ChecklistGuideWizard(MainWindow &mainWindow);

  /// Wizard selection for curve names
  QStringList curveNames () const;

  /// Wizard selection of lines versus points
  bool withLines () const;

 private:
  ChecklistGuideWizard();

  MainWindow &m_mainWindow;
  QPushButton *m_btnCancel;
  QPushButton *m_btnOk;

  QString m_dialogName;

  ChecklistGuidePageIntro *m_pageIntro;
  ChecklistGuidePageCurves *m_pageCurves;
  ChecklistGuidePageConclusion *m_pageConclusion;
};

#endif // CHECKLIST_GUIDE_WIZARD_H
