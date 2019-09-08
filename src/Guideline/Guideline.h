/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_H
#define GUIDELINE_H

#include "GuidelineStateContext.h"
#include <QGraphicsLineItem>

class QGraphicsScene;

/// This class is a special case of the standard QGraphicsLineItem for guidelines,
/// and serves as the base class for the guideline state classes. This class has
/// a state machine to handle the different states
class Guideline : public QObject, public QGraphicsLineItem
{
  Q_OBJECT;

public:
  /// Single constructor.
  Guideline(QGraphicsScene &scene,
            GuidelineState guidelineStateInitial);
  ~Guideline();

  /// Highlight this Guideline upon hover enter
  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

  /// Unset highlighting triggered by hover enter
  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

  /// Displayed line width of template guidelines
  double lineWidthTemplate () const;

  /// Cleanup after being dragged
  virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);

  /// Apply/remove highlighting triggered by hover enter/leave
  void setHover (bool hover);
  
private:
  Guideline();

  GuidelineStateContext m_context;
};

#endif // GUIDELINE_H
