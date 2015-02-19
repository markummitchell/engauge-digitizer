#ifndef CMD_PASTE_H
#define CMD_PASTE_H

#include "CmdAbstract.h"
#include "MimePoints.h"
#include <QHash>
#include <QStringList>

typedef QHash<QString, bool> PointIdentifiers;

/// Command for moving all selected Points by a specified translation.
class CmdPaste : public CmdAbstract
{
public:
  /// Single constructor.
  CmdPaste(MainWindow &mainWindow,
           Document &document,
           const QStringList &selectedPointIdentifiers);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdPaste();

  PointIdentifiers m_copiedPoints;
  MimePoints m_mimePoints;
};

#endif // CMD_PASTE_H
