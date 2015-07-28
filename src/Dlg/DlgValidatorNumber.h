#ifndef DLG_VALIDATOR_NUMBER_H
#define DLG_VALIDATOR_NUMBER_H

#include "CoordScale.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsPolarTheta.h"
#include "DlgValidatorAbstract.h"

/// Validator for generic (=simple) numbers
class DlgValidatorNumber : public DlgValidatorAbstract
{
public:
  /// Single constructor
  DlgValidatorNumber(CoordScale coordScale,
                     QObject *parent = 0);

  /// Apply the standard validation with 0 as the exclusive minimum. Call setCoordScale just before calling this method
  virtual QValidator::State validate (QString &input,
                                      int &pos) const;

private:
  DlgValidatorNumber();

  const CoordScale m_coordScale;

};

#endif // DLG_VALIDATOR_NUMBER_H
