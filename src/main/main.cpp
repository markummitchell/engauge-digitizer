#include "ColorFilterMode.h"
#include <iostream>
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <QProcessEnvironment>

using namespace std;

const QString CMD_DEBUG("debug");
const QString CMD_ERROR_REPORT("errorreport");
const QString CMD_FILE_CMD_SCRIPT("filecmdscript");
const QString CMD_GNUPLOT("gnuplot");
const QString CMD_HELP("help");
const QString CMD_REGRESSION("regression");
const QString DASH("-");
const QString DASH_DEBUG("-" + CMD_DEBUG);
const QString DASH_ERROR_REPORT("-" + CMD_ERROR_REPORT);
const QString DASH_FILE_CMD_SCRIPT("-" + CMD_FILE_CMD_SCRIPT);
const QString DASH_GNUPLOT("-" + CMD_GNUPLOT);
const QString DASH_HELP("-" + CMD_HELP);
const QString DASH_REGRESSION("-" + CMD_REGRESSION);
const QString ENGAUGE_LOG_FILE("engauge.log");

// Prototypes
bool checkFileExists(const QString &file);
QString engaugeLogFilename();
bool engaugeLogFilenameAttempt(const QString &path, QString &pathAndFile);
void parseCmdLine(int argc, char **argv, bool &isDebug,
                  QString &errorReportFile, QString &fileCmdScriptFile,
                  bool &isRegressionTest, bool &isGnuplot,
                  QStringList &loadStartupFiles);

// Functions
bool checkFileExists(const QString &file) {
  QFileInfo check(file);
  return check.exists() && check.isFile();
}

QString engaugeLogFilename() {
  QProcessEnvironment env;
  QString pathAndFile;

  // Make multiple attempts until a directory is found where the log file can be
  // written
  if (!engaugeLogFilenameAttempt(QCoreApplication::applicationDirPath(),
                                 pathAndFile)) {
    if (!engaugeLogFilenameAttempt(env.value("HOME"), pathAndFile)) {
      if (!engaugeLogFilenameAttempt(env.value("TEMP"), pathAndFile)) {
        pathAndFile = ENGAUGE_LOG_FILE; // Current directory will have to do
      }
    }
  }

  return pathAndFile;
}

bool engaugeLogFilenameAttempt(const QString &path, QString &pathAndFile) {
  bool success = false;

  // Test if file can be opened. Checking permissions on directory is unreliable
  // in Windows/OSX
  pathAndFile =
      QString("%1%2%3").arg(path).arg(QDir::separator()).arg(ENGAUGE_LOG_FILE);
  QFile file(pathAndFile);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    // Success
    file.close();
    success = true;
  }

  return success;
}

int main(int argc, char *argv[]) {
  qRegisterMetaType<ColorFilterMode>("ColorFilterMode");

  QApplication a(argc, argv);

  bool isDebug, isGnuplot, isRegressionTest;
  QString errorReportFile, fileCmdScriptFile;
  QStringList loadStartupFiles;
  parseCmdLine(argc, argv, isDebug, errorReportFile, fileCmdScriptFile,
               isRegressionTest, isGnuplot, loadStartupFiles);

  initializeLogging("engauge", engaugeLogFilename(), isDebug);
  LOG4CPP_INFO_S((*mainCat))
      << "main args=" << QApplication::arguments().join(" ").toLatin1().data();

  MainWindow w(errorReportFile, fileCmdScriptFile, isRegressionTest, isGnuplot,
               loadStartupFiles);
  w.show();

  return a.exec();
}

