#include "CmdMediator.h"
#include "Document.h"
#include "Logger.h"
#include "Point.h"
#include <QImage>
#include <QUndoCommand>
#include "Transformation.h"

CmdMediator::CmdMediator (const QImage &image) :
  m_document (image)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdMediator::CmdMediator";
}

CmdMediator::CmdMediator (const QString &fileName) :
  m_document (fileName)
{
}

void CmdMediator::applyTransformation (const Transformation &transformation)
{
  m_document.applyTransformation (transformation);
}

CoordsType CmdMediator::coordsType () const
{
  return m_document.coordsType();
}

const Curve &CmdMediator::curveAxes () const
{
  return m_document.curveAxes ();
}

QStringList CmdMediator::curvesGraphsNames () const
{
  return m_document.curvesGraphsNames();
}

int CmdMediator::curvesGraphsNumPoints (const QString &curveName) const
{
  return m_document.curvesGraphsNumPoints(curveName);
}

Document &CmdMediator::document()
{
  return m_document;
}

bool CmdMediator::isModified () const
{
  return m_document.isModified ();
}

void CmdMediator::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  m_document.iterateThroughCurvePointsAxes (ftorWithCallback);
}

void CmdMediator::iterateThroughCurvePointsAxes (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  m_document.iterateThroughCurvePointsAxes (ftorWithCallback);
}

void CmdMediator::iterateThroughCurvesPointsGraphs (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  return m_document.iterateThroughCurvesPointsGraphs (ftorWithCallback);
}

QPixmap CmdMediator::pixmap () const
{
  Q_ASSERT (m_document.successfulRead ());

  return m_document.pixmap ();
}

QString CmdMediator::reasonForUnsuccessfulRead () const
{
  return m_document.reasonForUnsuccessfulRead ();
}

bool CmdMediator::successfulRead () const
{
  return m_document.successfulRead();
}
