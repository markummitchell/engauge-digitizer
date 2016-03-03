/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CHECKLIST_GUIDE_PAGE_CONCLUSION_H
#define CHECKLIST_GUIDE_PAGE_CONCLUSION_H

#include "ChecklistGuidePage.h"

/// This class uses the validation method of the Conclusion page to perform final processing for ChecklistGuideWizard
class ChecklistGuidePageConclusion : public ChecklistGuidePage
{
  Q_OBJECT;

 public:
  /// Single constructor
  ChecklistGuidePageConclusion ();

  /// Perform final processing
  virtual bool validatePage ();

};

#endif // CHECKLIST_GUIDE_PAGE_CONCLUSION_H
