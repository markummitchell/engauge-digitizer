# engauge.pro : Builds make files for engauge executable
#
# Instructions are in the INSTALL file, with some comments about setting the configuration variable 'CONFIG' included below

TEMPLATE    = app

# CONFIG comments:
# 1) Remove 'debug' in the CONFIG= line or set environment variable ENGAUGE_RELEASE=1 to create a release version 
#    without debug information
# 2) Add 'jpeg2000' to the CONFIG= line to include support for JPEG2000 input files. Requires JPEG2000_INCLUDE and JPEG2000_LIB 
#    environment variables
# 3) Gratuitous warning about import_qpa_plugin in Fedora is due to 'CONFIG=qt' but that option takes care of 
#    include/library files in an automated and platform-independent manner, so it will not be removed
CONFIG      = qt warn_on thread debug

_ENGAUGE_RELEASE = $$(ENGAUGE_RELEASE)
isEmpty(_ENGAUGE_RELEASE) {
} else {
CONFIG -= debug
# Comments:
# 1) Release version has warnings enabled so they can be removed
# 2) Full coverage requires disabling of ENGAUGE_ASSERT by setting QT_NO_DEBUG
# 3) -Wuninitialized requires O1, O2 or O3 optimization
DEFINES += QT_NO_DEBUG 
QMAKE_CXXFLAGS_WARN_ON += -Wreturn-type -O1 -Wuninitialized -Wunused-variable
}

OBJECTS_DIR = .objs
MOC_DIR = .moc
RCC_DIR = .rcc

