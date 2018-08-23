/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ChecklistGuidePageConclusion.h"
#include "Logger.h"

ChecklistGuidePageConclusion::ChecklistGuidePageConclusion() :
  ChecklistGuidePage (tr ("Conclusion"))
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageConclusion::ChecklistGuidePageConclusion";

  addHtml (QString ("<p>%1</p>"
               "<br/><br/><br/>"
               "<p><font color=\"red\">%2</font> "
               "%3</p>")
      .arg (tr ("A checklist guide has been created."))
      .arg (tr ("Why does the imported image look different?"))
      .arg (tr ("After import, a filtered image is shown in the background. This filtered image is produced from "
                "the original image according to the parameters set in Settings / Color Filter. When the parameters "
                "have been set correctly, unimportant information (such as grid lines and background colors) has been "
                "removed from the filtered images so automated feature extraction can be performed. If desirable "
                "features have been removed from the image, the parameters can be adjusted using Settings / Color Filter, "
                "or the original image can be displayed instead using View / Background / Show Original Image.")));
}

bool ChecklistGuidePageConclusion::validatePage ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageConclusion::validatePage";

  return true;
}

