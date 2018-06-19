/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorFilterMode.h"
#include "FittingCurveCoefficients.h"
#include <iostream>
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QObject>
#include <QProcessEnvironment>
#include <QStyleFactory>
#include "TranslatorContainer.h"
#include "ZoomFactor.h"

using namespace std;

const QString CMD_DEBUG ("debug");
const QString CMD_ERROR_REPORT ("errorreport");
const QString CMD_EXPORT_ONLY ("exportonly");
const QString CMD_FILE_CMD_SCRIPT ("filecmdscript");
const QString CMD_GNUPLOT ("gnuplot");
const QString CMD_HELP ("help");
const QString CMD_REGRESSION ("regression");
const QString CMD_RESET ("reset");
const QString CMD_STYLES ("styles"); // Not to be confused with -style option that qt handles
const QString DASH ("-");
const QString DASH_DEBUG ("-" + CMD_DEBUG);
const QString DASH_ERROR_REPORT ("-" + CMD_ERROR_REPORT);
const QString DASH_EXPORT_ONLY ("-" + CMD_EXPORT_ONLY);
const QString DASH_FILE_CMD_SCRIPT ("-" + CMD_FILE_CMD_SCRIPT);
const QString DASH_GNUPLOT ("-" + CMD_GNUPLOT);
const QString DASH_HELP ("-" + CMD_HELP);
const QString DASH_REGRESSION ("-" + CMD_REGRESSION);
const QString DASH_RESET ("-" + CMD_RESET);
const QString DASH_STYLES ("-" + CMD_STYLES);
const QString ENGAUGE_LOG_FILE (".engauge.log");

// Prototypes
bool checkFileExists (const QString &file);
QString engaugeLogFilename ();
bool engaugeLogFilenameAttempt (const QString &path,
                                QString &pathAndFile);
void parseCmdLine (int argc,
                   char **argv,
                   bool &isDebug,
                   bool &isReset,
                   QString &errorReportFile,
                   QString &fileCmdScriptFile,
                   bool &isErrorReportRegressionTest,
                   bool &isGnuplot,
                   bool &isExportOnly,
                   QStringList &loadStartupFiles);
void showStylesAndExit ();

// Functions
bool checkFileExists (const QString &file)
{
  QFileInfo check (file);
  return check.exists() && check.isFile();
}

QString engaugeLogFilename()
{
  QString pathAndFile; // Return empty value in OSX which is unused

#if !defined(OSX_RELEASE) && !defined(WIN_RELEASE) && !defined(APPIMAGE_RELEASE)
  QProcessEnvironment env;

  // Make multiple attempts until a directory is found where the log file can be written
  if (!engaugeLogFilenameAttempt (QCoreApplication::applicationDirPath(), pathAndFile)) {
    if (!engaugeLogFilenameAttempt (env.value ("HOME"), pathAndFile)) {
      if (!engaugeLogFilenameAttempt (env.value ("TEMP"), pathAndFile)) {
        pathAndFile = ENGAUGE_LOG_FILE; // Current directory will have to do
      }
    }
  }
#endif

  return pathAndFile;
}

bool engaugeLogFilenameAttempt (const QString &path,
                                QString &pathAndFile)
{
  bool success = false;

  // Test if file can be opened. Checking permissions on directory is unreliable in Windows/OSX
  pathAndFile = QString ("%1%2%3")
                         .arg (path)
                         .arg (QDir::separator())
                         .arg (ENGAUGE_LOG_FILE);
  QFile file (pathAndFile);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    // Success
    file.close();
    file.remove(); // Cleanup
    success = true;
  }

  return success;
}

