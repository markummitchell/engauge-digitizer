#ifndef CMD_DIGITIZE_STATE_NEXT_H
#define CMD_DIGITIZE_STATE_NEXT_H

#include "CmdAbstract.h"

class QXmlStreamReader;

/// Command for jumping to the next state in the DigitizeState enum.
/// This is a debu command since it is not meant to be called by normal users, and instead
/// is only called with an obscure keyboard shortcut (when setting up a regression test)
class CmdDigitizeStateNext : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdDigitizeStateNext(MainWindow &mainWindow,
                       Document &document);

  /// Constructor for parsing error report file xml
  CmdDigitizeStateNext(MainWindow &mainWindow,
                       Document &document,
                       const QString &cmdDescription,
                       QXmlStreamReader &reader);

  virtual ~CmdDigitizeStateNext();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdDigitizeStateNext();
};

#endif // CMD_DIGITIZE_STATE_NEXT_H
