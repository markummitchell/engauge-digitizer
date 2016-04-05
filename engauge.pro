# engauge.pro : Builds make files for engauge executable
#
# Comments:
# 1) Set environment variable ENGAUGE_RELEASE=1 to create a release version  without debug information. Releases use
#    dynamic linking to allow plugins (like Qt Help Collection and some image format libraries)
# 2) Remove 'debug' in the CONFIG= line to build without debug information, when not creating a release
# 3) Add 'jpeg2000' to the CONFIG= line to include support for JPEG2000 input files. Requires JPEG2000_INCLUDE and JPEG2000_LIB 
#    environment variables. At some point, Qt may provide its own support for this format, at which point this can be skipped
# 4) Gratuitous warning about import_qpa_plugin in Fedora is due to 'CONFIG=qt' but that option takes care of 
#    include/library files in an automated and platform-independent manner, so it will not be removed
# 5) Set environment variable HELPDIR to override the default directory for the help files. On the command line, use
#    qmake "DEFINES+=HELPDIR=<directory>". The <directory> is absolute or relative to the application executable directory
#
# More comments are in the INSTALL file, and below

# Comment out this CONFIG line in OSX to produce an OSX application bundle
CONFIG = qt warn_on thread debug
QT += core gui help network printsupport widgets xml

_ENGAUGE_RELEASE = $$(ENGAUGE_RELEASE)
isEmpty(_ENGAUGE_RELEASE) {
} else {
CONFIG -= debug
# Comments:
# 1) Release version has warnings enabled so they can be removed
# 2) Full coverage requires disabling of ENGAUGE_ASSERT by setting QT_NO_DEBUG
# 3) -Wuninitialized requires O1, O2 or O3 optimization
DEFINES += QT_NO_DEBUG
*-g++* {
QMAKE_CXXFLAGS_WARN_ON += -Wreturn-type -O1 -Wuninitialized -Wunused-variable
}
}

OBJECTS_DIR = src/.objs
MOC_DIR = src/.moc
RCC_DIR = src/.rcc