HEADERS  += \
    Background/BackgroundImage.h \
    Background/BackgroundStateAbstractBase.h \
    Background/BackgroundStateContext.h \
    Background/BackgroundStateCurve.h \
    Background/BackgroundStateNone.h \
    Background/BackgroundStateOriginal.h \
    Background/BackgroundStateUnloaded.h \
    Callback/CallbackAddPointsInCurvesGraphs.h \
    Callback/CallbackAxesCheckerFromAxesPoints.h \
    Callback/CallbackAxisPointsAbstract.h \
    Callback/CallbackBoundingRects.h \
    Callback/CallbackCheckAddPointAxis.h \
    Callback/CallbackCheckEditPointAxis.h \
    Callback/CallbackGatherXThetaValuesFunctions.h \
    Callback/CallbackNextOrdinal.h \
    Callback/CallbackPointOrdinal.h \
    Callback/CallbackRemovePointsInCurvesGraphs.h \
    Callback/CallbackSceneUpdateAfterCommand.h \
    Callback/CallbackSearchReturn.h \
    Callback/CallbackUpdateTransform.h \
    Checker/Checker.h \
    Checker/CheckerMode.h \
    Checklist/ChecklistGuide.h \
    Checklist/ChecklistGuideBrowser.h \
    Checklist/ChecklistGuidePage.h \
    Checklist/ChecklistGuidePageConclusion.h \
    Checklist/ChecklistGuidePageCurves.h \
    Checklist/ChecklistGuidePageIntro.h \
    Checklist/ChecklistGuideWizard.h \
    Checklist/ChecklistLineEdit.h \
    Checklist/ChecklistTemplate.h \
    Cmd/CmdAbstract.h \
    Cmd/CmdAddPointAxis.h \
    Cmd/CmdAddPointGraph.h \
    Cmd/CmdAddPointsGraph.h \
    Cmd/CmdCopy.h \
    Cmd/CmdCut.h \
    Cmd/CmdDelete.h \
    Cmd/CmdEditPointAxis.h \
    Cmd/CmdFactory.h \
    Cmd/CmdMediator.h \
    Cmd/CmdMoveBy.h \
    Cmd/CmdPaste.h \
    Cmd/CmdSettingsAxesChecker.h \
    Cmd/CmdSettingsColorFilter.h \
    Cmd/CmdSettingsCommon.h \
    Cmd/CmdSettingsCoords.h \
    Cmd/CmdSettingsCurveAddRemove.h \
    Cmd/CmdSettingsCurveProperties.h \
    Cmd/CmdSettingsDigitizeCurve.h \
    Cmd/CmdSettingsExportFormat.h \
    Cmd/CmdSettingsGridRemoval.h \
    Cmd/CmdSettingsPointMatch.h \
    Cmd/CmdSettingsSegments.h \
    Cmd/CmdStackShadow.h \
    Color/ColorConstants.h \
    Color/ColorFilter.h \
    Color/ColorFilterEntry.h \
    Color/ColorFilterHistogram.h \
    Color/ColorFilterMode.h \
    Color/ColorFilterSettings.h \
    Color/ColorPalette.h \
    Coord/CoordScale.h \
    Coord/CoordsType.h \
    Coord/CoordSymbol.h \
    Coord/CoordUnitsDate.h \
    Coord/CoordUnitsNonPolarTheta.h \
    Coord/CoordUnitsPolarTheta.h \
    Coord/CoordUnitsTime.h \
    Correlation/Correlation.h \
    Cursor/CursorFactory.h \
    Cursor/CursorSize.h \
    Curve/Curve.h \
    Curve/CurveConnectAs.h \
    Curve/CurveNameList.h \
    Curve/CurveNameListEntry.h \
    Curve/CurveSettingsInt.h \
    Curve/CurvesGraphs.h \
    Curve/CurveStyle.h \
    Curve/CurveStyles.h \
    util/DataKey.h \
    DigitizeState/DigitizeStateAbstractBase.h \
    DigitizeState/DigitizeStateAxis.h \
    DigitizeState/DigitizeStateColorPicker.h \
    DigitizeState/DigitizeStateContext.h \
    DigitizeState/DigitizeStateCurve.h \
    DigitizeState/DigitizeStateEmpty.h \
    DigitizeState/DigitizeStatePointMatch.h \
    DigitizeState/DigitizeStateSegment.h \
    DigitizeState/DigitizeStateSelect.h \
    Dlg/DlgAbout.h \
    Dlg/DlgEditPoint.h \
    Dlg/DlgErrorReport.h \
    Dlg/DlgFilterCommand.h \
    Dlg/DlgFilterThread.h \
    Dlg/DlgFilterWorker.h \
    Dlg/DlgRequiresTransform.h \
    Dlg/DlgSettingsAbstractBase.h \
    Dlg/DlgSettingsAxesChecker.h \
    Dlg/DlgSettingsColorFilter.h \
    Dlg/DlgSettingsCommon.h \
    Dlg/DlgSettingsCoords.h \
    Dlg/DlgSettingsCurveAddRemove.h \
    Dlg/DlgSettingsCurveProperties.h \
    Dlg/DlgSettingsDigitizeCurve.h \
    Dlg/DlgSettingsExportFormat.h \
    Dlg/DlgSettingsGridRemoval.h \
    Dlg/DlgSettingsPointMatch.h \
    Dlg/DlgSettingsSegments.h \
    Dlg/DlgValidatorAbstract.h \
    Dlg/DlgValidatorDateTime.h \
    Dlg/DlgValidatorDegreesMinutesSeconds.h \
    Dlg/DlgValidatorFactory.h \
    Dlg/DlgValidatorNumber.h \
    Document/Document.h \
    Document/DocumentModelAbstractBase.h \
    Document/DocumentModelAxesChecker.h \
    Document/DocumentModelColorFilter.h \
    Document/DocumentModelCommon.h \
    Document/DocumentModelCoords.h \
    Document/DocumentModelDigitizeCurve.h \
    Document/DocumentModelExportFormat.h \
    Document/DocumentModelGridRemoval.h \
    Document/DocumentModelPointMatch.h \
    Document/DocumentModelSegments.h \
    Document/DocumentSerialize.h \
    include/EngaugeAssert.h \
    util/EnumsToQt.h \
    Export/ExportAlignLinear.h \
    Export/ExportAlignLog.h \
    Export/ExportDelimiter.h \
    Export/ExportLayoutFunctions.h \
    Export/ExportPointsIntervalUnits.h \
    Export/ExportPointsSelectionFunctions.h \
    Export/ExportPointsSelectionRelations.h \
    Export/ExportDelimiter.h \
    Export/ExportFileAbstractBase.h \
    Export/ExportFileFunctions.h \
    Export/ExportFileRelations.h \
    Export/ExportHeader.h \
    Export/ExportOrdinalsSmooth.h \
    Export/ExportOrdinalsStraight.h \
    Export/ExportToClipboard.h \
    Export/ExportToFile.h \
    Export/ExportValuesOrdinal.h \
    Export/ExportValuesXOrY.h \
    Export/ExportXThetaValuesMergedFunctions.h \
    Filter/FilterImage.h \
    Format/FormatCoordsUnits.h \
    Format/FormatCoordsUnitsStrategyAbstractBase.h \
    Format/FormatCoordsUnitsStrategyNonPolarTheta.h \
    Format/FormatCoordsUnitsStrategyPolarTheta.h \
    Format/FormatDateTime.h \
    Format/FormatDegreesMinutesSecondsBase.h \
    Format/FormatDegreesMinutesSecondsNonPolarTheta.h \
    Format/FormatDegreesMinutesSecondsPolarTheta.h \
    Callback/functor.h \
    Graphics/GraphicsArcItem.h \
    Graphics/GraphicsItemType.h \
    Graphics/GraphicsLinesForCurve.h \
    Graphics/GraphicsLinesForCurves.h \
    Graphics/GraphicsPoint.h \
    Graphics/GraphicsPointAbstractBase.h \
    Graphics/GraphicsPointEllipse.h \
    Graphics/GraphicsPointFactory.h \
    Graphics/GraphicsPointPolygon.h \
    Graphics/GraphicsScene.h \
    Graphics/GraphicsView.h \
    Grid/GridClassifier.h \
    Grid/GridCoordDisable.h \
    Grid/GridHealer.h \
    Grid/GridRemoval.h \
    Help/HelpBrowser.h \
    Help/HelpWindow.h \
    Line/LineStyle.h \
    Load/LoadImageFromUrl.h \
    Logger/Logger.h \
    Logger/LoggerUpload.h \
    main/MainWindow.h \
    Mime/MimePoints.h \
    util/mmsubs.h \
    Network/NetworkClient.h \
    Ordinal/OrdinalGenerator.h \
    Ordinal/OrdinalToGraphicsPoint.h \
    Point/Point.h \
    Point/PointComparator.h \
    Point/PointIdentifiers.h \
    Point/PointMatchAlgorithm.h \
    Point/PointMatchPixel.h \
    Point/PointMatchTriplet.h \
    Point/Points.h \
    Point/PointShape.h \
    Point/PointStyle.h \
    util/QtToString.h \
    Segment/Segment.h \
    Segment/SegmentFactory.h \
    Segment/SegmentLine.h \
    Settings/Settings.h \
    Spline/Spline.h \
    Spline/SplineCoeff.h \
    Spline/SplinePair.h \
    StatusBar/StatusBar.h \
    StatusBar/StatusBarMode.h \
    Transformation/Transformation.h \
    Transformation/TransformationStateAbstractBase.h \
    Transformation/TransformationStateContext.h \
    Transformation/TransformationStateDefined.h \
    Transformation/TransformationStateUndefined.h \
    Tutorial/TutorialButton.h \
    Tutorial/TutorialButtonRect.h \
    Tutorial/TutorialButtonText.h \
    Tutorial/TutorialDlg.h \
    Tutorial/TutorialStateAbstractBase.h \
    Tutorial/TutorialStateAxisPoints.h \
    Tutorial/TutorialStateChecklistWizardAbstract.h \
    Tutorial/TutorialStateChecklistWizardLines.h \
    Tutorial/TutorialStateChecklistWizardPoints.h \
    Tutorial/TutorialStateColorFilter.h \
    Tutorial/TutorialStateContext.h \
    Tutorial/TutorialStateCurveSelection.h \
    Tutorial/TutorialStateCurveType.h \
    Tutorial/TutorialStateIntroduction.h \
    Tutorial/TutorialStatePointMatch.h \
    Tutorial/TutorialStateSegmentFill.h \
    include/ValuesVectorXOrY.h \
    util/Version.h \
    View/ViewPointStyle.h \
    View/ViewPreview.h \
    View/ViewProfile.h \
    View/ViewProfileDivider.h \
    View/ViewProfileParameters.h \
    View/ViewProfileScale.h \
    View/ViewSegmentFilter.h \
    util/Xml.h \
    include/ZoomFactor.h

