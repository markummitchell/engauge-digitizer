/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GEOMETRY_MODEL_H
#define GEOMETRY_MODEL_H

#include <QStandardItemModel>
#include <QString>

/// Model that adds row highlighting according to the currently select point identifier
class GeometryModel : public QStandardItemModel
{
public:
  /// Single constructor
  GeometryModel ();
  virtual ~GeometryModel ();

  /// Override for special processing
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  /// Set the point identifier to be highlighted. Value is empty for no highlighting
  void setCurrentPointIdentifier (const QString  &pointIdentifier);

private:

  int rowToBeHighlighted () const;

  int m_rowToBeHighlighted;
  QString m_pointIdentifier; // Point to be higlighted. Empty if none
};

#endif // GEOMETRY_MODEL_H
