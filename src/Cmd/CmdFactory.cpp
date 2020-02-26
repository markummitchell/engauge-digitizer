/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAbstract.h"
#include "CmdAddPointAxis.h"
#include "CmdAddPointGraph.h"
#include "CmdAddPointsGraph.h"
#include "CmdCopy.h"
#include "CmdCut.h"
#include "CmdDelete.h"
#include "CmdEditPointAxis.h"
#include "CmdEditPointGraph.h"
#include "CmdFactory.h"
#include "CmdGong.h"
#include "CmdGuidelineAddXT.h"
#include "CmdGuidelineAddYR.h"
#include "CmdGuidelineMoveXT.h"
#include "CmdGuidelineMoveYR.h"
#include "CmdGuidelineRemoveXT.h"
#include "CmdGuidelineRemoveYR.h"
#include "CmdMoveBy.h"
#include "CmdRedoForTest.h"
#include "CmdSelectCoordSystem.h"
#include "CmdSettingsAxesChecker.h"
#include "CmdSettingsColorFilter.h"
#include "CmdSettingsCoords.h"
#include "CmdSettingsCurveList.h"
#include "CmdSettingsCurveProperties.h"
#include "CmdSettingsDigitizeCurve.h"
#include "CmdSettingsExportFormat.h"
#include "CmdSettingsGeneral.h"
#include "CmdSettingsGridRemoval.h"
#include "CmdSettingsPointMatch.h"
#include "CmdSettingsSegments.h"
#include "CmdUndoForTest.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

CmdFactory::CmdFactory ()
{
}

CmdAbstract *CmdFactory::createCmd (MainWindow &mainWindow,
                                    Document &document,
                                    QXmlStreamReader &reader)
{
  CmdAbstract *cmd = nullptr;

  QXmlStreamAttributes attributes = reader.attributes();
  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_CMD_TYPE) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION)) {

    // Invalid xml
    ENGAUGE_ASSERT(false);

  }

  // Get common attributes
  QString cmdType = attributes.value(DOCUMENT_SERIALIZE_CMD_TYPE).toString();
  QString cmdDescription = attributes.value(DOCUMENT_SERIALIZE_CMD_DESCRIPTION).toString();

  if (cmdType == DOCUMENT_SERIALIZE_CMD_ADD_POINT_AXIS) {
    cmd = new CmdAddPointAxis (mainWindow,
                               document,
                               cmdDescription,
                               reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_ADD_POINT_GRAPH) {
    cmd = new CmdAddPointGraph (mainWindow,
                                document,
                                cmdDescription,
                                reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_ADD_POINTS_GRAPH) {
    cmd = new CmdAddPointsGraph (mainWindow,
                                 document,
                                 cmdDescription,
                                 reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_COPY) {
    cmd = new CmdCopy (mainWindow,
                       document,
                       cmdDescription,
                       reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_CUT) {
    cmd = new CmdCut (mainWindow,
                      document,
                      cmdDescription,
                      reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_DELETE) {
    cmd = new CmdDelete (mainWindow,
                         document,
                         cmdDescription,
                         reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_EDIT_POINT_AXIS) {
    cmd = new CmdEditPointAxis (mainWindow,
                                document,
                                cmdDescription,
                                reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_EDIT_POINT_GRAPH) {
    cmd = new CmdEditPointGraph (mainWindow,
                                 document,
                                 cmdDescription,
                                 reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_GONG) {
    cmd = new CmdGong (mainWindow,
                       document,
                       cmdDescription,
                       reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_GUIDELINE_ADD_X_T) {
    cmd = new CmdGuidelineAddXT (mainWindow,
                                 document,
                                 cmdDescription,
                                 reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_GUIDELINE_ADD_Y_R) {
    cmd = new CmdGuidelineAddYR (mainWindow,
                                 document,
                                 cmdDescription,
                                 reader);    
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_GUIDELINE_MOVE_X_T) {
    cmd = new CmdGuidelineMoveXT (mainWindow,
                                  document,
                                  cmdDescription,
                                  reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_GUIDELINE_MOVE_Y_R) {
    cmd = new CmdGuidelineMoveYR (mainWindow,
                                  document,
                                  cmdDescription,
                                  reader);    
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_GUIDELINE_REMOVE_X_T) {
    cmd = new CmdGuidelineRemoveXT (mainWindow,
                                    document,
                                    cmdDescription,
                                    reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_GUIDELINE_REMOVE_Y_R) {
    cmd = new CmdGuidelineRemoveYR (mainWindow,
                                    document,
                                    cmdDescription,
                                    reader);        
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_MOVE_BY) {
    cmd = new CmdMoveBy (mainWindow,
                         document,
                         cmdDescription,
                         reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_REDO_FOR_TEST) {
    cmd = new CmdRedoForTest (mainWindow,
                              document,
                              cmdDescription,
                              reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SELECT_COORD_SYSTEM) {
    cmd = new CmdSelectCoordSystem (mainWindow,
                                    document, 
                                    cmdDescription,
                                    reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_AXES_CHECKER) {
    cmd = new CmdSettingsAxesChecker (mainWindow,
                                      document,
                                      cmdDescription,
                                      reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_COLOR_FILTER) {
    cmd = new CmdSettingsColorFilter (mainWindow,
                                      document,
                                      cmdDescription,
                                      reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_COORDS) {
    cmd = new CmdSettingsCoords (mainWindow,
                                 document,
                                 cmdDescription,
                                 reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_CURVE_LIST) {
    cmd = new CmdSettingsCurveList (mainWindow,
                                    document,
                                    cmdDescription,
                                    reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_CURVE_PROPERTIES) {
    cmd = new CmdSettingsCurveProperties (mainWindow,
                                          document,
                                          cmdDescription,
                                          reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_DIGITIZE_CURVE) {
    cmd = new CmdSettingsDigitizeCurve (mainWindow,
                                        document,
                                        cmdDescription,
                                        reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_EXPORT) {
    cmd = new CmdSettingsExportFormat (mainWindow,
                                       document,
                                       cmdDescription,
                                       reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_GENERAL) {
    cmd = new CmdSettingsGeneral (mainWindow,
                                  document,
                                  cmdDescription,
                                  reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_GRID_REMOVAL) {
    cmd = new CmdSettingsGridRemoval (mainWindow,
                                      document,
                                      cmdDescription,
                                      reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_POINT_MATCH) {
    cmd = new CmdSettingsPointMatch (mainWindow,
                                     document,
                                     cmdDescription,
                                     reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_SETTINGS_SEGMENTS) {
    cmd = new CmdSettingsSegments (mainWindow,
                                   document,
                                   cmdDescription,
                                   reader);
  } else if (cmdType == DOCUMENT_SERIALIZE_CMD_UNDO_FOR_TEST) {
    cmd = new CmdUndoForTest (mainWindow,
                              document,
                              cmdDescription,
                              reader);
  } else {

    // Invalid xml
    ENGAUGE_ASSERT (false);

  }

  return cmd;
}
