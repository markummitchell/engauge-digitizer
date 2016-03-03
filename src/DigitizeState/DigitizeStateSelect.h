/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DIGITIZE_STATE_SELECT_H
#define DIGITIZE_STATE_SELECT_H

#include "DigitizeStateAbstractBase.h"

/// Digitizing state for selecting one or more Points in the Document.
class DigitizeStateSelect : public DigitizeStateAbstractBase
{
public:
  /// Single constructor.
  DigitizeStateSelect(DigitizeStateContext &context);
  virtual ~DigitizeStateSelect();

  virtual QString activeCurve () const;
  virtual void begin(CmdMediator *cmdMediator,
                     DigitizeState previousState);
  virtual QCursor cursor (CmdMediator *cmdMediator) const;
  virtual void end();
  virtual void handleCurveChange(CmdMediator *cmdMediator);
  virtual void handleKeyPress (CmdMediator *cmdMediator,
                               Qt::Key key,
                               bool atLeastOneSelectedItem);
  virtual void handleMouseMove (CmdMediator *cmdMediator,
                                QPointF posScreen);
  virtual void handleMousePress (CmdMediator *cmdMediator,
                                 QPointF posScreen);
  virtual void handleMouseRelease (CmdMediator *cmdMediator,
                                   QPointF posScreen);
  virtual QString state() const;
  virtual void updateModelDigitizeCurve (CmdMediator *cmdMediator,
                                         const DocumentModelDigitizeCurve &modelDigitizeCurve);
  virtual void updateModelSegments(const DocumentModelSegments &modelSegments);

private:
  DigitizeStateSelect();

  void keyPressArrow (CmdMediator *cmdMediator,
                      Qt::Key key);
  QString moveTextFromDeltaScreen (const QPointF &deltaScreen);
  void setCursorForPoints();
  void unsetCursorForPoints();
  double zoomedToUnzoomedScreenX () const;
  double zoomedToUnzoomedScreenY () const;

  // Click and drag cases are:
  // 1) rubber band selection
  //    Result = selection of any items inside the rubber band but no movement
  // 2) selection and moving with no initially selected items.
  //    Result = selection and movement of item under cursor
  // 3) selection and moving with only item under cursor initially selected
  //    Result = same result as case #2
  // 4) selection and moving with item under cursor not initially selected but other item(s) selected
  //    Result = other items get unselected so the result is the same as case #2 but with some items now unselected
  // 5) selection and moving with item under cursor initially selected along with other selected items
  //    Result = all selected items get moved
  // Originally, determining if any object was under the cursor during mousePressEvent was done with various hit tests, but
  // none were 100% consistent with the internal hit test done by the QGraphicsView. The solution was to simply:
  // 1) Mark all items as unmoved when the mousePressEvent occurs
  // 2) Mark items that undergo QGraphicsItem::ItemScaleHasChanged as having moved
  // 3) Harvest the results when the mouseReleaseEvent occurs
  // All moved items then have the currentCursorPosition - m_movingStart translation applied to them
  QPointF m_movingStart;
};

#endif // DIGITIZE_STATE_SELECT_H
