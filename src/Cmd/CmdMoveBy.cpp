/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMoveBy.h"
#include "DataKey.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "GraphicsItemType.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsItem>
#include <QtToString.h>
#include <QXmlStreamReader>
#include "Xml.h"

CmdMoveBy::CmdMoveBy(MainWindow &mainWindow,
                     Document &document,
                     const QPointF &deltaScreen,
                     const QString &moveText,
                     const QStringList &selectedPointIdentifiers) :
  CmdPointChangeBase (mainWindow,
                      document,
                      moveText),
  m_deltaScreen (deltaScreen)
{
  QStringList selected; // For debug
  QStringList::const_iterator itr;
  for (itr = selectedPointIdentifiers.begin (); itr != selectedPointIdentifiers.end (); itr++) {

    QString selectedPointIdentifier = *itr;

    selected << selectedPointIdentifier;
    m_movedPoints.setKeyValue (selectedPointIdentifier, true);
  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdMoveBy::CmdMoveBy"
                              << " deltaScreen=" << QPointFToString (deltaScreen).toLatin1 ().data ()
                              << " selected=" << selected.join (", ").toLatin1 ().data () << ")";
}

CmdMoveBy::CmdMoveBy (MainWindow &mainWindow,
                      Document &document,
                      const QString &cmdDescription,
                      QXmlStreamReader &reader) :
  CmdPointChangeBase (mainWindow,
                      document,
                      cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdMoveBy::CmdMoveBy";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_SCREEN_X_DELTA) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_SCREEN_Y_DELTA) ) {
    xmlExitWithError (reader,
                      QString ("%1 %2 %3 %4")
                      .arg (QObject::tr ("Missing attribute(s)"))
                      .arg (DOCUMENT_SERIALIZE_SCREEN_X_DELTA)
                      .arg (QObject::tr ("and/or"))
                      .arg (DOCUMENT_SERIALIZE_SCREEN_Y_DELTA));
  }

  m_deltaScreen.setX(attributes.value(DOCUMENT_SERIALIZE_SCREEN_X_DELTA).toDouble());
  m_deltaScreen.setY(attributes.value(DOCUMENT_SERIALIZE_SCREEN_Y_DELTA).toDouble());
  m_movedPoints.loadXml (reader);
}

CmdMoveBy::~CmdMoveBy ()
{
}

void CmdMoveBy::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdMoveBy::cmdRedo"
                              << " deltaScreen=" << QPointFToString (m_deltaScreen).toLatin1().data()
                              << " moving=" << m_movedPoints.count ();

  saveOrCheckPreCommandDocumentStateHash (document ());
  saveDocumentState (document ());
  moveBy (m_deltaScreen);
  mainWindow().updateAfterCommand();
  resetSelection(m_movedPoints);
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdMoveBy::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdMoveBy::cmdUndo"
                              << " deltaScreen=" << QPointFToString (-1.0 * m_deltaScreen).toLatin1().data()
                              << " moving=" << m_movedPoints.count ();

  saveOrCheckPostCommandDocumentStateHash (document ());
  restoreDocumentState (document ());
  mainWindow().updateAfterCommand();
  resetSelection(m_movedPoints);
  saveOrCheckPreCommandDocumentStateHash (document ());
}

void CmdMoveBy::moveBy (const QPointF &deltaScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdMoveBy::moveBy";

  // Move Points in the Document
  for (int i = 0; i < m_movedPoints.count(); i++) {

    QString pointIdentifier = m_movedPoints.getKey (i);
    document().movePoint (pointIdentifier, deltaScreen);

  }

  // Move Points in GraphicsScene, using the new positions in Document
  QList<QGraphicsItem *> items = mainWindow().view().items();
  QList<QGraphicsItem *>::iterator itrS;
  for (itrS = items.begin (); itrS != items.end (); itrS++) {

    QGraphicsItem *item = *itrS;
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_POINT) {

      QString pointIdentifier = item->data (DATA_KEY_IDENTIFIER).toString ();

      if (m_movedPoints.contains (pointIdentifier)) {

        // Get the new position
        QPointF posScreen = document().positionScreen (pointIdentifier);

        if (item->pos () != posScreen) {

          // Save the new position
          item->setPos (posScreen);
        }
      }
    }
  }

  document().updatePointOrdinals (mainWindow().transformation());

  // Update the lines attached to the points
  mainWindow().updateGraphicsLinesToMatchGraphicsPoints();
}

void CmdMoveBy::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_MOVE_BY);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_X_DELTA, QString::number (m_deltaScreen.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_Y_DELTA, QString::number (m_deltaScreen.y()));
  m_movedPoints.saveXml (writer);
  writer.writeEndElement();
}
