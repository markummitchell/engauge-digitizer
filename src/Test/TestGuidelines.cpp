#include "CmdAddPointAxis.h"
#include "CmdDelete.h"
#include "CmdGong.h"
#include "GuidelineAbstract.h"
#include "Guidelines.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QSettings>
#include <QTextStream>
#include <QThread>
#include <QtTest/QtTest>
#include "Settings.h"
#include "Test/TestGuidelines.h"

using namespace std;

const int NUMBER_TESTS = 3;

QTEST_MAIN (TestGuidelines)

// TestGuidelines::Result
TestGuidelines::Result::Result (bool pass,
                                const QString &problem) :
  m_pass (pass),
  m_problem (problem)
{
}

bool TestGuidelines::Result::pass () const
{
  return m_pass;
}

QString TestGuidelines::Result::problem () const
{
  return m_problem;
}

// TestGuidelines
TestGuidelines::TestGuidelines(QObject *parent) :
  QObject(parent),
  m_mainWindow (nullptr)
{
}

void TestGuidelines::cleanupTestCase ()
{
}

TestGuidelines::Result TestGuidelines::compareExpectedAndGot (const QVector<int> &countsExpectedXT,
                                                              const QVector<int> &countsExpectedYR)
{
  Guidelines &guidelines = m_mainWindow->guidelines();
  const GuidelineContainerPrivate &containerXT = guidelines.guidelineContainerPrivateXT ();
  const GuidelineContainerPrivate &containerYR = guidelines.guidelineContainerPrivateYR ();  

  GuidelineContainerPrivate::const_iterator itr;
  
  QVector<int> countsGotXT (NUM_GUIDELINE_STATES);
  for (itr = containerXT.begin(); itr != containerXT.end(); itr++) {
    const GuidelineAbstract *guideline = *itr;

    GuidelineState state = guidelineStateFromString (guideline->stateName ());
    countsGotXT [state] += 1;
  }
  
  QVector<int> countsGotYR (NUM_GUIDELINE_STATES);
  for (itr = containerYR.begin(); itr != containerYR.end(); itr++) {
    const GuidelineAbstract *guideline = *itr;

    GuidelineState state = guidelineStateFromString (guideline->stateName ());
    countsGotYR [state] += 1;
  }  

  // Compare expected and got counts
  bool success = true;
  for (int state = 0; state < NUM_GUIDELINE_STATES; state++) {

    // We look for a difference, except for the discarded state which is not important
    if (countsExpectedXT [state] != countsGotXT [state] ||
        countsExpectedYR [state] != countsGotYR [state]) {
      if (state != GUIDELINE_STATE_DISCARDED) {

        success = false;
        break;
      }
    }
  }

  // Debug
  if (success) {

    return Result (true,
                   "");

  } else {

    QString text;
    QTextStream str (&text);
    str << "Expected/got=";
    for (int state = 0; state < NUM_GUIDELINE_STATES; state++) {
      if ((countsExpectedXT [state] != 0) ||
          (countsExpectedYR [state] != 0) ||
          (countsGotXT [state] != 0) ||
          (countsGotYR [state] != 0)) {

        str << guidelineStateAsString (static_cast<GuidelineState> (state)) << "=";
        if (state == GUIDELINE_STATE_DISCARDED) {
          str << "ARBITRARY";
        } else {
          str << countsExpectedXT [state];
        }
        str << "/" << countsGotXT [state] << " and ";
        if (state == GUIDELINE_STATE_DISCARDED) {
          str << "ARBITRARY";
        } else {
          str << countsExpectedYR [state];
        }
        str << "/" << countsGotYR [state] << " ";
      }
    }

    return Result (false,
                   text);
  }
}

GuidelineState TestGuidelines::guidelineStateFromString (const QString &string) const
{
  for (int i = 0; i < NUM_GUIDELINE_STATES; i++) {
    GuidelineState state = static_cast<GuidelineState> (i);
    if (string == guidelineStateAsString (state)) {
      return state;
    }
  }

  return GUIDELINE_STATE_DISCARDED;
}

void TestGuidelines::initTestCase ()
{
  turnOffChecklist ();

  // Start MainWindow
  const bool NO_DROP_REGRESSION = false;
  const QString NO_ERROR_REPORT_LOG_FILE;
  const QString NO_REGRESSION_OPEN_FILE;
  const bool NO_GNUPLOT_LOG_FILES = false;
  const bool NO_REGRESSION_IMPORT = false;
  const bool NO_RESET = false;
  const bool NO_EXPORT_ONLY = false;
  const bool NO_EXPORT_IMAGE_ONLY = false;
  const QString NO_EXPORT_IMAGE_EXTENSION;
  const bool DEBUG_FLAG = false;
  QStringList importFile;
  const QStringList NO_COMMAND_LINE;

  importFile << "../samples/inverse.jpg";

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  m_mainWindow = new MainWindow (NO_ERROR_REPORT_LOG_FILE,
                                 NO_REGRESSION_OPEN_FILE,
                                 NO_DROP_REGRESSION,
                                 NO_REGRESSION_IMPORT,
                                 NO_GNUPLOT_LOG_FILES,
                                 NO_RESET,
                                 NO_EXPORT_ONLY,
                                 NO_EXPORT_IMAGE_ONLY,
                                 NO_EXPORT_IMAGE_EXTENSION,
                                 importFile,
                                 NO_COMMAND_LINE);
  
  m_mainWindow->show ();

  test00StartupWithoutTransformationPrepare ();

  // We cannot return until every test has finished, since as soon as this
  // finishes, QtTest will start calling the private slots
  while (m_results.size () < NUMBER_TESTS) {
    qApp->processEvents ();
  }
}

