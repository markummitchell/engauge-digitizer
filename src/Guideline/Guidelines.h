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

class DocumentModelGuidelines;
class GraphicsScene;
class GuidelineAbstract;
class GuidelineFactory;
class MainWindow;
class QGraphicsScene;

typedef QList<GuidelineAbstract*> GuidelineContainerPrivate;

/// This class contains all Guideline objects
class Guidelines
{
  /// For unit testing
  friend class TestGuidelines;

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
  GuidelineAbstract *createGuideline (const QString &identifier,
                                      GuidelineState stateInitial);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE
  void createGuidelineR (const QString &identifier,
                         double r);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE
  void createGuidelineR (const QString &identifier,
                         const QPointF &posScreen);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE
  void createGuidelineT (const QString &identifier,
                         double t);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE
  void createGuidelineT (const QString &identifier,
                         const QPointF &posScreen);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE
  void createGuidelineX (const QString &identifier,
                         double x);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE
  void createGuidelineX (const QString &identifier,
                         const QPointF &posScreen);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE
  void createGuidelineY (const QString &identifier,
                         double y);

  /// Factory method for creating a new GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE
  void createGuidelineY (const QString &identifier,
                         const QPointF &posScreen);

  /// Factory method for creating a new replacement Guideline, which replaces one
  /// handle and one visible Guideline after a drag
  void createReplacementGuideline (const QString &identifierReplaced,
                                   double newValue,
                                   GuidelineState guidelineStateForReplacement);

  /// DigitizeState change so active status may (or may not) be toggled 
  void handleActiveChange (bool active);

  /// User toggled guideline mode
  void handleGuidelineMode (bool visible,
                            bool locked);

  /// Initialize Guideline factory
  void initialize (GraphicsScene &scene);

  /// Return complete set of guidelines information for Document
  DocumentModelGuidelines modelGuidelines () const;

  /// Move an X/T guideline from one value to another. Closest value wins
  void moveGuidelineXT (const QString &identifier,
                        double valueAfter);

  /// Move an Y/R guideline from one value to another. Closest value wins
  void moveGuidelineYR (const QString &identifier,
                        double valueAfter);

  /// Remove an X/T or Y/R guideline. Since Guideline identifiers are unique this
  /// method is not implemented with separate X/T and Y/R versions
  void removeGuideline (const QString &identifier);

  /// Load Guidelines from Document
  void setModelGuidelines (CoordsType coordsType,
                           const DocumentModelGuidelines &modelGuidelines);

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

  GuidelineContainerPrivate::iterator findIdentifierXT (const QString &identifier);
  GuidelineContainerPrivate::iterator findIdentifierYR (const QString &identifier);

  /// Return read-only reference to X/T and Y/R containers for testing only
  const GuidelineContainerPrivate &guidelineContainerPrivateXT () const;
  const GuidelineContainerPrivate &guidelineContainerPrivateYR () const;

  /// Add a new Guideline to the global list maintained by this class
  void registerGuidelineXT (GuidelineAbstract *guideline);
  void registerGuidelineYR (GuidelineAbstract *guideline);

  GuidelineAbstract *unregisterGuideline (const QString &identifier);

  // Save for easy removal later
  GuidelineContainerPrivate m_guidelineContainerXT;
  GuidelineContainerPrivate m_guidelineContainerYR;

  MainWindow &m_mainWindow;

  GuidelineFactory *m_guidelineFactory;
};

#endif // GUIDELINES_H
