# engauge_test_template.pro : Builds make files for testing engauge executable
#
# Instructions are in the INSTALL file, with some comments about setting the configuration variable 'CONFIG' included below

TEMPLATE    = app

# CONFIG comments:
# 1) Add 'jpeg2000' to the qmake command line to include support for JPEG2000 input files. Requires
#       1) previous installation of the jpeg2000 development package
#       2) JPEG2000_INCLUDE environment variable pointing to directory containing openjpeg.h
#       3) JPEG2000_LIB environment variable pointing to directory containing libopenjp2.so
#    Sample command lines
#       qmake CONFIG+=jpeg2000
#       qmake "CONFIG+=debug jpeg2000"
# 2) Add 'pdf' to the qmake command line to include support for PDF input files. Requires
#       1) previous installation of the poppler-qt5 development package
#       2) POPPLER_INCLUDE environment variable pointing to directory containing poppler-qt5.h
#       3) POPPLER_LIB environment variable pointing to directory containing libpoppler-qt5.so
#    Sample command lines
#       qmake CONFIG+=pdf
#       qmake "CONFIG+=debug pdf"
# 3) Gratuitous warning about import_qpa_plugin in Fedora is due to 'CONFIG=qt' but that option takes care of 
#    include/library files in an automated and platform-independent manner, so it will not be removed
# 4) c++11 is required for nullptr
CONFIG      += qt warn_on thread testcase c++11

