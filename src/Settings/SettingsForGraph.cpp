/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include <QSettings>
#include "Settings.h"
#include "SettingsForGraph.h"

SettingsForGraph::SettingsForGraph ()
{
}

QString SettingsForGraph::defaultCurveName (int indexOneBased,
                                            const QString &defaultName) const
{
  QString groupName = groupNameForNthCurve (indexOneBased);

  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup (groupName);

  QString curveName = settings.value (SETTINGS_CURVE_NAME,
                                      defaultName).toString();

  settings.endGroup ();

  return curveName;
}

QString SettingsForGraph::groupNameForNthCurve (int indexOneBased) const
{
  ENGAUGE_ASSERT (indexOneBased != 0); // Make sure index is one-based versus zero-based

  QString groupNameWithPlaceholder = SETTINGS_GROUP_CURVE_GRAPH;
  QString groupName = groupNameWithPlaceholder.replace (SETTINGS_GROUP_CURVE_GRAPH_PLACEHOLDER,
                                                        QString::number (indexOneBased));

  return groupName;
}

int SettingsForGraph::numberOfCurvesForImport() const
{
  const QString EMPTY_CURVE_NAME;

  // Loop until the configuration file returns an empty string
  int indexOneBased = 1;
  while (defaultCurveName (indexOneBased + 1, EMPTY_CURVE_NAME) != EMPTY_CURVE_NAME) {
    ++indexOneBased;
  }

  return indexOneBased;
}
