# Requirements:
# 1) LOG4CPP with environment variable LOG4CPP_INCLUDE pointing to that packages include directory. Example:
#        LOG4CPP=$HOME/log4cpp_null/include
# 2) openjpeg with environment variable JPEG_INCLUDE pointing to that packages include directory. Example:
#        JPEG_INCLUDE=$HOME/openjpeg-version.2.1/usr/local/include/openjpeg-2.1

_JPEG_INCLUDE = $$(JPEG_INCLUDE)
_LOG4CPP_HOME = $$(LOG4CPP_HOME)
isEmpty(_JPEG_INCLUDE) {
  error("JPEG_INCLUDE and LOG4CPP_HOME environment variables must be defined")
} else {
  isEmpty(_LOG4CPP_HOME) {
    error("JPEG_INCLUDE and LOG4CPP_HOME environment variables must be defined")
  }
}

TEMPLATE = lib

SOURCES += Jpeg2000Callbacks.cpp \
           Jpeg2000Color.cpp \
           Jpeg2000Convert.cpp \
           Jpeg2000.cpp

HEADERS += Jpeg2000Callbacks.h \
           Jpeg2000Color.h \
           Jpeg2000Convert.h \
           Jpeg2000FormatDefs.h \
           Jpeg2000.h

INCLUDEPATH += $$(JPEG_INCLUDE) \
               $$(LOG4CPP_HOME)/include \
               ../Logger
