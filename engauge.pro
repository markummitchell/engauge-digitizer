# engauge.pro : Builds make files for engauge executable
#
# Comments:
# 1) Version numbers for the packages mentioned in the following comments are documented in the BUILD file
# 2) This builds 'release' executables by default, to greatly reduce the chances of a 'debug' build getting deployed.
#    To get a 'debug' build, add 'CONFIG=debug' to the qmake command line:
#        qmake CONFIG=debug
# 3) Add 'jpeg2000' to the qmake command line to include support for JPEG2000 input files. Requires:
#        1) previous installation of OpenJPEG development package
#        2) OPENJPEG_INCLUDE environment variable pointing to directory with openjpeg.h
#        3) OPENJPEG_LIB environment variable pointing to directory with libopenjp2.so
#    Sample command lines:
#        qmake CONFIG+=jpeg2000
#        qmake "CONFIG+=debug jpeg2000"
#    At some point, Qt may provide its own support for this format, at which point this can be skipped
# 4) Add 'pdf' to the qmake command line to include support for PDF input files. Requires
#        1) previous installation of the poppler-qt5 development package
#        2) POPPLER_INCLUDE environment variable pointing to directory containing poppler-qt5.h
#        3) POPPLER_LIB environment variable pointing to directory containing libpoppler-qt5.so
#    Sample command lines:
#        qmake CONFIG+=pdf
#        qmake "CONFIG+=debug pdf"
# 5) Set environment variable HELPDIR to override the default directory for the help files. On the command line, use
#    qmake "DEFINES+=HELPDIR=<directory>". The <directory> is absolute or relative to the application executable directory
# 6) Gratuitous warning about import_qpa_plugin in Fedora is due to 'CONFIG=qt' but that option takes care of 
#    include/library files in an automated and platform-independent manner, so it will not be removed
# 7) 'network' module of Qt is not included for Windows version since installation file gets blocked by Avast antivirus.
#    Likewise, it is not included for OSX since it is interpretted as a threat. 
#    The network module can download files, which is what malware does to install bad things
# 8) In OSX, QtHelp requires QtNetwork which is rejected by the operating system, so QtHelp is disabled
#
# More comments are in the INSTALL file, and below

QT += core gui printsupport widgets xml

win32-*|linux-*|unix-* {
QT += help
HEADERS += src/Help/HelpBrowser.h \
           src/Help/HelpWindow.h
SOURCES += src/Help/HelpBrowser.cpp \
           src/Help/HelpWindow.cpp
}

