#include "ColorFilterMode.h"
#include <iostream>
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QFileInfo>

using namespace std;

const QString CMD_CURVES ("curves");
const QString CMD_DEBUG ("debug");
const QString CMD_ERROR ("error");
const QString CMD_GNUPLOT ("gnuplot");
const QString CMD_HELP ("help");
const QString DASH ("-");
const QString DASH_CURVES ("-" + CMD_CURVES);
const QString DASH_DEBUG ("-" + CMD_DEBUG);
const QString DASH_ERROR ("-" + CMD_ERROR);
const QString DASH_GNUPLOT ("-" + CMD_GNUPLOT);
const QString DASH_HELP ("-" + CMD_HELP);

// Prototypes
bool checkFileExists (const QString &file);
void parseCmdLine (int argc,
                   char **argv,
                   bool &isDebug,
                   QString &curveFile,
                   QString &errorReportFile,
                   bool &isGnuplot,
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

  bool isDebug, isGnuplot;
  QString curvesFile, errorReportFile;
  QStringList loadStartupFiles;
  parseCmdLine (argc,
                argv,
                isDebug,
                curvesFile,
                errorReportFile,
                isGnuplot,
                loadStartupFiles);

  initializeLogging ("engauge",
                     "engauge.log",
                     isDebug);
  LOG4CPP_INFO_S ((*mainCat)) << "main args=" << QApplication::arguments().join (" ").toLatin1().data();

  MainWindow w (curvesFile,
                errorReportFile,
                isGnuplot,
                loadStartupFiles);
  w.show();

  return a.exec();
}

void parseCmdLine (int argc,
                   char **argv,
                   bool &isDebug,
                   QString &curvesFile,
                   QString &errorReportFile,
                   bool &isGnuplot,
                   QStringList &loadStartupFiles)
{
  const int COLUMN_WIDTH = 20;
  bool showUsage = false;

  // State
  bool nextIsCurvesFile = false;
  bool nextIsErrorReportFile = false;

  // Defaults
  isDebug = false;
  errorReportFile = "";
  isGnuplot = false;

  for (int i = 1; i < argc; i++) {

    if (nextIsCurvesFile) {
      curvesFile = argv [i];
      showUsage |= !checkFileExists (curvesFile);
      nextIsCurvesFile = false;
    } else if (nextIsErrorReportFile) {
      errorReportFile = argv [i];
      showUsage |= !checkFileExists (errorReportFile);
      nextIsErrorReportFile = false;
    } else if (strcmp (argv [i], DASH_CURVES.toLatin1().data()) == 0) {
      nextIsCurvesFile = true;
    } else if (strcmp (argv [i], DASH_DEBUG.toLatin1().data()) == 0) {
      isDebug = true;
    } else if (strcmp (argv [i], DASH_ERROR.toLatin1().data()) == 0) {
      nextIsErrorReportFile = true;
    } else if (strcmp (argv [i], DASH_GNUPLOT.toLatin1().data()) == 0) {
      isGnuplot = true;
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
         << "[" << DASH_CURVES.toLatin1().data() << " <file>] "
         << "[" << DASH_DEBUG.toLatin1().data() << "] "
         << "[" << DASH_ERROR.toLatin1().data() << " <file>] "
         << "[" << DASH_GNUPLOT.toLatin1().data() << "] "
         << "[" << DASH_HELP.toLatin1().data() << "] "
         << "[<load_file1>] [<load_file2>] ..." << endl
         << "  " << DASH_CURVES.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Specifies an Engauge file with curve names for imported images" << endl
         << "  " << DASH_DEBUG.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Enables extra debug information" << endl
         << "  " << DASH_ERROR.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Specifies an error report fie as input" << endl
         << "  " << DASH_GNUPLOT.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Output diagnostic gnuplot input files for debugging" << endl
         << "  " << DASH_HELP.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Show this help information" << endl
         << "  " << QString ("<load file> ").leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "File to be imported or opened at startup" << endl;

    exit (0);
  }
}
