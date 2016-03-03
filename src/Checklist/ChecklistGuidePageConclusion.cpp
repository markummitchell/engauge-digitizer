/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ChecklistGuidePageConclusion.h"
#include "Logger.h"

ChecklistGuidePageConclusion::ChecklistGuidePageConclusion() :
  ChecklistGuidePage ("Conclusion")
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageConclusion::ChecklistGuidePageConclusion";

  addHtml (tr ("<p>A checklist guide has been created.</p>"));
}

bool ChecklistGuidePageConclusion::validatePage ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageConclusion::validatePage";

  return true;
}

