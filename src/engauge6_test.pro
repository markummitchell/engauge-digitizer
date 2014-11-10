TEMPLATE    = app
CONFIG      = qt warn_on thread debug testcase
OBJECTS_DIR = .objs_test

HEADERS  += \
    Callback/CallbackAxisPointsAbstract.h \
    Callback/CallbackCheckAddPointAxis.h \
    Callback/CallbackCheckEditPointAxis.h \
    Callback/CallbackSearchReturn.h \
    Callback/CallbackUpdateTransform.h \
    Cmd/CmdAbstract.h \
    Cmd/CmdAddPointAxis.h \
    Cmd/CmdEditPointAxis.h \
    Cmd/CmdMediator.h \
    Cmd/CmdMoveBy.h \
    Curve/Curve.h \
    Curve/CurvesGraphs.h \
    include/DataKey.h \
    DigitizeState/DigitizeStateAbstractBase.h \
    DigitizeState/DigitizeStateAxis.h \
    DigitizeState/DigitizeStateContext.h \
    DigitizeState/DigitizeStateCurve.h \
    DigitizeState/DigitizeStateEmpty.h \
    DigitizeState/DigitizeStateScale.h \
    DigitizeState/DigitizeStateSegment.h \
    DigitizeState/DigitizeStateSelect.h \
    Dlg/DlgAbout.h \
    Dlg/DlgEditPoint.h \
    Document/Document.h \
    Callback/functor.h \
    Graphics/GraphicsItemType.h \
    Graphics/GraphicsPointAbstractBase.h \
    Graphics/GraphicsPointCircle.h \
    Graphics/GraphicsPointPolygon.h \
    Graphics/GraphicsScene.h \
    Graphics/GraphicsView.h \
    Load/LoadImageFromUrl.h \
    Logger/Logger.h \
    main/MainWindow.h \
    Point/Point.h \
    Point/PointShape.h \
    util/QtToString.h \
    StatusBar/StatusBar.h \
    StatusBar/StatusBarMode.h \
    Test/TestGraphCoords.h \
    Transformation/Transformation.h \
    include/ZoomFactor.h

SOURCES += \
    Callback/CallbackAxisPointsAbstract.cpp \
    Callback/CallbackCheckAddPointAxis.cpp \
    Callback/CallbackCheckEditPointAxis.cpp \
    Callback/CallbackUpdateTransform.cpp \
    Cmd/CmdAbstract.cpp \
    Cmd/CmdAddPointAxis.cpp \
    Cmd/CmdEditPointAxis.cpp \
    Cmd/CmdMediator.cpp \
    Cmd/CmdMoveBy.cpp \
    Curve/Curve.cpp \
    Curve/CurvesGraphs.cpp \
    DigitizeState/DigitizeStateAbstractBase.cpp \
    DigitizeState/DigitizeStateAxis.cpp \
    DigitizeState/DigitizeStateContext.cpp \
    DigitizeState/DigitizeStateCurve.cpp \
    DigitizeState/DigitizeStateEmpty.cpp \
    DigitizeState/DigitizeStateScale.cpp \
    DigitizeState/DigitizeStateSegment.cpp \
    DigitizeState/DigitizeStateSelect.cpp \
    Dlg/DlgEditPoint.cpp \
    Dlg/DlgAbout.cpp \
    Document/Document.cpp \
    Graphics/GraphicsPointAbstractBase.cpp \
    Graphics/GraphicsPointCircle.cpp \
    Graphics/GraphicsPointPolygon.cpp \
    Graphics/GraphicsScene.cpp \
    Graphics/GraphicsView.cpp \
    Load/LoadImageFromUrl.cpp \
    Logger/Logger.cpp  \
    main/MainWindow.cpp \
    Point/Point.cpp \
    Point/PointShape.cpp \
    util/QtToString.cpp \
    StatusBar/StatusBar.cpp \
    Test/TestGraphCoords.cpp \
    Transformation/Transformation.cpp

TARGET = ../bin/engauge6_test

MOC_DIR = .moc_test
QT += core gui network printsupport testlib widgets
LIBS += -llog4cpp
INCLUDEPATH += Callback \
               Cmd \
               Curve \
               DigitizeState \
               Dlg \
               Document \
               Graphics \
               include \
               Load \
               Logger \
               main \
               Point \
               StatusBar \
               Transformation \
               util
