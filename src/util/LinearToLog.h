/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef LINEAR_TO_LOG_H
#define LINEAR_TO_LOG_H

/// Warps log coordinates to make them linear before passing them to code that accepts only linear coordinates. For
/// example, the Spline funtions are already complicated (third order polynomial interpolation) so upgrading them to
/// handle log coordinates in addition to linear coordinates would be painful to implement and debug
class LinearToLog
{
 public:
  LinearToLog();

  /// Convert linear coordinates to log. This is a noop if the output is supposed to be linear
  double delinearize (double value,
                      bool isLog) const;
  
  /// Convert log coordinates to linear. This is a noop if the input is already linear
  double linearize (double value,
                    bool isLog) const;

};

#endif // LINEAR_TO_LOG_H
