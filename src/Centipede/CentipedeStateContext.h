/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_STATE_CONTEXT_H
#define CENTIPEDE_STATE_CONTEXT_H

#include "CentipedeState.h"
#include "DocumentModelCoords.h"
#include "DocumentModelGuideline.h"
#include <QPointF>
#include <QVector>

class CentipedeStateAbstractBase;
class CmdMediator;
class DigitizeStateGuideline;
class GraphicsScene;
class MainWindow;
class Transformation;

/// State context class for tracking the steps involved in creating centipedes in preparation
/// for creating a guideline
class CentipedeStateContext
{
public:
  /// Single constructor
  CentipedeStateContext (DigitizeStateGuideline &stateGuideline);
  virtual ~CentipedeStateContext ();

  /// Create a command for creating a Guideline
  void createGuidelineCommand (bool selectedXTFinal,
                               double valueFinal);

  /// Get method for forwarded GraphicsScene
  GraphicsScene *graphicsScene () const;
  
  virtual void handleKeyPress (Qt::Key key,
                               bool atLeastOneSelectedItem);
  virtual void handleMouseMove (QPointF posScreen);
  virtual void handleMousePress (GraphicsScene *scene,
                                 MainWindow &mainWindow,
                                 const Transformation &transformation,
                                 const DocumentModelGuideline &modelGuideline,
                                 const DocumentModelCoords &modelCoords,
                                 QPointF posScreen,
                                 bool clickedOnItem);
  virtual void handleMouseRelease (QPointF posScreen);

  /// Get method for forwarded DocumentModelCoords
  DocumentModelCoords modelCoords () const;
  
  /// Get method for forwarded DocumentModelGuideline
  DocumentModelGuideline modelGuideline () const;

  /// Get method for forwarded click point
  QPointF posClickScreen () const;
  
  /// Initiate state transition to be performed later, when CentipedeState is off the stack
  void requestDelayedStateTransition (CentipedeState centipedeState);
  
  /// Perform immediate state transition for immediate action. Called when states are off the stack
  void requestImmediateStateTransition (CentipedeState centipedeState);

  /// Get method for forwarded GraphicsScene
  GraphicsScene &scene () const;

  /// Get method for forwarded Transformation
  Transformation transformation () const;
  
private:

  void completeRequestedStateTransitionIfExists ();

  // State machine
  QVector<CentipedeStateAbstractBase*> m_states;
  CentipedeState m_currentState;
  CentipedeState m_requestedState; // Same as m_currentState until requestDelayedStateTransition is called

  // Owning state
  DigitizeStateGuideline &m_stateGuideline;

  // Variables for creating graphics items. Values are forwarded through handleKeyPress
  GraphicsScene *m_scene;
  Transformation *m_transformation;
  DocumentModelGuideline m_modelGuideline;
  DocumentModelCoords m_modelCoords;
  QPointF m_posClickScreen;
};

#endif // CENTIPEDE_STATE_CONTEXT_H
