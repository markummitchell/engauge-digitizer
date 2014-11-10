#ifndef TEST_PLOT_CLASSIFIER_H
#define TEST_PLOT_CLASSIFIER_H

#include <QtTest/QtTest>

class TestPlotClassifier : public QObject
{
  Q_OBJECT;

 public:
  TestPlotClassifier();

 private slots:
  void slotNoAffine();

};

#endif // TEST_PLOT_CLASSIFIER_H
