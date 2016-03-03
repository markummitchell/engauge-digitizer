/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
