#include "ColorFilterMode.h"
#include <iostream>
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>

using namespace std;

const QString CMD_DEBUG ("debug");
const QString CMD_ERROR ("error");
const QString CMD_GNUPLOT ("gnuplot");
const QString CMD_HELP ("help");
const QString DASH_DEBUG ("-" + CMD_DEBUG);
const QString DASH_ERROR ("-" + CMD_ERROR);
const QString DASH_GNUPLOT ("-" + CMD_GNUPLOT);
const QString DASH_HELP ("-" + CMD_HELP);

// Prototypes
void parseCmdLine (int argc, char **argv, bool &isDebug, QString &errorReportFile, bool &isGnuplot);

// Functions
int main(int argc, char *argv[])
{
  qRegisterMetaType<ColorFilterMode> ("ColorFilterMode");

  QApplication a(argc, argv);

  bool isDebug, isGnuplot;
  QString errorReportFile;
  parseCmdLine (argc,
                argv,
                isDebug,
                errorReportFile,
                isGnuplot);

  initializeLogging ("engauge",
                     "engauge.log",
                     isDebug);

  MainWindow w (errorReportFile,
                isGnuplot);
  w.show();

  return a.exec();
}

void parseCmdLine (int argc,
                   char **argv,
                   bool &isDebug,
                   QString &errorReportFile,
                   bool &isGnuplot)
{
  const int COLUMN_WIDTH = 20;
  bool showUsage = false;

  // State
  bool nextIsErrorReportFile = false;

  // Defaults
  isDebug = false;
  errorReportFile = "";
  isGnuplot = false;

  for (int i = 1; i < argc; i++) {

    if (nextIsErrorReportFile) {
      errorReportFile = argv [i];
      nextIsErrorReportFile = false;
    } else if (strcmp (argv [i], DASH_DEBUG.toLatin1().data()) == 0) {
      isDebug = true;
    } else if (strcmp (argv [i], DASH_ERROR.toLatin1().data()) == 0) {
      nextIsErrorReportFile = true;
    } else if (strcmp (argv [i], DASH_GNUPLOT.toLatin1().data()) == 0) {
      isGnuplot = true;
    } else {
      showUsage = true;
    }
  }

  if (showUsage || nextIsErrorReportFile) {

    cerr << "Usage: engauge "
         << "[" << DASH_DEBUG.toLatin1().data() << "] "
         << "[" << DASH_ERROR.toLatin1().data() << " <file>] "
         << "[" << DASH_GNUPLOT.toLatin1().data() << "]" << endl
         << "  " << DASH_DEBUG.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Enables extra debug information" << endl
         << "  " << DASH_ERROR.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Specifies an error report fie as input" << endl
         << "  " << DASH_GNUPLOT.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data() << "Output diagnostic gnuplot input files for debugging" << endl;

    exit (0);
  }
}
