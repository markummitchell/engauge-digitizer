/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_STATE_ABSTRACT_BASE_H
#define CENTIPEDE_STATE_ABSTRACT_BASE_H

#include "CentipedeState.h"
#include <QPointF>

class CentipedeStateContext;
class CmdMediator;

/// Base class for CentipedePair states
class CentipedeStateAbstractBase
{
public:
  /// Single constructor
  CentipedeStateAbstractBase(CentipedeStateContext &context);
  virtual ~CentipedeStateAbstractBase ();

  /// Method that is called at the exact moment a state is entered. Typically called just after end for the previous stat
  virtual void begin() = 0;

  /// Reference to the CentipedeStateContext that contains all the CentipedeStateAbstractBase subclasses
  CentipedeStateContext &context();

  /// Method that is called at the exact moment a state is exited. Typically called just before start of the next stat
  virtual void end() = 0;

  /// Handle key press event
  virtual void handleKeyPress (CmdMediator &cmdMediator,
                               Qt::Key key,
                               bool atLeastOneSelectedItem) = 0;

  /// Handle mouse move event
  virtual void handleMouseMove (CmdMediator *cmdMediator,
                                QPointF posScreen) = 0;
  
  /// Handle mouse press event
  virtual void handleMousePress (CmdMediator *cmdMediator,
                                 QPointF posScreen) = 0;

  /// Handle mouse release event
  virtual void handleMouseRelease (CmdMediator *cmdMediator,
                                   QPointF posScreen) = 0;

private:
  CentipedeStateAbstractBase();

  CentipedeStateContext &m_context;
};

#endif // CENTIPEDE_STATE_ABSTRACT_BASE_H
