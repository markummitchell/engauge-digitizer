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