OBJECTS_DIR = .objs_test
MOC_DIR = .moc_test
RCC_DIR = .rcc_test

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
    Callback/CallbackDocumentHash.h \
    Callback/CallbackDocumentScrub.h \
    Callback/CallbackGatherXThetasAbstractBase.h \
    Callback/CallbackGatherXThetasInCurves.h \
    Callback/CallbackGatherXThetasInGridLines.h \
    Callback/CallbackNextOrdinal.h \
    Callback/CallbackPointOrdinal.h \
    Callback/CallbackRemovePointsInCurvesGraphs.h \
    Callback/CallbackScaleBar.h \
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
    Cmd/CmdAddScale.h \
    Cmd/CmdCopy.h \
    Cmd/CmdCut.h \
    Cmd/CmdDelete.h \
    Cmd/CmdEditPointAxis.h \
    Cmd/CmdEditPointGraph.h \
    Cmd/CmdFactory.h \
    Cmd/CmdMediator.h \
    Cmd/CmdMoveBy.h \
    Cmd/CmdPointChangeBase.h \
    Cmd/CmdRedoForTest.h \
    Cmd/CmdSelectCoordSystem.h \
    Cmd/CmdSettingsAxesChecker.h \
    Cmd/CmdSettingsColorFilter.h \
    Cmd/CmdSettingsCoords.h \
    Cmd/CmdSettingsCurveList.h \
    Cmd/CmdSettingsCurveProperties.h \
    Cmd/CmdSettingsDigitizeCurve.h \
    Cmd/CmdSettingsExportFormat.h \
    Cmd/CmdSettingsGeneral.h \
    Cmd/CmdSettingsGridDisplay.h \
    Cmd/CmdSettingsGridRemoval.h \
    Cmd/CmdSettingsPointMatch.h \
    Cmd/CmdSettingsSegments.h \
    Cmd/CmdStackShadow.h \
    Cmd/CmdUndoForTest.h \
    Color/ColorConstants.h \
    Color/ColorFilter.h \
    Color/ColorFilterEntry.h \
    Color/ColorFilterHistogram.h \
    Color/ColorFilterMode.h \
    Color/ColorFilterSettings.h \
    Color/ColorFilterSettingsStrategyAbstractBase.h \
    Color/ColorFilterSettingsStrategyForeground.h \
    Color/ColorFilterSettingsStrategyHue.h \
    Color/ColorFilterSettingsStrategyIntensity.h \
    Color/ColorFilterSettingsStrategySaturation.h \
    Color/ColorFilterSettingsStrategyValue.h \
    Color/ColorFilterStrategyAbstractBase.h \
    Color/ColorFilterStrategyForeground.h \
    Color/ColorFilterStrategyHue.h \
    Color/ColorFilterStrategyIntensity.h \
    Color/ColorFilterStrategySaturation.h \
    Color/ColorFilterStrategyValue.h \
    Color/ColorPalette.h \
    Coord/CoordScale.h \
    Coord/CoordsType.h \
    Coord/CoordSymbol.h \
    CoordSystem/CoordSystem.h \
    CoordSystem/CoordSystemContext.h \
    CoordSystem/CoordSystemIndex.h \
    CoordSystem/CoordSystemInterface.h \
    Coord/CoordUnitsDate.h \
    Coord/CoordUnitsNonPolarTheta.h \
    Coord/CoordUnitsPolarTheta.h \
    Coord/CoordUnitsTime.h \
    Correlation/Correlation.h \
    Create/CreateActions.h \
    Create/CreateCentralWidget.h \
    Create/CreateCommandStackShadow.h \
    Create/CreateDockableWidgets.h \
    Create/CreateFacade.h \
    Create/CreateHelpWindow.h \
    Create/CreateIcons.h \
    Create/CreateLoadImage.h \
    Create/CreateMenus.h \
    Create/CreateNetwork.h \
    Create/CreateScene.h \
    Create/CreateSettingsDialogs.h \
    Create/CreateStateContexts.h \
    Create/CreateStatusBar.h \
    Create/CreateToolBars.h \
    Create/CreateTutorial.h \
    Create/CreateZoomMaps.h \
    Cursor/CursorFactory.h \
    Cursor/CursorSize.h \
    Curve/Curve.h \
    Curve/CurveConnectAs.h \
    Curve/CurveNameList.h \
    include/CurveLimits.h \
    include/CurvesIncludedHash.h \
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
    DigitizeState/DigitizeStateScale.h \    
    DigitizeState/DigitizeStateSegment.h \
    DigitizeState/DigitizeStateSelect.h \
    Dlg/DlgAbout.h \
    Dlg/DlgEditPointAxis.h \
    Dlg/DlgEditPointGraph.h \
    Dlg/DlgEditPointGraphLineEdit.h \
    Dlg/DlgEditScale.h \    
    Dlg/DlgErrorReportAbstractBase.h \
    Dlg/DlgErrorReportLocal.h \    
    Dlg/DlgFilterCommand.h \
    Dlg/DlgFilterThread.h \
    Dlg/DlgFilterWorker.h \
    Dlg/DlgImportAdvanced.h \
    Dlg/DlgImportCroppingNonPdf.h \
    Dlg/DlgRequiresTransform.h \
    Dlg/DlgSettingsAbstractBase.h \
    Dlg/DlgSettingsAxesChecker.h \
    Dlg/DlgSettingsColorFilter.h \
    Dlg/DlgSettingsCoords.h \
    Dlg/DlgSettingsCurveList.h \
    Dlg/DlgSettingsCurveProperties.h \
    Dlg/DlgSettingsDigitizeCurve.h \
    Dlg/DlgSettingsExportFormat.h \
    Dlg/DlgSettingsGeneral.h \
    Dlg/DlgSettingsGridDisplay.h \
    Dlg/DlgSettingsGridRemoval.h \
    Dlg/DlgSettingsMainWindow.h \
    Dlg/DlgSettingsPointMatch.h \
    Dlg/DlgSettingsSegments.h \
    Dlg/DlgValidatorAboveZero.h \
    Dlg/DlgValidatorAbstract.h \
    Dlg/DlgValidatorDateTime.h \
    Dlg/DlgValidatorDegreesMinutesSeconds.h \
    Dlg/DlgValidatorFactory.h \
    Dlg/DlgValidatorNumber.h \
    Document/Document.h \
    Document/DocumentAxesPointsRequired.h \
    Document/DocumentHash.h \
    Document/DocumentHashGenerator.h \
    Document/DocumentModelAbstractBase.h \
    Document/DocumentModelAxesChecker.h \
    Document/DocumentModelColorFilter.h \
    Document/DocumentModelCoords.h \
    Document/DocumentModelDigitizeCurve.h \
    Document/DocumentModelExportFormat.h \
    Document/DocumentModelGeneral.h \
    Document/DocumentModelGridDisplay.h \
    Document/DocumentModelGridRemoval.h \
    Document/DocumentModelPointMatch.h \
    Document/DocumentModelSegments.h \
    Document/DocumentScrub.h \
    Document/DocumentSerialize.h \
    util/EllipseParameters.h \
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
    Export/ExportImageForRegression.h \
    Export/ExportOrdinalsSmooth.h \
    Export/ExportOrdinalsStraight.h \
    Export/ExportToClipboard.h \
    Export/ExportToFile.h \
    Export/ExportValuesOrdinal.h \
    Export/ExportValuesXOrY.h \
    Export/ExportXThetaValuesMergedFunctions.h \
    FileCmd/FileCmdAbstract.h \
    FileCmd/FileCmdClose.h \
    FileCmd/FileCmdExport.h \
    FileCmd/FileCmdFactory.h \
    FileCmd/FileCmdImport.h \
    FileCmd/FileCmdOpen.h \
    FileCmd/FileCmdSerialize.h \
    FileCmd/FileCmdScript.h \
    Filter/FilterImage.h \
    Fitting/FittingCurve.h \
    Fitting/FittingCurveCoefficients.h \            
    Fitting/FittingModel.h \
    Fitting/FittingPointsConvenient.h \        
    Fitting/FittingStatistics.h \
    Fitting/FittingWindow.h \
    Format/FormatCoordsUnits.h \
    Format/FormatCoordsUnitsStrategyAbstractBase.h \
    Format/FormatCoordsUnitsStrategyNonPolarTheta.h \
    Format/FormatCoordsUnitsStrategyPolarTheta.h \
    Format/FormatDateTime.h \
    Format/FormatDegreesMinutesSecondsBase.h \
    Format/FormatDegreesMinutesSecondsNonPolarTheta.h \
    Format/FormatDegreesMinutesSecondsPolarTheta.h \
    Callback/functor.h \
    Geometry/GeometryModel.h \
    Geometry/GeometryStrategyAbstractBase.h \
    Geometry/GeometryStrategyContext.h \
    Geometry/GeometryStrategyFunctionSmooth.h \
    Geometry/GeometryStrategyFunctionStraight.h \
    Geometry/GeometryStrategyRelationSmooth.h \
    Geometry/GeometryStrategyRelationStraight.h \
    Geometry/GeometryWindow.h \
    Ghosts/GhostEllipse.h \
    Ghosts/GhostPath.h \
    Ghosts/GhostPolygon.h \
    Ghosts/Ghosts.h \
    util/gnuplot.h \
    Graphics/GraphicsArcItem.h \
    Graphics/GraphicsItemsExtractor.h \
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
    Grid/GridHealerAbstractBase.h \
    Grid/GridHealerHorizontal.h \
    Grid/GridHealerVertical.h \
    Grid/GridIndependentToDependent.h \
    Grid/GridInitializer.h \
    Grid/GridLine.h \
    Grid/GridLineFactory.h \
    Grid/GridLineLimiter.h \
    Grid/GridLines.h \
    Grid/GridLineStyle.h \
    Grid/GridLog.h \
    Grid/GridRemoval.h \
    Grid/GridTriangleFill.h \
    Guideline/GuidelineAbstract.h \
    Guideline/GuidelineEllipse.h \
    Guideline/GuidelineFormat.h \
    Guideline/GuidelineLine.h \
    Guideline/GuidelineProjectorAbstract.h \
    Guideline/GuidelineProjectorConstantR.h \
    Guideline/GuidelineProjectorConstantT.h \
    Guideline/GuidelineProjectorConstantX.h \
    Guideline/GuidelineProjectorConstantY.h \
    Guideline/Guidelines.h \
    Guideline/GuidelineState.h \
    Guideline/GuidelineStateAbstractBase.h \
    Guideline/GuidelineStateContext.h \
    Guideline/GuidelineStateDeployedAbstract.h \
    Guideline/GuidelineStateDeployedConstantRAbstract.h \
    Guideline/GuidelineStateDeployedConstantRActive.h \
    Guideline/GuidelineStateDeployedConstantRHide.h \
    Guideline/GuidelineStateDeployedConstantRHover.h \
    Guideline/GuidelineStateDeployedConstantRLocked.h \
    Guideline/GuidelineStateDeployedConstantTAbstract.h \
    Guideline/GuidelineStateDeployedConstantTActive.h \
    Guideline/GuidelineStateDeployedConstantTHide.h \
    Guideline/GuidelineStateDeployedConstantTHover.h \
    Guideline/GuidelineStateDeployedConstantTLocked.h \
    Guideline/GuidelineStateDeployedConstantXAbstract.h \
    Guideline/GuidelineStateDeployedConstantXActive.h \
    Guideline/GuidelineStateDeployedConstantXHide.h \
    Guideline/GuidelineStateDeployedConstantXHover.h \
    Guideline/GuidelineStateDeployedConstantXLocked.h \
    Guideline/GuidelineStateDeployedConstantYAbstract.h \
    Guideline/GuidelineStateDeployedConstantYActive.h \
    Guideline/GuidelineStateDeployedConstantYHide.h \
    Guideline/GuidelineStateDeployedConstantYHover.h \
    Guideline/GuidelineStateDeployedConstantYLocked.h \
    Guideline/GuidelineStateDiscarded.h \
    Guideline/GuidelineStateHandle.h \
    Guideline/GuidelineStateTemplateAbstract.h \
    Guideline/GuidelineStateTemplateHorizontalBottomAbstract.h \
    Guideline/GuidelineStateTemplateHorizontalBottomHide.h \
    Guideline/GuidelineStateTemplateHorizontalBottomHover.h \
    Guideline/GuidelineStateTemplateHorizontalBottomLurking.h \
    Guideline/GuidelineStateTemplateHorizontalTopAbstract.h \
    Guideline/GuidelineStateTemplateHorizontalTopHide.h \
    Guideline/GuidelineStateTemplateHorizontalTopHover.h \
    Guideline/GuidelineStateTemplateHorizontalTopLurking.h \
    Guideline/GuidelineStateTemplateVerticalLeftAbstract.h \
    Guideline/GuidelineStateTemplateVerticalLeftHide.h \
    Guideline/GuidelineStateTemplateVerticalLeftHover.h \
    Guideline/GuidelineStateTemplateVerticalLeftLurking.h \
    Guideline/GuidelineStateTemplateVerticalRightAbstract.h \
    Guideline/GuidelineStateTemplateVerticalRightHide.h \
    Guideline/GuidelineStateTemplateVerticalRightHover.h \
    Guideline/GuidelineStateTemplateVerticalRightLurking.h \
    Help/HelpBrowser.h \
    Help/HelpWindow.h \
    Import/ImportCropping.h \
    Import/ImportCroppingUtilBase.h \
    Import/ImportCroppingUtilNonPdf.h \
    Import/ImportImageExtensions.h \
    util/LinearToLog.h \
    Line/LineStyle.h \
    Load/LoadFileInfo.h \
    Load/LoadImageFromUrl.h \
    Logger/Logger.h \
    Logger/LoggerUpload.h \
    main/MainDirectoryPersist.h \
    main/MainTitleBarFormat.h \
    main/MainWindow.h \
    main/MainWindowModel.h \
    Matrix/Matrix.h \
    util/MigrateToVersion6.h \
    Mime/MimePointsDetector.h \
    Mime/MimePointsExport.h \
    Mime/MimePointsImport.h \    
    util/mmsubs.h \
    Network/NetworkClient.h \
    NonPdf/NonPdf.h \
    NonPdf/NonPdfCropping.h \
    NonPdf/NonPdfFrameHandle.h \
    Ordinal/OrdinalGenerator.h \
    Ordinal/OrdinalToGraphicsPoint.h \
    Pdf/PdfResolution.h \
    util/Pixels.h \
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
    ScaleBar/ScaleBarAxisPointsUnite.h \
    Segment/Segment.h \
    Segment/SegmentFactory.h \
    Segment/SegmentLine.h \
    Settings/Settings.h \
    Settings/SettingsForGraph.h \
    Spline/Spline.h \
    Spline/SplineCoeff.h \
    Spline/SplineDrawer.h \
    Spline/SplinePair.h \
    StatusBar/StatusBar.h \
    StatusBar/StatusBarMode.h \
    Test/TEST.h \
    Transformation/Transformation.h \
    Transformation/TransformationStateAbstractBase.h \
    Transformation/TransformationStateContext.h \
    Transformation/TransformationStateDefined.h \
    Transformation/TransformationStateUndefined.h \
    Translator/TranslatorContainer.h \
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
    Window/WindowAbstractBase.h \
    Window/WindowModelBase.h \
    Window/WindowTable.h \    
    util/Xml.h \
    Zoom/ZoomControl.h \
    Zoom/ZoomFactor.h \
    Zoom/ZoomFactorInitial.h\
    Zoom/ZoomLabels.h \
    Zoom/ZoomTransition.h \
    util/ZValues.h

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
    Callback/CallbackDocumentHash.cpp \
    Callback/CallbackDocumentScrub.cpp \
    Callback/CallbackGatherXThetasAbstractBase.cpp \
    Callback/CallbackGatherXThetasInCurves.cpp \
    Callback/CallbackGatherXThetasInGridLines.cpp \
    Callback/CallbackNextOrdinal.cpp \
    Callback/CallbackPointOrdinal.cpp \
    Callback/CallbackRemovePointsInCurvesGraphs.cpp \
    Callback/CallbackScaleBar.cpp \
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
    Cmd/CmdAddScale.cpp \    
    Cmd/CmdCopy.cpp \
    Cmd/CmdCut.cpp \
    Cmd/CmdDelete.cpp \
    Cmd/CmdEditPointAxis.cpp \
    Cmd/CmdEditPointGraph.cpp \
    Cmd/CmdFactory.cpp \
    Cmd/CmdMediator.cpp \
    Cmd/CmdMoveBy.cpp \
    Cmd/CmdRedoForTest.cpp \
    Cmd/CmdPointChangeBase.cpp \
    Cmd/CmdSelectCoordSystem.cpp \
    Cmd/CmdSettingsAxesChecker.cpp \
    Cmd/CmdSettingsColorFilter.cpp \
    Cmd/CmdSettingsCoords.cpp \
    Cmd/CmdSettingsCurveList.cpp \
    Cmd/CmdSettingsCurveProperties.cpp \
    Cmd/CmdSettingsDigitizeCurve.cpp \
    Cmd/CmdSettingsExportFormat.cpp \
    Cmd/CmdSettingsGeneral.cpp \
    Cmd/CmdSettingsGridDisplay.cpp \
    Cmd/CmdSettingsGridRemoval.cpp \
    Cmd/CmdSettingsPointMatch.cpp \
    Cmd/CmdSettingsSegments.cpp \
    Cmd/CmdStackShadow.cpp \
    Cmd/CmdUndoForTest.cpp \
    Color/ColorFilter.cpp \
    Color/ColorFilterHistogram.cpp \
    Color/ColorFilterMode.cpp \
    Color/ColorFilterSettings.cpp \
    Color/ColorFilterSettingsStrategyAbstractBase.cpp \
    Color/ColorFilterSettingsStrategyForeground.cpp \
    Color/ColorFilterSettingsStrategyHue.cpp \
    Color/ColorFilterSettingsStrategyIntensity.cpp \
    Color/ColorFilterSettingsStrategySaturation.cpp \
    Color/ColorFilterSettingsStrategyValue.cpp \
    Color/ColorFilterStrategyAbstractBase.cpp \
    Color/ColorFilterStrategyForeground.cpp \
    Color/ColorFilterStrategyHue.cpp \
    Color/ColorFilterStrategyIntensity.cpp \
    Color/ColorFilterStrategySaturation.cpp \
    Color/ColorFilterStrategyValue.cpp \
    Color/ColorPalette.cpp \
    Coord/CoordScale.cpp \
    Coord/CoordsType.cpp \
    Coord/CoordSymbol.cpp \
    CoordSystem/CoordSystem.cpp \
    CoordSystem/CoordSystemContext.cpp \
    CoordSystem/CoordSystemInterface.cpp \
    Coord/CoordUnitsDate.cpp \
    Coord/CoordUnitsNonPolarTheta.cpp \
    Coord/CoordUnitsPolarTheta.cpp \
    Coord/CoordUnitsTime.cpp \
    Correlation/Correlation.cpp \
    Create/CreateActions.cpp \
    Create/CreateCentralWidget.cpp \
    Create/CreateCommandStackShadow.cpp \
    Create/CreateDockableWidgets.cpp \
    Create/CreateFacade.cpp \
    Create/CreateHelpWindow.cpp \
    Create/CreateIcons.cpp \
    Create/CreateLoadImage.cpp \
    Create/CreateMenus.cpp \
    Create/CreateNetwork.cpp \
    Create/CreateScene.cpp \
    Create/CreateSettingsDialogs.cpp \
    Create/CreateStateContexts.cpp \
    Create/CreateStatusBar.cpp \
    Create/CreateToolBars.cpp \
    Create/CreateTutorial.cpp \
    Create/CreateZoomMaps.cpp \
    Cursor/CursorFactory.cpp \
    Cursor/CursorSize.cpp \
    Curve/Curve.cpp \
    Curve/CurveConnectAs.cpp \
    Curve/CurveNameList.cpp \
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
    DigitizeState/DigitizeStateScale.cpp \        
    DigitizeState/DigitizeStateSegment.cpp \
    DigitizeState/DigitizeStateSelect.cpp \
    Dlg/DlgAbout.cpp \
    Dlg/DlgEditPointAxis.cpp \
    Dlg/DlgEditPointGraph.cpp \
    Dlg/DlgEditPointGraphLineEdit.cpp \
    Dlg/DlgEditScale.cpp \        
    Dlg/DlgErrorReportAbstractBase.cpp \
    Dlg/DlgErrorReportLocal.cpp \        
    Dlg/DlgFilterCommand.cpp \
    Dlg/DlgFilterThread.cpp \
    Dlg/DlgFilterWorker.cpp \
    Dlg/DlgImportAdvanced.cpp \
    Dlg/DlgImportCroppingNonPdf.cpp \
    Dlg/DlgRequiresTransform.cpp \
    Dlg/DlgSettingsAbstractBase.cpp \
    Dlg/DlgSettingsAxesChecker.cpp \
    Dlg/DlgSettingsColorFilter.cpp \
    Dlg/DlgSettingsCoords.cpp \
    Dlg/DlgSettingsCurveList.cpp \
    Dlg/DlgSettingsCurveProperties.cpp \
    Dlg/DlgSettingsDigitizeCurve.cpp \
    Dlg/DlgSettingsExportFormat.cpp \
    Dlg/DlgSettingsGeneral.cpp \
    Dlg/DlgSettingsGridDisplay.cpp \
    Dlg/DlgSettingsGridRemoval.cpp \
    Dlg/DlgSettingsMainWindow.cpp \
    Dlg/DlgSettingsPointMatch.cpp \
    Dlg/DlgSettingsSegments.cpp \
    Dlg/DlgValidatorAboveZero.cpp \
    Dlg/DlgValidatorAbstract.cpp \
    Dlg/DlgValidatorDateTime.cpp \
    Dlg/DlgValidatorDegreesMinutesSeconds.cpp \
    Dlg/DlgValidatorFactory.cpp \
    Dlg/DlgValidatorNumber.cpp \
    Document/Document.cpp \
    Document/DocumentHashGenerator.cpp \
    Document/DocumentModelAbstractBase.cpp \
    Document/DocumentModelAxesChecker.cpp \
    Document/DocumentModelColorFilter.cpp \
    Document/DocumentModelCoords.cpp \
    Document/DocumentModelDigitizeCurve.cpp \
    Document/DocumentModelExportFormat.cpp \
    Document/DocumentModelGeneral.cpp \
    Document/DocumentModelGridDisplay.cpp \
    Document/DocumentModelGridRemoval.cpp \
    Document/DocumentModelPointMatch.cpp \
    Document/DocumentModelSegments.cpp \
    Document/DocumentScrub.cpp \
    Document/DocumentSerialize.cpp \
    util/EllipseParameters.cpp \
    util/EnumsToQt.cpp \
    Export/ExportAlignLinear.cpp \
    Export/ExportAlignLog.cpp \
    Export/ExportDelimiter.cpp \
    Export/ExportFileAbstractBase.cpp \
    Export/ExportFileFunctions.cpp \
    Export/ExportFileRelations.cpp \
    Export/ExportHeader.cpp \
    Export/ExportImageForRegression.cpp \
    Export/ExportLayoutFunctions.cpp \
    Export/ExportOrdinalsSmooth.cpp \
    Export/ExportOrdinalsStraight.cpp \
    Export/ExportPointsIntervalUnits.cpp \
    Export/ExportPointsSelectionFunctions.cpp \
    Export/ExportPointsSelectionRelations.cpp \
    Export/ExportToClipboard.cpp \
    Export/ExportToFile.cpp \
    Export/ExportXThetaValuesMergedFunctions.cpp \
    FileCmd/FileCmdAbstract.cpp \
    FileCmd/FileCmdClose.cpp \
    FileCmd/FileCmdExport.cpp \
    FileCmd/FileCmdFactory.cpp \
    FileCmd/FileCmdImport.cpp \
    FileCmd/FileCmdOpen.cpp \
    FileCmd/FileCmdSerialize.cpp \
    FileCmd/FileCmdScript.cpp \
    Filter/FilterImage.cpp \
    Fitting/FittingCurve.cpp \    
    Fitting/FittingModel.cpp \
    Fitting/FittingStatistics.cpp \
    Fitting/FittingWindow.cpp \    
    Format/FormatCoordsUnits.cpp \
    Format/FormatCoordsUnitsStrategyAbstractBase.cpp \
    Format/FormatCoordsUnitsStrategyNonPolarTheta.cpp \
    Format/FormatCoordsUnitsStrategyPolarTheta.cpp \
    Format/FormatDateTime.cpp \
    Format/FormatDegreesMinutesSecondsBase.cpp \
    Format/FormatDegreesMinutesSecondsNonPolarTheta.cpp \
    Format/FormatDegreesMinutesSecondsPolarTheta.cpp \
    Geometry/GeometryModel.cpp \
    Geometry/GeometryStrategyAbstractBase.cpp \
    Geometry/GeometryStrategyContext.cpp \
    Geometry/GeometryStrategyFunctionSmooth.cpp \
    Geometry/GeometryStrategyFunctionStraight.cpp \
    Geometry/GeometryStrategyRelationSmooth.cpp \
    Geometry/GeometryStrategyRelationStraight.cpp \
    Geometry/GeometryWindow.cpp \
    Ghosts/GhostEllipse.cpp \
    Ghosts/GhostPath.cpp \
    Ghosts/GhostPolygon.cpp \
    Ghosts/Ghosts.cpp \
    util/gnuplot.cpp \
    Graphics/GraphicsArcItem.cpp \
    Graphics/GraphicsItemsExtractor.cpp \
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
    Grid/GridHealerAbstractBase.cpp \
    Grid/GridHealerHorizontal.cpp \
    Grid/GridHealerVertical.cpp \
    Grid/GridInitializer.cpp \
    Grid/GridLine.cpp \
    Grid/GridLineFactory.cpp \
    Grid/GridLineLimiter.cpp \
    Grid/GridLines.cpp \
    Grid/GridLog.cpp \
    Grid/GridRemoval.cpp \
    Grid/GridTriangleFill.cpp \
    Guideline/GuidelineAbstract.cpp \
    Guideline/GuidelineEllipse.cpp \
    Guideline/GuidelineFormat.cpp \
    Guideline/GuidelineLine.cpp \
    Guideline/GuidelineProjectorAbstract.cpp \
    Guideline/GuidelineProjectorConstantR.cpp \
    Guideline/GuidelineProjectorConstantT.cpp \
    Guideline/GuidelineProjectorConstantX.cpp \
    Guideline/GuidelineProjectorConstantY.cpp \
    Guideline/Guidelines.cpp \
    Guideline/GuidelineStateAbstractBase.cpp \
    Guideline/GuidelineStateContext.cpp \
    Guideline/GuidelineStateDeployedAbstract.cpp \
    Guideline/GuidelineStateDeployedConstantRAbstract.cpp \
    Guideline/GuidelineStateDeployedConstantRActive.cpp \
    Guideline/GuidelineStateDeployedConstantRHide.cpp \
    Guideline/GuidelineStateDeployedConstantRHover.cpp \
    Guideline/GuidelineStateDeployedConstantRLocked.cpp \
    Guideline/GuidelineStateDeployedConstantTAbstract.cpp \
    Guideline/GuidelineStateDeployedConstantTActive.cpp \
    Guideline/GuidelineStateDeployedConstantTHide.cpp \
    Guideline/GuidelineStateDeployedConstantTHover.cpp \
    Guideline/GuidelineStateDeployedConstantTLocked.cpp \
    Guideline/GuidelineStateDeployedConstantXAbstract.cpp \
    Guideline/GuidelineStateDeployedConstantXActive.cpp \
    Guideline/GuidelineStateDeployedConstantXHide.cpp \
    Guideline/GuidelineStateDeployedConstantXHover.cpp \
    Guideline/GuidelineStateDeployedConstantXLocked.cpp \
    Guideline/GuidelineStateDeployedConstantYAbstract.cpp \
    Guideline/GuidelineStateDeployedConstantYActive.cpp \
    Guideline/GuidelineStateDeployedConstantYHide.cpp \
    Guideline/GuidelineStateDeployedConstantYHover.cpp \
    Guideline/GuidelineStateDeployedConstantYLocked.cpp \
    Guideline/GuidelineStateDiscarded.cpp \
    Guideline/GuidelineStateHandle.cpp \
    Guideline/GuidelineStateTemplateAbstract.cpp \
    Guideline/GuidelineStateTemplateHorizontalBottomAbstract.cpp \
    Guideline/GuidelineStateTemplateHorizontalBottomHide.cpp \
    Guideline/GuidelineStateTemplateHorizontalBottomHover.cpp \
    Guideline/GuidelineStateTemplateHorizontalBottomLurking.cpp \
    Guideline/GuidelineStateTemplateHorizontalTopAbstract.cpp \
    Guideline/GuidelineStateTemplateHorizontalTopHide.cpp \
    Guideline/GuidelineStateTemplateHorizontalTopHover.cpp \
    Guideline/GuidelineStateTemplateHorizontalTopLurking.cpp \
    Guideline/GuidelineStateTemplateVerticalLeftAbstract.cpp \
    Guideline/GuidelineStateTemplateVerticalLeftHide.cpp \
    Guideline/GuidelineStateTemplateVerticalLeftHover.cpp \
    Guideline/GuidelineStateTemplateVerticalLeftLurking.cpp \
    Guideline/GuidelineStateTemplateVerticalRightAbstract.cpp \
    Guideline/GuidelineStateTemplateVerticalRightHide.cpp \
    Guideline/GuidelineStateTemplateVerticalRightHover.cpp \
    Guideline/GuidelineStateTemplateVerticalRightLurking.cpp \
    Help/HelpBrowser.cpp \
    Help/HelpWindow.cpp \
    Import/ImportCroppingUtilBase.cpp \
    Import/ImportCroppingUtilNonPdf.cpp \
    Import/ImportImageExtensions.cpp \
    util/LinearToLog.cpp \
    Line/LineStyle.cpp \
    Load/LoadFileInfo.cpp \
    Load/LoadImageFromUrl.cpp \
    Logger/Logger.cpp \
    Logger/LoggerUpload.cpp \
    main/MainDirectoryPersist.cpp \
    main/MainWindow.cpp \
    main/MainWindowModel.cpp \
    Matrix/Matrix.cpp \
    util/MigrateToVersion6.cpp \
    Mime/MimePointsDetector.cpp \
    Mime/MimePointsExport.cpp \
    Mime/MimePointsImport.cpp \    
    util/mmsubs.cpp \
    Network/NetworkClient.cpp \
    NonPdf/NonPdf.cpp \
    NonPdf/NonPdfCropping.cpp \
    NonPdf/NonPdfFrameHandle.cpp \
    Ordinal/OrdinalGenerator.cpp \
    Pdf/PdfResolution.cpp \
    util/Pixels.cpp \
    Point/Point.cpp \
    Point/PointIdentifiers.cpp \
    Point/PointMatchAlgorithm.cpp \
    Point/PointMatchPixel.cpp \
    Point/PointMatchTriplet.cpp \
    Point/PointShape.cpp \
    Point/PointStyle.cpp \
    util/QtToString.cpp \
    ScaleBar/ScaleBarAxisPointsUnite.cpp \    
    Segment/Segment.cpp \
    Segment/SegmentFactory.cpp \
    Segment/SegmentLine.cpp \
    Settings/Settings.cpp \
    Settings/SettingsForGraph.cpp \
    Spline/Spline.cpp \
    Spline/SplineCoeff.cpp \
    Spline/SplineDrawer.cpp \
    Spline/SplinePair.cpp \
    StatusBar/StatusBar.cpp \
    StatusBar/StatusBarMode.cpp \
    Test/TEST.cpp \
    Transformation/Transformation.cpp \
    Transformation/TransformationStateAbstractBase.cpp \
    Transformation/TransformationStateContext.cpp \
    Transformation/TransformationStateDefined.cpp \
    Transformation/TransformationStateUndefined.cpp \
    Translator/TranslatorContainer.cpp \
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
    Window/WindowAbstractBase.cpp \    
    Window/WindowModelBase.cpp \
    Window/WindowTable.cpp \    
    util/Xml.cpp \
    Zoom/ZoomLabels.cpp \
    Zoom/ZoomTransition.cpp \
    util/ZValues.cpp

