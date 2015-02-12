TEMPLATE    = app
CONFIG      = qt warn_on thread debug testcase
OBJECTS_DIR = .objs_test
MOC_DIR = .moc_test
RCC_DIR = .rcc_test

HEADERS  += \
    include/BackgroundImage.h \
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
    Cmd/CmdSettingsAxesChecker.h \
    Cmd/CmdSettingsCoords.h \
    Cmd/CmdSettingsCurveProperties.h \
    Cmd/CmdSettingsCurves.h \
    Cmd/CmdSettingsExport.h \
    Cmd/CmdSettingsFilter.h \
    Cmd/CmdSettingsGridRemoval.h \
    Cmd/CmdSettingsPointMatch.h \
    Cmd/CmdSettingsSegments.h \
    include/ColorPalette.h \
    Coord/CoordScale.h \
    Coord/CoordsType.h \
    Coord/CoordThetaUnits.h \
    Curve/Curve.h \
    Curve/CurveConnectAs.h \
    Curve/CurveSettingsInt.h \
    Curve/CurvesGraphs.h \
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
    Dlg/DlgFilterCommand.h \
    Dlg/DlgFilterThread.h \
    Dlg/DlgFilterWorker.h \
    Dlg/DlgSettingsAbstractBase.h \
    Dlg/DlgSettingsAxesChecker.h \
    Dlg/DlgSettingsCoords.h \
    Dlg/DlgSettingsCurves.h \
    Dlg/DlgSettingsCurveProperties.h \
    Dlg/DlgSettingsExport.h \
    Dlg/DlgSettingsFilter.h \
    Dlg/DlgSettingsGridRemoval.h \
    Dlg/DlgSettingsPointMatch.h \
    Dlg/DlgSettingsSegments.h \
    Dlg/DlgSpinBoxDouble.h \
    Dlg/DlgSpinBoxInt.h \
    Document/Document.h \
    Document/DocumentModelAbstractBase.h \
    Document/DocumentModelAxesChecker.h \
    Document/DocumentModelCoords.h \
    Document/DocumentModelCurveProperties.h \
    Document/DocumentModelCurves.h \
    Document/DocumentModelCurvesEntry.h \
    Document/DocumentModelExport.h \
    Document/DocumentModelFilter.h \
    Document/DocumentModelGridRemoval.h \
    Document/DocumentModelPointMatch.h \
    Document/DocumentModelSegments.h \
    util/EnumsToQt.h \
    Export/ExportLayoutFunctions.h \
    Export/ExportPointsSelectionFunctions.h \
    Export/ExportPointsSelectionRelations.h \
    Export/ExportDelimiter.h \
    Export/ExportHeader.h \
    Export/ExportToClipboard.h \
    Export/ExportToFile.h \
    Filter/Filter.h \
    Filter/FilterColorEntry.h \
    Filter/FilterMode.h \
    Callback/functor.h \
    Graphics/GraphicsItemType.h \
    Graphics/GraphicsPointAbstractBase.h \
    Graphics/GraphicsPoint.h \
    Graphics/GraphicsScene.h \
    Graphics/GraphicsView.h \
    Grid/GridCoordDisable.h \
    Highlight/Indicator.h \
    Line/LineStyle.h \
    Load/LoadImageFromUrl.h \
    Logger/Logger.h \
    main/MainWindow.h \
    Mime/MimePoints.h \
    Point/Point.h \
    Point/PointIdentifierToGraphicsPoint.h \
    Point/PointShape.h \
    Point/PointStyle.h \
    util/QtToString.h \
    Settings/SettingsCurve.h \
    StatusBar/StatusBar.h \
    StatusBar/StatusBarMode.h \
    Transformation/Transformation.h \
    View/ViewPreview.h \
    View/ViewProfile.h \
    View/ViewProfileDivider.h \
    View/ViewProfileParameters.h \
    View/ViewProfileScale.h \
    include/ZoomFactor.h

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
    Cmd/CmdSettingsAxesChecker.cpp \
    Cmd/CmdSettingsCoords.cpp \
    Cmd/CmdSettingsCurveProperties.cpp \
    Cmd/CmdSettingsCurves.cpp \
    Cmd/CmdSettingsExport.cpp \
    Cmd/CmdSettingsFilter.cpp \
    Cmd/CmdSettingsGridRemoval.cpp \
    Cmd/CmdSettingsPointMatch.cpp \
    Cmd/CmdSettingsSegments.cpp \
    Curve/Curve.cpp \
    Curve/CurveSettingsInt.cpp \
    Curve/CurvesGraphs.cpp \
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
    Dlg/DlgFilterCommand.cpp \
    Dlg/DlgFilterThread.cpp \
    Dlg/DlgFilterWorker.cpp \
    Dlg/DlgSettingsAbstractBase.cpp \
    Dlg/DlgSettingsAxesChecker.cpp \
    Dlg/DlgSettingsCoords.cpp \
    Dlg/DlgSettingsCurves.cpp \
    Dlg/DlgSettingsCurveProperties.cpp \
    Dlg/DlgSettingsExport.cpp \
    Dlg/DlgSettingsFilter.cpp \
    Dlg/DlgSettingsGridRemoval.cpp \
    Dlg/DlgSettingsPointMatch.cpp \
    Dlg/DlgSettingsSegments.cpp \
    Dlg/DlgSpinBoxDouble.cpp \
    Dlg/DlgSpinBoxInt.cpp \
    Document/Document.cpp \
    Document/DocumentModelAbstractBase.cpp \
    Document/DocumentModelAxesChecker.cpp \
    Document/DocumentModelCoords.cpp \
    Document/DocumentModelCurveProperties.cpp \
    Document/DocumentModelCurves.cpp \
    Document/DocumentModelCurvesEntry.cpp \
    Document/DocumentModelExport.cpp \
    Document/DocumentModelFilter.cpp \
    Document/DocumentModelGridRemoval.cpp \
    Document/DocumentModelPointMatch.cpp \
    Document/DocumentModelSegments.cpp \
    util/EnumsToQt.cpp \
    Export/ExportToClipboard.cpp \
    Export/ExportToFile.cpp \
    Filter/Filter.cpp \
    Graphics/GraphicsPointAbstractBase.cpp \
    Graphics/GraphicsPoint.cpp \
    Graphics/GraphicsScene.cpp \
    Graphics/GraphicsView.cpp \
    Line/LineStyle.cpp \
    Load/LoadImageFromUrl.cpp \
    Logger/Logger.cpp \
    main/MainWindow.cpp \
    Mime/MimePoints.cpp \
    Point/Point.cpp \
    Point/PointStyle.cpp \
    util/QtToString.cpp \
    Settings/SettingsCurve.cpp \
    StatusBar/StatusBar.cpp \
    Transformation/Transformation.cpp \
    View/ViewPreview.cpp \
    View/ViewProfile.cpp \
    View/ViewProfileDivider.cpp \
    View/ViewProfileParameters.cpp \
    View/ViewProfileScale.cpp

# Main entry point for test
HEADERS += Test/TestGraphCoords.h
SOURCES += Test/TestGraphCoords.cpp

TARGET = ../bin/engauge_test

QT += core gui network printsupport testlib widgets
LIBS += -llog4cpp
INCLUDEPATH += Callback \
               Cmd \
               Coord \
               Curve \
               DigitizeState \
               Dlg \
               Document \
               Export \
               Filter \
               Graphics \
               Grid \
               Highlight \
               img \
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