void parseCmdLine(int argc, char **argv, bool &isDebug,
                  QString &errorReportFile, QString &fileCmdScriptFile,
                  bool &isRegressionTest, bool &isGnuplot,
                  QStringList &loadStartupFiles) {
  const int COLUMN_WIDTH = 20;
  bool showUsage = false;

  // State
  bool nextIsErrorReportFile = false;
  bool nextIsFileCmdScript = false;

  // Defaults
  isDebug = false;
  errorReportFile = "";
  fileCmdScriptFile = "";
  isRegressionTest = false;
  isGnuplot = false;

  for (int i = 1; i < argc; i++) {

    if (nextIsErrorReportFile) {
      errorReportFile = argv[i];
      showUsage |= !checkFileExists(errorReportFile);
      nextIsErrorReportFile = false;
    } else if (nextIsFileCmdScript) {
      fileCmdScriptFile = argv[i];
      showUsage |= !checkFileExists(fileCmdScriptFile);
      nextIsFileCmdScript = false;
    } else if (strcmp(argv[i], DASH_DEBUG.toLatin1().data()) == 0) {
      isDebug = true;
    } else if (strcmp(argv[i], DASH_ERROR_REPORT.toLatin1().data()) == 0) {
      nextIsErrorReportFile = true;
    } else if (strcmp(argv[i], DASH_FILE_CMD_SCRIPT.toLatin1().data()) == 0) {
      nextIsFileCmdScript = true;
    } else if (strcmp(argv[i], DASH_GNUPLOT.toLatin1().data()) == 0) {
      isGnuplot = true;
    } else if (strcmp(argv[i], DASH_HELP.toLatin1().data()) == 0) {
      showUsage = true; // User requested help
    } else if (strcmp(argv[i], DASH_REGRESSION.toLatin1().data()) == 0) {
      isRegressionTest = true;
    } else if (strncmp(argv[i], DASH.toLatin1().data(), 1) == 0) {
      showUsage = true; // User entered an unrecognized token
    } else {
      // MainWindow will change current directory (which is often some obscure
      // application directory),
      // so relative paths must be changed in advance to absolute so the files
      // can still be found
      QString fileName = argv[i];
      QFileInfo fInfo(fileName);
      if (fInfo.isRelative()) {
        fileName = fInfo.absoluteFilePath();
      }
      loadStartupFiles << fileName; // Save file name
    }
  }

  if (showUsage || nextIsErrorReportFile) {

    cerr << "Usage: engauge "
         << "[" << DASH_DEBUG.toLatin1().data() << "] "
         << "[" << DASH_ERROR_REPORT.toLatin1().data() << " <file>] "
         << "[" << DASH_FILE_CMD_SCRIPT.toLatin1().data() << " <file> "
         << "[" << DASH_GNUPLOT.toLatin1().data() << "] "
         << "[" << DASH_HELP.toLatin1().data() << "] "
         << "[" << DASH_REGRESSION.toLatin1().data() << "] "
         << "[<load_file1>] [<load_file2>] ..." << endl
         << "  "
         << DASH_DEBUG.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data()
         << QObject::tr("Enables extra debug information. Used for debugging")
                .toLatin1()
                .data()
         << endl
         << "  "
         << DASH_ERROR_REPORT.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data()
         << QObject::tr("Specifies an error report file as input. Used for "
                        "debugging and testing")
                .toLatin1()
                .data()
         << endl
         << "  "
         << DASH_FILE_CMD_SCRIPT.leftJustified(COLUMN_WIDTH, ' ')
                .toLatin1()
                .data()
         << QObject::tr("Specifies a file command script file as input. Used "
                        "for debugging and testing")
                .toLatin1()
                .data()
         << endl
         << "  "
         << DASH_GNUPLOT.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data()
         << QObject::tr(
                "Output diagnostic gnuplot input files. Used for debugging")
                .toLatin1()
                .data()
         << endl
         << "  " << DASH_HELP.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data()
         << QObject::tr("Show this help information").toLatin1().data() << endl
         << "  "
         << DASH_REGRESSION.leftJustified(COLUMN_WIDTH, ' ').toLatin1().data()
         << QObject::tr("Executes the error report file or file command "
                        "script. Used for regression testing")
                .toLatin1()
                .data()
         << endl
         << "  "
         << QString("<load file> ")
                .leftJustified(COLUMN_WIDTH, ' ')
                .toLatin1()
                .data()
         << QObject::tr("File(s) to be imported or opened at startup")
                .toLatin1()
                .data()
         << endl;

    exit(0);
  }
}
