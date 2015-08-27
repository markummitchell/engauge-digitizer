#include "ChecklistGuidePageCurves.h"
#include "Logger.h"
#include <QHeaderView>
#include <QRadioButton>
#include <QTableWidget>

const int FIRST_COL = 0;
const int NUM_COL = 1;
const int NUM_ROW = 6;

ChecklistGuidePageCurves::ChecklistGuidePageCurves() :
  ChecklistGuidePage ("Curves")
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageCurves::ChecklistGuidePageCurves";

  addHtml ("<p>What are the names of the curves that are to be digitized?</p>");

  m_tableCurves = new QTableWidget (NUM_ROW,
                                    NUM_COL,
                                    this);
  for (int i = 0; i < m_tableCurves->rowCount(); i++) {
    m_tableCurves->setItem (i, FIRST_COL, new QTableWidgetItem (""));
  }
  m_tableCurves->horizontalHeader()->hide();
  m_tableCurves->verticalHeader()->hide();
  m_tableCurves->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_tableCurves->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  connect (m_tableCurves, SIGNAL (itemChanged (QTableWidgetItem*)), this, SLOT (slotTableChanged (QTableWidgetItem*)));

  addTable (m_tableCurves);

  addHtml ("<p>&nbsp;</p>");

  addHtml ("<p>How are those curves drawn?</p>");

  m_btnLines = addLabelAndRadioButton ("With lines (with or without points)");
  m_btnPoints = addLabelAndRadioButton ("With points only (no lines between points)");

  m_btnLines->setChecked (true); // Default encourages digitizing using the lines, since that is easier
}

QStringList ChecklistGuidePageCurves::curveNames () const
{
  QStringList curveNames;

  for (int i = 0; i < m_tableCurves->rowCount(); i++) {

    if (!m_tableCurves->item (i, FIRST_COL)->text().isEmpty ()) {

      curveNames << m_tableCurves->item (i, FIRST_COL)->text();
    }
  }

  return curveNames;
}

bool ChecklistGuidePageCurves::isComplete () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageCurves::isComplete";

  bool hasCurveData = false;

  // Updated cell does not have text. See if other cells have text
  for (int i = 0; i < m_tableCurves->rowCount(); i++) {
    
    if (!m_tableCurves->item (i, FIRST_COL)->text().isEmpty ()) {
        
      hasCurveData = true;
      break;
    }
  }

  return hasCurveData;
}

void ChecklistGuidePageCurves::slotTableChanged (QTableWidgetItem * /* item */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageCurves::slotTableChanged";

  emit completeChanged ();
}

bool ChecklistGuidePageCurves::withLines() const
{
  return m_btnLines->isChecked();
}
