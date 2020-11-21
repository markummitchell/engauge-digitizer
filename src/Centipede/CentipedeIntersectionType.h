/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_INTERSECTION_TYPE_H
#define CENTIPEDE_INTERSECTION_TYPE_H

/// Intersect with one of the following XT or YT coordinates for constant YR or XT respectively
enum CentipedeIntersectionType {
  CENTIPEDE_INTERSECTION_LOW,    /// Intersection along circle perimeter with lowest value of XT or YR
  CENTIPEDE_INTERSECTION_HIGH    /// Intersection along circle perimeter with highest value of XT or YR
};

#endif // CENTIPEDE_INTERSECTION_TYPE_H