void TestGuidelines::test00StartupWithoutTransformation ()
{
  // Expected and got counts
  QVector<int> countsExpectedXT (NUM_GUIDELINE_STATES), countsExpectedYR (NUM_GUIDELINE_STATES);

  m_results.push_back (compareExpectedAndGot (countsExpectedXT,
                                              countsExpectedYR));

  // Connect to next test here
  test01AfterAddingTransformationPrepare ();
}

void TestGuidelines::test00StartupWithoutTransformationPrepare ()
{
  const int FIVE_SECONDS = 5000;

  // Setup for first test in the chain. We use a timer to give the gui time to
  // start up
  connect (&m_showTimer, SIGNAL (timeout ()),
           this, SLOT (test00StartupWithoutTransformation ()));

  m_showTimer.setSingleShot (true);
  m_showTimer.start (FIVE_SECONDS);
}

void TestGuidelines::test00StartupWithoutTransformationReport ()
{
  // If there is no result for this test then NUMBER_TESTS is off
  const Result &result = m_results.front ();
  if (!result.pass ()) {
    cout << result.problem().toLatin1().data() << endl;
  }

  bool pass = result.pass ();
  m_results.pop_front ();

  QVERIFY (pass);
}

void TestGuidelines::test01AfterAddingTransformation ()
{
  // Expected and got counts
  QVector<int> countsExpectedXT (NUM_GUIDELINE_STATES), countsExpectedYR (NUM_GUIDELINE_STATES);

  m_results.push_back (compareExpectedAndGot (countsExpectedXT,
                                              countsExpectedYR));

  // Connect to next test here
  test02AfterRemovingTransformationPrepare ();
}

void TestGuidelines::test01AfterAddingTransformationPrepare ()
{
  // Setup for next test in the chain
  disconnect (m_mainWindow, SIGNAL (signalGong ()),
              this, SLOT (test00StartupWithoutTransformation ()));
  connect (m_mainWindow, SIGNAL (signalGong ()),
           this, SLOT (test01AfterAddingTransformation ()));

  QPointF posScreen0 (400, 400);
  QPointF posScreen1 (600, 400);
  QPointF posScreen2 (400, 200);
  QPointF posGraph0 (40, 40);
  QPointF posGraph1 (60, 40);
  QPointF posGraph2 (40, 20);
  CmdAddPointAxis *cmd0 = new CmdAddPointAxis (*m_mainWindow,
                                               m_mainWindow->cmdMediator()->document(),
                                               posScreen0,
                                               posGraph0,
                                               0.0,
                                               false);
  CmdAddPointAxis *cmd1 = new CmdAddPointAxis (*m_mainWindow,
                                               m_mainWindow->cmdMediator()->document(),
                                               posScreen1,
                                               posGraph1,
                                               1.0,
                                               false);
  CmdAddPointAxis *cmd2 = new CmdAddPointAxis (*m_mainWindow,
                                               m_mainWindow->cmdMediator()->document(),
                                               posScreen2,
                                               posGraph2,
                                               2.0,
                                               false);
  CmdGong *cmd3 = new CmdGong (*m_mainWindow,
                               m_mainWindow->cmdMediator()->document());
                               
  m_mainWindow->cmdMediator()->push (cmd0);
  m_mainWindow->cmdMediator()->push (cmd1);
  m_mainWindow->cmdMediator()->push (cmd2);
  m_mainWindow->cmdMediator()->push (cmd3);  
}

void TestGuidelines::test01AfterAddingTransformationReport ()
{
  // If there is no result for this test then NUMBER_TESTS is off
  const Result &result = m_results.front ();
  if (!result.pass ()) {
    cout << result.problem().toLatin1().data() << endl;
  }

  bool pass = result.pass ();
  m_results.pop_front ();

  QVERIFY (pass);
}

void TestGuidelines::test02AfterRemovingTransformation ()
{
  // Expected and got counts
  QVector<int> countsExpectedXT (NUM_GUIDELINE_STATES), countsExpectedYR (NUM_GUIDELINE_STATES);

  m_results.push_back (compareExpectedAndGot (countsExpectedXT,
                                              countsExpectedYR));

  // Connect to next test here
  //test03... ();
}

void TestGuidelines::test02AfterRemovingTransformationPrepare ()
{
  // Setup for next test in the chain
  disconnect (m_mainWindow, SIGNAL (signalGong ()),
              this, SLOT (test01AfterAddingTransformation ()));
  connect (m_mainWindow, SIGNAL (signalGong ()),
           this, SLOT (test02AfterRemovingTransformation ()));

  const QString POINT2_IDENTIFIER ("Axes\tpoint\t2");
  QStringList pointsToDelete;
  pointsToDelete << POINT2_IDENTIFIER;

  CmdDelete *cmd0 = new CmdDelete (*m_mainWindow,
                                   m_mainWindow->cmdMediator()->document(),
                                   pointsToDelete);
  CmdGong *cmd1 = new CmdGong (*m_mainWindow,
                               m_mainWindow->cmdMediator()->document());

  m_mainWindow->cmdMediator()->push (cmd0);
  m_mainWindow->cmdMediator()->push (cmd1);
}

void TestGuidelines::test02AfterRemovingTransformationReport ()
{
  // If there is no result for this test then NUMBER_TESTS is off
  const Result &result = m_results.front ();
  if (!result.pass ()) {
    cout << result.problem().toLatin1().data() << endl;
  }

  bool pass = result.pass ();
  m_results.pop_front ();

  QVERIFY (pass);
}

void TestGuidelines::turnOffChecklist ()
{
  // Turn off checklist
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  
  settings.beginGroup (SETTINGS_GROUP_MAIN_WINDOW);
  settings.setValue (SETTINGS_CHECKLIST_GUIDE_WIZARD, false);
  settings.endGroup ();
}
