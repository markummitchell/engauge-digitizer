/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ChecklistGuidePageCurves.h"
#include "ChecklistLineEdit.h"
#include "Curve.h"
#include "Logger.h"
#include <QHeaderView>
#include <QRadioButton>
#include <QTableWidget>
#include "SettingsForGraph.h"

ChecklistGuidePageCurves::ChecklistGuidePageCurves(const QString &title) :
  ChecklistGuidePage (title)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePageCurves::ChecklistGuidePageCurves";

  const QString WHATS_THIS_CURVE (tr ("Curve name. Empty if unused."));
  const QString WHATS_THIS_LINES (tr ("Draw lines between points in each curve."));
  const QString WHATS_THIS_POINTS (tr ("Draw points in each curve, without lines between the points."));

  addHtml (QString ("<p>%1</p>")
           .arg (tr ("What are the names of the curves that are to be digitized? At least one entry is required.")));

  m_edit = new ChecklistLineEdit* [NUM_CURVE_NAMES()];

  for (int i = 0; i < NUM_CURVE_NAMES(); i++) {
    m_edit [i] = new ChecklistLineEdit;
    connect (m_edit [i], SIGNAL (signalKeyRelease()), this, SLOT (slotTableChanged()));
    addLineEdit (m_edit [i],
                 WHATS_THIS_CURVE);
  }

  SettingsForGraph settingsForGraph;
  QString curveName = settingsForGraph.defaultCurveName (1,
                                                         DEFAULT_GRAPH_CURVE_NAME);

  m_edit [0]->setText (curveName);

  addHtml ("<p>&nbsp;</p>");

  addHtml (QString ("<p>%1</p>")
           .arg (tr ("How are those curves drawn?")));

  m_btnLines = addLabelAndRadioButton (tr ("With lines (with or without points)"),
                                       WHATS_THIS_LINES);
  m_btnPoints = addLabelAndRadioButton (tr ("With points only (no lines between points)"),
                                        WHATS_THIS_POINTS);

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
