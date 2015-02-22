#ifndef CMD_PASTE_H
#define CMD_PASTE_H

#include "CmdAbstract.h"
#include "MimePoints.h"
#include "PointIdentifiers.h"
#include <QStringList>

class QXmlStreamReader;

/// Command for moving all selected Points by a specified translation.
class CmdPaste : public CmdAbstract
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
