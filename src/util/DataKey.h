#ifndef DATA_KEY_H
#define DATA_KEY_H

#include <QString>

/// Index values for storing item details in QGraphicsItem using setData/data
enum DataKey {
  DATA_KEY_IDENTIFIER,           ///> Unique identifier for QGraphicsItem object
  DATA_KEY_GRAPHICS_ITEM_TYPE,   ///> Item type (i.e. image versus point)
  DATA_KEY_ORDINAL_LAST,         ///> Ordinal value of previous point. This and DATA_KEY_ORDINAL apply to a line since it has two points
  DATA_KEY_ORDINAL,              ///> Ordinal value for ordering points when drawing lines
  DATA_KEY_POSITION_HAS_CHANGED  ///> True if item has changed since last mousePressEvent
};

extern QString dataKeyToString (DataKey dataKey);

#endif // DATA_KEY_H
