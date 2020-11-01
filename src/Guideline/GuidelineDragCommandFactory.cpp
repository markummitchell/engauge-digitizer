/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAbstract.h"
#include "CmdGuidelineMoveXT.h"
#include "CmdGuidelineMoveYR.h"
#include "CmdGuidelineRemoveXT.h"
#include "CmdGuidelineRemoveYR.h"
#include "DocumentModelGuideline.h"
#include "EngaugeAssert.h"
#include "GuidelineDragCommandFactory.h"
#include "Guidelines.h"
#include "Logger.h"
#include "MainWindow.h"

GuidelineDragCommandFactory::GuidelineDragCommandFactory ()
{
}

CmdAbstract *GuidelineDragCommandFactory::createAfterDrag (MainWindow &mainWindow,
                                                           Document &document,
                                                           double valueAfter,
                                                           const DocumentModelGuideline &modelGuidelineDocument,
                                                           const QString &identifier,
                                                           bool draggedOffscreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineDragCommandFactory::GuidelineDragCommandFactory";

  GuidelineValues valuesXDocument = modelGuidelineDocument.valuesX ();
  GuidelineValues valuesYDocument = modelGuidelineDocument.valuesY ();

  // So which Guideline moved?
  double valueBefore = valueForIdentifier (modelGuidelineDocument,
                                           identifier);

  // What type was the Guideline?
  bool isXT = isXTForIdentifier (modelGuidelineDocument,
                                 identifier);
  
  CmdAbstract *cmd = nullptr;

  if (draggedOffscreen) {

    // Delete
    if (isXT) {
      cmd = new CmdGuidelineRemoveXT(mainWindow,
                                     document,
                                     identifier,
                                     valueBefore);
    } else {
      cmd = new CmdGuidelineRemoveYR(mainWindow,
                                     document,
                                     identifier,
                                     valueBefore);
    }
  } else {

    // Move
    if (isXT) {
      cmd = new CmdGuidelineMoveXT(mainWindow,
                                   document,
                                   identifier,
                                   valueBefore,
                                   valueAfter);
    } else {
      cmd = new CmdGuidelineMoveYR(mainWindow,
                                   document,
                                   identifier,
                                   valueBefore,
                                   valueAfter);
    }
  }

  return cmd;
}

bool GuidelineDragCommandFactory::isXTForIdentifier (const DocumentModelGuideline &modelGuideline,
                                                     const QString &identifierWanted) const
{
  GuidelineValues::const_iterator itr;

  const GuidelineValues &valuesX = modelGuideline.valuesX();
  for (itr = valuesX.begin(); itr != valuesX.end(); itr++) {
    QString identifierGot = itr.key();
    if (identifierWanted == identifierGot) {
      return true;
    }
  }

  return false;
}

double GuidelineDragCommandFactory::valueForIdentifier (const DocumentModelGuideline &modelGuideline,
                                                        const QString &identifierWanted) const
{
  GuidelineValues::const_iterator itr;

  const GuidelineValues &valuesX = modelGuideline.valuesX();
  for (itr = valuesX.begin(); itr != valuesX.end(); itr++) {
    QString identifierGot = itr.key();
    if (identifierWanted == identifierGot) {
      return itr.value ();
    }
  }

  const GuidelineValues &valuesY = modelGuideline.valuesY();
  for (itr = valuesY.begin(); itr != valuesY.end(); itr++) {
    QString identifierGot = itr.key();
    if (identifierWanted == identifierGot) {
      return itr.value ();
    }
  }

  LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineDragCommandFactory::valueForIdentifier identifier "
                               << identifierWanted.toLatin1().data() << " was not found";

  return 0.0;
}
