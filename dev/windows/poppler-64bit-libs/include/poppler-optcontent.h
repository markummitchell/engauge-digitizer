/* poppler-optcontent.h: qt interface to poppler
 *
 * Copyright (C) 2007, Brad Hards <bradh@kde.org>
 * Copyright (C) 2008, Pino Toscano <pino@kde.org>
 * Copyright (C) 2013, Anthony Granger <grangeranthony@gmail.com>
 * Copyright (C) 2016, Albert Astals Cid <aacid@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef POPPLER_OPTCONTENT_H
#define POPPLER_OPTCONTENT_H

#include <QtCore/QAbstractListModel>

#include "poppler-export.h"
#include "poppler-link.h"

class OCGs;

namespace Poppler
{
  class Document;
  class OptContentModelPrivate;

  /**
   * \brief Model for optional content
   *
   * OptContentModel is an item model representing the optional content items
   * that can be found in PDF documents.
   *
   * The model offers a mostly read-only display of the data, allowing to
   * enable/disable some contents setting the Qt::CheckStateRole data role.
   *
   * \since 0.8
   */
  class POPPLER_QT5_EXPORT OptContentModel : public QAbstractItemModel
  {
    friend class Document;

    Q_OBJECT

    public:
    ~OptContentModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole ) override;

    Qt::ItemFlags flags ( const QModelIndex & index ) const override;

    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;

    /**
     * Applies the Optional Content Changes specified by that link.
     * \since 0.50
     */
    void applyLink( LinkOCGState *link );

    private:
    OptContentModel( OCGs *optContent, QObject *parent = 0);

    friend class OptContentModelPrivate;
    OptContentModelPrivate *d;
  };
}

#endif
