#ifndef CMD_MEDIATOR_H
#define CMD_MEDIATOR_H

#include "CoordsType.h"
#include "Document.h"
#include "PointStyle.h"
#include <QUndoStack>
#include "SettingsCurves.h"

class QImage;
class Transformation;

/// Command queue stack.
/// This class lies between the Document and the rest of the application. This approach is attractive because the
/// command stack and Document are born together, work together, and deleted together. Also, wrapping this class
/// around Document helps to encapsulate Document that much more.
class CmdMediator : public QUndoStack
{
public:
  /// Constructor for imported images and dragged images.
  CmdMediator (const QImage &image);

  /// Constructor for opened Documents. The specified file is opened and read.
  CmdMediator (const QString &fileName);

  /// See CurvesGraphs::applyTransformation
  void applyTransformation (const Transformation &transformation);

  /// See Document::coordsType
  CoordsType coordsType () const;

  /// See CurvesGraphs::curvesGraphsNames.
  QStringList curvesGraphsNames () const;

  /// Provide the Document to commands, primarily for undo/redo processing.
  Document &document();

  /// See Document::isModified.
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

  /// See Document::settingsCurves.
  SettingsCurves settingsCurves () const;

  /// Wrapper for Document::successfulRead
  bool successfulRead () const;

private:
  CmdMediator ();

  Document m_document;
};

#endif // CMD_MEDIATOR_H
