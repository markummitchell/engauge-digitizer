#include "CmdAbstract.h"
#include "CmdMediator.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Point.h"
#include <QImage>
#include <QUndoCommand>
#include <QXmlStreamWriter>
#include "Transformation.h"

CmdMediator::CmdMediator (MainWindow &mainWindow,
                          const QImage &image) :
  m_document (image)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdMediator::CmdMediator image=" << image.width() << "x" << image.height ();

  connectSignals(mainWindow);
}

CmdMediator::CmdMediator (MainWindow &mainWindow,
                          const QString &fileName) :
  m_document (fileName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdMediator::CmdMediator filename=" << fileName.toLatin1().data();

  connectSignals(mainWindow);
}

void CmdMediator::applyTransformation (const Transformation &transformation)
{
  m_document.applyTransformation (transformation);
}

void CmdMediator::connectSignals (MainWindow &mainWindow)
{
  connect (this, SIGNAL (cleanChanged (bool)), &mainWindow, SLOT (slotCleanChanged (bool)));
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

const Document &CmdMediator::document() const
{
  return m_document;
}

bool CmdMediator::isModified () const
{
  return !isClean();
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

void CmdMediator::saveXml(QXmlStreamWriter &writer) const
{
  for (int i = 0; i < index(); i++) {

    const CmdAbstract *cmd = dynamic_cast<const CmdAbstract *>(command(i));
    cmd->saveXml (writer);
  }
}

bool CmdMediator::successfulRead () const
{
  return m_document.successfulRead();
}
