#ifndef DLG_MODEL_CURVES_H
#define DLG_MODEL_CURVES_H

#include "DlgModelCurveEntry.h"
#include <QAbstractTableModel>
#include <QStringList>

/// Model for QListView in DlgSettingsCurves. First column is visible with current curve name.
/// Second column is hidden with curve name at the start of editing, or empty if none.
class DlgModelCurves : public QAbstractTableModel
{
public:
  DlgModelCurves();

  /// Columns are current curve name in first column, and original curve name in second column.
  virtual int columnCount (const QModelIndex &parent = QModelIndex()) const;

  /// Return true if specified curve name is already in the list.
  bool containsCurveNameCurrent (const QString &curveName) const;

  /// Retrieve data from model.
  virtual QVariant data (const QModelIndex & index,
                         int role = Qt::DisplayRole) const;

  /// Override normal flags with additional editing flags.
  virtual Qt::ItemFlags flags (const QModelIndex &index) const;

  /// Insert one row.
  virtual bool insertRows (int row, int count, const QModelIndex &parent = QModelIndex ());

  /// Remove one row.
  virtual bool removeRows (int row, int count, const QModelIndex &parent);

  /// One row per curve name.
  virtual int rowCount (const QModelIndex & parent = QModelIndex()) const;

  /// Store one curve name data.
  virtual bool setData(const QModelIndex &index,
                       const QVariant &value,
                       int role = Qt::EditRole);

  /// Allow dragging for reordering.
  virtual Qt::DropActions supportedDropActions () const;

private:

  /// Store entries as QStrings for easy translation into QVariants. Use DlgModelCurveEntry to translate
  QStringList m_modelCurveEntries;
};

#endif // DLG_MODEL_CURVES_H
