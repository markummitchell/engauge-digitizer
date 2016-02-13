#include "ColorFilterMode.h"
#include <iostream>
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QFileInfo>

using namespace std;

const QString CMD_DEBUG ("debug");
const QString CMD_ERROR ("error");
const QString CMD_GNUPLOT ("gnuplot");
const QString CMD_HELP ("help");
const QString CMD_REGRESSION_IMPORT ("regressionimport");
const QString CMD_REGRESSION_OPEN ("regressionopen");
const QString DASH ("-");
const QString DASH_DEBUG ("-" + CMD_DEBUG);
const QString DASH_ERROR ("-" + CMD_ERROR);
const QString DASH_GNUPLOT ("-" + CMD_GNUPLOT);
const QString DASH_HELP ("-" + CMD_HELP);
const QString DASH_REGRESSION_IMPORT ("-" + CMD_REGRESSION_IMPORT);
const QString DASH_REGRESSION_OPEN ("-" + CMD_REGRESSION_OPEN);

// Prototypes
bool checkFileExists (const QString &file);
void parseCmdLine (int argc,
                   char **argv,
                   bool &isDebug,
                   QString &errorReportFile,
                   QString &regressionOpenFile,
                   bool &isGnuplot,
                   bool &isRegressionImport,
                   QStringList &loadStartupFiles);

// Functions
bool checkFileExists (const QString &file)
{
  QFileInfo check (file);
  return check.exists() && check.isFile();
}

int main(int argc, char *argv[])
{
  qRegisterMetaType<ColorFilterMode> ("ColorFilterMode");

  QApplication a(argc, argv);

  bool isDebug, isGnuplot, isRegressionImport;
  QString errorReportFile, regressionOpenFile;
  QStringList loadStartupFiles;
  parseCmdLine (argc,
                argv,
                isDebug,
                errorReportFile,
                regressionOpenFile,
                isGnuplot,
                isRegressionImport,
                loadStartupFiles);

  initializeLogging ("engauge",
                     "engauge.log",
                     isDebug);
  LOG4CPP_INFO_S ((*mainCat)) << "main args=" << QApplication::arguments().join (" ").toLatin1().data();

  MainWindow w (errorReportFile,
                regressionOpenFile,
                isGnuplot,
                isRegressionImport,
                loadStartupFiles);
  w.show();

  return a.exec();
}

void parseCmdLine (int argc,
                   char **argv,
                   bool &isDebug,
                   QString &errorReportFile,
                   QString &regressionOpenFile,
                   bool &isGnuplot,
                   bool &isRegressionImport,
                   QStringList &loadStartupFiles)
{
  const int COLUMN_WIDTH = 20;
  bool showUsage = false;

  // State
  bool nextIsErrorReportFile = false;
  bool nextIsRegressionImportFile = false;
  bool nextIsRegressionOpenFile = false;

  // Defaults
  isDebug = false;
  errorReportFile = "";
  regressionOpenFile = "";
  isGnuplot = false;
  isRegressionImport = false;

  for (int i = 1; i < argc; i++) {

    if (nextIsErrorReportFile) {
      errorReportFile = argv [i];
      showUsage |= !checkFileExists (errorReportFile);
      nextIsErrorReportFile = false;
    } else if (nextIsRegressionImportFile) {
      errorReportFile = argv [i];
      showUsage |= !checkFileExists (errorReportFile);
      nextIsRegressionImportFile = false;
    } else if (nextIsRegressionOpenFile) {
      regressionOpenFile = argv [i];
      showUsage |= !checkFileExists (regressionOpenFile);
      nextIsRegressionOpenFile = false;
    } else if (strcmp (argv [i], DASH_DEBUG.toLatin1().data()) == 0) {
      isDebug = true;
    } else if (strcmp (argv [i], DASH_ERROR.toLatin1().data()) == 0) {
      nextIsErrorReportFile = true;
    } else if (strcmp (argv [i], DASH_GNUPLOT.toLatin1().data()) == 0) {
      isGnuplot = true;
    } else if (strcmp (argv [i], DASH_HELP.toLatin1().data()) == 0) {
      showUsage = true; // User requested help
    } else if (strcmp (argv [i], DASH_REGRESSION_IMPORT.toLatin1().data()) == 0) {
      nextIsErrorReportFile = true;
      isRegressionImport = true;
    } else if (strcmp (argv [i], DASH_REGRESSION_OPEN.toLatin1().data()) == 0) {
      nextIsRegressionOpenFile = true;
    } else if (strncmp (argv [i], DASH.toLatin1().data(), 1) == 0) {
      showUsage = true; // User entered an unrecognized token
    } else {
      loadStartupFiles << argv [i]; // Save file name
    }
  }

  if (showUsage || nextIsErrorReportFile) {

    cerr << "Usage: engauge "
         << "[" << DASH_DEBUG.toLatin1().data() << "] "
         << "[" << DASH_ERROR.toLatin1().data() << " <file>] "
         << "[" << DASH_GNUPLOT.toLatin1().data() << "] "
         << "[" << DASH_HELP.toLatin1().data() << "] "
         << "[" << DASH_REGRESSION_IMPORT.toLatin1().data() << " <file>] "
         << "[" << DASH_REGRESSION_OPEN.toLatin1().data() << " <file>] "
         << "[<load_file1>] [<load_file2>] ..." << endl
         << "  " << DASH_DEBUG.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Enables extra debug information" << endl
         << "  " << DASH_ERROR.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Specifies an error report file as input" << endl
         << "  " << DASH_GNUPLOT.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Output diagnostic gnuplot input files for debugging" << endl
         << "  " << DASH_HELP.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Show this help information" << endl
         << "  " << DASH_REGRESSION_IMPORT.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Specifies an error report file as input for regression testing" << endl
         << "  " << DASH_REGRESSION_OPEN.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Specifies a Engauge document file as input for regression testing" << endl
         << "  " << QString ("<load file> ").leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "File to be imported or opened at startup" << endl;

    exit (0);
  }
}
