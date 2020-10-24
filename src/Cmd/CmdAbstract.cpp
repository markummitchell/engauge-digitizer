/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAbstract.h"
#include "DataKey.h"
#include "DigitizeState.h"
#include "Document.h"
#include "DocumentHashGenerator.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "GraphicsItemType.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "GuidelineState.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Point.h"
#include <QGraphicsItem>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Xml.h"

CmdAbstract::CmdAbstract(MainWindow &mainWindow,
                         Document &document,
                         const QString &cmdDescription) :
  QUndoCommand (cmdDescription),
  m_mainWindow (mainWindow),
  m_document (document),
  m_isFirstRedo (true),
  m_digitizeState (mainWindow.digitizeState ()),
  m_guidelineViewState (mainWindow.guidelineViewState ())
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::CmdAbstract";
}

CmdAbstract::~CmdAbstract()
{
}

void CmdAbstract::baseAttributes (QXmlStreamWriter &writer) const
{
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_STATE, QString::number (m_digitizeState));
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_STATE_STRING, digitizeStateAsString (m_digitizeState));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE, QString::number (m_guidelineViewState));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE_STRING, guidelineViewStateAsString (m_guidelineViewState));  
}

Document &CmdAbstract::document ()
{
  return m_document;
}

const Document &CmdAbstract::document () const
{
  return m_document;
}

void CmdAbstract::leafAttributes (const QXmlStreamAttributes &attributes,
                                  const QStringList &requiredAttributesLeaf,
                                  QXmlStreamReader &reader)
{
  // Check for leaf class if called directly, or for base class if called indirectly through leafAndBaseAttributes
  QStringList::const_iterator itr;
  QStringList missingAttributes;
  for (itr = requiredAttributesLeaf.begin (); itr != requiredAttributesLeaf.end (); itr++) {

    QString attribute = *itr;
    if (!attributes.hasAttribute (attribute)) {
      missingAttributes << attribute;
    }
  }

  if (missingAttributes.size () > 0) {
    xmlExitWithError (reader,
                      QString ("Missing attribute(s) %1"). arg (missingAttributes.join (", ")));
  }
}

void CmdAbstract::leafAndBaseAttributes (const QXmlStreamAttributes &attributes,
                                         const QStringList &requiredAttributesLeaf,
                                         QXmlStreamReader &reader)
{
  // Aggregate attributes for leaf and this abstract class
  QStringList requiredAttributes = requiredAttributesLeaf;
  requiredAttributes << DOCUMENT_SERIALIZE_DIGITIZE_STATE;
  requiredAttributes << DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE;

  // Check as if this base class was a leaf class
  leafAttributes (attributes,
                  requiredAttributes,
                  reader);

  // Extract parent class attributes
  m_digitizeState = static_cast<DigitizeState> (attributes.value (DOCUMENT_SERIALIZE_DIGITIZE_STATE).toInt());
  m_guidelineViewState = static_cast<GuidelineViewState> (attributes.value (DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE).toInt());
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

void CmdAbstract::restoreState ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::restoreState";

  m_mainWindow.updateDigitizeStateIfSoftwareTriggered (m_digitizeState);
  m_mainWindow.setGuidelineViewState (m_guidelineViewState);
}

void CmdAbstract::saveOrCheckPostCommandDocumentStateHash (const Document &document)
{
  // LOG4CPP_INFO_S is below

  DocumentHashGenerator documentHashGenerator;
  DocumentHash documentHash = documentHashGenerator.generate (document);

  if (m_documentHashPost.count() == 0) {

    // This is the first time through here so save the initial value
    m_documentHashPost = documentHash;

  } else {

    // This is not the first time through here so compare the current value to the initial value
    ENGAUGE_ASSERT (documentHash == m_documentHashPost);

  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::saveOrCheckPostCommandDocumentStateHash stateHash=" << m_documentHashPost.data ();

}

void CmdAbstract::saveOrCheckPreCommandDocumentStateHash (const Document &document)
{
  // LOG4CPP_INFO_S is below

  DocumentHashGenerator documentHashGenerator;
  DocumentHash documentHash = documentHashGenerator.generate (document);

  if (m_documentHashPre.count() == 0) {

    // This is the first time through here so save the initial value
    m_documentHashPre = documentHash;

  } else {

    // This is not the first time through here so compare the current value to the initial value
    ENGAUGE_ASSERT (documentHash == m_documentHashPre);

  }

  LOG4CPP_INFO_S ((*mainCat)) << "CmdAbstract::saveOrCheckPreCommandDocumentStateHash stateHash=" << m_documentHashPre.data ();

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
