#include "ChecklistGuidePageConclusion.h"
#include "Logger.h"

ChecklistGuidePageConclusion::ChecklistGuidePageConclusion() :
  ChecklistGuidePage ("Conclusion")
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageConclusion::ChecklistGuidePageConclusion";

  addHtml ("<p>A checklist guide has been created.</p>");
}

bool ChecklistGuidePageConclusion::validatePage ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageConclusion::validatePage";

  return true;
}

