#include "ChecklistGuidePage.h"
#include "ChecklistGuidePageConclusion.h"
#include "ChecklistGuidePageCurves.h"
#include "ChecklistGuidePageIntro.h"
#include "ChecklistGuideWizard.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGridLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QRadioButton>
#include <QTextStream>
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

  m_pageIntro = new ChecklistGuidePageIntro();
  m_pageCurves = new ChecklistGuidePageCurves();
  m_pageConclusion = new ChecklistGuidePageConclusion();

  addPage(m_pageIntro);
  addPage(m_pageCurves);
  addPage(m_pageConclusion);
}

QStringList ChecklistGuideWizard::curveNames() const
{
  return m_pageCurves->curveNames();
}

QString ChecklistGuideWizard::html () const
{
  QStringList curveNames = m_pageCurves->curveNames();
  bool withLines = m_pageCurves->withLines();

  QString html;
  QTextStream str (&html);

  str << "<p><img src="":/engauge/img/12-Button-Red.png"">Add three axis points to define the coordinate system.</p>";

  QStringList::const_iterator itr;
  for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

    QString curveName = *itr;
    str << "<p><img src="":/engauge/img/12-Button-Red.png"">Add points for curve '" << curveName << "'</p>\n";
  }

  return html;
}
