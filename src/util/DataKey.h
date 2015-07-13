#ifndef DATA_KEY_H
#define DATA_KEY_H

#include <QString>

/// Index values for storing item details in QGraphicsItem using setData/data
enum DataKey {
  DATA_KEY_IDENTIFIER,           ///> Unique identifier for QGraphicsItem object
  DATA_KEY_GRAPHICS_ITEM_TYPE,   ///> Item type (i.e. image versus point)
  DATA_KEY_POSITION_HAS_CHANGED  ///> True if item has changed since last mousePressEvent
};

extern QString dataKeyToString (DataKey dataKey);

#endif // DATA_KEY_H
