/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_DELIMITER_H
#define EXPORT_DELIMITER_H

#include <QString>

/// Delimiter values that may or may not be overridden by DOCUMENT_SERIALIZE_EXPORT_DELIMITER_OVERRIDE_CSV_TSV
/// for CSV and TSV files
enum ExportDelimiter {
  EXPORT_DELIMITER_COMMA,
  EXPORT_DELIMITER_SPACE,
  EXPORT_DELIMITER_TAB
};

extern QString exportDelimiterToString (ExportDelimiter exportDelimiter); // Text appearing in logging/debugging
extern QString exportDelimiterToText (ExportDelimiter exportDelimiter); // Text appearing in exported file

#endif // EXPORT_DELIMITER_H
