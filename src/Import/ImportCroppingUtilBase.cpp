/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "ImportCroppingUtilBase.h"
#include <QHash>
#include <QObject>

const ImportCropping DEFAULT_IMPORT_CROPPING = IMPORT_CROPPING_NEVER; // Traditional, and simplest, option

ImportCroppingUtilBase::ImportCroppingUtilBase()
{
}

QString ImportCroppingUtilBase::importCroppingToString (ImportCropping importCropping)
{
  QHash<ImportCropping, QString> lookupTable;

  lookupTable.insert (IMPORT_CROPPING_NEVER, QObject::tr ("No cropping"));
  lookupTable.insert (IMPORT_CROPPING_MULTIPAGE_PDFS, QObject::tr ("Crop pdf files with multiple pages"));
  lookupTable.insert (IMPORT_CROPPING_ALWAYS, QObject::tr ("Always crop"));

  ENGAUGE_ASSERT (lookupTable.count() == NUMBER_IMPORT_CROPPING);

  QString rtn;

  if (lookupTable.contains (importCropping)) {
    rtn = lookupTable [importCropping];
  }

  return rtn;
}
