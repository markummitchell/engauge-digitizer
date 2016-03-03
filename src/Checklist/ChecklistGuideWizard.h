/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CHECKLIST_GUIDE_WIZARD_H
#define CHECKLIST_GUIDE_WIZARD_H

#include "CoordSystemIndex.h"
#include <QList>
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
  Q_OBJECT;

 public:
  /// Single constructor
  ChecklistGuideWizard(MainWindow &mainWindow,
                       unsigned int numberCoordSystem);

  /// Curve names to be placed into Document
  QStringList curveNames(CoordSystemIndex coordSystemIndex) const;

  /// Create entries in CurvesGraphs for each curve name that user provided
  void populateCurvesGraphs (CoordSystemIndex coordSystemIndex,
                             CurvesGraphs &curvesGraphs);

  /// Template html comprising the checklist for display
  QString templateHtml (CoordSystemIndex coordSystemIndex) const;

 private:
  ChecklistGuideWizard();

  QString pageCurvesTitle (CoordSystemIndex coordSystemIndex,
                           unsigned int numberCoordSystem) const;
  QString templateHtmlToAdjustColorFilterSettings () const;

  MainWindow &m_mainWindow;

  QPushButton *m_btnCancel;
  QPushButton *m_btnOk;

  QString m_dialogName;

  ChecklistGuidePageIntro *m_pageIntro;
  QList<ChecklistGuidePageCurves *> m_pageCurves; // One page per coordinate system
  ChecklistGuidePageConclusion *m_pageConclusion;
};

#endif // CHECKLIST_GUIDE_WIZARD_H
