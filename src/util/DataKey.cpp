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

  case DATA_KEY_ORDINAL_LAST:
    return "DATA_KEY_ORDINAL_LAST";
    break;

  case DATA_KEY_ORDINAL:
    return "DATA_KEY_ORDINAL";
    break;

  case DATA_KEY_POSITION_HAS_CHANGED:
    return "DATA_KEY_POSITION_HAS_CHANGED";
    break;

  default:
    return "<unknown>";
  }
}
