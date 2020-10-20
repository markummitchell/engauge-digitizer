/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <QApplication>
#include <QClipboard>
#include <qdebug.h>
#include <QDrag>
#include <QGuiApplication>
#include <QHeaderView>
#include <QMimeData>
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

void WindowTable::doDragAndClipboardCopy ()
{
  // Drag operation
  QDrag *drag = new QDrag (this);
  QMimeData *mimeData = new QMimeData;

  mimeData->setText (exportText ());
  drag->setMimeData (mimeData);

  drag->exec (Qt::CopyAction);

  // Copy to clipboard. In linux the result can be checked using 'xclip c -o'
  QGuiApplication::clipboard()->setText (exportText ());
}

QString WindowTable::exportText () const
{
  QString rtn;

  QModelIndexList indexes = selectionModel ()->selection ().indexes ();
  if (indexes.count () > 0) {

    // Copy the rectangular region around the selected cells. Tab-separation
    // seems to nicely copy to spreadsheets and other apps
    int rowMin = 0, rowMax = 0, colMin = 0, colMax = 0;
    for (int i = 0; i < indexes.count(); i++) {
      QModelIndex index = indexes.at (i);
      if (i == 0 || index.row() < rowMin) {
        rowMin = index.row();
      }
      if (i == 0 || index.column() < colMin) {
        colMin = index.column();
      }
      if (i == 0 || rowMax < index.row()) {
        rowMax = index.row();
      }
      if (i == 0 || colMax < index.column()) {
        colMax = index.column();
      }
    }

    // Output table with tab separation
    for (int row = rowMin; row <= rowMax; row++) {
      for (int col = colMin; col <= colMax; col++) {
        if (col > 0) {
          rtn += QString ("\t");
        }

        rtn += model()->index (row, col).data().toString();
      }

      rtn += QString ("\n");
    }
  }

  return rtn;
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

void WindowTable::mouseMoveEvent (QMouseEvent *event)
{
  // Only use left clicks
  if (! (event->buttons() & Qt::LeftButton)) {
    return;
  }

  // Ignore small moves
  if ((event->pos() - m_pressPos).manhattanLength() < QApplication::startDragDistance ()) {
    return;
  }

  doDragAndClipboardCopy ();

  QTableView::mouseMoveEvent (event);
}

void WindowTable::mousePressEvent (QMouseEvent *event)
{
  // Only use left clicks
  if (event->button() == Qt::LeftButton) {
    m_pressPos = event->pos();
  }

  QTableView::mousePressEvent (event);
}

void WindowTable::selectionChanged(const QItemSelection &selected,
                                   const QItemSelection &deselected)
{
  QTableView::selectionChanged (selected,
                                deselected);

  emit signalTableStatusChange ();
}
