#include "CurveIcon.h"
#include "EnumsToQt.h"
#include <QIcon>
#include <QImage>
#include <QPainter>

const double LENGTH = 32;

CurveIcon::CurveIcon(const PointStyle &pointStyle) :
  m_pointStyle (pointStyle)
{
}

QPixmap CurveIcon::pixmap () const
{
  // Use solid background since transparent never worked, even with an alpha channel
  const QBrush BRUSH (Qt::white);

  // Polygon that is sized for the main drawing window.
  QPolygonF polygonUnscaled = m_pointStyle.polygon();

  // Resize polygon to fit icon, by builiding a new scaled polygon from the unscaled polygon
  double xMinGot = polygonUnscaled.boundingRect().left();
  double xMaxGot = polygonUnscaled.boundingRect().right();
  double yMinGot = polygonUnscaled.boundingRect().top();
  double yMaxGot = polygonUnscaled.boundingRect().bottom();

  QPolygonF polygonScaled;
  for (int i = 0; i < polygonUnscaled.length(); i++) {
    QPointF pOld = polygonUnscaled.at(i);
    polygonScaled.append (QPointF ((LENGTH - 1) * (pOld.x() - xMinGot) / (xMaxGot - xMinGot),
                                   (LENGTH - 1) * (pOld.y() - yMinGot) / (yMaxGot - yMinGot)));
  }

  // Color
  QColor color = ColorPaletteToQColor(m_pointStyle.paletteColor());

  // Image for drawing
  QImage img (LENGTH, LENGTH, QImage::Format_RGB32);
  QPainter painter (&img);
  painter.fillRect (0, 0, LENGTH, LENGTH, BRUSH);
  painter.setPen (QPen (color));
  painter.drawPolygon (polygonScaled);

  // Create pixmap from image
  QPixmap pixmap = QPixmap::fromImage (img);

  return pixmap;
}