HEADERS  += \
    src/Background/BackgroundImage.h \
    src/Background/BackgroundStateAbstractBase.h \
    src/Background/BackgroundStateContext.h \
    src/Background/BackgroundStateCurve.h \
    src/Background/BackgroundStateNone.h \
    src/Background/BackgroundStateOriginal.h \
    src/Background/BackgroundStateUnloaded.h \
    src/Callback/CallbackAddPointsInCurvesGraphs.h \
    src/Callback/CallbackAxesCheckerFromAxesPoints.h \
    src/Callback/CallbackAxisPointsAbstract.h \
    src/Callback/CallbackBoundingRects.h \
    src/Callback/CallbackCheckAddPointAxis.h \
    src/Callback/CallbackCheckEditPointAxis.h \
    src/Callback/CallbackGatherXThetaValuesFunctions.h \
    src/Callback/CallbackNextOrdinal.h \
    src/Callback/CallbackPointOrdinal.h \
    src/Callback/CallbackRemovePointsInCurvesGraphs.h \
    src/Callback/CallbackSceneUpdateAfterCommand.h \
    src/Callback/CallbackSearchReturn.h \
    src/Callback/CallbackUpdateTransform.h \
    src/Checker/Checker.h \
    src/Checker/CheckerMode.h \
    src/Checklist/ChecklistGuide.h \
    src/Checklist/ChecklistGuideBrowser.h \
    src/Checklist/ChecklistGuidePage.h \
    src/Checklist/ChecklistGuidePageConclusion.h \
    src/Checklist/ChecklistGuidePageCurves.h \
    src/Checklist/ChecklistGuidePageIntro.h \
    src/Checklist/ChecklistGuideWizard.h \
    src/Checklist/ChecklistLineEdit.h \
    src/Checklist/ChecklistTemplate.h \
    src/Cmd/CmdAbstract.h \
    src/Cmd/CmdAddPointAxis.h \
    src/Cmd/CmdAddPointGraph.h \
    src/Cmd/CmdAddPointsGraph.h \
    src/Cmd/CmdCopy.h \
    src/Cmd/CmdCut.h \
    src/Cmd/CmdDelete.h \
    src/Cmd/CmdEditPointAxis.h \
    src/Cmd/CmdFactory.h \
    src/Cmd/CmdMediator.h \
    src/Cmd/CmdMoveBy.h \
    src/Cmd/CmdPaste.h \
    src/Cmd/CmdSelectCoordSystem.h \
    src/Cmd/CmdSettingsAxesChecker.h \
    src/Cmd/CmdSettingsColorFilter.h \
    src/Cmd/CmdSettingsCoords.h \
    src/Cmd/CmdSettingsCurveAddRemove.h \
    src/Cmd/CmdSettingsCurveProperties.h \
    src/Cmd/CmdSettingsDigitizeCurve.h \
    src/Cmd/CmdSettingsExportFormat.h \
    src/Cmd/CmdSettingsGeneral.h \
    src/Cmd/CmdSettingsGridRemoval.h \
    src/Cmd/CmdSettingsPointMatch.h \
    src/Cmd/CmdSettingsSegments.h \
    src/Cmd/CmdStackShadow.h \
    src/Color/ColorConstants.h \
    src/Color/ColorFilter.h \
    src/Color/ColorFilterEntry.h \
    src/Color/ColorFilterHistogram.h \
    src/Color/ColorFilterMode.h \
    src/Color/ColorFilterSettings.h \
    src/Color/ColorPalette.h \
    src/Coord/CoordScale.h \
    src/Coord/CoordsType.h \
    src/Coord/CoordSymbol.h \
    src/CoordSystem/CoordSystem.h \
    src/CoordSystem/CoordSystemContext.h \
    src/CoordSystem/CoordSystemIndex.h \
    src/CoordSystem/CoordSystemInterface.h \
    src/Coord/CoordUnitsDate.h \
    src/Coord/CoordUnitsNonPolarTheta.h \
    src/Coord/CoordUnitsPolarTheta.h \
    src/Coord/CoordUnitsTime.h \
    src/Correlation/Correlation.h \
    src/Cursor/CursorFactory.h \
    src/Cursor/CursorSize.h \
    src/Curve/Curve.h \
    src/Curve/CurveConnectAs.h \
    src/Curve/CurveNameList.h \
    src/Curve/CurveNameListEntry.h \
    src/Curve/CurveSettingsInt.h \
    src/Curve/CurvesGraphs.h \
    src/Curve/CurveStyle.h \
    src/Curve/CurveStyles.h \
    src/util/DataKey.h \
    src/DigitizeState/DigitizeStateAbstractBase.h \
    src/DigitizeState/DigitizeStateAxis.h \
    src/DigitizeState/DigitizeStateColorPicker.h \
    src/DigitizeState/DigitizeStateContext.h \
    src/DigitizeState/DigitizeStateCurve.h \
    src/DigitizeState/DigitizeStateEmpty.h \
    src/DigitizeState/DigitizeStatePointMatch.h \
    src/DigitizeState/DigitizeStateSegment.h \
    src/DigitizeState/DigitizeStateSelect.h \
    src/Dlg/DlgAbout.h \
    src/Dlg/DlgEditPoint.h \
    src/Dlg/DlgErrorReport.h \
    src/Dlg/DlgFilterCommand.h \
    src/Dlg/DlgFilterThread.h \
    src/Dlg/DlgFilterWorker.h \
    src/Dlg/DlgImportAdvanced.h \
    src/Dlg/DlgRequiresTransform.h \
    src/Dlg/DlgSettingsAbstractBase.h \
    src/Dlg/DlgSettingsAxesChecker.h \
    src/Dlg/DlgSettingsColorFilter.h \
    src/Dlg/DlgSettingsCoords.h \
    src/Dlg/DlgSettingsCurveAddRemove.h \
    src/Dlg/DlgSettingsCurveProperties.h \
    src/Dlg/DlgSettingsDigitizeCurve.h \
    src/Dlg/DlgSettingsExportFormat.h \
    src/Dlg/DlgSettingsGeneral.h \
    src/Dlg/DlgSettingsGridRemoval.h \
    src/Dlg/DlgSettingsMainWindow.h \
    src/Dlg/DlgSettingsPointMatch.h \
    src/Dlg/DlgSettingsSegments.h \
    src/Dlg/DlgValidatorAbstract.h \
    src/Dlg/DlgValidatorDateTime.h \
    src/Dlg/DlgValidatorDegreesMinutesSeconds.h \
    src/Dlg/DlgValidatorFactory.h \
    src/Dlg/DlgValidatorNumber.h \
    src/Document/Document.h \
    src/Document/DocumentAxesPointsRequired.h \
    src/Document/DocumentModelAbstractBase.h \
    src/Document/DocumentModelAxesChecker.h \
    src/Document/DocumentModelColorFilter.h \
    src/Document/DocumentModelCoords.h \
    src/Document/DocumentModelDigitizeCurve.h \
    src/Document/DocumentModelExportFormat.h \
    src/Document/DocumentModelGeneral.h \
    src/Document/DocumentModelGridRemoval.h \
    src/Document/DocumentModelPointMatch.h \
    src/Document/DocumentModelSegments.h \
    src/Document/DocumentSerialize.h \
    src/include/EngaugeAssert.h \
    src/util/EnumsToQt.h \
    src/Export/ExportAlignLinear.h \
    src/Export/ExportAlignLog.h \
    src/Export/ExportDelimiter.h \
    src/Export/ExportLayoutFunctions.h \
    src/Export/ExportPointsIntervalUnits.h \
    src/Export/ExportPointsSelectionFunctions.h \
    src/Export/ExportPointsSelectionRelations.h \
    src/Export/ExportDelimiter.h \
    src/Export/ExportFileAbstractBase.h \
    src/Export/ExportFileFunctions.h \
    src/Export/ExportFileRelations.h \
    src/Export/ExportHeader.h \
    src/Export/ExportOrdinalsSmooth.h \
    src/Export/ExportOrdinalsStraight.h \
    src/Export/ExportToClipboard.h \
    src/Export/ExportToFile.h \
    src/Export/ExportValuesOrdinal.h \
    src/Export/ExportValuesXOrY.h \
    src/Export/ExportXThetaValuesMergedFunctions.h \
    src/FileCmd/FileCmdAbstract.h \
    src/FileCmd/FileCmdClose.h \
    src/FileCmd/FileCmdExport.h \
    src/FileCmd/FileCmdFactory.h \
    src/FileCmd/FileCmdImport.h \
    src/FileCmd/FileCmdOpen.h \
    src/FileCmd/FileCmdScript.h \
    src/FileCmd/FileCmdSerialize.h \
    src/Filter/FilterImage.h \
    src/Format/FormatCoordsUnits.h \
    src/Format/FormatCoordsUnitsStrategyAbstractBase.h \
    src/Format/FormatCoordsUnitsStrategyNonPolarTheta.h \
    src/Format/FormatCoordsUnitsStrategyPolarTheta.h \
    src/Format/FormatDateTime.h \
    src/Format/FormatDegreesMinutesSecondsBase.h \
    src/Format/FormatDegreesMinutesSecondsNonPolarTheta.h \
    src/Format/FormatDegreesMinutesSecondsPolarTheta.h \
    src/Callback/functor.h \
    src/Ghosts/GhostEllipse.h \
    src/Ghosts/GhostPath.h \
    src/Ghosts/GhostPolygon.h \
    src/Ghosts/Ghosts.h \
    src/Graphics/GraphicsArcItem.h \
    src/Graphics/GraphicsItemType.h \
    src/Graphics/GraphicsLinesForCurve.h \
    src/Graphics/GraphicsLinesForCurves.h \
    src/Graphics/GraphicsPoint.h \
    src/Graphics/GraphicsPointAbstractBase.h \
    src/Graphics/GraphicsPointEllipse.h \
    src/Graphics/GraphicsPointFactory.h \
    src/Graphics/GraphicsPointPolygon.h \
    src/Graphics/GraphicsScene.h \
    src/Graphics/GraphicsView.h \
    src/Grid/GridClassifier.h \
    src/Grid/GridCoordDisable.h \
    src/Grid/GridHealer.h \
    src/Grid/GridRemoval.h \
    src/Help/HelpBrowser.h \
    src/Help/HelpWindow.h \
    src/Line/LineStyle.h \
    src/Load/LoadFileInfo.h \
    src/Load/LoadImageFromUrl.h \
    src/Logger/Logger.h \
    src/Logger/LoggerUpload.h \
    src/main/MainTitleBarFormat.h \
    src/main/MainWindow.h \
    src/main/MainWindowModel.h \
    src/util/MigrateToVersion6.h \
    src/Mime/MimePoints.h \
    src/util/mmsubs.h \
    src/Network/NetworkClient.h \
    src/Ordinal/OrdinalGenerator.h \
    src/Ordinal/OrdinalToGraphicsPoint.h \
    src/Point/Point.h \
    src/Point/PointComparator.h \
    src/Point/PointIdentifiers.h \
    src/Point/PointMatchAlgorithm.h \
    src/Point/PointMatchPixel.h \
    src/Point/PointMatchTriplet.h \
    src/Point/Points.h \
    src/Point/PointShape.h \
    src/Point/PointStyle.h \
    src/util/QtToString.h \
    src/Segment/Segment.h \
    src/Segment/SegmentFactory.h \
    src/Segment/SegmentLine.h \
    src/Settings/Settings.h \
    src/Settings/SettingsForGraph.h \
    src/Spline/Spline.h \
    src/Spline/SplineCoeff.h \
    src/Spline/SplinePair.h \
    src/StatusBar/StatusBar.h \
    src/StatusBar/StatusBarMode.h \
    src/Transformation/Transformation.h \
    src/Transformation/TransformationStateAbstractBase.h \
    src/Transformation/TransformationStateContext.h \
    src/Transformation/TransformationStateDefined.h \
    src/Transformation/TransformationStateUndefined.h \
    src/Translator/TranslatorContainer.h \
    src/Tutorial/TutorialButton.h \
    src/Tutorial/TutorialButtonRect.h \
    src/Tutorial/TutorialButtonText.h \
    src/Tutorial/TutorialDlg.h \
    src/Tutorial/TutorialStateAbstractBase.h \
    src/Tutorial/TutorialStateAxisPoints.h \
    src/Tutorial/TutorialStateChecklistWizardAbstract.h \
    src/Tutorial/TutorialStateChecklistWizardLines.h \
    src/Tutorial/TutorialStateChecklistWizardPoints.h \
    src/Tutorial/TutorialStateColorFilter.h \
    src/Tutorial/TutorialStateContext.h \
    src/Tutorial/TutorialStateCurveSelection.h \
    src/Tutorial/TutorialStateCurveType.h \
    src/Tutorial/TutorialStateIntroduction.h \
    src/Tutorial/TutorialStatePointMatch.h \
    src/Tutorial/TutorialStateSegmentFill.h \
    src/include/ValuesVectorXOrY.h \
    src/util/Version.h \
    src/View/ViewPointStyle.h \
    src/View/ViewPreview.h \
    src/View/ViewProfile.h \
    src/View/ViewProfileDivider.h \
    src/View/ViewProfileParameters.h \
    src/View/ViewProfileScale.h \
    src/View/ViewSegmentFilter.h \
    src/util/Xml.h \
    src/Zoom/ZoomControl.h \
    src/Zoom/ZoomFactor.h \
    src/Zoom/ZoomFactorInitial.h \
    src/Zoom/ZoomLabels.h