int main(int argc, char *argv[])
{
  qRegisterMetaType<ColorFilterMode> ("ColorFilterMode");
  qRegisterMetaType<FittingCurveCoefficients> ("FilterCurveCoefficients");
  qRegisterMetaType<ZoomFactor> ("ZoomFactor");

  QApplication app(argc, argv);

  // Translations
  TranslatorContainer translatorContainer (app); // Must exist until execution terminates

  // Command line
  bool isDebug, isReset, isGnuplot, isErrorReportRegressionTest, isExportOnly;
  QString errorReportFile, fileCmdScriptFile;
  QStringList loadStartupFiles;
  parseCmdLine (argc,
                argv,
                isDebug,
                isReset,
                errorReportFile,
                fileCmdScriptFile,
                isErrorReportRegressionTest,
                isGnuplot,
                isExportOnly,
                loadStartupFiles);

  // Logging
  initializeLogging ("engauge",
                     engaugeLogFilename(),
                     isDebug);
  LOG4CPP_INFO_S ((*mainCat)) << "main args=" << QApplication::arguments().join (" ").toLatin1().data();

  // Create and show main window
  MainWindow w (errorReportFile,
                fileCmdScriptFile,
                isErrorReportRegressionTest,
                isGnuplot,
                isReset,
                isExportOnly,
                loadStartupFiles);
  w.show();

  // Event loop
  return app.exec();
}

