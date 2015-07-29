#include "DlgValidatorDegreesMinutesSeconds.h"
#include "FormatDegreesMinutesSeconds.h"
#include "Logger.h"

DlgValidatorDegreesMinutesSeconds::DlgValidatorDegreesMinutesSeconds(CoordScale coordScale,
                                                                     QObject *parent) :
  DlgValidatorAbstract(parent),
  m_coordScale (coordScale)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorDegreesMinutesSeconds::DlgValidatorDegreesMinutesSeconds";
}

QValidator::State DlgValidatorDegreesMinutesSeconds::validate (QString &input,
                                                               int &pos) const
{
  FormatDegreesMinutesSeconds formatDegreesMinutesSeconds;
  bool success = false;
  formatDegreesMinutesSeconds.parseInput (input,
                                          success);

  QValidator::State state = (success ?
                               QValidator::Acceptable :
                               QValidator::Invalid);

  if (state != QValidator::Acceptable) {

    pos = 0; // Would be nice to set to a value that meant something

  }

  return state;
}
