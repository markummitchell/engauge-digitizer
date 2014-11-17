#include "DlgViewCurves.h"
#include <QDropEvent>

DlgViewCurves::DlgViewCurves(QWidget *parent) :
  QListView(parent)
{
}

void DlgViewCurves::dropEvent (QDropEvent *e)
{
  e->setDropAction (Qt::MoveAction);

  QListView::dropEvent (e);
}

void DlgViewCurves::startDrag (Qt::DropActions /* actions */)
{
  QListView::startDrag (Qt::MoveAction);
}
