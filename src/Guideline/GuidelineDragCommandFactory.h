/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_DRAG_COMMAND_FACTORY_H
#define GUIDELINE_DRAG_COMMAND_FACTORY_H

#include "GuidelineValues.h"
#include <QString>

class CmdAbstract;
class Document;
class DocumentModelGuidelines;
class Guidelines;
class MainWindow;

/// Determine if inputs that were collected after a Guideline drag should result in a Cmd to move or
/// Cmd to delete, and then generate the appropriate Cmd
class GuidelineDragCommandFactory
{
public:
  /// Single constructor.
  GuidelineDragCommandFactory();

  /// Create delete or move Cmd. The selected Cmd will act on the document Guidelines to make that set
  /// consistent with the displayed Guidelines (which includes the just-moved Guideline)
  CmdAbstract *createAfterDrag (MainWindow &mainWindow,
                                Document &document,
                                double newValue,
                                const DocumentModelGuidelines &modelGuidelinesDocument,
                                const QString &identifier,
                                bool draggedOffscreen);

private:
  bool isXTForIdentifier (const DocumentModelGuidelines &modelGuidelines,
                          const QString &identifier) const;
  double valueForIdentifier (const DocumentModelGuidelines &modelGuidelines,
                             const QString &identifier) const;  

};

#endif // GUIDELINE_DRAG_COMMAND_FACTORY_H
