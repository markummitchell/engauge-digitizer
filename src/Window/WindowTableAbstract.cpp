/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <qdebug.h>
#include <QHeaderView>
#include <QMouseEvent>
#include <QStandardItemModel>
#include "WindowTableAbstract.h"

// Modes:
// -ContiguousSelection is an ok selection mode when dragging is disabled since user can click and drag
//  to easily define a rectangular selection. However, dragging changes that sequence into the start of a drag and drop.
// -ExtendedSelection is best selection mode when dragging is disabled since it acts as ContiguousSelection and also
//  allows control-click to select/unselect individual cells
// -MultiSelection is frustrating since user cannot easily remove existing selection by clicking on an unselected cell,
//  which results in tedious deselections
const QAbstractItemView::SelectionMode SELECTION_MODE = QAbstractItemView::ExtendedSelection;

WindowTableAbstract::WindowTableAbstract(QStandardItemModel &model)
{
  horizontalHeader()->setStretchLastSection (true);
  setModel (&model);
  setSelectionMode (SELECTION_MODE);
  setDragEnabled (true);  setDragDropMode (QAbstractItemView::DragOnly);
  horizontalHeader()->hide();
  verticalHeader()->hide();
  setEditTriggers (QAbstractItemView::NoEditTriggers); // Control is read only  

  // No WhatsThis text is needed since this table is within a dockable widget that has the same WhatsThis text for
  // a click anywhere in that widget
}

WindowTableAbstract::~WindowTableAbstract()
{
}
