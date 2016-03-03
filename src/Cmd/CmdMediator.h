/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_MEDIATOR_H
#define CMD_MEDIATOR_H

#include "CoordsType.h"
#include "Document.h"
#include "DocumentAxesPointsRequired.h"
#include "PointStyle.h"
#include <QUndoStack>

class MainWindow;
class QImage;

/// Command queue stack.
/// This class lies between the Document and the rest of the application. This approach is attractive because the
/// command stack and Document are born together, work together, and deleted together. Also, wrapping this class
/// around Document helps to encapsulate Document that much more.
class CmdMediator : public QUndoStack
{
public:
  /// Constructor for imported images and dragged images. Only one coordinate system is created but others can be added later.
  CmdMediator (MainWindow &mainWindow,
               const QImage &image);

  /// Constructor for opened Documents and error report files. The specified xml file is opened and read.
  CmdMediator (MainWindow &mainWindow,
               const QString &fileName);

  /// Destructor
  ~CmdMediator();

  /// Provide the current CoordSystem to commands with read-only access, primarily for undo/redo processing.
  const CoordSystem &coordSystem () const;

  /// See Document::curveAxes
  const Curve &curveAxes () const;

  /// See CurvesGraphs::curvesGraphsNames.
  QStringList curvesGraphsNames () const;

  /// See CurvesGraphs::curvesGraphsNumPoints
  int curvesGraphsNumPoints (const QString &curveName) const;

  /// Provide the Document to commands, primarily for undo/redo processing.
  Document &document();

  /// Provide the Document to commands with read-only access, primarily for undo/redo processing.
  const Document &document () const;

  /// Dirty flag. Document is dirty if there are any unsaved changes. The dirty flag is pushed (rather than pulled from this method) through
  /// the QUndoStack::cleanChanged signal
  bool isModified () const;

  /// See Curve::iterateThroughCurvePoints, for the single axes curve.
  void iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);

  /// See Curve::iterateThroughCurvePoints, for the single axes curve.
  void iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const;

  /// See Curve::iterateThroughCurvePoints, for all the graphs curves.
  void iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback);

  /// See Document::pixmap.
  QPixmap pixmap () const;

  /// See Document::reasonForUnsuccessfulRead.
  QString reasonForUnsuccessfulRead () const;

  /// Serialize to xml
  void saveXml(QXmlStreamWriter &writer) const;

  /// Set the number of axes points required. This is called during the Document creation process, after imported images have
  /// been previewed or loaded files have had at least some xml parsing
  void setDocumentAxesPointsRequired (DocumentAxesPointsRequired documentAxesPointsRequired);

  /// Wrapper for Document::successfulRead
  bool successfulRead () const;

private:
  CmdMediator ();

  void connectSignals (MainWindow &mainWindow);

  Document m_document;

};

#endif // CMD_MEDIATOR_H
