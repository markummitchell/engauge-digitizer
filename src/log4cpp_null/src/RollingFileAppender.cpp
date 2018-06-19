#include "log4cpp/RollingFileAppender.hh"

namespace log4cpp {

  RollingFileAppender::RollingFileAppender (const std::string &name,
                                            const std::string &fileName,
                                            size_t maxFileSize,
                                            unsigned int maxBackupIndex,
                                            bool append) :
    FileAppender (name),
    m_fileName (fileName),
    m_maxFileSize (maxFileSize),
    m_maxBackupIndex (maxBackupIndex),
    m_append (append)
  {
  }

  RollingFileAppender::~RollingFileAppender ()
  {
  }

  void RollingFileAppender::setMaxBackupIndex(unsigned int)
  {
  }

  bool RollingFileAppender::getAppend () const
  {
    return m_append;
  }

  unsigned int RollingFileAppender::getMaxBackupIndex() const
  {
    return m_maxBackupIndex;
  }

  void RollingFileAppender::setMaximumFileSize(size_t maxFileSize)
  {
    m_maxFileSize = maxFileSize;
  }

  size_t RollingFileAppender::getMaxFileSize() const
  {
    return m_maxFileSize;
  }

  void RollingFileAppender::setLayout (Layout *)
  {
  }
}

