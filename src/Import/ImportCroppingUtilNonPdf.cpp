/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ImportCroppingUtilNonPdf.h"
#include <QSettings>
#include "Settings.h"

ImportCroppingUtilNonPdf::ImportCroppingUtilNonPdf()
{
}

bool ImportCroppingUtilNonPdf::applyImportCropping (bool isRegression) const
{
  bool cropping = true;

  if (!isRegression) {

    QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
    settings.beginGroup (SETTINGS_GROUP_MAIN_WINDOW);

    ImportCropping importCroppingInput = (ImportCropping) settings.value (SETTINGS_IMPORT_CROPPING,
                                                                          QVariant (DEFAULT_IMPORT_CROPPING)).toInt();

    cropping = (importCroppingInput == IMPORT_CROPPING_ALWAYS);
  }

  return cropping;
}
