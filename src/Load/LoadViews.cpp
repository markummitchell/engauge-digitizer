/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Centipeder, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "LoadViews.h"
#include <QHash>

typedef QHash<LoadViews, QString> LoadViewsHash;

static LoadViewsHash loadViewsHash;

QString loadViewsAsString (LoadViews loadViews)
{
  if (loadViewsHash.size () == 0) {

    // First time through we load the hash
    loadViewsHash [LOAD_VIEWS_KEEP_CURRENT] = "LoadViewsKeepCurrent";
    loadViewsHash [LOAD_VIEWS_USE_DOCUMENT] = "LoadViewsUseDocument";
  }

  if (loadViewsHash.contains (loadViews)) {
    return loadViewsHash [loadViews];
  } else {
    return "?";
  }
}
