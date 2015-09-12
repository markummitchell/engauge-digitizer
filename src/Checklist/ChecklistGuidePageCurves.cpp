#include "ChecklistGuidePageCurves.h"
#include "ChecklistLineEdit.h"
#include "Curve.h"
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

  addHtml ("<p>What are the names of the curves that are to be digitized? At least one entry is required.</p>");

  m_edit = new ChecklistLineEdit* [NUM_CURVE_NAMES()];

  for (int i = 0; i < NUM_CURVE_NAMES(); i++) {
    m_edit [i] = new ChecklistLineEdit;
    connect (m_edit [i], SIGNAL (signalKeyRelease()), this, SLOT (slotTableChanged()));
    addLineEdit (m_edit [i]);
  }

  m_edit [0]->setText (DEFAULT_GRAPH_CURVE_NAME); // Simple default name

  addHtml ("<p>&nbsp;</p>");

  addHtml ("<p>How are those curves drawn?</p>");

  m_btnLines = addLabelAndRadioButton ("With lines (with or without points)");
  m_btnPoints = addLabelAndRadioButton ("With points only (no lines between points)");

  m_btnLines->setChecked (true); // Default encourages digitizing using the lines, since that is easier
}

QStringList ChecklistGuidePageCurves::curveNames () const
{
  QStringList curveNames;

  for (int i = 0; i < NUM_CURVE_NAMES(); i++) {
    const QLineEdit *edit = m_edit [i];
    QString text = edit->text();
    if (!text.isEmpty()) {
      curveNames << text;
    }
  }

  return curveNames;
}

bool ChecklistGuidePageCurves::curveNamesAreAllUnique() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageCurves::curveNamesAreAllUnique";

  QStringList names = curveNames();

  int numberDuplicatesRemoved = names.removeDuplicates();

  return (numberDuplicatesRemoved == 0);
}

bool ChecklistGuidePageCurves::isComplete () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageCurves::isComplete";

  return !curveNames().isEmpty () &&
      curveNamesAreAllUnique ();
}

void ChecklistGuidePageCurves::slotTableChanged ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageCurves::slotTableChanged";

  emit completeChanged();
}

bool ChecklistGuidePageCurves::withLines() const
{
  return m_btnLines->isChecked();
}