SOURCES += \
    Background/BackgroundImage.cpp \
    Background/BackgroundStateAbstractBase.cpp \
    Background/BackgroundStateContext.cpp \
    Background/BackgroundStateCurve.cpp \
    Background/BackgroundStateNone.cpp \
    Background/BackgroundStateOriginal.cpp \
    Background/BackgroundStateUnloaded.cpp \
    Callback/CallbackAddPointsInCurvesGraphs.cpp \
    Callback/CallbackAxesCheckerFromAxesPoints.cpp \
    Callback/CallbackAxisPointsAbstract.cpp \
    Callback/CallbackBoundingRects.cpp \
    Callback/CallbackCheckAddPointAxis.cpp \
    Callback/CallbackCheckEditPointAxis.cpp \
    Callback/CallbackGatherXThetaValuesFunctions.cpp \
    Callback/CallbackNextOrdinal.cpp \
    Callback/CallbackPointOrdinal.cpp \
    Callback/CallbackRemovePointsInCurvesGraphs.cpp \
    Callback/CallbackSceneUpdateAfterCommand.cpp \
    Callback/CallbackUpdateTransform.cpp \
    Checker/Checker.cpp \
    Checker/CheckerMode.cpp \
    Checklist/ChecklistGuide.cpp \
    Checklist/ChecklistGuideBrowser.cpp \
    Checklist/ChecklistGuidePage.cpp \
    Checklist/ChecklistGuidePageConclusion.cpp \
    Checklist/ChecklistGuidePageCurves.cpp \
    Checklist/ChecklistGuidePageIntro.cpp \
    Checklist/ChecklistGuideWizard.cpp \
    Checklist/ChecklistLineEdit.cpp \
    Checklist/ChecklistTemplate.cpp \
    Cmd/CmdAbstract.cpp \
    Cmd/CmdAddPointAxis.cpp \
    Cmd/CmdAddPointGraph.cpp \
    Cmd/CmdAddPointsGraph.cpp \
    Cmd/CmdCopy.cpp \
    Cmd/CmdCut.cpp \
    Cmd/CmdDelete.cpp \
    Cmd/CmdEditPointAxis.cpp \
    Cmd/CmdFactory.cpp \
    Cmd/CmdMediator.cpp \
    Cmd/CmdMoveBy.cpp \
    Cmd/CmdPaste.cpp \
    Cmd/CmdSettingsAxesChecker.cpp \
    Cmd/CmdSettingsColorFilter.cpp \
    Cmd/CmdSettingsCommon.cpp \
    Cmd/CmdSettingsCoords.cpp \
    Cmd/CmdSettingsCurveAddRemove.cpp \
    Cmd/CmdSettingsCurveProperties.cpp \
    Cmd/CmdSettingsDigitizeCurve.cpp \
    Cmd/CmdSettingsExportFormat.cpp \
    Cmd/CmdSettingsGridRemoval.cpp \
    Cmd/CmdSettingsPointMatch.cpp \
    Cmd/CmdSettingsSegments.cpp \
    Cmd/CmdStackShadow.cpp \
    Color/ColorFilter.cpp \
    Color/ColorFilterHistogram.cpp \
    Color/ColorFilterMode.cpp \
    Color/ColorFilterSettings.cpp \
    Color/ColorPalette.cpp \
    Coord/CoordScale.cpp \
    Coord/CoordsType.cpp \
    Coord/CoordSymbol.cpp \
    Coord/CoordUnitsDate.cpp \
    Coord/CoordUnitsNonPolarTheta.cpp \
    Coord/CoordUnitsPolarTheta.cpp \
    Coord/CoordUnitsTime.cpp \
    Correlation/Correlation.cpp \
    Cursor/CursorFactory.cpp \
    Cursor/CursorSize.cpp \
    Curve/Curve.cpp \
    Curve/CurveConnectAs.cpp \
    Curve/CurveNameList.cpp \
    Curve/CurveNameListEntry.cpp \
    Curve/CurveSettingsInt.cpp \
    Curve/CurvesGraphs.cpp \
    Curve/CurveStyle.cpp \
    Curve/CurveStyles.cpp \
    util/DataKey.cpp \
    DigitizeState/DigitizeStateAbstractBase.cpp \
    DigitizeState/DigitizeStateAxis.cpp \
    DigitizeState/DigitizeStateColorPicker.cpp \
    DigitizeState/DigitizeStateContext.cpp \
    DigitizeState/DigitizeStateCurve.cpp \
    DigitizeState/DigitizeStateEmpty.cpp \
    DigitizeState/DigitizeStatePointMatch.cpp \
    DigitizeState/DigitizeStateSegment.cpp \
    DigitizeState/DigitizeStateSelect.cpp \
    Dlg/DlgAbout.cpp \
    Dlg/DlgEditPoint.cpp \
    Dlg/DlgErrorReport.cpp \
    Dlg/DlgFilterCommand.cpp \
    Dlg/DlgFilterThread.cpp \
    Dlg/DlgFilterWorker.cpp \
    Dlg/DlgRequiresTransform.cpp \
    Dlg/DlgSettingsAbstractBase.cpp \
    Dlg/DlgSettingsAxesChecker.cpp \
    Dlg/DlgSettingsColorFilter.cpp \
    Dlg/DlgSettingsCommon.cpp \
    Dlg/DlgSettingsCoords.cpp \
    Dlg/DlgSettingsCurveAddRemove.cpp \
    Dlg/DlgSettingsCurveProperties.cpp \
    Dlg/DlgSettingsDigitizeCurve.cpp \
    Dlg/DlgSettingsExportFormat.cpp \
    Dlg/DlgSettingsGridRemoval.cpp \
    Dlg/DlgSettingsPointMatch.cpp \
    Dlg/DlgSettingsSegments.cpp \
    Dlg/DlgValidatorAbstract.cpp \
    Dlg/DlgValidatorDateTime.cpp \
    Dlg/DlgValidatorDegreesMinutesSeconds.cpp \
    Dlg/DlgValidatorFactory.cpp \
    Dlg/DlgValidatorNumber.cpp \
    Document/Document.cpp \
    Document/DocumentModelAbstractBase.cpp \
    Document/DocumentModelAxesChecker.cpp \
    Document/DocumentModelColorFilter.cpp \
    Document/DocumentModelCommon.cpp \
    Document/DocumentModelCoords.cpp \
    Document/DocumentModelDigitizeCurve.cpp \
    Document/DocumentModelExportFormat.cpp \
    Document/DocumentModelGridRemoval.cpp \
    Document/DocumentModelPointMatch.cpp \
    Document/DocumentModelSegments.cpp \
    Document/DocumentSerialize.cpp \
    util/EnumsToQt.cpp \
    Export/ExportAlignLinear.cpp \
    Export/ExportAlignLog.cpp \
    Export/ExportDelimiter.cpp \
    Export/ExportFileAbstractBase.cpp \
    Export/ExportFileFunctions.cpp \
    Export/ExportFileRelations.cpp \
    Export/ExportHeader.cpp \
    Export/ExportLayoutFunctions.cpp \
    Export/ExportOrdinalsSmooth.cpp \
    Export/ExportOrdinalsStraight.cpp \
    Export/ExportPointsIntervalUnits.cpp \
    Export/ExportPointsSelectionFunctions.cpp \
    Export/ExportPointsSelectionRelations.cpp \
    Export/ExportToClipboard.cpp \
    Export/ExportToFile.cpp \
    Export/ExportXThetaValuesMergedFunctions.cpp \
    Filter/FilterImage.cpp \
    Format/FormatCoordsUnits.cpp \
    Format/FormatCoordsUnitsStrategyAbstractBase.cpp \
    Format/FormatCoordsUnitsStrategyNonPolarTheta.cpp \
    Format/FormatCoordsUnitsStrategyPolarTheta.cpp \
    Format/FormatDateTime.cpp \
    Format/FormatDegreesMinutesSecondsBase.cpp \
    Format/FormatDegreesMinutesSecondsNonPolarTheta.cpp \
    Format/FormatDegreesMinutesSecondsPolarTheta.cpp \
    Graphics/GraphicsArcItem.cpp \
    Graphics/GraphicsLinesForCurve.cpp \
    Graphics/GraphicsLinesForCurves.cpp \
    Graphics/GraphicsPoint.cpp \
    Graphics/GraphicsPointAbstractBase.cpp \
    Graphics/GraphicsPointEllipse.cpp \
    Graphics/GraphicsPointFactory.cpp \
    Graphics/GraphicsPointPolygon.cpp \
    Graphics/GraphicsScene.cpp \
    Graphics/GraphicsView.cpp \
    Grid/GridClassifier.cpp \
    Grid/GridCoordDisable.cpp \
    Grid/GridHealer.cpp \
    Grid/GridRemoval.cpp \
    Help/HelpBrowser.cpp \
    Help/HelpWindow.cpp \
    Line/LineStyle.cpp \
    Load/LoadImageFromUrl.cpp \
    Logger/Logger.cpp \
    Logger/LoggerUpload.cpp \
    main/main.cpp \
    main/MainWindow.cpp \
    Mime/MimePoints.cpp \
    util/mmsubs.cpp \
    Network/NetworkClient.cpp \
    Ordinal/OrdinalGenerator.cpp \
    Point/Point.cpp \
    Point/PointIdentifiers.cpp \
    Point/PointMatchAlgorithm.cpp \
    Point/PointMatchPixel.cpp \
    Point/PointMatchTriplet.cpp \
    Point/PointShape.cpp \
    Point/PointStyle.cpp \
    util/QtToString.cpp \
    Segment/Segment.cpp \
    Segment/SegmentFactory.cpp \
    Segment/SegmentLine.cpp \
    Settings/Settings.cpp \
    Spline/Spline.cpp \
    Spline/SplineCoeff.cpp \
    Spline/SplinePair.cpp \
    StatusBar/StatusBar.cpp \
    Transformation/Transformation.cpp \
    Transformation/TransformationStateAbstractBase.cpp \
    Transformation/TransformationStateContext.cpp \
    Transformation/TransformationStateDefined.cpp \
    Transformation/TransformationStateUndefined.cpp \
    Tutorial/TutorialButton.cpp \
    Tutorial/TutorialButtonRect.cpp \
    Tutorial/TutorialButtonText.cpp \
    Tutorial/TutorialDlg.cpp \
    Tutorial/TutorialStateAbstractBase.cpp \
    Tutorial/TutorialStateAxisPoints.cpp \
    Tutorial/TutorialStateChecklistWizardAbstract.cpp \
    Tutorial/TutorialStateChecklistWizardLines.cpp \
    Tutorial/TutorialStateChecklistWizardPoints.cpp \
    Tutorial/TutorialStateColorFilter.cpp \
    Tutorial/TutorialStateContext.cpp \
    Tutorial/TutorialStateCurveSelection.cpp \
    Tutorial/TutorialStateCurveType.cpp \
    Tutorial/TutorialStateIntroduction.cpp \
    Tutorial/TutorialStatePointMatch.cpp \
    Tutorial/TutorialStateSegmentFill.cpp \
    util/Version.cpp \
    View/ViewPointStyle.cpp \
    View/ViewPreview.cpp \
    View/ViewProfile.cpp \
    View/ViewProfileDivider.cpp \
    View/ViewProfileParameters.cpp \
    View/ViewProfileScale.cpp \
    View/ViewSegmentFilter.cpp \
    util/Xml.cpp

