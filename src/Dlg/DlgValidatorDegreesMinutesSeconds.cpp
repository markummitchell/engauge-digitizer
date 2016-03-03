/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgValidatorDegreesMinutesSeconds.h"
#include "FormatDegreesMinutesSecondsBase.h"
#include "Logger.h"

DlgValidatorDegreesMinutesSeconds::DlgValidatorDegreesMinutesSeconds(CoordScale coordScale,
                                                                     QObject *parent) :
  DlgValidatorAbstract(parent),
  m_coordScale (coordScale)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorDegreesMinutesSeconds::DlgValidatorDegreesMinutesSeconds";
}

QValidator::State DlgValidatorDegreesMinutesSeconds::validate (QString &input,
                                                               int & /* pos */) const
{
  FormatDegreesMinutesSecondsBase formatDegreesMinutesSeconds;

  double value;
  return formatDegreesMinutesSeconds.parseInput (input,
                                                 value);
}
