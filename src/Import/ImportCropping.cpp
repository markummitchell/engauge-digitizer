/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ImportCropping.h"
#include <QObject>

const QString IMPORT_CROPPING_NEVER_STRING (QObject::tr ("Never crop during import"));
const QString IMPORT_CROPPING_MULTIPAGE_PDFS_STRING (QObject::tr ("Crop during import only for multiple-page pdf files"));
const QString IMPORT_CROPPING_ALWAYS_STRING (QObject::tr ("Always crop during import"));

const ImportCropping DEFAULT_IMPORT_CROPPING = IMPORT_CROPPING_NEVER;

QString ImportCroppingToString (ImportCropping importCropping)
{

}
