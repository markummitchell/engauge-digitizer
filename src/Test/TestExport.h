#ifndef TEST_EXPORT_H
#define TEST_EXPORT_H

#include "DocumentModelCoords.h"
#include "DocumentModelExportFormat.h"
#include "DocumentModelGeneral.h"
#include "ExportValuesXOrY.h"
#include "MainWindowModel.h"
#include <QObject>
#include "Transformation.h"

class Document;
class MainWindow;

/// Unit test of Export classes
class TestExport : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestExport(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  // For Switzerland cases below we are testing for case when comma is used,
  // but on some computers that locale will use period instead so we handle
  // both cases (to prevent false alarms)
  void testCommasInFunctionsForCommasSwitzerland ();
  void testCommasInFunctionsForCommasUnitedStates ();  
  void testCommasInFunctionsForTabsSwitzerland ();
  void testCommasInFunctionsForTabsUnitedStates ();    
  void testCommasInRelationsForCommasSwitzerland ();
  void testCommasInRelationsForCommasUnitedStates ();  
  void testCommasInRelationsForTabsSwitzerland ();  
  void testCommasInRelationsForTabsUnitedStates ();
  void testExportOnlyNonRegressionLowerCase ();
  void testExportOnlyNonRegressionUpperCase ();  
  void testExportOnlyRegressionLowerCase ();
  void testExportOnlyRegressionUpperCase ();    
  void testLogExtrapolationFunctionsAll ();

private:
  bool checkCommasInFunctionsForDelimiter (ExportDelimiter delimiter,
                                           QLocale::Country country,
                                           QString &output);
  bool checkCommasInRelationsForDelimiter (ExportDelimiter delimiter,
                                           QLocale::Country country,                                           
                                           QString &output);
  void initData (bool isLog,
                 ExportDelimiter delimiter,
                 QLocale::Country country);

  MainWindow *m_mainWindow;
  Document *m_document;
  DocumentModelCoords m_modelCoords;
  DocumentModelExportFormat m_modelExportOverride;
  DocumentModelGeneral m_modelGeneral;
  MainWindowModel m_modelMainWindow;
  Transformation m_transformation;
  ExportValuesXOrY m_xThetaValues;
  QStringList m_curvesIncluded;
};

#endif // TEST_EXPORT_H
