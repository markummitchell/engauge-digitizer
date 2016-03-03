/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef ZOOM_FACTOR_INITIAL_H
#define ZOOM_FACTOR_INITIAL_H

enum ZoomFactorInitial {
  ZOOM_INITIAL_16_TO_1,
  ZOOM_INITIAL_8_TO_1,
  ZOOM_INITIAL_4_TO_1,
  ZOOM_INITIAL_2_TO_1,
  ZOOM_INITIAL_1_TO_1,
  ZOOM_INITIAL_1_TO_2,
  ZOOM_INITIAL_1_TO_4,
  ZOOM_INITIAL_1_TO_8,
  ZOOM_INITIAL_1_TO_16,
  ZOOM_INITIAL_FILL,
  ZOOM_INITIAL_PREVIOUS
};

// ZOOM_INITIAL_PREVIOUS is default according to the principle of least surprises for the user interface.
const ZoomFactorInitial DEFAULT_ZOOM_FACTOR_INITIAL = ZOOM_INITIAL_PREVIOUS;

#endif // ZOOM_FACTOR_INITIAL_H
