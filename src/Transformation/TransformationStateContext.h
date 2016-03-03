/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef TRANSFORMATION_STATE_CONTEXT_H
#define TRANSFORMATION_STATE_CONTEXT_H

#include <QVector>
#include "TransformationStateAbstractBase.h"

class CmdMediator;
class DocumentModelAxesChecker;
class QGraphicsScene;
class Transformation;

/// Context class for transformation state machine. This removes some tricky state processing from MainWindow.
/// Unlike typical state machines, the transitions are driven directly from the outside rather than indirectly
/// by events that are processed by the states (this has triggerStateTransition rather than requestStateTransition)
class TransformationStateContext
{
public:
  /// Single constructor.
  TransformationStateContext(QGraphicsScene &scene,
                             bool isGnuplot);
  virtual ~TransformationStateContext();

  /// Flag for gnuplot debug files
  bool isGnuplot () const;

  /// Reset, when loading a document after the first, to same state that first document was at when loaded
  void resetOnLoad();

  /// Trigger a state transition to be performed immediately.
  void triggerStateTransition (TransformationState transformationState,
                               CmdMediator &cmdMediator,
                               const Transformation &transformation,
                               const QString &selectedGraphCurve);

  /// Apply the new DocumentModelAxesChecker
  void updateAxesChecker (CmdMediator &cmdMediator,
                          const Transformation &transformation);

private:
  TransformationStateContext();

  QVector<TransformationStateAbstractBase*> m_states;
  TransformationState m_currentState;
  bool m_isGnuplot;
};

#endif // TRANSFORMATION_STATE_CONTEXT_H
