/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineState.h"
#include <QHash>

typedef QHash<GuidelineState, QString> GuidelineStateHash;

static GuidelineStateHash guidelineStateHash;

QString guidelineStateAsString (GuidelineState state)
{
  if (guidelineStateHash.size () == 0) {

    // First time through we load the hash
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT]           = "DeployedConstantRSelectEdit";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT_APPEARING] = "DeployedConstantRSelectEditAppearing";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT_HOVER]     = "DeployedConstantRSelectEditHover";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_HIDE]           = "DeployedConstantRSelectHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_LOCK]           = "DeployedConstantRSelectLock";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_EDIT]         = "DeployedConstantRUnselectEdit";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_HIDE]         = "DeployedConstantRUnselectHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_LOCK]         = "DeployedConstantRUnselectLock";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT]           = "DeployedConstantTSelectEdit";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT_APPEARING] = "DeployedConstantTSelectEditAppearing";    
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT_HOVER]     = "DeployedConstantTSelectEditHover";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_HIDE]           = "DeployedConstantTSelectHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_LOCK]           = "DeployedConstantTSelectLock";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_EDIT]         = "DeployedConstantTUnselectEdit";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_HIDE]         = "DeployedConstantTUnselectHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_LOCK]         = "DeployedConstantTUnselectLock";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT]           = "DeployedConstantXSelectEdit";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT_APPEARING] = "DeployedConstantXSelectEditAppearing";    
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT_HOVER]     = "DeployedConstantXSelectEditHover";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_HIDE]           = "DeployedConstantXSelectHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_LOCK]           = "DeployedConstantXSelectLock";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_EDIT]         = "DeployedConstantXUnselectEdit";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_HIDE]         = "DeployedConstantXUnselectHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_LOCK]         = "DeployedConstantXUnselectLock";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT]           = "DeployedConstantYSelectEdit";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT_APPEARING] = "DeployedConstantYSelectEditAppearing";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT_HOVER]     = "DeployedConstantYSelectEditHover";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_HIDE]           = "DeployedConstantYSelectHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_LOCK]           = "DeployedConstantYSelectLock";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_EDIT]         = "DeployedConstantYUnselectEdit";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_HIDE]         = "DeployedConstantYUnselectHide";
    guidelineStateHash [GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_LOCK]         = "DeployedConstantYUnselectLock";
    guidelineStateHash [GUIDELINE_STATE_DISCARDED]                                 = "Discarded";
    guidelineStateHash [GUIDELINE_STATE_HANDLE_R]                                  = "HandleR";
    guidelineStateHash [GUIDELINE_STATE_HANDLE_T]                                  = "HandleT";
    guidelineStateHash [GUIDELINE_STATE_HANDLE_X]                                  = "HandleX";
    guidelineStateHash [GUIDELINE_STATE_HANDLE_Y]                                  = "HandleY";        
  }

  if (guidelineStateHash.contains (state)) {
    return guidelineStateHash [state];
  } else {
    return "?";
  }
}
