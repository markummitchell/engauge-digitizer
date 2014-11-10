#ifndef VIEW_PROFILE_SHADES_H
#define VIEW_PROFILE_SHADES_H

#include <QObject>
#include <QPointF>

class QGraphicsItem;
class QGraphicsRectItem;
class QGraphicsScene;

/// Shades regions that ranges from a ViewProfileDivider to the other ViewProfileDivider or a side.
/// These are handled as a single unit since they are sometimes not independent - when the two shades
/// overlap we do not want the intersecting region to look extra dark (confusing and ugly).
class ViewProfileShades : public QObject
{
  Q_OBJECT;

public:
  /// Single constructor.
  explicit ViewProfileShades(QGraphicsScene *scene,
                             QGraphicsItem *parent = 0);

signals:

public slots:
  /// Update shades after a ViewProfileDivider has moved.
  void slotDividerMoved (bool isLower, QPointF pos);

private:

  void updateGeometry();

  QGraphicsRectItem *m_shadeLower;
  QGraphicsRectItem *m_shadeUpper;

  int m_xLower;
  int m_xUpper;
};

#endif // VIEW_PROFILE_SHADES_H
