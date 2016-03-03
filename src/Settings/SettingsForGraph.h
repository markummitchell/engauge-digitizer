#ifndef SETTINGS_FOR_GRAPH_H
#define SETTINGS_FOR_GRAPH_H

#include <QString>

/// Manage storage and retrieval of the settings for the curves
class SettingsForGraph {
public:
  /// Single constructor
  SettingsForGraph();

  /// Default graph name for the specified curve index
  QString defaultCurveName(int indexOneBased, const QString &defaultName) const;

  /// Return the group name, that appears in the settings file/registry, for the
  /// specified curve index
  QString groupNameForNthCurve(int indexOneBased) const;
};

#endif // SETTINGS_FOR_GRAPH_H
