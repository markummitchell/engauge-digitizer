#ifndef ROLLING_FILE_APPENDER_HH
#define ROLLING_FILE_APPENDER_HH

#include "log4cpp/FileAppender.hh"
#include <string>
#include <stdarg.h>

namespace log4cpp {

  class RollingFileAppender : public FileAppender
  {
  public:
    RollingFileAppender (const std::string &name,
                         const std::string &fileName,
                         size_t maxFileSize,
                         unsigned int maxBackupIndex,
                         bool append);
    virtual ~RollingFileAppender();

    void setMaxBackupIndex(unsigned int maxBackups);
    unsigned int getMaxBackupIndex() const;
    void setMaximumFileSize(size_t maxFileSize);
    size_t getMaxFileSize() const;
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
