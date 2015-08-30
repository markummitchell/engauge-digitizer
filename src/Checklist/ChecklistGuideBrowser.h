#ifndef CHECKLIST_GUIDE_BROWSER_H
#define CHECKLIST_GUIDE_BROWSER_H

#include "CmdMediator.h"
#include <QHash>
#include <QTextBrowser>

/// Class that adds rudimentary tree collapse/expand functionality to QTextBrowser
class ChecklistGuideBrowser : public QTextBrowser
{
  Q_OBJECT;

 public:
  /// Single constructor
  ChecklistGuideBrowser();

  /// Populate the browser with template html. The template html will be converted to real html
  virtual void setTemplateHtml (const QString &html,
                                const QStringList &curveNames);

  /// Update using current CmdMediator/Document state
  void update (const CmdMediator &cmdMediator,
               bool documentIsExported);

 private slots:
  void slotAnchorClicked (const QUrl &url);

 private:

  QString ahref (QString &html,
                 const QString &name) const;

  void check (QString &html,
              const QString &anchor,
              bool isChecked) const;
  void divHide (QString &html,
                const QString &anchor) const;
  void divShow (QString &html,
                const QString &anchor) const;

  /// Replace A+HREF placeholders by "More..." or "Less..." hyperlinks. Placeholder corresponding to
  /// specified anchor gets "Less..." and all others get "More..."
  QString processAhrefs (const QString &htmlBefore);

  /// Replace checkbox placeholders by checkboxes. Checked/unchecked status is computed from Document
  QString processCheckboxes (const QString &htmlBefore);

  /// Filter out all tag-delimited divs except the one corresponding to the specified anchor. If anchor is empty, all divs are removed
  QString processDivs (const QString &htmlBefore);

  /// Transform the template html, using staged information in m_anchor and m_checkedTags, into pure html and display it
  void refresh ();

  void repopulateCheckedTags (const CmdMediator &cmdMediator,
                              bool documentIsExported);

  QString m_templateHtml;
  QStringList m_curveNames; // Needed for iterating over all Curves in Document

  // Staging area for information that gets displayed. Since this information comes from two sources (QTextBrowser hyperlinks
  // and Document), this information is stored here. When either QTextBrowser or Document has new data, we update the info here
  // and then refresh the display
  QString m_anchor; // From user clicking on a hyperlink in the browser window. Empty value means no div gets shown
  QHash<QString, bool> m_checkedTags; // From Document. Each tag is in this lookup table if checked, otherwise unchecked. Boolean value is ignored
};

#endif // CHECKLIST_GUIDE_BROWSER_H
