TEMPLATE    = app
CONFIG      = qt warn_on thread debug
OBJECTS_DIR = .objs
MOC_DIR = .moc
RCC_DIR = .rcc

HEADERS  += \
    Callback/CallbackAddPointsInCurvesGraphs.h \
    Callback/CallbackAxisPointsAbstract.h \
    Callback/CallbackCheckAddPointAxis.h \
    Callback/CallbackCheckEditPointAxis.h \
    Callback/CallbackRemovePointsInCurvesGraphs.h \
    Callback/CallbackSceneUpdateAfterCommand.h \
    Callback/CallbackSearchReturn.h \
    Callback/CallbackUpdateTransform.h \
    Cmd/CmdAbstract.h \
    Cmd/CmdAddPointAxis.h \
    Cmd/CmdAddPointGraph.h \
    Cmd/CmdCopy.h \
    Cmd/CmdCut.h \
    Cmd/CmdDelete.h \
    Cmd/CmdEditPointAxis.h \
    Cmd/CmdMediator.h \
    Cmd/CmdMoveBy.h \
    Cmd/CmdPaste.h \
    include/ColorPalette.h \
    include/CoordsType.h \
    Curve/Curve.h \
    Curve/CurveConnectAs.h \
    Curve/CurvesGraphs.h \
    Curve/CurveStyle.h \
    include/DataKey.h \
    DigitizeState/DigitizeStateAbstractBase.h \
    DigitizeState/DigitizeStateAxis.h \
    DigitizeState/DigitizeStateContext.h \
    DigitizeState/DigitizeStateCurve.h \
    DigitizeState/DigitizeStateEmpty.h \
    DigitizeState/DigitizeStatePointMatch.h \
    DigitizeState/DigitizeStateScale.h \
    DigitizeState/DigitizeStateSegment.h \
    DigitizeState/DigitizeStateSelect.h \
    Dlg/DlgEditPoint.h \
    Dlg/DlgEditPreferences.h \
    Dlg/DlgModelCurveEntry.h \
    Dlg/DlgModelCurves.h \
    Dlg/DlgPreferencesPageAbstractBase.h \
    Dlg/DlgPreferencesPageCoords.h \
    Dlg/DlgPreferencesPageCurves.h \
    Dlg/DlgPreferencesPageCurveProperties.h \
    Dlg/DlgPreferencesPageExport.h \
    Dlg/DlgPreferencesPageFilter.h \
    Dlg/DlgPreferencesPageGridDisplay.h \
    Dlg/DlgPreferencesPageGridRemoval.h \
    Dlg/DlgPreferencesPagePointMatch.h \
    Dlg/DlgPreferencesPageSegments.h \
    Document/Document.h \
    Callback/functor.h \
    Graphics/GraphicsItemType.h \
    Graphics/GraphicsPointAbstractBase.h \
    Graphics/GraphicsPointCircle.h \
    Graphics/GraphicsPointPolygon.h \
    Graphics/GraphicsScene.h \
    Graphics/GraphicsView.h \
    Line/LineStyle.h \
    Load/LoadImageFromUrl.h \
    Logger/Logger.h \
    main/MainWindow.h \
    Mime/MimePoints.h \
    Point/Point.h \
    Point/PointIdentifierToGraphicsItem.h \
    Point/PointShape.h \
    Point/PointStyle.h \
    util/QtToString.h \
    Settings/SettingsCurve.h \
    Settings/SettingsCurves.h \
    StatusBar/StatusBar.h \
    StatusBar/StatusBarMode.h \
    Transformation/Transformation.h \
    View/ViewPreview.h \
    View/ViewProfile.h \
    View/ViewProfileDivider.h \
    View/ViewProfileParameters.h \
    View/ViewProfileShades.h \
    include/ZoomFactor.h \
    Dlg/DlgViewCurves.h

