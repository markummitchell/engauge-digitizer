#include "PlotClassifier.h"
#include <QPixmap>
#include "TestPlotClassifier.h"

QTEST_MAIN (TestPlotClassifier);

TestPlotClassifier::TestPlotClassifier ()
{
  QPixmap pixmap;

  pixmap.load ("../samples/gnuplot_x_y_lines_grid.png");
  PlotClassifier plotClassifier (pixmap);
}

void TestPlotClassifier::slotNoAffine ()
{
}
