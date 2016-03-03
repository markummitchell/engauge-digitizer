/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DATA_KEY_H
#define DATA_KEY_H

#include <QString>

/// Index values for storing item details in QGraphicsItem using setData/data
enum DataKey {
  DATA_KEY_IDENTIFIER,           ///> Unique identifier for QGraphicsItem object
  DATA_KEY_GRAPHICS_ITEM_TYPE,   ///> Item type (i.e. image versus point)
  DATA_KEY_POSITION_HAS_CHANGED, ///> True if item has changed since last mousePressEvent
  DATA_KEY_GHOST                 ///> True if item is a temporary ghost. False or undefined otherwise
};

extern QString dataKeyToString (DataKey dataKey);

#endif // DATA_KEY_H
