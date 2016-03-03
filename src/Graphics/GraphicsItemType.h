/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_ITEM_TYPE_H
#define GRAPHICS_ITEM_TYPE_H

/// Runtime type identification (RTTI) for QGraphicsItem objects.
enum GraphicsItemType {
  GRAPHICS_ITEM_TYPE_IMAGE,
  GRAPHICS_ITEM_TYPE_LINE,
  GRAPHICS_ITEM_TYPE_POINT,
  GRAPHICS_ITEM_TYPE_SEGMENT
};

#endif // GRAPHICS_ITEM_TYPE_H
