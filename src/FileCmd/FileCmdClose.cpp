#include "EngaugeAssert.h"
#include "FileCmdClose.h"
#include "FileCmdSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION("Close File");

FileCmdClose::FileCmdClose(QXmlStreamReader & /* reader */)
    : FileCmdAbstract(CMD_DESCRIPTION) {
  LOG4CPP_INFO_S((*mainCat)) << "FileCmdClose::FileCmdClose";
}

FileCmdClose::~FileCmdClose() {}

void FileCmdClose::redo(MainWindow &mainWindow) {
  LOG4CPP_INFO_S((*mainCat)) << "FileCmdClose::redo";

  mainWindow.cmdFileClose();
}