SOURCES += \
    src/Background/BackgroundImage.cpp \
    src/Background/BackgroundStateAbstractBase.cpp \
    src/Background/BackgroundStateContext.cpp \
    src/Background/BackgroundStateCurve.cpp \
    src/Background/BackgroundStateNone.cpp \
    src/Background/BackgroundStateOriginal.cpp \
    src/Background/BackgroundStateUnloaded.cpp \
    src/Callback/CallbackAddPointsInCurvesGraphs.cpp \
    src/Callback/CallbackAxesCheckerFromAxesPoints.cpp \
    src/Callback/CallbackAxisPointsAbstract.cpp \
    src/Callback/CallbackBoundingRects.cpp \
    src/Callback/CallbackCheckAddPointAxis.cpp \
    src/Callback/CallbackCheckEditPointAxis.cpp \
    src/Callback/CallbackGatherXThetaValuesFunctions.cpp \
    src/Callback/CallbackNextOrdinal.cpp \
    src/Callback/CallbackPointOrdinal.cpp \
    src/Callback/CallbackRemovePointsInCurvesGraphs.cpp \
    src/Callback/CallbackSceneUpdateAfterCommand.cpp \
    src/Callback/CallbackUpdateTransform.cpp \
    src/Checker/Checker.cpp \
    src/Checker/CheckerMode.cpp \
    src/Checklist/ChecklistGuide.cpp \
    src/Checklist/ChecklistGuideBrowser.cpp \
    src/Checklist/ChecklistGuidePage.cpp \
    src/Checklist/ChecklistGuidePageConclusion.cpp \
    src/Checklist/ChecklistGuidePageCurves.cpp \
    src/Checklist/ChecklistGuidePageIntro.cpp \
    src/Checklist/ChecklistGuideWizard.cpp \
    src/Checklist/ChecklistLineEdit.cpp \
    src/Checklist/ChecklistTemplate.cpp \
    src/Cmd/CmdAbstract.cpp \
    src/Cmd/CmdAddPointAxis.cpp \
    src/Cmd/CmdAddPointGraph.cpp \
    src/Cmd/CmdAddPointsGraph.cpp \
    src/Cmd/CmdCopy.cpp \
    src/Cmd/CmdCut.cpp \
    src/Cmd/CmdDelete.cpp \
    src/Cmd/CmdEditPointAxis.cpp \
    src/Cmd/CmdFactory.cpp \
    src/Cmd/CmdMediator.cpp \
    src/Cmd/CmdMoveBy.cpp \
    src/Cmd/CmdPaste.cpp \
    src/Cmd/CmdSelectCoordSystem.cpp \
    src/Cmd/CmdSettingsAxesChecker.cpp \
    src/Cmd/CmdSettingsColorFilter.cpp \
    src/Cmd/CmdSettingsCoords.cpp \
    src/Cmd/CmdSettingsCurveAddRemove.cpp \
    src/Cmd/CmdSettingsCurveProperties.cpp \
    src/Cmd/CmdSettingsDigitizeCurve.cpp \
    src/Cmd/CmdSettingsExportFormat.cpp \
    src/Cmd/CmdSettingsGeneral.cpp \
    src/Cmd/CmdSettingsGridRemoval.cpp \
    src/Cmd/CmdSettingsPointMatch.cpp \
    src/Cmd/CmdSettingsSegments.cpp \
    src/Cmd/CmdStackShadow.cpp \
    src/Color/ColorFilter.cpp \
    src/Color/ColorFilterHistogram.cpp \
    src/Color/ColorFilterMode.cpp \
    src/Color/ColorFilterSettings.cpp \
    src/Color/ColorPalette.cpp \
    src/Coord/CoordScale.cpp \
    src/Coord/CoordsType.cpp \
    src/Coord/CoordSymbol.cpp \
    src/CoordSystem/CoordSystem.cpp \
    src/CoordSystem/CoordSystemContext.cpp \
    src/CoordSystem/CoordSystemInterface.cpp \
    src/Coord/CoordUnitsDate.cpp \
    src/Coord/CoordUnitsNonPolarTheta.cpp \
    src/Coord/CoordUnitsPolarTheta.cpp \
    src/Coord/CoordUnitsTime.cpp \
    src/Correlation/Correlation.cpp \
    src/Cursor/CursorFactory.cpp \
    src/Cursor/CursorSize.cpp \
    src/Curve/Curve.cpp \
    src/Curve/CurveConnectAs.cpp \
    src/Curve/CurveNameList.cpp \
    src/Curve/CurveNameListEntry.cpp \
    src/Curve/CurveSettingsInt.cpp \
    src/Curve/CurvesGraphs.cpp \
    src/Curve/CurveStyle.cpp \
    src/Curve/CurveStyles.cpp \
    src/util/DataKey.cpp \
    src/DigitizeState/DigitizeStateAbstractBase.cpp \
    src/DigitizeState/DigitizeStateAxis.cpp \
    src/DigitizeState/DigitizeStateColorPicker.cpp \
    src/DigitizeState/DigitizeStateContext.cpp \
    src/DigitizeState/DigitizeStateCurve.cpp \
    src/DigitizeState/DigitizeStateEmpty.cpp \
    src/DigitizeState/DigitizeStatePointMatch.cpp \
    src/DigitizeState/DigitizeStateSegment.cpp \
    src/DigitizeState/DigitizeStateSelect.cpp \
    src/Dlg/DlgAbout.cpp \
    src/Dlg/DlgEditPoint.cpp \
    src/Dlg/DlgErrorReport.cpp \
    src/Dlg/DlgFilterCommand.cpp \
    src/Dlg/DlgFilterThread.cpp \
    src/Dlg/DlgFilterWorker.cpp \
    src/Dlg/DlgImportAdvanced.cpp \
    src/Dlg/DlgRequiresTransform.cpp \
    src/Dlg/DlgSettingsAbstractBase.cpp \
    src/Dlg/DlgSettingsAxesChecker.cpp \
    src/Dlg/DlgSettingsColorFilter.cpp \
    src/Dlg/DlgSettingsCoords.cpp \
    src/Dlg/DlgSettingsCurveAddRemove.cpp \
    src/Dlg/DlgSettingsCurveProperties.cpp \
    src/Dlg/DlgSettingsDigitizeCurve.cpp \
    src/Dlg/DlgSettingsExportFormat.cpp \
    src/Dlg/DlgSettingsGeneral.cpp \
    src/Dlg/DlgSettingsGridRemoval.cpp \
    src/Dlg/DlgSettingsMainWindow.cpp \
    src/Dlg/DlgSettingsPointMatch.cpp \
    src/Dlg/DlgSettingsSegments.cpp \
    src/Dlg/DlgValidatorAbstract.cpp \
    src/Dlg/DlgValidatorDateTime.cpp \
    src/Dlg/DlgValidatorDegreesMinutesSeconds.cpp \
    src/Dlg/DlgValidatorFactory.cpp \
    src/Dlg/DlgValidatorNumber.cpp \
    src/Document/Document.cpp \
    src/Document/DocumentModelAbstractBase.cpp \
    src/Document/DocumentModelAxesChecker.cpp \
    src/Document/DocumentModelColorFilter.cpp \
    src/Document/DocumentModelCoords.cpp \
    src/Document/DocumentModelDigitizeCurve.cpp \
    src/Document/DocumentModelExportFormat.cpp \
    src/Document/DocumentModelGeneral.cpp \
    src/Document/DocumentModelGridRemoval.cpp \
    src/Document/DocumentModelPointMatch.cpp \
    src/Document/DocumentModelSegments.cpp \
    src/Document/DocumentSerialize.cpp \
    src/util/EnumsToQt.cpp \
    src/Export/ExportAlignLinear.cpp \
    src/Export/ExportAlignLog.cpp \
    src/Export/ExportDelimiter.cpp \
    src/Export/ExportFileAbstractBase.cpp \
    src/Export/ExportFileFunctions.cpp \
    src/Export/ExportFileRelations.cpp \
    src/Export/ExportHeader.cpp \
    src/Export/ExportLayoutFunctions.cpp \
    src/Export/ExportOrdinalsSmooth.cpp \
    src/Export/ExportOrdinalsStraight.cpp \
    src/Export/ExportPointsIntervalUnits.cpp \
    src/Export/ExportPointsSelectionFunctions.cpp \
    src/Export/ExportPointsSelectionRelations.cpp \
    src/Export/ExportToClipboard.cpp \
    src/Export/ExportToFile.cpp \
    src/Export/ExportXThetaValuesMergedFunctions.cpp \
    src/FileCmd/FileCmdAbstract.cpp \
    src/FileCmd/FileCmdClose.cpp \
    src/FileCmd/FileCmdExport.cpp \
    src/FileCmd/FileCmdFactory.cpp \
    src/FileCmd/FileCmdImport.cpp \
    src/FileCmd/FileCmdOpen.cpp \
    src/FileCmd/FileCmdScript.cpp \
    src/FileCmd/FileCmdSerialize.cpp \
    src/Filter/FilterImage.cpp \
    src/Format/FormatCoordsUnits.cpp \
    src/Format/FormatCoordsUnitsStrategyAbstractBase.cpp \
    src/Format/FormatCoordsUnitsStrategyNonPolarTheta.cpp \
    src/Format/FormatCoordsUnitsStrategyPolarTheta.cpp \
    src/Format/FormatDateTime.cpp \
    src/Format/FormatDegreesMinutesSecondsBase.cpp \
    src/Format/FormatDegreesMinutesSecondsNonPolarTheta.cpp \
    src/Format/FormatDegreesMinutesSecondsPolarTheta.cpp \
    src/Ghosts/GhostEllipse.cpp \
    src/Ghosts/GhostPath.cpp \
    src/Ghosts/GhostPolygon.cpp \
    src/Ghosts/Ghosts.cpp \
    src/Graphics/GraphicsArcItem.cpp \
    src/Graphics/GraphicsLinesForCurve.cpp \
    src/Graphics/GraphicsLinesForCurves.cpp \
    src/Graphics/GraphicsPoint.cpp \
    src/Graphics/GraphicsPointAbstractBase.cpp \
    src/Graphics/GraphicsPointEllipse.cpp \
    src/Graphics/GraphicsPointFactory.cpp \
    src/Graphics/GraphicsPointPolygon.cpp \
    src/Graphics/GraphicsScene.cpp \
    src/Graphics/GraphicsView.cpp \
    src/Grid/GridClassifier.cpp \
    src/Grid/GridCoordDisable.cpp \
    src/Grid/GridHealer.cpp \
    src/Grid/GridRemoval.cpp \
    src/Help/HelpBrowser.cpp \
    src/Help/HelpWindow.cpp \
    src/Line/LineStyle.cpp \
    src/Load/LoadFileInfo.cpp \
    src/Load/LoadImageFromUrl.cpp \
    src/Logger/Logger.cpp \
    src/Logger/LoggerUpload.cpp \
    src/main/main.cpp \
    src/main/MainWindow.cpp \
    src/main/MainWindowModel.cpp \
    src/util/MigrateToVersion6.cpp \
    src/Mime/MimePoints.cpp \
    src/util/mmsubs.cpp \
    src/Network/NetworkClient.cpp \
    src/Ordinal/OrdinalGenerator.cpp \
    src/Point/Point.cpp \
    src/Point/PointIdentifiers.cpp \
    src/Point/PointMatchAlgorithm.cpp \
    src/Point/PointMatchPixel.cpp \
    src/Point/PointMatchTriplet.cpp \
    src/Point/PointShape.cpp \
    src/Point/PointStyle.cpp \
    src/util/QtToString.cpp \
    src/Segment/Segment.cpp \
    src/Segment/SegmentFactory.cpp \
    src/Segment/SegmentLine.cpp \
    src/Settings/Settings.cpp \
    src/Settings/SettingsForGraph.cpp \
    src/Spline/Spline.cpp \
    src/Spline/SplineCoeff.cpp \
    src/Spline/SplinePair.cpp \
    src/StatusBar/StatusBar.cpp \
    src/Transformation/Transformation.cpp \
    src/Transformation/TransformationStateAbstractBase.cpp \
    src/Transformation/TransformationStateContext.cpp \
    src/Transformation/TransformationStateDefined.cpp \
    src/Transformation/TransformationStateUndefined.cpp \
    src/Translator/TranslatorContainer.cpp \
    src/Tutorial/TutorialButton.cpp \
    src/Tutorial/TutorialButtonRect.cpp \
    src/Tutorial/TutorialButtonText.cpp \
    src/Tutorial/TutorialDlg.cpp \
    src/Tutorial/TutorialStateAbstractBase.cpp \
    src/Tutorial/TutorialStateAxisPoints.cpp \
    src/Tutorial/TutorialStateChecklistWizardAbstract.cpp \
    src/Tutorial/TutorialStateChecklistWizardLines.cpp \
    src/Tutorial/TutorialStateChecklistWizardPoints.cpp \
    src/Tutorial/TutorialStateColorFilter.cpp \
    src/Tutorial/TutorialStateContext.cpp \
    src/Tutorial/TutorialStateCurveSelection.cpp \
    src/Tutorial/TutorialStateCurveType.cpp \
    src/Tutorial/TutorialStateIntroduction.cpp \
    src/Tutorial/TutorialStatePointMatch.cpp \
    src/Tutorial/TutorialStateSegmentFill.cpp \
    src/util/Version.cpp \
    src/View/ViewPointStyle.cpp \
    src/View/ViewPreview.cpp \
    src/View/ViewProfile.cpp \
    src/View/ViewProfileDivider.cpp \
    src/View/ViewProfileParameters.cpp \
    src/View/ViewProfileScale.cpp \
    src/View/ViewSegmentFilter.cpp \
    src/util/Xml.cpp \
    src/Zoom/ZoomLabels.cpp

