#include "ChecklistGuidePageIntro.h"
#include "Logger.h"

ChecklistGuidePageIntro::ChecklistGuidePageIntro() :
  ChecklistGuidePage ("Introduction")
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageIntro::ChecklistGuidePageIntro";

  addHtml ("<p>Engauge converts an image of a graph or map into numbers, as long as the image has axes and/or grid lines "
           "to define the coordinates.</p>"
           "<p>This wizard creates a checklist of steps that can serve as a helpful guide. By following those steps, you "
           "can obtain digitized data points in an exported file.</p>");
}
