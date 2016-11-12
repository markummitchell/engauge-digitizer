/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FITTING_MODEL_H
#define FITTING_MODEL_H

#include <QString>
#include "WindowModelBase.h"

/// Model for FittingWindow
class FittingModel : public WindowModelBase
{
public:
  /// Single constructor
  FittingModel ();
  virtual ~FittingModel ();

  /// Override for special processing
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:

};

#endif // FITTING_MODEL_H
