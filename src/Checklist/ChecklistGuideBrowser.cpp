#include "ChecklistGuideBrowser.h"
#include "ChecklistTemplate.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QDebug>

const int MIN_WIDTH_BROWSER = 340; // Make just big enough that each "More..." appears on same line

ChecklistGuideBrowser::ChecklistGuideBrowser () :
  m_document (0)
{
  setOpenLinks (false); // Disable automatic link following
  setMinimumWidth(MIN_WIDTH_BROWSER);

  connect (this, SIGNAL (anchorClicked (const QUrl &)), this, SLOT (slotAnchorClicked (const QUrl &)));
}

QString ChecklistGuideBrowser::ahref (QString &html,
                                      const QString &name,
                                      const QString &anchor) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::bindToDocument";

  QString expression = QString ("%1%2%3")
                       .arg (TAG_AHREF_DELIMITER_START)
                       .arg (name)
                       .arg (TAG_AHREF_DELIMITER_END);

  QString link;
  if (name == anchor) {

    // Click on this hyperlink to reload the page without details under this link, since anchor is empty
    link = QString ("<a href=""#"">Less ...</a>");

  } else {

    // Click on this hyperlink to reload the page with details under this link
    link = QString ("<a href=""#%1"">More ...</a>")
           .arg (name);

  }

  html.replace (expression, link);

  return html;
}

void ChecklistGuideBrowser::bindToDocument(Document &document)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::bindToDocument";

  m_document = &document;
}

void ChecklistGuideBrowser::check (QString &html,
                                   const QString &anchor,
                                   bool isChecked) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::check";

  QString tag = QString ("%1%2%3")
                .arg (TAG_ANCHOR_DELIMITER_START)
                .arg (anchor)
                .arg (TAG_ANCHOR_DELIMITER_END);

  if (isChecked) {
    html.replace (tag, "<img src="":/engauge/img/16-checked.png"">");
  } else {
    html.replace (tag, "<img src=""./engauge/img/16-unchecked.png"">");
  }
}

void ChecklistGuideBrowser::divHide (QString &html,
                                     const QString &anchor) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::divHide"
                              << " anchor=" << anchor.toLatin1().data();

  // Remove everything between the start and end tags, inclusive
  QString expression = QString ("\\%1%2\\%3.*\\%4%5\\%6")
                       .arg (TAG_DIV_DELIMITER_START)
                       .arg (anchor)
                       .arg (TAG_DIV_DELIMITER_END)
                       .arg (TAG_DIV_DELIMITER_START_SLASH)
                       .arg (anchor)
                       .arg (TAG_DIV_DELIMITER_END);
  QRegExp regExp  (expression);
  html.replace (regExp, "");
}

void ChecklistGuideBrowser::divShow (QString &html,
                                     const QString &anchor) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::divShow"
                              << " anchor=" << anchor.toLatin1().data();

  if (!anchor.isEmpty ()) {

    // Remove the start and end tags, but leave the text in between
    QString expressionStart = QString ("\\%1%2\\%3")
                              .arg (TAG_DIV_DELIMITER_START)
                              .arg (anchor)
                              .arg (TAG_DIV_DELIMITER_END);
    QString expressionEnd = QString ("\\%1%2\\%3")
                            .arg (TAG_DIV_DELIMITER_START_SLASH)
                            .arg (anchor)
                            .arg (TAG_DIV_DELIMITER_END);
    QRegExp regExpStart (expressionStart);
    QRegExp regExpEnd (expressionEnd);
    html.replace (regExpStart, "");
    html.replace (regExpEnd, "");
  }
}

QString ChecklistGuideBrowser::processAhrefs (const QString &htmlBefore,
                                              const QString &anchor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::processAhrefs"
                              << " anchor=" << anchor.toLatin1().data();

  QString html = htmlBefore;

  // Fixed axis point hrefs
  ahref (html, NAME_AXIS1, anchor);
  ahref (html, NAME_AXIS2, anchor);
  ahref (html, NAME_AXIS3, anchor);

  // Curves
  QStringList curveNames = m_document->curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

    QString curveName = *itr;
    ahref (html, curveName, anchor);
  }

  // Export
  ahref (html, NAME_EXPORT, anchor);

  return html;
}

QString ChecklistGuideBrowser::processCheckboxes (const QString &htmlBefore)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::processCheckboxes";

  QString html = htmlBefore;

  if (m_document != 0) {

    bool isAxis1 = (m_document->curveAxes().numPoints() > 0);
    bool isAxis2 = (m_document->curveAxes().numPoints() > 1);
    bool isAxis3 = (m_document->curveAxes().numPoints() > 2);

    check (html, NAME_AXIS1, isAxis1);
    check (html, NAME_AXIS2, isAxis2);
    check (html, NAME_AXIS3, isAxis3);

    // Curves
    QStringList curveNames = m_document->curvesGraphsNames();
    QStringList::const_iterator itr;
    for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

      QString curveName = *itr;
      bool isCurve = (m_document->curvesGraphsNumPoints (curveName) > 0);
      check (html, curveName, isCurve);
    }


  }

  return html;
}

QString ChecklistGuideBrowser::processDivs (const QString &htmlBefore,
                                            const QString &anchor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::processDivs";

  QString html = htmlBefore;

  // Show div associated with anchor. Since this removes the tags, applying divHide below
  // will have no effect, so we apply divHide to everything
  divShow (html, anchor);

  // Fixed axis point tags
  divHide (html, NAME_AXIS1);
  divHide (html, NAME_AXIS2);
  divHide (html, NAME_AXIS3);

  if (m_document != 0) {

    // Curve name tags
    QStringList curveNames = m_document->curvesGraphsNames();
    QStringList::const_iterator itr;
    for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

      QString curveName = *itr;
      divHide (html, curveName);
    }
  }

  divHide (html, NAME_EXPORT);

  return html;
}

void ChecklistGuideBrowser::processTemplateHtmlAndDisplay(const QString &anchor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::processTemplateHtmlAndDisplay"
                              << " anchor=" << anchor.toLatin1().data();

  QString html = m_templateHtml;

  html = processAhrefs (html,
                        anchor);
  html = processCheckboxes (html);
  html = processDivs (html,
                      anchor);

  QTextBrowser::setHtml (html);
}

void ChecklistGuideBrowser::setTemplateHtml (const QString &html)
{
  QString NO_ANCHOR;

  m_templateHtml = html;

  processTemplateHtmlAndDisplay (NO_ANCHOR);
}

void ChecklistGuideBrowser::slotAnchorClicked (const QUrl &url)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::slotAnchorClicked";

  QString anchor;
  if (url.hasFragment ()) {
    anchor = url.fragment ();
  }

  processTemplateHtmlAndDisplay (anchor);
}

void ChecklistGuideBrowser::unbindFromDocument()
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuideBrowser::unbindFromDocument";

  m_document = 0;
}
