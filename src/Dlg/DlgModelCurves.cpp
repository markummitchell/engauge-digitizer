#include "DlgModelCurves.h"

DlgModelCurves::DlgModelCurves()
{
}

QVariant DlgModelCurves::data (const QModelIndex &index,
                               int role) const
{

}


Qt::ItemFlags DlgModelCurves::flags (const QModelIndex &index) const
{
  return flags (index) | Qt::ItemIsEditable;
}

bool DlgModelCurves::insertRows (int row,
                                 int count,
                                 const QModelIndex &parent)
{
}

bool DlgModelCurves::removeRows (int row,
                                 int count,
                                 const QModelIndex &parent)
{

}

int DlgModelCurves::rowCount (const QModelIndex &parent)
{

}

bool DlgModelCurves::setData (const QModelIndex &index,
                              const QVariant &value,
                              int role)
{

}
