/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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

// Prevent comma ambiguity with group separator commas and field delimiting commas
const QLocale::NumberOption HIDE_GROUP_SEPARATOR = QLocale::OmitGroupSeparator;

MainWindowModel::MainWindowModel() :
  m_zoomControl (ZOOM_CONTROL_MENU_WHEEL_PLUSMINUS),
  m_zoomFactorInitial (DEFAULT_ZOOM_FACTOR_INITIAL),
  m_mainTitleBarFormat (MAIN_TITLE_BAR_FORMAT_PATH)
{
  // Locale member variable m_locale is initialized to default locale when default constructor is called
}

MainWindowModel::MainWindowModel(const MainWindowModel &other) :
  m_locale (other.locale()),
  m_zoomControl (other.zoomControl()),
  m_zoomFactorInitial (other.zoomFactorInitial()),
  m_mainTitleBarFormat (other.mainTitleBarFormat())
{
}

MainWindowModel &MainWindowModel::operator=(const MainWindowModel &other)
{
  m_locale = other.locale();
  m_zoomControl = other.zoomControl();
  m_zoomFactorInitial = other.zoomFactorInitial();
  m_mainTitleBarFormat = other.mainTitleBarFormat();

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

MainTitleBarFormat MainWindowModel::mainTitleBarFormat() const
{
  return m_mainTitleBarFormat;
}

void MainWindowModel::printStream(QString indentation,
                                     QTextStream &str) const
{
  str << indentation << "MainWindowModel\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "locale=" << m_locale.name() << "\n";
  str << indentation << "zoomControl=" << m_zoomControl << "\n";
  str << indentation << "zoomFactorInitial=" << m_zoomFactorInitial << "\n";
  str << indentation << "mainWindowTitleBarFormat=" << (m_mainTitleBarFormat == MAIN_TITLE_BAR_FORMAT_NO_PATH ?
                                                        "NoPath" :
                                                        "Path");
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
  locale.setNumberOptions(HIDE_GROUP_SEPARATOR);

  m_locale = locale;
}

void MainWindowModel::setLocale (const QLocale &locale)
{
  m_locale = locale;
  m_locale.setNumberOptions(HIDE_GROUP_SEPARATOR);
}

void MainWindowModel::setMainTitleBarFormat(MainTitleBarFormat mainTitleBarFormat)
{
  m_mainTitleBarFormat = mainTitleBarFormat;
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
