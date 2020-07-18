/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "InactiveOpacity.h"
#include <QHash>

static QHash<InactiveOpacity, int> inactiveOpacityValueLookupTable;
static QHash<InactiveOpacity, QString> inactiveOpacityQStringLookupTable;

int inactiveOpacityEnumToAlpha (InactiveOpacity inactiveOpacity)
{
  if (inactiveOpacityValueLookupTable.size () == 0) {

    // Initialize
    inactiveOpacityValueLookupTable [INACTIVE_OPACITY_0] = 0;
    inactiveOpacityValueLookupTable [INACTIVE_OPACITY_32] = 32;
    inactiveOpacityValueLookupTable [INACTIVE_OPACITY_64] = 64;
    inactiveOpacityValueLookupTable [INACTIVE_OPACITY_96]  = 96;
    inactiveOpacityValueLookupTable [INACTIVE_OPACITY_128] = 128;
    inactiveOpacityValueLookupTable [INACTIVE_OPACITY_160] = 160;
    inactiveOpacityValueLookupTable [INACTIVE_OPACITY_192] = 192;
    inactiveOpacityValueLookupTable [INACTIVE_OPACITY_224] = 224;
    inactiveOpacityValueLookupTable [INACTIVE_OPACITY_256] = 255;
  }

  if (inactiveOpacityValueLookupTable.contains (inactiveOpacity)) {

    return inactiveOpacityValueLookupTable [inactiveOpacity];

  } else {

    return inactiveOpacityValueLookupTable [DEFAULT_INACTIVE_OPACITY_ENUM];

  }
}

QString inactiveOpacityEnumToQString (InactiveOpacity inactiveOpacity)
{
  if (inactiveOpacityQStringLookupTable.size () == 0) {

    // Initialize
    inactiveOpacityQStringLookupTable [INACTIVE_OPACITY_0] = "0";
    inactiveOpacityQStringLookupTable [INACTIVE_OPACITY_32] = "32";
    inactiveOpacityQStringLookupTable [INACTIVE_OPACITY_64] = "64";
    inactiveOpacityQStringLookupTable [INACTIVE_OPACITY_96]  = "96";
    inactiveOpacityQStringLookupTable [INACTIVE_OPACITY_128] = "128";
    inactiveOpacityQStringLookupTable [INACTIVE_OPACITY_160] = "160";
    inactiveOpacityQStringLookupTable [INACTIVE_OPACITY_192] = "192";
    inactiveOpacityQStringLookupTable [INACTIVE_OPACITY_224] = "224";
    inactiveOpacityQStringLookupTable [INACTIVE_OPACITY_256] = "256";
  }

  if (inactiveOpacityQStringLookupTable.contains (inactiveOpacity)) {

    return inactiveOpacityQStringLookupTable [inactiveOpacity];

  } else {

    return inactiveOpacityQStringLookupTable [DEFAULT_INACTIVE_OPACITY_ENUM];

  }
}
