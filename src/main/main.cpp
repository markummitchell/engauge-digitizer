#include "FilterParameter.h"
#include <iostream>
#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>

using namespace std;

// Prototypes
void parseCmdLine (int argc, char **argv, bool &isDebug);

// Functions
int main(int argc, char *argv[])
{
  qRegisterMetaType<FilterParameter> ("FilterParameter");

  QApplication a(argc, argv);

  bool isDebug;
  parseCmdLine (argc, argv, isDebug);

  initializeLogging ("engauge",
                     "engauge.log",
                     isDebug);

  MainWindow w;
  w.show();

  return a.exec();
}

void parseCmdLine (int argc, char **argv, bool &isDebug)
{
  bool showUsage = false;

  // Defaults
  isDebug = false;

  for (int i = 1; i < argc; i++) {

    if (strcmp (argv [i], "-debug") == 0) {
      isDebug = true;
    } else {
      showUsage = true;
    }
  }

  if (showUsage) {

    cerr << "Usage: engauge [-debug]" << endl
         << "  -debug     Enable extra debug information" << endl;

    exit (0);
  }
}
