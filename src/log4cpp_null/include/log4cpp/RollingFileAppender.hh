#ifndef ROLLING_FILE_APPENDER_HH
#define ROLLING_FILE_APPENDER_HH

#include "log4cpp/FileAppender.hh"
#include <string>
#include <stdarg.h>

namespace log4cpp {

  /// Noop class that mimics the same class in the log4cpp library
  class RollingFileAppender : public FileAppender
  {
  public:
    /// Single constructor
    RollingFileAppender (const std::string &name,
                         const std::string &fileName,
                         size_t maxFileSize,
                         unsigned int maxBackupIndex,
                         bool append);
    virtual ~RollingFileAppender();

    /// Noop method for setting the number of backups
    void setMaxBackupIndex(unsigned int maxBackups);

    /// Noop method for getting the number of backups
    unsigned int getMaxBackupIndex() const;

    /// Noop method for setting the maximum file size
    void setMaximumFileSize(size_t maxFileSize);

    /// Noop method for getting the maximum file size
    size_t getMaxFileSize() const;

    /// Noop method for getting the append flag
    bool getAppend() const;

    virtual void setLayout(Layout *layout);

  private:
    
    std::string m_fileName;
    size_t m_maxFileSize;
    unsigned int m_maxBackupIndex;
    bool m_append;
  };
}

#endif // ROLLING_FILE_APPENDER_HH
