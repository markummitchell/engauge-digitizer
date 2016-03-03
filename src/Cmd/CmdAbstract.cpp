/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAbstract.h"
#include "DataKey.h"
#include "Document.h"
#include "GraphicsItemType.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Point.h"
#include <QGraphicsItem>

CmdAbstract::CmdAbstract(MainWindow &mainWindow,
                         Document &document,
                         const QString &cmdDescription) :
  QUndoCommand (cmdDescription),
  m_mainWindow (mainWindow),
  m_document (document),
  m_isFirstRedo (true)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::CmdAbstract";
}

CmdAbstract::~CmdAbstract()
{
}

Document &CmdAbstract::document ()
{
  return m_document;
}

const Document &CmdAbstract::document () const
{
  return m_document;
}

MainWindow &CmdAbstract::mainWindow ()
{
  return m_mainWindow;
}

void CmdAbstract::redo ()
{
  // Note that m_identifierIndexBeforeRedo and m_identifierIndexAfterRedo are not set until below (at which point they are logged)
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::redo";

  if (m_isFirstRedo) {

    m_identifierIndexBeforeRedo = Point::identifierIndex ();

  } else {

    // Reset state. The first time this is called, this is a noop since m_identifierIndex was just set to
    // GraphicsPointAbstractBase::identifierIndex in the constructor of this class
    Point::setIdentifierIndex (m_identifierIndexBeforeRedo);

  }

  // Invoke the leaf class redo method
  cmdRedo ();

  if (m_isFirstRedo) {

    m_isFirstRedo = false;
    m_identifierIndexAfterRedo = Point::identifierIndex();

  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::redo identifierIndex=" << m_identifierIndexBeforeRedo << "->"
                              << m_identifierIndexAfterRedo;
}

void CmdAbstract::resetSelection(const PointIdentifiers &pointIdentifiersToSelect)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::resetSelection";

  QList<QGraphicsItem *> items = mainWindow().view().items();
  QList<QGraphicsItem *>::iterator itrS;
  for (itrS = items.begin (); itrS != items.end (); itrS++) {

    QGraphicsItem *item = *itrS;
    bool selected = false;
    if (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_POINT) {

      QString pointIdentifier = item->data (DATA_KEY_IDENTIFIER).toString ();

      selected = pointIdentifiersToSelect.contains (pointIdentifier);
    }

    item->setSelected (selected);
  }
}

void CmdAbstract::undo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::undo identifierIndex=" << m_identifierIndexAfterRedo << "->"
                              << m_identifierIndexBeforeRedo;

  Point::setIdentifierIndex (m_identifierIndexAfterRedo);

  // Invoke the leaf class undo method
  cmdUndo ();

  Point::setIdentifierIndex (m_identifierIndexBeforeRedo);
}
