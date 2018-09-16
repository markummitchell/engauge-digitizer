/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CREATE_LOAD_IMAGE_H
#define CREATE_LOAD_IMAGE_H

#include <QObject>

class MainWindow;

/// Class to create LoadImageFromUrl for MainWindow class. This is derived from QObject 
/// so the tr function can be accessed more easily
class CreateLoadImage : public QObject
{
public:
  /// Single constructor.
  CreateLoadImage();

  /// Create LoadImageFromUrl instance
  void create (MainWindow &mw);

};

#endif // CREATE_LOAD_IMAGE_H
