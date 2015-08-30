#ifndef CHECKLIST_GUIDE_WIZARD_H
#define CHECKLIST_GUIDE_WIZARD_H

#include <QStringList>
#include <QWizard>

class ChecklistGuidePageConclusion;
class ChecklistGuidePageCurves;
class ChecklistGuidePageIntro;
class CurvesGraphs;
class MainWindow;
class QPushButton;

/// Wizard for setting up the checklist guide
class ChecklistGuideWizard : public QWizard
{
 public:
  /// Single constructor
  ChecklistGuideWizard(MainWindow &mainWindow);

  /// Curve names to be placed into Document
  QStringList curveNames() const;

  /// Create entries in CurvesGraphs for each curve name that user provided
  void populateCurvesGraphs (CurvesGraphs &curvesGraphs);

  /// Template html comprising the checklist for display
  QString templateHtml () const;

 private:
  ChecklistGuideWizard();

  QString templateHtmlToAdjustColorFilterSettings () const;

  MainWindow &m_mainWindow;
  QPushButton *m_btnCancel;
  QPushButton *m_btnOk;

  QString m_dialogName;

  ChecklistGuidePageIntro *m_pageIntro;
  ChecklistGuidePageCurves *m_pageCurves;
  ChecklistGuidePageConclusion *m_pageConclusion;
};

#endif // CHECKLIST_GUIDE_WIZARD_H
