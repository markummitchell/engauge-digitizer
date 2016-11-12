/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QTableView>
#include "WindowAbstractBase.h"

WindowAbstractBase::WindowAbstractBase (QWidget *parent) :
  QDockWidget (parent)
{
}

WindowAbstractBase::~WindowAbstractBase ()
{
}

void WindowAbstractBase::getTableStatus (bool &tableIsActive,
                                         bool &tableIsCopyable) const
{
  tableIsActive = false;
  tableIsCopyable = false;

  if (view() != 0) {

    QItemSelectionModel *selectionModel = view()->selectionModel ();
    QModelIndexList selection = selectionModel->selectedIndexes ();

    tableIsActive = view()->hasFocus ();
    tableIsCopyable = (selection.count () > 0);
  }
}
