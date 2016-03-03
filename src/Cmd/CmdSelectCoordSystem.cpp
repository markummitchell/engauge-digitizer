#include "CmdSelectCoordSystem.h"
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

const QString CMD_DESCRIPTION("Select Coordinate System");

CmdSelectCoordSystem::CmdSelectCoordSystem(MainWindow &mainWindow,
                                           Document &document,
                                           CoordSystemIndex coordSystemIndex)
    : CmdAbstract(mainWindow, document, CMD_DESCRIPTION),
      m_coordSystemIndexBefore(document.coordSystemIndex()),
      m_coordSystemIndexAfter(coordSystemIndex) {
  LOG4CPP_INFO_S((*mainCat)) << "CmdSelectCoordSystem::CmdSelectCoordSystem";
}

CmdSelectCoordSystem::CmdSelectCoordSystem(MainWindow &mainWindow,
                                           Document &document,
                                           const QString &cmdDescription,
                                           QXmlStreamReader & /* reader */)
    : CmdAbstract(mainWindow, document, cmdDescription) {
  LOG4CPP_INFO_S((*mainCat)) << "CmdSelectCoordSystem::CmdSelectCoordSystem";
}

CmdSelectCoordSystem::~CmdSelectCoordSystem() {}

void CmdSelectCoordSystem::cmdRedo() {
  LOG4CPP_INFO_S((*mainCat)) << "CmdSelectCoordSystem::cmdRedo"
                             << " index=" << m_coordSystemIndexBefore << "->"
                             << m_coordSystemIndexAfter;

  mainWindow().updateCoordSystem(m_coordSystemIndexAfter);
}

void CmdSelectCoordSystem::cmdUndo() {
  LOG4CPP_INFO_S((*mainCat)) << "CmdSelectCoordSystem::cmdUndo"
                             << " index=" << m_coordSystemIndexAfter << "->"
                             << m_coordSystemIndexBefore;

  mainWindow().updateCoordSystem(m_coordSystemIndexBefore);
}

void CmdSelectCoordSystem::saveXml(QXmlStreamWriter &writer) const {
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeEndElement();
}