SOURCES += \
    Callback/CallbackAddPointsInCurvesGraphs.cpp \
    Callback/CallbackAxisPointsAbstract.cpp \
    Callback/CallbackCheckAddPointAxis.cpp \
    Callback/CallbackCheckEditPointAxis.cpp \
    Callback/CallbackRemovePointsInCurvesGraphs.cpp \
    Callback/CallbackSceneUpdateAfterCommand.cpp \
    Callback/CallbackUpdateTransform.cpp \
    Cmd/CmdAbstract.cpp \
    Cmd/CmdAddPointAxis.cpp \
    Cmd/CmdAddPointGraph.cpp \
    Cmd/CmdCopy.cpp \
    Cmd/CmdCut.cpp \
    Cmd/CmdDelete.cpp \
    Cmd/CmdEditPointAxis.cpp \
    Cmd/CmdMediator.cpp \
    Cmd/CmdMoveBy.cpp \
    Cmd/CmdPaste.cpp \
    Curve/Curve.cpp \
    Curve/CurvesGraphs.cpp \
    Curve/CurveStyle.cpp \
    DigitizeState/DigitizeStateAbstractBase.cpp \
    DigitizeState/DigitizeStateAxis.cpp \
    DigitizeState/DigitizeStateContext.cpp \
    DigitizeState/DigitizeStateCurve.cpp \
    DigitizeState/DigitizeStateEmpty.cpp \
    DigitizeState/DigitizeStatePointMatch.cpp \
    DigitizeState/DigitizeStateScale.cpp \
    DigitizeState/DigitizeStateSegment.cpp \
    DigitizeState/DigitizeStateSelect.cpp \
    Dlg/DlgEditPoint.cpp \
    Dlg/DlgEditPreferences.cpp \
    Dlg/DlgModelCurveEntry.cpp \
    Dlg/DlgModelCurves.cpp \
    Dlg/DlgPreferencesPageAbstractBase.cpp \
    Dlg/DlgPreferencesPageCoords.cpp \
    Dlg/DlgPreferencesPageCurves.cpp \
    Dlg/DlgPreferencesPageCurveProperties.cpp \
    Dlg/DlgPreferencesPageExport.cpp \
    Dlg/DlgPreferencesPageFilter.cpp \
    Dlg/DlgPreferencesPageGridDisplay.cpp \
    Dlg/DlgPreferencesPageGridRemoval.cpp \
    Dlg/DlgPreferencesPagePointMatch.cpp \
    Dlg/DlgPreferencesPageSegments.cpp \
    Document/Document.cpp \
    Graphics/GraphicsPointAbstractBase.cpp \
    Graphics/GraphicsPointCircle.cpp \
    Graphics/GraphicsPointPolygon.cpp \
    Graphics/GraphicsScene.cpp \
    Graphics/GraphicsView.cpp \
    Line/LineStyle.cpp \
    Load/LoadImageFromUrl.cpp \
    Logger/Logger.cpp \
    main/main.cpp \
    main/MainWindow.cpp \
    Mime/MimePoints.cpp \
    Point/Point.cpp \
    Point/PointStyle.cpp \
    util/QtToString.cpp \
    Settings/SettingsCurve.cpp \
    Settings/SettingsCurves.cpp \
    StatusBar/StatusBar.cpp \
    Transformation/Transformation.cpp \
    View/ViewPreview.cpp \
    View/ViewProfile.cpp \
    View/ViewProfileDivider.cpp \
    View/ViewProfileParameters.cpp \
    View/ViewProfileShades.cpp \
    Dlg/DlgViewCurves.cpp

TARGET = ../bin/engauge

QT += core gui network printsupport widgets
LIBS += -llog4cpp
INCLUDEPATH += Callback \
               Cmd \
               Curve \
               DigitizeState \
               Dlg \
               Document \
               Graphics \
               include \
               Line \
               Load \
               Logger \
               main \
               Mime \
               Plot \
               Point \
               Settings \
               StatusBar \
               Transformation \
               util \
               View

RESOURCES += \
    engauge.qrc
