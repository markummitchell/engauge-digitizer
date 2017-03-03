/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DIGITIZE_STATE_SELECT_H
#define DIGITIZE_STATE_SELECT_H

#include "DigitizeStateAbstractBase.h"

/// Digitizing state for selecting one or more Points in the Document.
///
/// Originally this class set the cursor for each QGraphicsItem at the beginning of the state, but that
/// triggered Qt bug 4190 which has the description 'If you have set the cursor for some QGraphicsItems
/// you can no longer change the cursor for the view in for example a mouseReleaseEvent'. In turn, that
/// lead to Engauge issue #155. Unfortunately, this means the user no longer has need feedback that suggests
/// the user can do something with the QGraphicsItems.
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
  virtual void handleContextMenuEventAxis (CmdMediator *cmdMediator,
                                           const QString &pointIdentifier);
  virtual void handleContextMenuEventGraph (CmdMediator *cmdMediator,
                                            const QStringList &pointIdentifiers);
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
  virtual void updateAfterPointAddition ();
  virtual void updateModelDigitizeCurve (CmdMediator *cmdMediator,
                                         const DocumentModelDigitizeCurve &modelDigitizeCurve);
  virtual void updateModelSegments(const DocumentModelSegments &modelSegments);

private:
  DigitizeStateSelect();

  void addHoverHighlighting();
  void handleContextMenuEventAxis2 (CmdMediator *cmdMediator);
  void handleContextMenuEventAxis34 (CmdMediator *cmdMediator,
                                     const QString &pointIdentifier);
  void keyPressArrow (CmdMediator *cmdMediator,
                      Qt::Key key);
  QString moveTextFromDeltaScreen (const QPointF &deltaScreen);
  void removeHoverHighlighting();
  double scaleBarLength (CmdMediator *cmdMediator) const;
  QString scaleBarPointIdentifier (CmdMediator *cmdMediator) const;
  void setHoverHighlighting(const MainWindowModel &modelMainWindow);
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
