#include "DlgValidatorAbstract.h"
#include "Logger.h"

DlgValidatorAbstract::DlgValidatorAbstract(QObject *parent) :
  QDoubleValidator(parent)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorAbstract::DlgValidatorAbstract";
}

DlgValidatorAbstract::~DlgValidatorAbstract()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorAbstract::~DlgValidatorAbstract";
}