macx-* {
CONFIG += app_bundle
QMAKE_CXXFLAGS += "-stdlib=libc++"
QMAKE_LFLAGS += "-stdlib=libc++"
INCLUDEPATH += -isystem /usr/local/Cellar/qt5/5.6.0/lib/QtPrintSupport.framework/Headers
LIBS += -framework CoreFoundation
} else {
TEMPLATE = app
TARGET = bin/engauge
}

win32-* {
CONFIG += windows
}

win32-msvc* {
QMAKE_CXXFLAGS += -EHsc
LIBS += $$(FFTW_HOME)/lib/libfftw3-3.lib $$(LOG4CPP_HOME)/lib/log4cpp.lib shell32.lib
} else {
win32-g++* {
LIBS += -L$$(LOG4CPP_HOME)/lib -L$$(FFTW_HOME)/lib
}
LIBS += -llog4cpp -lfftw3
}

INCLUDEPATH += src \
               src/Background \
               src/Callback \
               src/Checker \
               src/Checklist \
               src/Cmd \
               src/Color \
               src/Coord \
               src/CoordSystem \
               src/Correlation \
               src/Cursor \
               src/Curve \
               src/DigitizeState \
               src/Dlg \
               src/Document \
               src/Export \
               src/FileCmd \
               src/Filter \
               src/Format \
               src/Ghosts \
               src/Graphics \
               src/Grid \
               src/Help \
               src/img \
               src/include \
               src/Line \
               src/Load \
               src/Logger \
               src/main \
               src/Mime \
               src/Network \
               src/Ordinal \
               src/Plot \
               src/Point \
               src/Segment \
               src/Settings \
               src/Spline \
               src/StatusBar \
               src/Transformation \
               src/Translator \
               src/Tutorial \
               src/util \
               src/View \
               src/Zoom

