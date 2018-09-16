/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CREATE_ICONS_H
#define CREATE_ICONS_H

#include <QObject>

class MainWindow;

/// Class to create icons for MainWindow class. This is derived from QObject
/// so the tr function can be accessed more easily
class CreateIcons : public QObject
{
public:
  /// Single constructor.
  CreateIcons();

  /// Create QIcon items
  void create (MainWindow &mw);

};

#endif // CREATE_ICONS_H