TARGET = ../bin/engauge

QT += core gui network printsupport widgets xml help

win32-g++* {
CONFIG += windows
LIBS += -L$$(LOG4CPP_HOME)/lib -L$$(FFTW_HOME)/lib
}
LIBS += -llog4cpp -lfftw3

INCLUDEPATH += Background \
               Callback \
               Checker \
               Checklist \
               Cmd \
               Color \
               Coord \
               Correlation \
               Cursor \
               Curve \
               DigitizeState \
               Dlg \
               Document \
               Export \
               Filter \
               Format \
               Graphics \
               Grid \
               Help \
               img \
               include \
               Line \
               Load \
               Logger \
               main \
               Mime \
               Network \
               Ordinal \
               Plot \
               Point \
               Segment \
               Settings \
               Spline \
               StatusBar \
               Transformation \
               Tutorial \
               util \
               View

win32-g++* {
INCLUDEPATH += $$(FFTW_HOME)/include \
               $$(LOG4CPP_HOME)/include
}

RESOURCES += \
    engauge.qrc

jpeg2000 {
    CONFIG(debug,debug|release) {
      message(Building debug version with support for JPEG2000 files)
    } else {
      message(Building release version with support for JPEG2000 files)
    }
    _JPEG2000_INCLUDE = $$(JPEG2000_INCLUDE)
    _JPEG2000_LIB = $$(JPEG2000_LIB)
    isEmpty(_JPEG2000_INCLUDE) {
      error("JPEG2000_INCLUDE and JPEG2000_LIB environment variables must be defined")
    } else {
      isEmpty(_JPEG2000_LIB) {
        error("JPEG2000_INCLUDE and JPEG2000_LIB environment variables must be defined")
      }
    }
    DEFINES += "ENGAUGE_JPEG2000"
    INCLUDEPATH += Jpeg2000 \
                   $$(JPEG2000_INCLUDE)
    LIBS += -L$$(JPEG2000_LIB) -lopenjp2

    HEADERS += Jpeg2000/Jpeg2000.h \
               Jpeg2000/Jpeg2000Callbacks.h \
               Jpeg2000/Jpeg2000Color.h \
               Jpeg2000/Jpeg2000Convert.h \
               Jpeg2000/Jpeg2000FormatDefs.h

    SOURCES += Jpeg2000/Jpeg2000.cpp \
               Jpeg2000/Jpeg2000Callbacks.cpp \
               Jpeg2000/Jpeg2000Color.cpp \
               Jpeg2000/Jpeg2000Convert.cpp

} else {
    CONFIG(debug,debug|release) {
      message(Building debug version without support for JPEG2000 files)
    } else {
      message(Building release version without support for JPEG2000 files)
    }
}
