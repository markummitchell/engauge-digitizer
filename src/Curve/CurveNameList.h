/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CURVE_NAME_LIST_H
#define CURVE_NAME_LIST_H

#include "CurveNameListEntry.h"
#include <QAbstractTableModel>
#include <QStringList>

/// Model for DlgSettingsCurveAddRemove and CmdSettingsCurveAddRemove. This is displayed as a QListView, with visible first column
/// showing current curve name. Second column is hidden with curve name at the start of editing, or empty if none.
class CurveNameList : public QAbstractTableModel
{
public:
  /// Default constructor.
  CurveNameList();

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

  /// Ensure curve names are never duplicated or else nasty bugs will appear when duplicates occur. Also prevent empty curve names
  bool curveNameIsAcceptable (const QString &curveNameNew,
                              int row) const;

  /// Store entries as QStrings for easy translation into QVariants. Use CurveNameListEntry to translate
  QStringList m_modelCurvesEntries;
};

#endif // CURVE_NAME_LIST_H
