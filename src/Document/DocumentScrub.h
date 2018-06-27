/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_SCRUB_H
#define DOCUMENT_SCRUB_H

class Document;
class MainWindow;

/// Check Document state. Primary reason is for catching when point identifiers get corrupted due,
/// possibly, to mixed language alphabets
class DocumentScrub
{
public:
  /// Single constructor
  DocumentScrub ();

  /// Check document state
  void check (MainWindow &mainWindow,
              const Document &document) const;

private:

};

#endif // DOCUMENT_SCRUB_H
