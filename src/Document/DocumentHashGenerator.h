/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_HASH_GENERATOR_H
#define DOCUMENT_HASH_GENERATOR_H

#include "DocumentHash.h"

class Document;

/// Generates a DocumentHash value representing the state of the entire Document
class DocumentHashGenerator
{
 public:
  /// Single constructor
  DocumentHashGenerator ();

  /// Generate the hash for external storage
  DocumentHash generate (const Document &document) const;

};

#endif // DOCUMENT_HASH_GENERATOR_H
