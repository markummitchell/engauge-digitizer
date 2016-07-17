/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H

#include "CmdMediator.h"
#include "GraphicsLinesForCurves.h"
#include <QGraphicsScene>
#include <QStringList>

class CmdMediator;
class Curve;
class CurvesGraphs;
class CurveStyles;
class GeometryWindow;
class GraphicsPoint;
class MainWindow;
class PointStyle;
class QTextStream;
class Transformation;

/// Add point and line handling to generic QGraphicsScene. The primary tasks are:
/// -# update the graphics items to stay in sync with the explicit Points in the Document
/// -# update the graphics items to stay in sync with the implicit lines between the Points, according to Document settings
///
/// This class stores points and lines as QGraphicsItems, but also maintains identifier-to-QGraphicsItems mappings to
/// the points and lines are accessible for updates (like when dragging points around and we need to update the attached lines).
class GraphicsScene : public QGraphicsScene
{
public:
  /// Single constructor.
  GraphicsScene(MainWindow *mainWindow);

  /// Add one temporary point to m_graphicsLinesForCurves. Non-temporary points are handled by the updateLineMembership functions
  void addTemporaryPoint (const QString &identifier,
                          GraphicsPoint *point);

  /// Create one QGraphicsItem-based object that represents one Point. It is NOT added to m_graphicsLinesForCurves (see addPoint)
  GraphicsPoint *createPoint (const QString &identifier,
                              const PointStyle &pointStyle,
                              const QPointF &posScreen,
                              GeometryWindow *geometryWindow);

  /// Hide all graphics items, except background image, in preparation for preview during IMPORT_TYPE_ADVANCED
  void hideAllItemsExceptImage();

  /// Return a list of identifiers for the points that have moved since the last call to resetPositionHasChanged.
  QStringList positionHasChangedPointIdentifiers () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str);

  /// Remove specified point. This aborts if the point does not exist
  void removePoint (const QString &identifier);

  /// Remove temporary point if it exists. Temporary point handling is so complicated that this method quietly
  /// allows redundant calls to this method, without complaining that the point has already been removed when called again
  void removeTemporaryPointIfExists ();

  /// Reset, when loading a document after the first, to same state that first document was at when loaded
  void resetOnLoad();

  /// Reset positionHasChanged flag for all items. Typically this is done as part of mousePressEvent.
  void resetPositionHasChangedFlags();

  /// Show or hide all Curves (if showAll is true) or just the selected Curve (if showAll is false);
  void showCurves (bool show,
                   bool showAll = false,
                   const QString &curveName = "");

  /// Update the Points and their Curves after executing a command. After a mouse drag, the lines are already updated and
  /// updating would be done on out of date information (since that would be brought up to date by the NEXT command)
  void updateAfterCommand (CmdMediator &cmdMediator,
                           double highlightOpacity,
                           GeometryWindow *geometryWindow);

  /// Update curve styles after settings changed.
  void updateCurveStyles(const CurveStyles &modelCurveStyles);

  /// A mouse move has just occurred so move the selected points, since they were dragged. The transformation is needed
  /// so the screen coordinates can be converted to graph coordinates when updating point ordinals
  void updateGraphicsLinesToMatchGraphicsPoints (const CurveStyles &modelCurveStyles,
                                                 const Transformation &transformation);

private:

  /// Dump all important cursors
  QString dumpCursors () const;

  const QGraphicsPixmapItem *image () const;

  /// Remove expired curves and add new curves
  void updateCurves (CmdMediator &cmdMediator);

  /// Update Points using a multi-pass algorithm.
  void updatePointMembership (CmdMediator &cmdMediator,
                              GeometryWindow *geometryWindow);

  /// Curve name to GraphicsLinesForCurve
  GraphicsLinesForCurves m_graphicsLinesForCurves;
};

#endif // GRAPHICS_SCENE_H
