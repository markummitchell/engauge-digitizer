/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ChecklistGuidePageIntro.h"
#include "Logger.h"

ChecklistGuidePageIntro::ChecklistGuidePageIntro() :
  ChecklistGuidePage (tr ("Introduction"))
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageIntro::ChecklistGuidePageIntro";

  addHtml (QString ("<p>%1</p>"
                    "<p>%2</p>"
                    "<p>%3</p>")
           .arg (tr ("Engauge converts an image of a graph or map into numbers, as long as the image has axes and/or grid lines "
                     "to define the coordinates."))
           .arg (tr ("This wizard creates a checklist of steps that can serve as a helpful guide. By following those steps, you "
                     "can obtain digitized data points in an exported file. This wizard also provides a quick summary of the "
                     "most useful features of Engauge."))
           .arg (tr ("New users are encouraged to use this wizard.")));
}
