#include "CmdGraph.h"
#include "DataKey.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MimePoints.h"
#include <QApplication>
#include <QClipboard>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Graph");

CmdGraph::CmdGraph(MainWindow &mainWindow,
                   Document &document,
                   const QStringList &selectedPointIdentifiers) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGraph::CmdGraph";
}

CmdGraph::CmdGraph (MainWindow &mainWindow,
                Document &document,
                const QString &cmdDescription,
                QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGraph::CmdGraph";
}

CmdGraph::~CmdGraph ()
{
}

void CmdGraph::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGraph::cmdRedo";
}

void CmdGraph::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGraph::cmdUndo";
}

void CmdGraph::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeEndElement();
}
