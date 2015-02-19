#include "CmdEditPointAxis.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QTextStream>
#include "QtToString.h"

CmdEditPointAxis::CmdEditPointAxis (MainWindow &mainWindow,
                                    Document &document,
                                    const QString &pointIdentifier,
                                    const QPointF &posGraphBefore,
                                    const QPointF &posGraphAfter) :
  CmdAbstract (mainWindow,
               document,
               "Edit axis point"),
  m_pointIdentifier (pointIdentifier),
  m_posGraphBefore (posGraphBefore),
  m_posGraphAfter (posGraphAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdEditPointAxis::CmdEditPointAxis point="
                              << pointIdentifier.toLatin1 ().data ()
                              << " posGraphBefore=" << QPointFToString (posGraphBefore).toLatin1 ().data ()
                              << " posGraphAfter=" << QPointFToString (posGraphAfter).toLatin1 ().data ();
}

CmdEditPointAxis::~CmdEditPointAxis ()
{
}

void CmdEditPointAxis::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdEditPointAxis::cmdRedo";

  document().editPointAxis (m_posGraphAfter,
                            m_pointIdentifier);
  mainWindow().updateAfterCommand();
}

void CmdEditPointAxis::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdEditPointAxis::cmdUndo";

  document().editPointAxis (m_posGraphBefore,
                            m_pointIdentifier);
  mainWindow().updateAfterCommand();
}

void CmdEditPointAxis::saveCommands (QXmlStreamWriter &writer) const
{
  writer.writeStartElement("CmdEditPointAxis");
  writer.writeAttribute("identifier", m_pointIdentifier);
  writer.writeAttribute("xGraphBefore", QString::number (m_posGraphBefore.x()));
  writer.writeAttribute("yGraphBefore", QString::number (m_posGraphBefore.y()));
  writer.writeAttribute("xGraphAfter", QString::number (m_posGraphAfter.x()));
  writer.writeAttribute("yGraphAfter", QString::number (m_posGraphAfter.y()));
  writer.writeEndElement();
}
