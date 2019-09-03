/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_H
#define GUIDELINE_H

#include <QGraphicsLineItem>

class QGraphicsScene;

/// This class is a special case of the standard QGraphicsLineItem for guidelines.
class Guideline : public QObject, public QGraphicsLineItem
{
  Q_OBJECT;

public:
  /// Single constructor.
  Guideline(QGraphicsScene &scene);
  ~Guideline();

  /// Highlight this Guideline upon hover enter
  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

  /// Unset highlighting triggered by hover enter
  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

  /// Displayed line width of presupplied guidelines
  static double linewidthPresupplied ();

  /// Apply/remove highlighting triggered by hover enter/leave
  void setHover (bool hover);

private:
  Guideline();

};

#endif // GUIDELINE_H
