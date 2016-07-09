/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef IMPORT_CROPPING_H
#define IMPORT_CROPPING_H

enum ImportCropping
{
  IMPORT_CROPPING_NEVER,
  IMPORT_CROPPING_MULTIPAGE_PDFS,
  IMPORT_CROPPING_ALWAYS,
  NUMBER_IMPORT_CROPPING
};

extern const ImportCropping DEFAULT_IMPORT_CROPPING;

#endif // IMPORT_CROPPING_H
