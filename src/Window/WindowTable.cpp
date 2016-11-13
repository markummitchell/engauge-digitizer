/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <qdebug.h>
#include <QHeaderView>
#include <QMouseEvent>
#include <QStandardItemModel>
#include "WindowModelBase.h"
#include "WindowTable.h"

// Modes:
// -ContiguousSelection is an ok selection mode when dragging is disabled since user can click and drag
//  to easily define a rectangular selection. However, dragging changes that sequence into the start of a drag and drop.
// -ExtendedSelection is best selection mode when dragging is disabled since it acts as ContiguousSelection and also
//  allows control-click to select/unselect individual cells
// -MultiSelection is frustrating since user cannot easily remove existing selection by clicking on an unselected cell,
//  which results in tedious deselections
const QAbstractItemView::SelectionMode SELECTION_MODE = QAbstractItemView::ExtendedSelection;

WindowTable::WindowTable(WindowModelBase &model)
{
  horizontalHeader()->setStretchLastSection (true);
  setModel (&model);
  setSelectionMode (SELECTION_MODE);
  // setDragEnabled (true); This is set later from MainWindowModel
  setDragDropMode (QAbstractItemView::DragOnly);
  horizontalHeader()->hide();
  verticalHeader()->hide();
  setEditTriggers (QAbstractItemView::NoEditTriggers); // Control is read only

  // No WhatsThis text is needed since this table is within a dockable widget that has the same WhatsThis text for
  // a click anywhere in that widget

  // Connect model to view so model can access the current selection
  model.setView (*this);
}

WindowTable::~WindowTable()
{
}

void WindowTable::focusInEvent (QFocusEvent *event)
{
  QTableView::focusInEvent (event);

  emit signalTableStatusChange ();
}

void WindowTable::focusOutEvent (QFocusEvent *event)
{
  QTableView::focusOutEvent (event);

  emit signalTableStatusChange ();
}

void WindowTable::selectionChanged(const QItemSelection &selected,
                                   const QItemSelection &deselected)
{
  QTableView::selectionChanged (selected,
                                deselected);

  emit signalTableStatusChange ();
}
