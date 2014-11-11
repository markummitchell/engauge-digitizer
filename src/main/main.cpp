#include "Logger.h"
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  initializeLogging ("engauge",
                     "engauge.log");

  MainWindow w;
  w.show();

  return a.exec();
}
