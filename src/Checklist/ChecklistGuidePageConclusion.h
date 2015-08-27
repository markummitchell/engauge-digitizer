#ifndef CHECKLIST_GUIDE_PAGE_CONCLUSION_H
#define CHECKLIST_GUIDE_PAGE_CONCLUSION_H

#include "ChecklistGuidePage.h"

/// This class uses the validation method of the Conclusion page to perform final processing for ChecklistGuideWizard
class ChecklistGuidePageConclusion : public ChecklistGuidePage
{
 public:
  /// Single constructor
  ChecklistGuidePageConclusion ();

  /// Perform final processing
  virtual bool validatePage ();

};

#endif // CHECKLIST_GUIDE_PAGE_CONCLUSION_H
