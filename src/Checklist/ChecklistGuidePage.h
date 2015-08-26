#ifndef CHECKLIST_GUIDE_PAGE_H
#define CHECKLIST_GUIDE_PAGE_H

#include <QWizardPage>

class QString;
class QTextEdit;

/// This class customizes QWizardPage for ChecklistGuideWizard
class ChecklistGuidePage : public QWizardPage
{
 public:
  /// Single constructor
  ChecklistGuidePage(const QString &title);

 private:
  ChecklistGuidePage();

  QTextEdit *m_edit;
};

#endif // CHECKLIST_GUIDE_PAGE_H
