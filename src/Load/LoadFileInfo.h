#ifndef LOAD_FILE_INFO_H
#define LOAD_FILE_INFO_H

#include <QString>

/// Returns information about files
class LoadFileInfo
{
public:
  /// Single constructor.
  LoadFileInfo();
  virtual ~LoadFileInfo();

  /// Returns true if specified file name can be loaded as a DIG file
  bool loadsAsDigFile (const QString &urlString) const;

};

#endif // LOAD_FILE_INFO_H
