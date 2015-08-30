#include "ChecklistGuidePage.h"
#include "ChecklistGuidePageConclusion.h"
#include "ChecklistGuidePageCurves.h"
#include "ChecklistGuidePageIntro.h"
#include "ChecklistGuideWizard.h"
#include "ChecklistTemplate.h"
#include "ColorFilterSettings.h"
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

void ChecklistGuideWizard::populateCurvesGraphs (CurvesGraphs &curvesGraphs)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::populateCurvesGraphs";

  QStringList curveNames = m_pageCurves->curveNames();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

    QString curveName = *itr;

    curvesGraphs.addGraphCurveAtEnd(Curve (curveName,
                                           ColorFilterSettings::defaultFilter (),
                                           CurveStyle (LineStyle::defaultGraphCurve (curvesGraphs.numCurves ()),
                                                       PointStyle::defaultGraphCurve (curvesGraphs.numCurves ()))));
  }
}

QString ChecklistGuideWizard::templateHtml () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::templateHtml";

  QStringList curveNames = m_pageCurves->curveNames();
  bool withLines = m_pageCurves->withLines();

  QString html;
  QTextStream str (&html);

  // Insert additional space between successive list items, using stylesheet
  str << "<style type='text/css'>li { margin-top: 10px 0; }</style>";

  str << "<p>The coordinates are defined by creating axis points:</p>\n";
  str << "<p>" << TAG_ANCHOR_AXIS_1 << "&nbsp;Add first of three axis points. " << TAG_AHREF_AXIS_1 << "</p>\n";
  str << TAG_DIV_AXIS_START_1;
  str << "<ul>\n";
  str << "<li>Click on <img src="":/engauge/img/16-DigitAxis""> for <b>Axis Points</b> mode</li>\n";
  str << "<li>Click on an axis tick mark, or intersection of two grid lines, with labeled coordinates</li>\n";
  str << "<li>Enter the coordinates of the axis point</li>\n";
  str << "<li>Click on Ok</li>\n";
  str << "</ul>\n";
  str << TAG_DIV_AXIS_END_1;
  str << "<p>" << TAG_ANCHOR_AXIS_2 << "&nbsp;Add second of three axis points. " << TAG_AHREF_AXIS_2 << "</p>\n";
  str << TAG_DIV_AXIS_START_2;
  str << "<ul>\n";
  str << "<li>Click on <img src="":/engauge/img/16-DigitAxis""> for <b>Axis Points</b> mode</li>\n";
  str << "<li>Click on an axis tick mark, or intersection of two grid lines, with labeled coordinates, away from the other axis point</li>\n";
  str << "<li>Enter the coordinates of the axis point</li>\n";
  str << "<li>Click on Ok</li>\n";
  str << "</ul>\n";
  str << TAG_DIV_AXIS_END_2;
  str << "<p>" << TAG_ANCHOR_AXIS_3 << "&nbsp;Add third of three axis points. " << TAG_AHREF_AXIS_3 << "</p>\n";
  str << TAG_DIV_AXIS_START_3;
  str << "<ul>\n";
  str << "<li>Click on <img src="":/engauge/img/16-DigitAxis""> for <b>Axis Points</b> mode</li>\n";
  str << "<li>Click on an axis tick mark, or intersection of two grid lines, with labeled coordinates, away from the other axis points</li>\n";
  str << "<li>Enter the coordinates of the axis point</li>\n";
  str << "<li>Click on Ok</li>\n";
  str << "</ul>\n";
  str << TAG_DIV_AXIS_END_3;

  str << "<p>&nbsp;</p>\n";
  str << "<p>Points are digitized along each curve:</p>\n";
  QStringList::const_iterator itr;
  for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

    QString curveName = *itr;

    QString tagACurve = QString ("%1%2%3")
                        .arg (TAG_AHREF_DELIMITER_START)
                        .arg (curveName)
                        .arg (TAG_AHREF_DELIMITER_END);

    str << "<p>" << TAG_ANCHOR_DELIMITER_START << curveName << TAG_ANCHOR_DELIMITER_END
        << "&nbsp;Add points for curve <b>" << curveName << "</b>. " << tagACurve << "</p>\n";
    str << TAG_DIV_DELIMITER_START << curveName << TAG_DIV_DELIMITER_END;
    str << "<ul>\n";

    if (withLines) {

      str << "<li>Click on <img src="":/engauge/img/16-DigitSegment""> for <b>Segment Fill</b> mode</li>\n";
      str << "<li>Select curve <b>" << curveName << "</b> in the drop-down list</li>\n";
      str << "<li>Move the cursor over the curve. If a line does not appear then adjust the <b>Color Filter</b> settings for this curve:\n";
      str << templateHtmlToAdjustColorFilterSettings () << "</li>\n";
      str << "<li>Move the cursor over the curve again. When the <b>Segment Fill</b> line appears, click on it to generate points</li>\n";
      str << "</ul>\n";

    } else {

      str << "<li>Click on <img src="":/engauge/img/16-DigitPointMatch""> for <b>Point Match</b> mode</li>\n";
      str << "<li>Select curve <b>" << curveName << "</b> in the drop-down list</li>\n";
      str << "<li>Move the cursor over a typical point in the curve. If the cursor circle does not change color then adjust";
      str << "    the <b>Color Filter</b> settings for this curve:\n";
      str << templateHtmlToAdjustColorFilterSettings () << "</li>\n";
      str << "<li>Move the cursor over a typical point in the curve again. Click on the point to start point matching</li>\n";
      str << "<li>Engauge will display a candidate point. To accept that candidate point, press the right arrow key</li>\n";
      str << "<li>The previous step repeats until you select a different mode</li>\n";
      str << "</ul>\n";
    }

    str << TAG_DIV_DELIMITER_START_SLASH << curveName << TAG_DIV_DELIMITER_END;
  }

  str << "<p>&nbsp;</p>\n";
  str << "<p>The digitized points can be exported:</p>\n";
  str << "<p>" << TAG_ANCHOR_EXPORT << "&nbsp;Export the points to a file. " << TAG_AHREF_EXPORT << "</p>\n";
  str << TAG_DIV_EXPORT_START;
  str << "<ul>\n";
  str << "<li>Select menu option <b>File / Export</b></li>\n";
  str << "<li>Enter the file name</li>\n";
  str << "<li>Click on Ok</li>\n";
  str << "<li>Congratulations!</li>\n";
  str << "</ul>\n";
  str << TAG_DIV_EXPORT_END;

  str << "<p>&nbsp;</p>\n";
  str << "<p>Hint - The background image can be switched between the original image and filtered image. " << TAG_AHREF_BACKGROUND << "</p>\n";
  str << TAG_DIV_BACKGROUND_START;
  str << "<ul>\n";
  str << "<li>Select menu option <b>View / Background / Show Original Image</b> to see the original image</li>\n";
  str << "<li>Select menu option <b>View / Background / Show Filtered Image</b> to see the image from <b>Color Filter</b></li>\n";
  str << "</ul>\n";
  str << TAG_DIV_BACKGROUND_END;

  return html;
}

QString ChecklistGuideWizard::templateHtmlToAdjustColorFilterSettings () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideWizard::templateHtmlToAdjustColorFilterSettings";

  QString html;
  QTextStream str (&html);

  str << "  <ul>\n";
  str << "  <li>Select menu option <b>Settings / Color Filter</b><li>\n";
  str << "  <li>Select the method for filtering. Hue is best if the curves have different colors</li>\n";
  str << "  <li>Slide the green buttons back and forth until the curve is easily visible in the preview window</li>\n";
  str << "  <li>Click on Ok</li>\n";
  str << "  </ul>\n";

  return html;
}