win32-* {
INCLUDEPATH += $$(FFTW_HOME)/include \
               $$(LOG4CPP_HOME)/include
}

RESOURCES += \
    src/engauge.qrc

jpeg2000 {
    CONFIG(debug,debug|release) {
      message(Building dynamic debug version with internal support for JPEG2000 files)
    } else {
      message(Building static release version with internal support for JPEG2000 files)
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

    HEADERS += src/Jpeg2000/Jpeg2000.h \
               src/Jpeg2000/Jpeg2000Callbacks.h \
               src/Jpeg2000/Jpeg2000Color.h \
               src/Jpeg2000/Jpeg2000Convert.h \
               src/Jpeg2000/Jpeg2000FormatDefs.h

    SOURCES += src/Jpeg2000/Jpeg2000.cpp \
               src/Jpeg2000/Jpeg2000Callbacks.cpp \
               src/Jpeg2000/Jpeg2000Color.cpp \
               src/Jpeg2000/Jpeg2000Convert.cpp

} else {
    CONFIG(debug,debug|release) {
      message(Building debug version without internal support for JPEG2000 files)
    } else {
      message(Building release version without internal support for JPEG2000 files)
    }
}

# People interested in translating a language can contact the developers for help. 
# 
# Translation file names are 'engauge_XX_YY' or 'engauge_XX' where:
#   XX = two letter language codes in column '639-1' at https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
#   YY = two letter country codes in column 'ISO 3166-2' at https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2
# where XX and YY are:
#   ar = Arabic     Egypt=_eg
#   de = German     Germany=_de
#   en = English    USA=us
#   es = Spanish    Spain=_es
#   fr = French     France=_fr
#   hi = Hindi      India=_in
#   it = Italian    Italy=_it
#   ja = Japanese   Japan=_jp
#   kk = Kazakh     Kazakhstan=_kz
#   ko = Korean     SouthKorea=_kr
#   pt = Portuguese Brazil=_br
#   ru = Russian    Federation=_ru
#   zh = Chinese    China=_cn
# When the user picks an (XX_YY) locale in Settings / Main Window and restarts Engauge, Engauge follows these steps to load:
#   1) 'engauge_XX_YY' is loaded if it exists and locale loading finishes
#   2) 'engauge_XX' is loaded if it exists and step 1 failed, and locale loading finishes
#   3) the default locale is loaded and steps 1 and 2 failed
# In other words, translations specific to a country are loaded if available, otherwise translations for a language
# (which often apply to multiple countries) are loaded.
TRANSLATIONS = translations/engauge_ar.ts \
               translations/engauge_de.ts \
               translations/engauge_en.ts \
               translations/engauge_es.ts \
               translations/engauge_fr.ts \               
               translations/engauge_hi.ts \               
               translations/engauge_it.ts \               
               translations/engauge_ja.ts \               
               translations/engauge_kk.ts \
               translations/engauge_ko.ts \
               translations/engauge_pt.ts \
               translations/engauge_ru.ts \
               translations/engauge_zh.ts
