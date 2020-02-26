#ifndef TEST_GUIDELINES_H
#define TEST_GUIDELINES_H

#include "GuidelineState.h"
#include <QObject>
#include <QString>
#include <QTimer>

class MainWindow;

/// Unit test of guidelines. Since the QtTest framework automatically screams through
/// the private slots of this class but we want mouse/command/signal events to happen
/// at their own pace in the gui, we use a multi-step approach:
/// -# Under initTestCase() we use run the actual tests. Each test gets two smaller steps:
///     -# Run the 'TestPrepare' method which queues up command(s) in MainWindow command queue
///     -# The 'Test' method gets called after the 'TestPrepare' method has done its magic. This
///        stores the result from each test into a FIFO list
/// -# Let QtTest framework call each private slot. Each private slot grabs the next result
///    in the FIFO list
/// This approach produces test output that is formatted just like 'normal' QtTest tests
/// (pass/fail in green/red, with class and function names afterwards)
class TestGuidelines : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestGuidelines(QObject *parent = 0);

public slots:
  // These would be private slots but we want to control when they are called so
  // these are moved outside of the private slots (which qttest automatically calls).
  // Number of methods here must agree with NUMBER_TESTS
  void test00StartupWithoutTransformation ();
  void test01AfterAddingTransformation ();
  void test02AfterRemovingTransformation ();

private slots:

  void cleanupTestCase ();
  void initTestCase ();

  // Number of tests (with one private slot per test) must equal NUMBER_TESTS
  void test00StartupWithoutTransformationReport ();
  void test01AfterAddingTransformationReport ();
  void test02AfterRemovingTransformationReport ();

private:

  /// Helper class containing result set from one test
  class Result
  {
  public:
    /// Single constructor
    Result (bool pass,
            const QString &problem);

    /// Get method for pass/fail result
    bool pass () const;

    /// Problem encountered with fail result
    QString problem () const;

  private:
    Result ();

    bool m_pass;
    QString m_problem;
  };

  /// Data collection
  typedef QList<Result> Results;

  Result compareExpectedAndGot (const QVector<int> &countsExpectedXT,
                                const QVector<int> &countsExpectedYR);
  GuidelineState guidelineStateFromString (const QString &string) const;

  // Number of methods here must agree with NUMBER_TESTS
  void test00StartupWithoutTransformationPrepare ();  
  void test01AfterAddingTransformationPrepare ();
  void test02AfterRemovingTransformationPrepare ();

  void turnOffChecklist ();

  MainWindow *m_mainWindow;
  QTimer m_showTimer;
  Results m_results;
};

#endif // TEST_GUIDELINES_H
