#include "EnumsToQt.h"
#include "Logger.h"
#include <QPainter>
#include "ViewPointStyle.h"

// Use solid background since transparent never worked, even with an alpha channel
const QColor COLOR_FOR_BRUSH (Qt::white);

ViewPointStyle::ViewPointStyle(QWidget *parent) :
  QLabel (parent)
{
  // Note the size is set externally by the layout engine
}

QPixmap ViewPointStyle::pixmap (const PointStyle &pointStyle) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ViewPointStyle::pixmap";

  // Polygon that is sized for the main drawing window.
  QPolygonF polygonUnscaled = pointStyle.polygon();

  // Resize polygon to fit icon, by builiding a new scaled polygon from the unscaled polygon
  double xMinGot = polygonUnscaled.boundingRect().left();
  double xMaxGot = polygonUnscaled.boundingRect().right();
  double yMinGot = polygonUnscaled.boundingRect().top();
  double yMaxGot = polygonUnscaled.boundingRect().bottom();

  QPolygonF polygonScaled;
  for (int i = 0; i < polygonUnscaled.length(); i++) {
    QPointF pOld = polygonUnscaled.at(i);
    polygonScaled.append (QPointF ((width () - 1) * (pOld.x() - xMinGot) / (xMaxGot - xMinGot),
                                   (height () - 1) * (pOld.y() - yMinGot) / (yMaxGot - yMinGot)));
  }

  // Color
  QColor color = ColorPaletteToQColor(pointStyle.paletteColor());

  // Image for drawing
  QImage img (width (),
              height (),
              QImage::Format_RGB32);
  QPainter painter (&img);
  painter.fillRect (0,
                    0,
                    width (),
                    height (),
                    QBrush (COLOR_FOR_BRUSH));
  painter.setPen (QPen (color));
  painter.drawPolygon (polygonScaled);

  // Create pixmap from image
  QPixmap pixmap = QPixmap::fromImage (img);

  return pixmap;
}

void ViewPointStyle::setPointStyle (const PointStyle &pointStyle)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ViewPointStyle::setPointStyle";

  setPixmap (pixmap (pointStyle));
}

void ViewPointStyle::unsetPointStyle ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "ViewPointStyle::unsetPointStyle";

  QPixmap pEmpty (width (),
                  height ());
  pEmpty.fill (COLOR_FOR_BRUSH);

  setPixmap (pEmpty);
}
