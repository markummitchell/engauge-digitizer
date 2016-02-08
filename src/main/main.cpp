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
const QString CMD_REGRESSION ("regression");
const QString DASH ("-");
const QString DASH_DEBUG ("-" + CMD_DEBUG);
const QString DASH_ERROR ("-" + CMD_ERROR);
const QString DASH_GNUPLOT ("-" + CMD_GNUPLOT);
const QString DASH_HELP ("-" + CMD_HELP);
const QString DASH_REGRESSION ("-" + CMD_REGRESSION);

// Prototypes
bool checkFileExists (const QString &file);
void parseCmdLine (int argc,
                   char **argv,
                   bool &isDebug,
                   QString &errorReportFile,
                   bool &isGnuplot,
                   bool &isRegression,
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

  bool isDebug, isGnuplot, isRegression;
  QString errorReportFile;
  QStringList loadStartupFiles;
  parseCmdLine (argc,
                argv,
                isDebug,
                errorReportFile,
                isGnuplot,
                isRegression,
                loadStartupFiles);

  initializeLogging ("engauge",
                     "engauge.log",
                     isDebug);
  LOG4CPP_INFO_S ((*mainCat)) << "main args=" << QApplication::arguments().join (" ").toLatin1().data();

  MainWindow w (errorReportFile,
                isGnuplot,
                isRegression,
                loadStartupFiles);
  w.show();

  return a.exec();
}

void parseCmdLine (int argc,
                   char **argv,
                   bool &isDebug,
                   QString &errorReportFile,
                   bool &isGnuplot,
                   bool &isRegression,
                   QStringList &loadStartupFiles)
{
  const int COLUMN_WIDTH = 20;
  bool showUsage = false;

  // State
  bool nextIsErrorReportFile = false;
  bool nextIsRegressionFile = false;

  // Defaults
  isDebug = false;
  errorReportFile = "";
  isGnuplot = false;
  isRegression = false;

  for (int i = 1; i < argc; i++) {

    if (nextIsErrorReportFile) {
      errorReportFile = argv [i];
      showUsage |= !checkFileExists (errorReportFile);
      nextIsErrorReportFile = false;
    } else if (nextIsRegressionFile) {
      errorReportFile = argv [i];
      showUsage |= !checkFileExists (errorReportFile);
      nextIsRegressionFile = false;
    } else if (strcmp (argv [i], DASH_DEBUG.toLatin1().data()) == 0) {
      isDebug = true;
    } else if (strcmp (argv [i], DASH_ERROR.toLatin1().data()) == 0) {
      nextIsErrorReportFile = true;
    } else if (strcmp (argv [i], DASH_GNUPLOT.toLatin1().data()) == 0) {
      isGnuplot = true;
    } else if (strcmp (argv [i], DASH_REGRESSION.toLatin1().data()) == 0) {
      nextIsErrorReportFile = true;
      isRegression = true;
    } else if (strcmp (argv [i], DASH_HELP.toLatin1().data()) == 0) {
      showUsage = true; // User requested help
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
         << "[" << DASH_REGRESSION.toLatin1().data() << " <file>] "
         << "[" << DASH_HELP.toLatin1().data() << "] "
         << "[<load_file1>] [<load_file2>] ..." << endl
         << "  " << DASH_DEBUG.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Enables extra debug information" << endl
         << "  " << DASH_ERROR.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Specifies an error report file as input" << endl
         << "  " << DASH_GNUPLOT.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Output diagnostic gnuplot input files for debugging" << endl
         << "  " << DASH_REGRESSION.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Specifies an error report file as input for regression testing" << endl
         << "  " << DASH_HELP.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Show this help information" << endl
         << "  " << QString ("<load file> ").leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "File to be imported or opened at startup" << endl;

    exit (0);
  }
}
