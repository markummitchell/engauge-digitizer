#include "CmdMoveBy.h"
#include "DataKey.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "GraphicsItemType.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsItem>
#include <QtToString.h>

CmdMoveBy::CmdMoveBy(MainWindow &mainWindow,
                     Document &document,
                     const QPointF &deltaScreen,
                     const QString &moveText,
                     const QStringList &selectedPointIdentifiers) :
  CmdAbstract(mainWindow,
              document,
              moveText),
  m_deltaScreen (deltaScreen)
{
  QStringList selected; // For debug
  QStringList::const_iterator itr;
  for (itr = selectedPointIdentifiers.begin (); itr != selectedPointIdentifiers.end (); itr++) {

    QString selectedPointIdentifier = *itr;

    selected << selectedPointIdentifier;
    m_movedPoints [selectedPointIdentifier] = true;
  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdMoveBy::CmdMoveBy"
                              << " deltaScreen=" << QPointFToString (deltaScreen).toLatin1 ().data ()
                              << " selected=" << selected.join (", ").toLatin1 ().data () << ")";
}

void CmdMoveBy::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdMoveBy::cmdRedo"
                              << " deltaScreen=" << QPointFToString (m_deltaScreen).toLatin1().data()
                              << " moving=" << m_movedPoints.count ();

  moveBy (m_deltaScreen);

  mainWindow().updateAfterCommand();
}

void CmdMoveBy::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdMoveBy::cmdUndo"
                              << " deltaScreen=" << QPointFToString (-1.0 * m_deltaScreen).toLatin1().data()
                              << " moving=" << m_movedPoints.count ();

  moveBy (-1.0 * m_deltaScreen);

  mainWindow().updateAfterCommand();
}

void CmdMoveBy::moveBy (const QPointF &deltaScreen)
{
  // Move Points in the Document
  PointIdentifiers::iterator itrD;
  for (itrD = m_movedPoints.begin (); itrD != m_movedPoints.end (); itrD++) {

      QString pointIdentifier = itrD.key ();
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

        QPointF posScreen = document().positionScreen (pointIdentifier);

        if (item->pos () != posScreen) {

          item->setPos (posScreen);
        }
      }
    }
  }
}

void CmdMoveBy::saveCommands (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD_MOVE_BY);
  writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_X_DELTA, QString::number (m_deltaScreen.x()));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SCREEN_Y_DELTA, QString::number (m_deltaScreen.y()));
  writer.writeStartElement(DOCUMENT_SERIALIZE_IDENTIFIERS);
  PointIdentifiers::const_iterator itr;
  for (itr = m_movedPoints.begin(); itr != m_movedPoints.end (); itr++) {
    QString identifier = itr.key();
    bool value = itr.value();
    writer.writeStartElement (DOCUMENT_SERIALIZE_IDENTIFIER, identifier);
    writer.writeAttribute(DOCUMENT_SERIALIZE_MOVED,
                          value ? DOCUMENT_SERIALIZE_BOOL_TRUE : DOCUMENT_SERIALIZE_BOOL_FALSE);
    writer.writeEndElement();
  }
  writer.writeEndElement();
  writer.writeEndElement();
}
