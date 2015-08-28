#ifndef CHECKLIST_GUIDE_PAGE_H
#define CHECKLIST_GUIDE_PAGE_H

#include <QWizardPage>

class ChecklistLineEdit;
class QGridLayout;
class QRadioButton;
class QString;
class QVBoxLayout;

/// This class customizes QWizardPage for ChecklistGuideWizard
class ChecklistGuidePage : public QWizardPage
{
 public:
  /// Single constructor
  ChecklistGuidePage(const QString &title);

  /// Insert html for display
  void addHtml (const QString &html);

  /// Insert radio button and corresponding label
  QRadioButton *addLabelAndRadioButton (const QString &label);

  /// Insert line edit
  void addLineEdit (ChecklistLineEdit *edit);

 private:
  ChecklistGuidePage();

  QGridLayout *m_layout;
  int m_row;

  // If ChecklistLineEdits are added, they are all put into a single QWidget since the spacing
  // in that QWidget can be set to zero. This prevents huge ugly gaps between adjacent CheclistLineEdits
  QWidget *m_checklineLineEditContainer; // 0 until used
  QVBoxLayout *m_checklineLineEditLayout; // 0 until used
};

#endif // CHECKLIST_GUIDE_PAGE_H
