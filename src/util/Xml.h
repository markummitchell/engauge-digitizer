/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef XML_H
#define XML_H

#include <QString>
#include <QXmlStreamReader>

/// Load next token from xml reader
extern QXmlStreamReader::TokenType loadNextFromReader (QXmlStreamReader &reader);

/// Show specified message for an error while reading xml, then quit. The reader will provide filename
/// (if available) and line number
extern void xmlExitWithError (QXmlStreamReader &reader,
                              const QString &message);

#endif // XML_H