CONFIG(debug,debug|release){
  # Debug version:
} else {
  # Release version:
  # 1) Release version has warnings enabled so they can be removed as a convenience for downstream package maintainers
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
    src/Callback/CallbackDocumentHash.h \
    src/Callback/CallbackGatherXThetaValuesFunctions.h \
    src/Callback/CallbackNextOrdinal.h \
    src/Callback/CallbackPointOrdinal.h \
    src/Callback/CallbackRemovePointsInCurvesGraphs.h \
    src/Callback/CallbackScaleBar.h \
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
    src/Cmd/CmdAddScale.h \    
    src/Cmd/CmdCopy.h \
    src/Cmd/CmdCut.h \
    src/Cmd/CmdDelete.h \
    src/Cmd/CmdEditPointAxis.h \
    src/Cmd/CmdEditPointGraph.h \
    src/Cmd/CmdFactory.h \
    src/Cmd/CmdMediator.h \
    src/Cmd/CmdMoveBy.h \
    src/Cmd/CmdPointChangeBase.h \
    src/Cmd/CmdRedoForTest.h \
    src/Cmd/CmdSelectCoordSystem.h \
    src/Cmd/CmdSettingsAxesChecker.h \
    src/Cmd/CmdSettingsColorFilter.h \
    src/Cmd/CmdSettingsCoords.h \
    src/Cmd/CmdSettingsCurveAddRemove.h \
    src/Cmd/CmdSettingsCurveProperties.h \
    src/Cmd/CmdSettingsDigitizeCurve.h \
    src/Cmd/CmdSettingsExportFormat.h \
    src/Cmd/CmdSettingsGeneral.h \
    src/Cmd/CmdSettingsGridDisplay.h \
    src/Cmd/CmdSettingsGridRemoval.h \
    src/Cmd/CmdSettingsPointMatch.h \
    src/Cmd/CmdSettingsSegments.h \
    src/Cmd/CmdStackShadow.h \
    src/Cmd/CmdUndoForTest.h \
    src/Color/ColorConstants.h \
    src/Color/ColorFilter.h \
    src/Color/ColorFilterEntry.h \
    src/Color/ColorFilterHistogram.h \
    src/Color/ColorFilterMode.h \
    src/Color/ColorFilterSettings.h \
    src/Color/ColorFilterSettingsStrategyAbstractBase.h \
    src/Color/ColorFilterSettingsStrategyForeground.h \
    src/Color/ColorFilterSettingsStrategyHue.h \
    src/Color/ColorFilterSettingsStrategyIntensity.h \
    src/Color/ColorFilterSettingsStrategySaturation.h \
    src/Color/ColorFilterSettingsStrategyValue.h \
    src/Color/ColorFilterStrategyAbstractBase.h \
    src/Color/ColorFilterStrategyForeground.h \
    src/Color/ColorFilterStrategyHue.h \
    src/Color/ColorFilterStrategyIntensity.h \
    src/Color/ColorFilterStrategySaturation.h \
    src/Color/ColorFilterStrategyValue.h \
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
    src/DigitizeState/DigitizeStateScale.h \    
    src/DigitizeState/DigitizeStateSegment.h \
    src/DigitizeState/DigitizeStateSelect.h \
    src/Dlg/DlgAbout.h \
    src/Dlg/DlgEditPointAxis.h \
    src/Dlg/DlgEditPointGraph.h \
    src/Dlg/DlgEditPointGraphLineEdit.h \
    src/Dlg/DlgEditScale.h \    
    src/Dlg/DlgErrorReportAbstractBase.h \    
    src/Dlg/DlgErrorReportLocal.h \
    src/Dlg/DlgErrorReportNetworking.h \    
    src/Dlg/DlgFilterCommand.h \
    src/Dlg/DlgFilterThread.h \
    src/Dlg/DlgFilterWorker.h \
    src/Dlg/DlgImportAdvanced.h \
    src/Dlg/DlgImportCroppingNonPdf.h \
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
    src/Dlg/DlgSettingsGridDisplay.h \
    src/Dlg/DlgSettingsGridRemoval.h \
    src/Dlg/DlgSettingsMainWindow.h \
    src/Dlg/DlgSettingsPointMatch.h \
    src/Dlg/DlgSettingsSegments.h \
    src/Dlg/DlgValidatorAboveZero.h \
    src/Dlg/DlgValidatorAbstract.h \
    src/Dlg/DlgValidatorDateTime.h \
    src/Dlg/DlgValidatorDegreesMinutesSeconds.h \
    src/Dlg/DlgValidatorFactory.h \
    src/Dlg/DlgValidatorNumber.h \
    src/Document/Document.h \
    src/Document/DocumentAxesPointsRequired.h \
    src/Document/DocumentHash.h \
    src/Document/DocumentHashGenerator.h \
    src/Document/DocumentModelAbstractBase.h \
    src/Document/DocumentModelAxesChecker.h \
    src/Document/DocumentModelColorFilter.h \
    src/Document/DocumentModelCoords.h \
    src/Document/DocumentModelDigitizeCurve.h \
    src/Document/DocumentModelExportFormat.h \
    src/Document/DocumentModelGeneral.h \
    src/Document/DocumentModelGridDisplay.h \
    src/Document/DocumentModelGridRemoval.h \
    src/Document/DocumentModelPointMatch.h \
    src/Document/DocumentModelSegments.h \
    src/Document/DocumentSerialize.h \
    src/include/EngaugeAssert.h \
    src/util/EnumsToQt.h \
    src/Export/ExportAlignLinear.h \
    src/Export/ExportAlignLog.h \
    src/Export/ExportDelimiter.h \
    src/Export/ExportImageForRegression.h \
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
    src/Fitting/FittingCurve.h \
    src/Fitting/FittingCurveCoefficients.h \
    src/Fitting/FittingModel.h \
    src/Fitting/FittingPointsConvenient.h \
    src/Fitting/FittingStatistics.h \
    src/Fitting/FittingWindow.h \
    src/Format/FormatCoordsUnits.h \
    src/Format/FormatCoordsUnitsStrategyAbstractBase.h \
    src/Format/FormatCoordsUnitsStrategyNonPolarTheta.h \
    src/Format/FormatCoordsUnitsStrategyPolarTheta.h \
    src/Format/FormatDateTime.h \
    src/Format/FormatDegreesMinutesSecondsBase.h \
    src/Format/FormatDegreesMinutesSecondsNonPolarTheta.h \
    src/Format/FormatDegreesMinutesSecondsPolarTheta.h \
    src/Callback/functor.h \
    src/Geometry/GeometryModel.h \
    src/Geometry/GeometryStrategyAbstractBase.h \
    src/Geometry/GeometryStrategyContext.h \
    src/Geometry/GeometryStrategyFunctionSmooth.h \
    src/Geometry/GeometryStrategyFunctionStraight.h \
    src/Geometry/GeometryStrategyRelationSmooth.h \
    src/Geometry/GeometryStrategyRelationStraight.h \
    src/Geometry/GeometryWindow.h \
    src/Ghosts/GhostEllipse.h \
    src/Ghosts/GhostPath.h \
    src/Ghosts/GhostPolygon.h \
    src/Ghosts/Ghosts.h \
    src/Graphics/GraphicsArcItem.h \
    src/Graphics/GraphicsItemsExtractor.h \
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
    src/Grid/GridInitializer.h \
    src/Grid/GridLine.h \
    src/Grid/GridLineFactory.h \
    src/Grid/GridLineLimiter.h \
    src/Grid/GridLines.h \
    src/Grid/GridLineStyle.h \
    src/Grid/GridRemoval.h \
    src/Import/ImportCropping.h \
    src/Import/ImportCroppingUtilBase.h \
    src/Import/ImportCroppingUtilNonPdf.h \
    src/util/LinearToLog.h \
    src/Line/LineStyle.h \
    src/Load/LoadFileInfo.h \
    src/Logger/Logger.h \
    src/Logger/LoggerUpload.h \
    src/Matrix/Matrix.h \
    src/main/MainTitleBarFormat.h \
    src/main/MainWindow.h \
    src/main/MainWindowModel.h \
    src/util/MigrateToVersion6.h \
    src/Mime/MimePointsDetector.h \
    src/Mime/MimePointsExport.h \
    src/Mime/MimePointsImport.h \    
    src/util/mmsubs.h \
    src/NonPdf/NonPdf.h \
    src/NonPdf/NonPdfCropping.h \
    src/NonPdf/NonPdfFrameHandle.h \
    src/Ordinal/OrdinalGenerator.h \
    src/Ordinal/OrdinalToGraphicsPoint.h \
    src/Pdf/PdfResolution.h \
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
    src/ScaleBar/ScaleBarAxisPointsUnite.h \
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
    src/Window/WindowAbstractBase.h \        
    src/Window/WindowModelBase.h \    
    src/Window/WindowTable.h \
    src/util/Xml.h \
    src/Zoom/ZoomControl.h \
    src/Zoom/ZoomFactor.h \
    src/Zoom/ZoomFactorInitial.h \
    src/Zoom/ZoomLabels.h \
    src/Zoom/ZoomTransition.h \
    src/util/ZValues.h

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
    src/Callback/CallbackDocumentHash.cpp \
    src/Callback/CallbackGatherXThetaValuesFunctions.cpp \
    src/Callback/CallbackNextOrdinal.cpp \
    src/Callback/CallbackPointOrdinal.cpp \
    src/Callback/CallbackRemovePointsInCurvesGraphs.cpp \
    src/Callback/CallbackScaleBar.cpp \
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
    src/Cmd/CmdAddScale.cpp \
    src/Cmd/CmdCopy.cpp \
    src/Cmd/CmdCut.cpp \
    src/Cmd/CmdDelete.cpp \
    src/Cmd/CmdEditPointAxis.cpp \
    src/Cmd/CmdEditPointGraph.cpp \
    src/Cmd/CmdFactory.cpp \
    src/Cmd/CmdMediator.cpp \
    src/Cmd/CmdMoveBy.cpp \
    src/Cmd/CmdRedoForTest.cpp \
    src/Cmd/CmdPointChangeBase.cpp \
    src/Cmd/CmdSelectCoordSystem.cpp \
    src/Cmd/CmdSettingsAxesChecker.cpp \
    src/Cmd/CmdSettingsColorFilter.cpp \
    src/Cmd/CmdSettingsCoords.cpp \
    src/Cmd/CmdSettingsCurveAddRemove.cpp \
    src/Cmd/CmdSettingsCurveProperties.cpp \
    src/Cmd/CmdSettingsDigitizeCurve.cpp \
    src/Cmd/CmdSettingsExportFormat.cpp \
    src/Cmd/CmdSettingsGeneral.cpp \
    src/Cmd/CmdSettingsGridDisplay.cpp \
    src/Cmd/CmdSettingsGridRemoval.cpp \
    src/Cmd/CmdSettingsPointMatch.cpp \
    src/Cmd/CmdSettingsSegments.cpp \
    src/Cmd/CmdStackShadow.cpp \
    src/Cmd/CmdUndoForTest.cpp \
    src/Color/ColorFilter.cpp \
    src/Color/ColorFilterHistogram.cpp \
    src/Color/ColorFilterMode.cpp \
    src/Color/ColorFilterSettings.cpp \
    src/Color/ColorFilterSettingsStrategyAbstractBase.cpp \
    src/Color/ColorFilterSettingsStrategyForeground.cpp \
    src/Color/ColorFilterSettingsStrategyHue.cpp \
    src/Color/ColorFilterSettingsStrategyIntensity.cpp \
    src/Color/ColorFilterSettingsStrategySaturation.cpp \
    src/Color/ColorFilterSettingsStrategyValue.cpp \
    src/Color/ColorFilterStrategyAbstractBase.cpp \
    src/Color/ColorFilterStrategyForeground.cpp \
    src/Color/ColorFilterStrategyHue.cpp \
    src/Color/ColorFilterStrategyIntensity.cpp \
    src/Color/ColorFilterStrategySaturation.cpp \
    src/Color/ColorFilterStrategyValue.cpp \
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
    src/DigitizeState/DigitizeStateScale.cpp \        
    src/DigitizeState/DigitizeStateSegment.cpp \
    src/DigitizeState/DigitizeStateSelect.cpp \
    src/Dlg/DlgAbout.cpp \
    src/Dlg/DlgEditPointAxis.cpp \
    src/Dlg/DlgEditPointGraph.cpp \
    src/Dlg/DlgEditPointGraphLineEdit.cpp \
    src/Dlg/DlgEditScale.cpp \        
    src/Dlg/DlgErrorReportAbstractBase.cpp \
    src/Dlg/DlgErrorReportLocal.cpp \
    src/Dlg/DlgErrorReportNetworking.cpp \
    src/Dlg/DlgFilterCommand.cpp \
    src/Dlg/DlgFilterThread.cpp \
    src/Dlg/DlgFilterWorker.cpp \
    src/Dlg/DlgImportAdvanced.cpp \
    src/Dlg/DlgImportCroppingNonPdf.cpp \
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
    src/Dlg/DlgSettingsGridDisplay.cpp \
    src/Dlg/DlgSettingsGridRemoval.cpp \
    src/Dlg/DlgSettingsMainWindow.cpp \
    src/Dlg/DlgSettingsPointMatch.cpp \
    src/Dlg/DlgSettingsSegments.cpp \
    src/Dlg/DlgValidatorAboveZero.cpp \
    src/Dlg/DlgValidatorAbstract.cpp \
    src/Dlg/DlgValidatorDateTime.cpp \
    src/Dlg/DlgValidatorDegreesMinutesSeconds.cpp \
    src/Dlg/DlgValidatorFactory.cpp \
    src/Dlg/DlgValidatorNumber.cpp \
    src/Document/Document.cpp \
    src/Document/DocumentHashGenerator.cpp \
    src/Document/DocumentModelAbstractBase.cpp \
    src/Document/DocumentModelAxesChecker.cpp \
    src/Document/DocumentModelColorFilter.cpp \
    src/Document/DocumentModelCoords.cpp \
    src/Document/DocumentModelDigitizeCurve.cpp \
    src/Document/DocumentModelExportFormat.cpp \
    src/Document/DocumentModelGeneral.cpp \
    src/Document/DocumentModelGridDisplay.cpp \
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
    src/Export/ExportImageForRegression.cpp \
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
    src/Fitting/FittingCurve.cpp \    
    src/Fitting/FittingModel.cpp \
    src/Fitting/FittingStatistics.cpp \
    src/Fitting/FittingWindow.cpp \    
    src/Format/FormatCoordsUnits.cpp \
    src/Format/FormatCoordsUnitsStrategyAbstractBase.cpp \
    src/Format/FormatCoordsUnitsStrategyNonPolarTheta.cpp \
    src/Format/FormatCoordsUnitsStrategyPolarTheta.cpp \
    src/Format/FormatDateTime.cpp \
    src/Format/FormatDegreesMinutesSecondsBase.cpp \
    src/Format/FormatDegreesMinutesSecondsNonPolarTheta.cpp \
    src/Format/FormatDegreesMinutesSecondsPolarTheta.cpp \
    src/Geometry/GeometryModel.cpp \
    src/Geometry/GeometryStrategyAbstractBase.cpp \
    src/Geometry/GeometryStrategyContext.cpp \
    src/Geometry/GeometryStrategyFunctionSmooth.cpp \
    src/Geometry/GeometryStrategyFunctionStraight.cpp \
    src/Geometry/GeometryStrategyRelationSmooth.cpp \
    src/Geometry/GeometryStrategyRelationStraight.cpp \
    src/Geometry/GeometryWindow.cpp \
    src/Ghosts/GhostEllipse.cpp \
    src/Ghosts/GhostPath.cpp \
    src/Ghosts/GhostPolygon.cpp \
    src/Ghosts/Ghosts.cpp \
    src/Graphics/GraphicsArcItem.cpp \
    src/Graphics/GraphicsItemsExtractor.cpp \
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
    src/Grid/GridInitializer.cpp \
    src/Grid/GridLine.cpp \
    src/Grid/GridLineFactory.cpp \
    src/Grid/GridLineLimiter.cpp \
    src/Grid/GridLines.cpp \
    src/Grid/GridRemoval.cpp \
    src/Import/ImportCroppingUtilBase.cpp \
    src/Import/ImportCroppingUtilNonPdf.cpp \
    src/util/LinearToLog.cpp \    
    src/Line/LineStyle.cpp \
    src/Load/LoadFileInfo.cpp \
    src/Logger/Logger.cpp \
    src/Logger/LoggerUpload.cpp \
    src/Matrix/Matrix.cpp \
    src/main/main.cpp \
    src/main/MainWindow.cpp \
    src/main/MainWindowModel.cpp \
    src/util/MigrateToVersion6.cpp \
    src/Mime/MimePointsDetector.cpp \
    src/Mime/MimePointsExport.cpp \
    src/Mime/MimePointsImport.cpp \    
    src/util/mmsubs.cpp \
    src/NonPdf/NonPdf.cpp \
    src/NonPdf/NonPdfCropping.cpp \
    src/NonPdf/NonPdfFrameHandle.cpp \
    src/Ordinal/OrdinalGenerator.cpp \
    src/Pdf/PdfResolution.cpp \
    src/Point/Point.cpp \
    src/Point/PointIdentifiers.cpp \
    src/Point/PointMatchAlgorithm.cpp \
    src/Point/PointMatchPixel.cpp \
    src/Point/PointMatchTriplet.cpp \
    src/Point/PointShape.cpp \
    src/Point/PointStyle.cpp \
    src/util/QtToString.cpp \
    src/ScaleBar/ScaleBarAxisPointsUnite.cpp \
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
    src/Window/WindowAbstractBase.cpp \
    src/Window/WindowModelBase.cpp \
    src/Window/WindowTable.cpp \    
    src/util/Xml.cpp \
    src/Zoom/ZoomLabels.cpp \
    src/Zoom/ZoomTransition.cpp \
    src/util/ZValues.cpp

macx-* {
  CONFIG(debug,debug|release){
    CONFIG -= app_bundle
    TARGET = engauge
    DESTDIR = bin
    QMAKE_CXXFLAGS += "-DOSX_DEBUG -stdlib=libc++ -gdwarf-2"
  } else {
    CONFIG += app_bundle
    TARGET = "Engauge Digitizer"
    QMAKE_CXXFLAGS += "-DOSX_RELEASE -stdlib=libc++ -gdwarf-2"
  }

  QMAKE_LFLAGS += "-stdlib=libc++ -gdwarf-2"
  # /usr/local/Cellar path below is for Travis builds
  INCLUDEPATH += $$(FFTW_HOME)/include \
                 $$(LOG4CPP_HOME)/include \
                 /usr/local/Cellar/qt5/5.5.1_2/lib/QtCore.framework/Versions/5/Headers \
                 /usr/local/Cellar/qt5/5.5.1_2/lib/QtPrintSupport.framework/Versions/5/Headers \
                 /usr/local/Cellar/qt5/5.5.1_2/lib/QtWidgets.framework/Versions/5/Headers \
                 /usr/local/Cellar/qt5/5.5.1_2/lib/QtXml.framework/Versions/5/Headers
  LIBS += -L/$$(FFTW_HOME)/lib -L$$(LOG4CPP_HOME)/lib -framework CoreFoundation
} else {
  CONFIG += qt warn_on thread
  TEMPLATE = app
  TARGET = engauge
  DESTDIR = bin
}

win32-* {
  CONFIG += windows
}

win32-msvc* {
  QMAKE_CXXFLAGS += -EHsc /F 32000000
  LIBS += $$(FFTW_HOME)/lib/libfftw3-3.lib $$(LOG4CPP_HOME)/lib/log4cpp.lib shell32.lib
} else {
  win32-g++* {
    LIBS += -L$$(LOG4CPP_HOME)/lib -L$$(FFTW_HOME)/lib
    QMAKE_LFLAGS += -Wl,--stack,32000000
  }
  LIBS += -lfftw3 -llog4cpp
}

linux-* {
  QT += network
  DEFINES += "NETWORKING"
  HEADERS += src/Load/LoadImageFromUrl.h \
             src/Network/NetworkClient.h
  SOURCES += src/Load/LoadImageFromUrl.cpp \
             src/Network/NetworkClient.cpp
  INCLUDEPATH += $$(FFTW_HOME)/include \
                 $$(LOG4CPP_HOME)/include
  LIBS += -L/$$(FFTW_HOME)/lib -L$$(LOG4CPP_HOME)/lib
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
               src/Fitting \
               src/Format \
               src/Geometry \
               src/Ghosts \
               src/Graphics \
               src/Grid \
               src/Help \
               src/img \
               src/Import \
               src/include \
               src/Line \
               src/Load \
               src/Logger \
               src/main \
               src/Matrix \
               src/Mime \
               src/Network \
               src/NonPdf \
               src/Ordinal \
               src/Pdf \
               src/Plot \
               src/Point \
               src/ScaleBar \
               src/Segment \
               src/Settings \
               src/Spline \
               src/StatusBar \
               src/Transformation \
               src/Translator \
               src/Tutorial \
               src/util \
               src/View \
               src/Window \
               src/Zoom

win32-* {
  INCLUDEPATH += $$(FFTW_HOME)/include \
                 $$(LOG4CPP_HOME)/include
}

RESOURCES += src/engauge.qrc

CONFIG(debug,debug|release) {
  message("Build type:       debug")
} else {
  message("Build type:       release")
}

jpeg2000 {
    message("JPEG2000 support: yes")
    _OPENJPEG_INCLUDE = $$(OPENJPEG_INCLUDE)
    _OPENJPEG_LIB = $$(OPENJPEG_LIB)
    isEmpty(_OPENJPEG_INCLUDE) {
      error("OPENJPEG_INCLUDE and OPENJPEG_LIB environment variables must be defined")
    } else {
      isEmpty(_OPENJPEG_LIB) {
        error("OPENJPEG_INCLUDE and OPENJPEG_LIB environment variables must be defined")
      }
    }
    DEFINES += "ENGAUGE_JPEG2000"
    INCLUDEPATH += $$(OPENJPEG_INCLUDE) \
                   src/Jpeg2000
    LIBS += -L$$(OPENJPEG_LIB) -lopenjp2
    HEADERS += src/Jpeg2000/Jpeg2000.h \
               src/Jpeg2000/Jpeg2000Callbacks.h \
               src/Jpeg2000/Jpeg2000Color.h \
               src/Jpeg2000/Jpeg2000Convert.h \
               src/Jpeg2000/Jpeg2000FormatDefs.h
    SOURCES += src/Jpeg2000/Jpeg2000.cpp \
               src/Jpeg2000/Jpeg2000Callbacks.cpp \
               src/Jpeg2000/Jpeg2000Color.cpp \
               src/Jpeg2000/Jpeg2000Convert.cpp
    QMAKE_LFLAGS += -Wl,-rpath=\'\$\$ORIGIN\'
    QMAKE_POST_LINK += cp $$(OPENJPEG_LIB)/libopenjp2.so.7 bin

} else {
    message("JPEG2000 support: no")
}

pdf {
    message("PDF support:      yes")
    _POPPLER_INCLUDE = $$(POPPLER_INCLUDE)
    _POPPLER_LIB = $$(POPPLER_LIB)
    isEmpty(_POPPLER_INCLUDE) {
      error("POPPLER_INCLUDE and POPPLER_LIB environment variables must be defined")
    } else {
      isEmpty(_POPPLER_LIB) {
        error("POPPLER_INCLUDE and POPPLER_LIB environment variables must be defined")
      }
    }
    DEFINES += "ENGAUGE_PDF"
    LIBS += -L$$(POPPLER_LIB) -lpoppler-qt5
    INCLUDEPATH += $$(POPPLER_INCLUDE)
    HEADERS += src/Dlg/DlgImportCroppingPdf.h \
               src/Import/ImportCroppingUtilPdf.h \
               src/Pdf/Pdf.h \
               src/Pdf/PdfCropping.h \
               src/Pdf/PdfFrameHandle.h
    SOURCES += src/Dlg/DlgImportCroppingPdf.cpp \
               src/Import/ImportCroppingUtilPdf.cpp \
               src/Pdf/Pdf.cpp \
               src/Pdf/PdfCropping.cpp \
               src/Pdf/PdfFrameHandle.cpp

} else {
    message("PDF support:      no")
}

# People interested in translating a language can contact the developers for help. 
# 
# Translation file names are 'engauge_XX_YY' or 'engauge_XX' where:
#   XX = two letter language codes in column '639-1' at https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
#   YY = two letter country codes in column 'ISO 3166-2' at https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2
# where XX and YY are:
#   ar = Arabic     Egypt=_eg
#   cs = Czech      Czech Republic=_cs
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
               translations/engauge_cs.ts \
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
