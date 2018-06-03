/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MAIN_DIRECTORY_PERSIST_H
#define MAIN_DIRECTORY_PERSIST_H

#include <QDir>
#include <QString>

/// Persist the directory between successive Import/Open operations, or successive Export/Save
/// operations. The Export/Import/Open/Save operations are performed by the MainWindow class.
/// This functionality is for the convenience of users who want to return to the same directory
/// automatically rather than manually move from the Engauge startup directory to a user directory
class MainDirectoryPersist
{
public:
  /// Default constructor.
  MainDirectoryPersist();

  /// Get the current Export/Save directory
  QDir getDirectoryExportSave () const;

  /// Get the current Import/Open directory
  QDir getDirectoryImportOpen () const;

  /// Save the current Export/Save directory, after user has accepted the Export/Save dialog
  void setDirectoryExportSaveFromFilename (const QString &fileName);

  /// Save the current Import/Open directory, after user has accepted the Import/Open dialog
  void setDirectoryImportOpenFromFilename (const QString &fileName);

private:

  // The directories are static so all instances of this class share the same values
  static QDir m_directoryExportSave;
  static QDir m_directoryImportOpen;

};

#endif // MAIN_DIRECTORY_PERSIST_H
