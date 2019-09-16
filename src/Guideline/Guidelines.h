/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINES_H
#define GUIDELINES_H

class QGraphicsScene;
class Guideline;

/// This class contains all Guideline objects
class Guidelines
{
public:
  /// Single constructor.
  Guidelines();
  ~Guidelines();

  /// Remove guidelines since the current Document is about to be closed
  void clear ();

  /// Load the presupplied template guidelines at the four boundaries after the scene has been loaded
  void initialize (QGraphicsScene &scene);

  /// Show/hide all guidelines. None are created or destroyed by this method
  void showHide (bool show);

  /// Update after a change to the transformation. Scene size is assumed to stay the same
  void update ();

private:

  Guideline *m_guidelinePresuppliedLeft;
  Guideline *m_guidelinePresuppliedRight;
  Guideline *m_guidelinePresuppliedTop;
  Guideline *m_guidelinePresuppliedBottom;

};

#endif // GUIDELINES_H
