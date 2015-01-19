#include <math.h>
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QPixmap>

void drawPoint (QPainter *paint,
                const QColor &color,
                double x,
                double y,
                double axisLinewidth,
                int size)
{
  QPen penOld = paint->pen();
  QBrush brushOld = paint->brush();

  double radius = axisLinewidth * 3.0;

  if (size < 32) {
    // Hack - at the start, line is too thick vertically so remove some pixels
    if (x == 4) {
      paint->setPen (Qt::white);
      paint->drawLine (QPointF (3, 11),
                      QPointF (4, 11));

      paint->setPen (color);
      paint->setBrush (Qt::NoBrush);

      paint->drawLine (QPointF (x, y),
                      QPointF (x + 2, y));
      paint->drawLine (QPointF (x + 1, y - 1),
                      QPointF (x + 1, y + 1));
    } else {
      paint->setPen (color);
      paint->setBrush (Qt::NoBrush);

      paint->drawLine (QPointF (x - 1, y),
                      QPointF (x + 1, y));
      paint->drawLine (QPointF (x, y - 1),
                      QPointF (x, y + 1));
    }
  } else {

    paint->setPen (Qt::NoPen);
    paint->setBrush (color);

    QPolygon polygon;
    polygon.append (QPoint (x + radius, y));
    polygon.append (QPoint (x, y - radius));
    polygon.append (QPoint (x - radius, y));
    polygon.append (QPoint (x, y + radius));
    polygon.append (QPoint (x + radius, y));
    paint->drawPolygon(polygon);
  }

  paint->setPen (penOld);
  paint->setBrush (brushOld);
}


int main(int , char **)
{
  for (int size = 16; size <= 256; size *= 2) {

    int numAxisPoints = (size > 32 ? 5 : 4);
    int numCurvePoints = (size > 32 ? 4 : 3);
    double axisLinewidth = pow ((double) size, 0.8) / 16.0;
    double curveLinewidth = 1.5 * pow ((double) size / 16.0, 0.5);
    double margin = size / 8.0;
    double ticHalfHeight = size * 4.0 / 200.0;
    if (size == 32) ticHalfHeight *= 2; // Hack
    double pixelsPerCurvePoint = fmax (1, size / 32.0);

    double xCurveMin = 2 * margin;
    double xCurveMax = size - margin;
    double yCurveMin = 2 * margin;
    double yCurveMax = size - margin;
    double xAxisMin = margin;
    double xAxisMax = size - margin;
    double yAxisMin = margin;
    double yAxisMax = size - margin;
    double xOffsetMax = xCurveMax - xCurveMin;
    double yOffsetMax = yCurveMax - yCurveMin;

    QImage *img = new QImage (size, size, QImage::Format_ARGB32_Premultiplied);
    img->fill (QColor (Qt::white));

    QPainter *paint = new QPainter (img);
    paint->begin(img);
    paint->setPen (QPen (QBrush (Qt::black), axisLinewidth));

    // X and y axes
    paint->drawLine (QPointF (margin, size - margin),
                    QPointF (size - margin, size - margin));
    paint->drawLine (QPointF (margin, size - margin),
                    QPointF (margin, margin));

    paint->setRenderHint (QPainter::Antialiasing, true);

    // Quadratic line from (2*margin,size-2*margin) to (size-margin,margin)
    QPolygonF curve;
    int numCurveSteps = (xCurveMax - xCurveMin) / pixelsPerCurvePoint;
    for (int ic = 0; ic < numCurveSteps; ic++) {

      double x = xCurveMin + ic * pixelsPerCurvePoint;

      double xOffset = x - xCurveMin;
      double yOffset = yOffsetMax * xOffset * xOffset / (xOffsetMax * xOffsetMax);
      double y = size - 2 * margin - yOffset;

      curve.append (QPointF (x, y));
    }
    QPen penOld = paint->pen();
    paint->setPen(QPen(QBrush (Qt::black), curveLinewidth));
    paint->drawPolyline (curve);
    paint->setPen(penOld);

    paint->setRenderHint (QPainter::Antialiasing, false);

    // Points along quadratic line. They are stretched evenly along the arc, rather than evenly
    // along the x direction, so it looks nicer
    double xDeltaCurve = (xCurveMax - xCurveMin) / (numCurvePoints - 1.0);
    for (int ip = 0; ip < numCurvePoints; ip++) {
      // Map from 0 through numAxisPoints-1 to 0 through numAxisPoints-1
      double xBefore = 1.0 + (2.71828 - 1.0) * ip / (double) (numCurvePoints - 1.0); // 1 to 2.71828
      double xAfter = log (xBefore); // 0 to 1
      double ipLog = (numCurvePoints - 1.0) * xAfter;

      double x = xCurveMin + ipLog * xDeltaCurve;

      double xOffset = x - xCurveMin;
      double yOffset = yOffsetMax * xOffset * xOffset / (xOffsetMax * xOffsetMax);
      double y = size - 2 * margin - yOffset;

      drawPoint (paint, QColor (Qt::green), x, y, axisLinewidth, size);
    }

    // X tics
    double xDelta = (xAxisMax - xAxisMin) / (numAxisPoints - 1.0);
    for (int ix = 0; ix < numAxisPoints; ix++) {
      double x = xAxisMin + ix * xDelta;
      double yCenter = size - margin;
      paint->drawLine (QPointF (x, yCenter - ticHalfHeight),
                      QPointF (x, yCenter + ticHalfHeight));
    }

    // Y tics
    double yDelta = (yAxisMax - yAxisMin) / (numAxisPoints- 1.0);
    for (int iy = 0; iy < numAxisPoints; iy++) {
      double xCenter = margin;
      double y = yAxisMin + iy * yDelta;
      paint->drawLine (QPointF (xCenter - ticHalfHeight, y),
                      QPointF (xCenter + ticHalfHeight, y));
    }

    drawPoint (paint, QColor (Qt::red), xAxisMin, size - margin, axisLinewidth, size);
    drawPoint (paint, QColor (Qt::red), xAxisMin, margin, axisLinewidth, size);
    drawPoint (paint, QColor (Qt::red), xAxisMax, size - margin, axisLinewidth, size);

    paint->end();

    // Save file
    QImage alpha = img->alphaChannel();
    for (int x = 0; x < img->width(); x++) {
      for (int y = 0; y < img->height(); y++) {
        QRgb pixel = img->pixel(x, y);
        if (qRed(pixel) == 255 && qGreen(pixel) == 255 && qBlue(pixel)) {
          alpha.setPixel(x, y, 255);
        }
      }
    }
    img->setAlphaChannel(alpha);
    QString filename = QString ("bannerapp_%1.xpm").arg (size);
    img->save (filename);

    delete img;
  }
}
