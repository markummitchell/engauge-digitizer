#ifndef CHECKLIST_GUIDE_BROWSER_H
#define CHECKLIST_GUIDE_BROWSER_H

#include "CmdMediator.h"
#include <QTextBrowser>

/// Class that adds rudimentary tree collapse/expand functionality to QTextBrowser
class ChecklistGuideBrowser : public QTextBrowser
{
  Q_OBJECT;

 public:
  /// Single constructor
  ChecklistGuideBrowser();

  /// Bind to the CmdMediator
  void bindToCmdMediator (const CmdMediator &cmdMediator);

  /// Populate the browser with template html. The template html will be converted to real html
  virtual void setTemplateHtml (const QString &html);

  /// Unbind to prevent connection to stale CmdMediator
  void unbindFromCmdMediator ();

 private slots:
  void slotAnchorClicked (const QUrl &url);

 private:

  QString ahref (QString &html,
                 const QString &name,
                 const QString &anchor) const;

  void check (QString &html,
              const QString &anchor,
              bool isChecked) const;

  /// Replace A+HREF placeholders by "More..." or "Less..." hyperlinks. Placeholder corresponding to
  /// specified anchor gets "Less..." and all others get "More..."
  QString processAhrefs (const QString &htmlBefore,
                         const QString &anchor);

  /// Replace checkbox placeholders by checkboxes. Checked/unchecked status is computed from Document
  QString processCheckboxes (const QString &htmlBefore);

  /// Filter out all tag-delimited divs except the one corresponding to the specified anchor. If anchor is empty, all divs are removed
  QString processDivs (const QString &htmlBefore,
                       const QString &anchor);

  void processTemplateHtmlAndDisplay (const QString &anchor);
  void divHide (QString &html,
                const QString &anchor) const;
  void divShow (QString &html,
                const QString &anchor) const;

  QString m_templateHtml;
  CmdMediator const *m_cmdMediator;
};

#endif // CHECKLIST_GUIDE_BROWSER_H
