QT += testlib core widgets
MOC_DIR = .moc
OBJECTS_DIR = .objs
RCC_DIR = .rcc
TEMPLATE = app
TARGET = test
INCLUDEPATH += . \
  ../src/Logger \
  ../src/Plot
LIBS += -llog4cpp

# Input
HEADERS += ../src/Logger/Logger.h \
           ../src/Plot/PlotClassifier.h \
           TestPlotClassifier.h
SOURCES += ../src/Logger/Logger.cpp \
           ../src/Plot/PlotClassifier.cpp \
           TestPlotClassifier.cpp
