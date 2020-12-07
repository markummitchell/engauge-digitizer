/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_STATE_BUILD_POLAR_H
#define CENTIPEDE_STATE_BUILD_POLAR_H

#include "CentipedeStateAbstractBase.h"

class CentipedePairPolar;

/// Class for period while building polar centipedes
class CentipedeStateBuildPolar : public CentipedeStateAbstractBase
{
public:
  /// Single constructor
  CentipedeStateBuildPolar(CentipedeStateContext &context);
  virtual ~CentipedeStateBuildPolar ();

  virtual void begin();
  virtual void end();
  virtual void handleKeyPress (Qt::Key key,
                               bool atLeastOneSelectedItem);
  virtual void handleMouseMove (QPointF posScreen);
  virtual void handleMousePress (QPointF posScreen);
  virtual void handleMouseRelease (QPointF posScreen);  

private:
  CentipedeStateBuildPolar();

  CentipedePairPolar *m_centipedePair;
};

#endif // CENTIPEDE_STATE_BUILD_POLAR_H
