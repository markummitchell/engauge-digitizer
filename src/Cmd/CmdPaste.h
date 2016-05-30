/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_PASTE_H
#define CMD_PASTE_H

#include "CmdPointChangeBase.h"
#include "MimePoints.h"
#include "PointIdentifiers.h"
#include <QStringList>

class QXmlStreamReader;

/// Command for moving all selected Points by a specified translation.
class CmdPaste : public CmdPointChangeBase
{
public:
  /// Constructor for normal creation
  CmdPaste(MainWindow &mainWindow,
           Document &document,
           const QStringList &selectedPointIdentifiers);

  /// Constructor for parsing error report file xml
  CmdPaste(MainWindow &mainWindow,
           Document &document,
           const QString &cmdDescription,
           QXmlStreamReader &reader);

  virtual ~CmdPaste();

  virtual void cmdRedo ();
  virtual void cmdUndo (); 
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdPaste();

  PointIdentifiers m_copiedPoints;
  MimePoints m_mimePoints;
};

#endif // CMD_PASTE_H
