#include "CmdMediator.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindowModel.h"
#include <QLocale>
#include <QObject>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamWriter>
#include "Xml.h"
#include "ZoomFactorInitial.h"

MainWindowModel::MainWindowModel() :
  m_zoomControl (ZOOM_CONTROL_MENU_WHEEL_PLUSMINUS),
  m_zoomFactorInitial (DEFAULT_ZOOM_FACTOR_INITIAL)
{
  // Locale member variable m_locale is initialized to default locale when default constructor is called
}

MainWindowModel::MainWindowModel(const MainWindowModel &other) :
  m_locale (other.locale()),
  m_zoomControl (other.zoomControl()),
  m_zoomFactorInitial (other.zoomFactorInitial())
{
}

MainWindowModel &MainWindowModel::operator=(const MainWindowModel &other)
{
  m_locale = other.locale();
  m_zoomControl = other.zoomControl();
  m_zoomFactorInitial = other.zoomFactorInitial();

  return *this;
}

void MainWindowModel::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindowModel::loadXml";

  bool success = true;

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
    reader.raiseError (QObject::tr ("Cannot read main window data"));
  }
}

QLocale MainWindowModel::locale () const
{
  return m_locale;
}

void MainWindowModel::printStream(QString indentation,
                                     QTextStream &str) const
{
  str << indentation << "MainWindowModel\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "locale=" << m_locale.name() << "\n";
  str << indentation << "zoomControl=" << m_zoomControl << "\n";
  str << indentation << "zoomFactorInitial=" << m_zoomFactorInitial << "\n";
}

void MainWindowModel::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainWindowModel::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_MAIN_WINDOW);
  writer.writeEndElement();
}

void MainWindowModel::setLocale (QLocale::Language language,
                                 QLocale::Country country)
{
  QLocale locale (language,
                  country);

  m_locale = locale;
}

void MainWindowModel::setLocale (const QLocale &locale)
{
  m_locale = locale;
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