TARGET = ../bin/TEST

QT += core gui network printsupport testlib widgets xml help

LIBS += -L$$(LOG4CPP_HOME)/lib -L$$(FFTW_HOME)/lib

win32-g++* {
CONFIG += windows
}

LIBS += -llog4cpp -lfftw3
INCLUDEPATH += Background \
               Callback \
               Checker \
               Checklist \
               Cmd \
               Color \
               Coord \
               CoordSystem \
               Correlation \
               Create \
               Cursor \
               Curve \
               DigitizeState \
               Dlg \
               Document \
               Export \
               FileCmd \
               Filter \
               Fitting \
               Format \
               Geometry \
               Ghosts \
               Graphics \
               Grid \
               Guideline \
               Help \
               img \
               Import \
               include \
               Line \
               Load \
               Logger \
               main \
               Matrix \
               Mime \
               Network \
               NonPdf \
               Ordinal \
               Pdf \
               Plot \
               Point \
               ScaleBar \
               Segment \
               Settings \
               Spline \
               StatusBar \
               Test \
               Transformation \
               Translator \
               Tutorial \
               util \
               View \
               Window \
               Zoom

INCLUDEPATH += $$(FFTW_HOME)/include \
               $$(LOG4CPP_HOME)/include

RESOURCES += \
    engauge.qrc

CONFIG(debug,debug|release) {
  message("Build type:       debug")
} else {
  message("Build type:       release")
}

jpeg2000 {
    message("JPEG2000 support: yes")
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
    INCLUDEPATH += $$(POPPLER_INCLUDE)
    LIBS += -L$$(POPPLER_LIB) -lpoppler -lpoppler-qt5
    HEADERS += Dlg/DlgImportCroppingPdf.h \
               Import/ImportCroppingUtilPdf.h \
               Pdf/Pdf.h \
               Pdf/PdfCropping.h \
               Pdf/PdfFrameHandle.h
    SOURCES += Dlg/DlgImportCroppingPdf.cpp \
               Import/ImportCroppingUtilPdf.cpp \
               Pdf/Pdf.cpp \
               Pdf/PdfCropping.cpp \
               Pdf/PdfFrameHandle.cpp

} else {
    message("PDF support:      no")
}

contains (DEFINES, NETWORKING) {
    message("networking build: yes")
} else {
    message("networking build: no")
}