void parseCmdLine (int argc,
                   char **argv,
                   bool &isDebug,
                   bool &isReset,
                   QString &errorReportFile,
                   QString &fileCmdScriptFile,
                   bool &isErrorReportRegressionTest,
                   bool &isGnuplot,
                   bool &isExportOnly,
                   QStringList &loadStartupFiles)
{
  bool showUsage = false;

  // State
  bool nextIsErrorReportFile = false;
  bool nextIsFileCmdScript = false;

  // Defaults
  isDebug = false;
  isReset = false;
  errorReportFile = "";
  fileCmdScriptFile = "";
  isErrorReportRegressionTest = false;
  isGnuplot = false;
  isExportOnly = false;

  for (int i = 1; i < argc; i++) {

    if (nextIsErrorReportFile) {
      errorReportFile = argv [i];
      showUsage |= !checkFileExists (errorReportFile);
      nextIsErrorReportFile = false;
    } else if (nextIsFileCmdScript) {
      fileCmdScriptFile = argv [i];
      showUsage |= !checkFileExists (fileCmdScriptFile);
      nextIsFileCmdScript = false;
    } else if (strcmp (argv [i], DASH_DEBUG.toLatin1().data()) == 0) {
      isDebug = true;
    } else if (strcmp (argv [i], DASH_ERROR_REPORT.toLatin1().data()) == 0) {
      nextIsErrorReportFile = true;
    } else if (strcmp (argv [i], DASH_EXPORT_ONLY.toLatin1().data()) == 0) {
      isExportOnly = true;
    } else if (strcmp (argv [i], DASH_FILE_CMD_SCRIPT.toLatin1().data()) == 0) {
      nextIsFileCmdScript = true;
    } else if (strcmp (argv [i], DASH_GNUPLOT.toLatin1().data()) == 0) {
      isGnuplot = true;
    } else if (strcmp (argv [i], DASH_HELP.toLatin1().data()) == 0) {
      showUsage = true; // User requested help
    } else if (strcmp (argv [i], DASH_REGRESSION.toLatin1().data()) == 0) {
      isErrorReportRegressionTest = true;
    } else if (strcmp (argv [i], DASH_RESET.toLatin1().data()) == 0) {
      isReset = true;
    } else if (strcmp (argv [i], DASH_STYLES.toLatin1().data()) == 0) {
      showStylesAndExit ();
    } else if (strncmp (argv [i], DASH.toLatin1().data(), 1) == 0) {
      showUsage = true; // User entered an unrecognized token
    } else {
      // MainWindow will change current directory (which is often some obscure application directory),
      // so relative paths must be changed in advance to absolute so the files can still be found
      QString fileName = argv [i];
      QFileInfo fInfo (fileName);
      if (fInfo.isRelative()) {
        fileName = fInfo.absoluteFilePath();
      }
      loadStartupFiles << fileName; // Save file name
    }
  }

  // Sanity checks
  if (isExportOnly && (!errorReportFile.isEmpty() ||
                       !fileCmdScriptFile.isEmpty() ||
                       loadStartupFiles.size() != 1)) {
    QString msg;
    QTextStream str (&msg);
    str << DASH_EXPORT_ONLY.toLatin1().data() << " " << QObject::tr (" is used only with one document file specified");
    QMessageBox::critical (0,
                           QObject::tr ("Engauge Digitizer"),
                           msg);
    exit (0);
  }

  // Usage
  if (showUsage || nextIsErrorReportFile) {

    QString msg;
    QTextStream str (&msg);
    str << "<html>Usage: engauge "
        << "[" << DASH_DEBUG.toLatin1().data() << "] "
        << "[" << DASH_ERROR_REPORT.toLatin1().data() << " <file>] "
        << "[" << DASH_EXPORT_ONLY.toLatin1().data() << "] "
        << "[" << DASH_FILE_CMD_SCRIPT.toLatin1().data() << " <file> "
        << "[" << DASH_GNUPLOT.toLatin1().data() << "] "
        << "[" << DASH_HELP.toLatin1().data() << "] "
        << "[" << DASH_REGRESSION.toLatin1().data() << "] "
        << "[" << DASH_RESET.toLatin1().data () << "] "
        << "[" << DASH_STYLES.toLatin1().data () << "] "
        << "[&lt;load_file1&gt;] [&lt;load_file2&gt;] ..." << endl
        << "<table>"
        << "<tr>"
        << "<td>" << DASH_DEBUG.toLatin1().data() << "</td>"
        << "<td>" << QObject::tr ("Enables extra debug information. Used for debugging").toLatin1().data() << "</td>"
        << "</tr>"
        << "<tr>"
        << "<td>" << DASH_ERROR_REPORT.toLatin1().data() << "</td>"
        << "<td>" << QObject::tr ("Specifies an error report file as input. Used for debugging and testing").toLatin1().data() << "</td>"
        << "</tr>"
        << "<tr>"
        << "<td>" << DASH_EXPORT_ONLY.toLatin1().data() << "</td>"
        << "<td>" << QObject::tr ("Export the loaded startup file, which must have all axis points defined, then stop").toLatin1().data() << "</td>"
        << "</tr>"
        << "<tr>"
        << "<td>" << DASH_FILE_CMD_SCRIPT.toLatin1().data() << "</td>"
        << "<td>" << QObject::tr ("Specifies a file command script file as input. Used for debugging and testing").toLatin1().data() << "</td>"
        << "</tr>"
        << "<tr>"
        << "<td>" << DASH_GNUPLOT.toLatin1().data() << "</td>"
        << "<td>" << QObject::tr ("Output diagnostic gnuplot input files. Used for debugging").toLatin1().data() << "</td>"
        << "</tr>"
        << "<tr>"
        << "<td>" << DASH_HELP.toLatin1().data() << "</td>"
        << "<td>" << QObject::tr ("Show this help information").toLatin1().data() << "</td>"
        << "</tr>"
        << "<tr>"
        << "<td>" << DASH_REGRESSION.toLatin1().data() << "</td>"
        << "<td>" << QObject::tr ("Executes the error report file or file command script. Used for regression testing").toLatin1().data() << "</td>"
        << "</tr>"
        << "<tr>"
        << "<td>" << DASH_RESET.toLatin1().data() << "</td>"
        << "<td>" << QObject::tr ("Removes all stored settings, including window positions. Used when windows start up offscreen").toLatin1().data() << "</td>"
        << "</tr>"
        << "<tr>"
        << "<td>" << DASH_STYLES.toLatin1().data() << "</td>"
        << "<td>" << QObject::tr ("Show a list of available styles that can be used with the -style command").toLatin1().data() << "</td>"
        << "</tr>"
        << "<tr>"
        << "<td>" << QString ("&lt;load file&gt; ").toLatin1().data() << "</td>"
        << "<td>" << QObject::tr ("File(s) to be imported or opened at startup").toLatin1().data() << "</td>"
        << "</tr>"
        << "</table></html>";

    // Show error in QMessageBox instead of cerr since console output is disabled in Microsoft Windows
    QMessageBox::critical (0,
                           QObject::tr ("Engauge Digitizer"),
                           msg);
    exit (0);
  }
}

void showStylesAndExit ()
{
  cout << "Available styles: " << QStyleFactory::keys ().join (", ").toLatin1().data() << endl;
  exit (0);
}
