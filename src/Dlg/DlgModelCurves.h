#ifndef DLG_MODEL_CURVES_H
#define DLG_MODEL_CURVES_H

#include "DlgModelCurveEntry.h"
#include <QAbstractListModel>
#include <QStringList>

class DlgModelCurves : public QAbstractListModel
{
public:
  DlgModelCurves();

  virtual QVariant data (const QModelIndex & index,
                         int role = Qt::DisplayRole) const;
  virtual Qt::ItemFlags flags (const QModelIndex &index) const;
  virtual bool insertRows (int row, int count, const QModelIndex &parent = QModelIndex ());
  virtual bool removeRows (int row, int count, const QModelIndex &parent = QModelIndex ());
  virtual int rowCount (const QModelIndex & parent = QModelIndex()) const;
  virtual bool setData(const QModelIndex &index,
                       const QVariant &value,
                       int role = Qt::EditRole);

private:

  /// Store entries as QStrings for easy translation into QVariants. Use DlgModelCurveEntry to translate
  QStringList m_modelCurveEntries;
};

#endif // DLG_MODEL_CURVES_H
