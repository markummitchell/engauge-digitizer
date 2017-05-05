/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DIGITIZE_STATE_ABSTRACT_BASE_H
#define DIGITIZE_STATE_ABSTRACT_BASE_H

#include "PointStyle.h"
#include <QCursor>
#include <QPointF>

class CmdMediator;
class DigitizeStateContext;
class DocumentModelDigitizeCurve;
class DocumentModelSegments;
class QSize;
class QString;
class QStringList;
class Transformation;

/// Set of possible states of Digitize toolbar.
enum DigitizeState {
  DIGITIZE_STATE_AXIS,
  DIGITIZE_STATE_COLOR_PICKER,
  DIGITIZE_STATE_CURVE,
  DIGITIZE_STATE_EMPTY,
  DIGITIZE_STATE_POINT_MATCH,
  DIGITIZE_STATE_SEGMENT,
  DIGITIZE_STATE_SELECT,
  DIGITIZE_STATE_SCALE, // Out of order for backwards compatibility with pre-version 10
  NUM_DIGITIZE_STATES
};

/// Base class for all digitizing states. This serves as an interface to DigitizeStateContext
class DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateAbstractBase(DigitizeStateContext &context);
  virtual ~DigitizeStateAbstractBase ();

  /// Name of the active Curve. This can include AXIS_CURVE_NAME
  virtual QString activeCurve () const = 0;

  /// Method that is called at the exact moment a state is entered. Typically called just after end for the previous state.
  /// The previousState value is used by DigitizeStateColorPicker to return to the previous state
  virtual void begin(CmdMediator *cmdMediator,
                     DigitizeState previousState) = 0;

  /// Return true if there is good data in the clipboard for pasting, and that is compatible with the current state
  virtual bool canPaste (const Transformation &transformation,
                         const QSize &viewSize) const = 0;

  /// Reference to the DigitizeStateContext that contains all the DigitizeStateAbstractBase subclasses, without const.
  DigitizeStateContext &context();

  /// Reference to the DigitizeStateContext that contains all the DigitizeStateAbstractBase subclasses, without const.
  const DigitizeStateContext &context() const;

  /// Method that is called at the exact moment a state is exited. Typically called just before begin for the next state
  virtual void end() = 0;

  /// Handle a right click, on an axis point, that was intercepted earlier
  virtual void handleContextMenuEventAxis (CmdMediator *cmdMediator,
                                           const QString &pointIdentifier) = 0;

  /// Handle a right click, on a graph point, that was intercepted earlier
  virtual void handleContextMenuEventGraph (CmdMediator *cmdMediator,
                                            const QStringList &pointIdentifiers) = 0;

  /// Handle the selection of a new curve. At a minimum, DigitizeStateSegment will generate a new set of Segments
  virtual void handleCurveChange (CmdMediator *cmdMediator) = 0;

  /// Handle a key press that was intercepted earlier.
  virtual void handleKeyPress (CmdMediator *cmdMediator,
                               Qt::Key key,
                               bool atLeastOneSelectedItem) = 0;

  /// Handle a mouse move. This is part of an experiment to see if augmenting the cursor in Point Match mode is worthwhile
  virtual void handleMouseMove (CmdMediator *cmdMediator,
                                QPointF posScreen) = 0;

  /// Handle a mouse press that was intercepted earlier.
  virtual void handleMousePress (CmdMediator *cmdMediator,
                                 QPointF pos) = 0;

  /// Handle a mouse release that was intercepted earlier.
  virtual void handleMouseRelease (CmdMediator *cmdMediator,
                                   QPointF pos) = 0;

  /// Update the cursor according to the current state.
  void setCursor(CmdMediator *cmdMediator);

  /// State name for debugging
  virtual QString state() const = 0;

  /// Update graphics attributes after possible new points. This is useful for highlight opacity
  virtual void updateAfterPointAddition () = 0;

  /// Update the digitize curve settings
  virtual void updateModelDigitizeCurve (CmdMediator *cmdMediator,
                                         const DocumentModelDigitizeCurve &modelDigitizeCurve) = 0;

  /// Update the segments given the new settings
  virtual void updateModelSegments(const DocumentModelSegments &modelSegments) = 0;

protected:
  /// Protected version of canPaste method. Some, but not all, leaf classes use this method
  bool canPasteProtected (const Transformation &transformation,
                          const QSize &viewSize) const;

  /// Returns the state-specific cursor shape.
  virtual QCursor cursor (CmdMediator *cmdMediator) const = 0;

private:
  DigitizeStateAbstractBase();

  DigitizeStateContext &m_context;

};

#endif // DIGITIZE_STATE_ABSTRACT_BASE_H
