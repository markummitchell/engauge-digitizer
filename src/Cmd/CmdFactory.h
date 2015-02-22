#ifndef CMD_FACTORY_H
#define CMD_FACTORY_H

class CmdAbstractBase;
class QDomNode;

/// Factory for CmdAbstractBase objects
class CmdFactory
{
public:
  /// Single constructor
  CmdFactory ();

  /// Factory method. Input is the xml node from an error report file
  CmdAbstractBase *createCmd (const QDomNode &nodeCmd);

};

#endif // CMD_FACTORY_H
