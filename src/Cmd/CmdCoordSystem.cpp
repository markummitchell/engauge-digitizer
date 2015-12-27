#include "CmdCoordSystem.h"
#include "DataKey.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MimePoints.h"
#include <QApplication>
#include <QClipboard>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Select Coordinate System");

CmdCoordSystem::CmdCoordSystem(MainWindow &mainWindow,
                               Document &document) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCoordSystem::CmdCoordSystem";
}

CmdCoordSystem::CmdCoordSystem (MainWindow &mainWindow,
                                Document &document,
                                const QString &cmdDescription,
                                QXmlStreamReader & /* reader */) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCoordSystem::CmdCoordSystem";
}

CmdCoordSystem::~CmdCoordSystem ()
{
}

void CmdCoordSystem::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCoordSystem::cmdRedo";
}

void CmdCoordSystem::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdCoordSystem::cmdUndo";
}

void CmdCoordSystem::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeEndElement();
}
