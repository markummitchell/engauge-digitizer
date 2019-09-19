/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINES_H
#define GUIDELINES_H

#include "GuidelineState.h"
#include <QList>

class GuidelineAbstract;
class MainWindow;
class QGraphicsScene;
class Transformation;

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

  /// Factory method for creating a new Guideline
  GuidelineAbstract *createGuideline (GuidelineState stateInitial);

  /// Load the presupplied template guidelines at the four boundaries after the scene has been loaded
  void initialize (QGraphicsScene &scene,
                   bool guidelinesAreActive);

  /// Show/hide all guidelines. None are created or destroyed by this method
  void showHide (bool show);

  /// Return copy of transformation owned by MainWindow
  Transformation transformation () const;

  /// Update after a change to the transformation. Scene size is assumed to stay the same
  void update (bool guidelinesAreActive);

  /// Update guidelines as selectable or not. This is called on DigitizeState transitions
  void updateGuidelinesSelectability (bool selectable);

private:
  Guidelines();

  /// Add a new Guideline to the global list maintained by this class
  void registerGuideline (GuidelineAbstract *guideline);

  GuidelineContainerPrivate m_guidelineContainer; // Save for easy removal later

  MainWindow &m_mainWindow;
};

#endif // GUIDELINES_H
