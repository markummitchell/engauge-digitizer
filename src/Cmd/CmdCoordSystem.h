#ifndef CMD_COORD_SYSTEM_H
#define CMD_COORD_SYSTEM_H

#include "CmdAbstract.h"

class QXmlStreamReader;

/// Command for changing the currently selected CoordSystem
class CmdCoordSystem : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdCoordSystem(MainWindow &mainWindow,
                 Document &document);

  /// Constructor for parsing error report file xml
  CmdCoordSystem(MainWindow &mainWindow,
                 Document &document,
                 const QString &cmdDescription,
                 QXmlStreamReader &reader);
  
  virtual ~CmdCoordSystem();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdCoordSystem();

  int m_coordSystemBefore;
  int m_coordSystemAfter;
};

#endif // CMD_COORD_SYSTEM_H
