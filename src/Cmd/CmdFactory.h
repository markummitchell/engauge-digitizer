#ifndef CMD_FACTORY_H
#define CMD_FACTORY_H

class CmdAbstract;
class Document;
class MainWindow;
class QXmlStreamReader;

/// Factory for CmdAbstractBase objects
class CmdFactory
{
public:
  /// Single constructor
  CmdFactory ();

  /// Factory method. Input is the xml node from an error report file
  CmdAbstract *createCmd (MainWindow &mainWindow,
                          Document &document,
                          QXmlStreamReader &reader);

};

#endif // CMD_FACTORY_H
