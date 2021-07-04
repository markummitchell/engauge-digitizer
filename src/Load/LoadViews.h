/******************************************************************************************************
 * (C) 2021 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef LOAD_VIEWS_H
#define LOAD_VIEWS_H

#include <QString>

/// Options for loading view states
enum LoadViews {
  LOAD_VIEWS_KEEP_CURRENT,
  LOAD_VIEWS_USE_DOCUMENT
};

extern QString loadViewsAsString (LoadViews loadViews);

#endif // LOAD_VIEWS__H
