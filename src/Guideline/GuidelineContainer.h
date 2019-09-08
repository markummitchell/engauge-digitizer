/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_CONTAINER_H
#define GUIDELINE_CONTAINER_H

#include <QList>

class QGraphicsScene;
class Guideline;

typedef QList<Guideline*> GuidelineContainerPrivate;

/// This class contains all Guideline objects
class GuidelineContainer
{
public:
  /// Single constructor.
  GuidelineContainer();
  ~GuidelineContainer();

  /// Update the presupplied guidelines at the four boundaries after the scene has (potentially or not)
  /// been resized
  void updateGuidelines (QGraphicsScene &scene);

private:

  Guideline *m_guidelinePresuppliedLeft;
  Guideline *m_guidelinePresuppliedRight;
  Guideline *m_guidelinePresuppliedTop;
  Guideline *m_guidelinePresuppliedBottom;
  GuidelineContainerPrivate m_containerClones; // Guidelines created by user dragging a presupplied guideline
};

#endif // GUIDELINE_CONTAINER_H
