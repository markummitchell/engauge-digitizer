/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"

QString dataKeyToString (DataKey dataKey)
{
  switch (dataKey) {

  case DATA_KEY_IDENTIFIER:
    return "DATA_KEY_IDENTIFIER";
    break;

  case DATA_KEY_GRAPHICS_ITEM_TYPE:
    return "DATA_KEY_GRAPHICS_ITEM_TYPE";
    break;

  case DATA_KEY_POSITION_HAS_CHANGED:
    return "DATA_KEY_POSITION_HAS_CHANGED";
    break;

  default:
    return "<unknown>";
  }
}
