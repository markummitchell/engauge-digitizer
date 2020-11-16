/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ButtonWhatsThis.h"
#include <QStyleOptionButton>

ButtonWhatsThis::ButtonWhatsThis (QWidget *parent) :
  QPushButton ("?", parent)
{
  auto textSize = fontMetrics().size (Qt::TextShowMnemonic,
                                      text());
  QStyleOptionButton opt;
  opt.initFrom (this);
  opt.rect.setSize (textSize);
  setMinimumSize (style()->sizeFromContents (QStyle::CT_PushButton,
                                             &opt,
                                             textSize,
                                             this));
  setMaximumSize (style()->sizeFromContents (QStyle::CT_PushButton,
                                             &opt,
                                             textSize,
                                             this));
}
