#include "CmdMediator.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindowModel.h"
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamWriter>
#include "Xml.h"
#include "ZoomFactorInitial.h"

MainWindowModel::MainWindowModel() :
  m_zoomControl (ZOOM_CONTROL_MENU_WHEEL_PLUSMINUS),
  m_zoomFactorInitial (DEFAULT_ZOOM_FACTOR_INITIAL)
{
}

MainWindowModel::MainWindowModel(const MainWindowModel &other) :
  m_zoomControl (other.zoomControl()),
  m_zoomFactorInitial (other.zoomFactorInitial())
{
}

MainWindowModel &MainWindowModel::operator=(const MainWindowModel &other)
{
  m_zoomControl = other.zoomControl();
  m_zoomFactorInitial = other.zoomFactorInitial();

  return *this;
}

void MainWindowModel::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindowModel::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  // Read until end of this subtree
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_MAIN_WINDOW)){
    loadNextFromReader(reader);
    if (reader.atEnd()) {
      success = false;
      break;
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read main window data");
  }
}

void MainWindowModel::printStream(QString indentation,
                                     QTextStream &str) const
{
  str << indentation << "MainWindowModel\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "zoomControl=" << m_zoomControl << "\n";
  str << indentation << "zoomFactorInitial=" << m_zoomFactorInitial << "\n";
}

void MainWindowModel::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindowModel::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_MAIN_WINDOW);
  writer.writeEndElement();
}

void MainWindowModel::setZoomControl (ZoomControl zoomControl)
{
  m_zoomControl = zoomControl;
}

void MainWindowModel::setZoomFactorInitial(ZoomFactorInitial zoomFactorInitial)
{
  m_zoomFactorInitial = zoomFactorInitial;
}

ZoomControl MainWindowModel::zoomControl () const
{
  return m_zoomControl;
}

ZoomFactorInitial MainWindowModel::zoomFactorInitial() const
{
  return m_zoomFactorInitial;
}
