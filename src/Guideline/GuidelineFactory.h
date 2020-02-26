/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_FACTORY_H
#define GUIDELINE_FACTORY_H

#include "Guidelines.h"
#include "GuidelineState.h"
#include <QMap>

class GraphicsScene;
class GuidelineAbstract;
class Guidelines;
class MainWindow;
class QGraphicsScene;

typedef QMap<GuidelineState, QGraphicsScene*> MapStateToScene;
typedef QMap<GuidelineState, bool> MapStatesWithEllipse;

/// Factory for generating Guideline objects. The complications are:
/// -# Some guidelines are lines (GuidelineLine) and some are ellipses (GuidelineEllipse)
/// -# Guidelines are either horizontal (X or theta T) or vertical (Y or range R)
class GuidelineFactory
{
public:
  /// Single constructor.
  GuidelineFactory (GraphicsScene *sceneMain);
  virtual ~GuidelineFactory();

  GuidelineAbstract *createGuideline (Guidelines &guidelines,
                                      GuidelineState stateInitial,
                                      MainWindow &mainWindow,
                                      const QString &identifier);
  
private:
  GuidelineFactory ();

  void createEllipseMap ();

  GraphicsScene *m_sceneMain;

  MapStatesWithEllipse m_mapStatesWithEllipse;
};

#endif // GUIDELINE_FACTORY_H
