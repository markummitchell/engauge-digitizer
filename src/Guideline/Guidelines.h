/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINES_H
#define GUIDELINES_H

#include "ColorPalette.h"
#include "CoordsType.h"
#include "GuidelineState.h"
#include <QList>
#include <QString>
#include "Transformation.h"

class DocumentModelCoords;
class GuidelineAbstract;
class MainWindow;
class QGraphicsScene;

typedef QList<GuidelineAbstract*> GuidelineContainerPrivate;

/// This class contains all Guideline objects
class Guidelines
{
public:
  /// Single constructor.
  Guidelines(MainWindow &mainWindow);
  ~Guidelines();

  /// Remove guidelines since the current Document is about to be closed
  void clear ();

  /// Color to be used for guidelines
  ColorPalette color () const;

  /// Return cartesian or polar
  CoordsType coordsType () const;

  /// Factory method for creating a new Guideline
  GuidelineAbstract *createGuideline (GuidelineState stateInitial);

  /// DigitizeState change so active status may (or may not) be toggled 
  void handleActiveChange (bool active);
  
  /// User toggled guideline visibility
  void handleVisibleChange (bool visible);

  /// Load the presupplied template guidelines at the four boundaries after the scene has been loaded.
  /// We do not set the initial state as a function of external conditions since during loading those
  /// conditions are not predictable
  void initialize (QGraphicsScene &scene);

  /// States listed as a string for debugging only
  QString stateDump () const;

  /// Return copy of transformation owned by MainWindow
  Transformation transformation () const;

  /// Force a color update
  void updateColor ();

  /// Update transformation. This is called after a command has been executed
  void updateWithLatestTransformation ();

private:
  Guidelines();

  /// Add a new Guideline to the global list maintained by this class
  void registerGuideline (GuidelineAbstract *guideline);

  GuidelineContainerPrivate m_guidelineContainer; // Save for easy removal later

  MainWindow &m_mainWindow;
};

#endif // GUIDELINES_H
