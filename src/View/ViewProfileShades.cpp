#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPen>
#include "ViewProfileParameters.h"
#include "ViewProfileShades.h"

const double OPACITY_SHADE = 0.1;
const double Z_VALUE_SHADE = 1.0;

ViewProfileShades::ViewProfileShades(QGraphicsScene *scene,
                                     QGraphicsItem *parent) :
  m_shadeLower (new QGraphicsRectItem(parent)),
  m_shadeUpper (new QGraphicsRectItem(parent)),
  m_xLower (VIEW_PROFILE_X_MIN),
  m_xUpper (VIEW_PROFILE_X_MAX)
{
  m_shadeLower->setOpacity (OPACITY_SHADE);
  m_shadeLower->setBrush (QBrush (qRgb (0.1, 0.1, 0.1)));
  m_shadeLower->setZValue (Z_VALUE_SHADE);
  m_shadeLower->setPen (QPen (Qt::NoPen));

  m_shadeUpper->setOpacity (OPACITY_SHADE);
  m_shadeUpper->setBrush (QBrush (qRgb (0.1, 0.1, 0.1)));
  m_shadeUpper->setZValue (Z_VALUE_SHADE);
  m_shadeUpper->setPen (QPen (Qt::NoPen));

  scene->addItem (m_shadeLower);
  scene->addItem (m_shadeUpper);

  updateGeometry();
}

void ViewProfileShades::slotDividerMoved (bool isLower,
                                          QPointF pos)
{
  if (isLower) {
    m_xLower = pos.x();
  } else {
    m_xUpper = pos.x();
  }

  updateGeometry();
}

void ViewProfileShades::updateGeometry()
{
  if (m_xLower <= m_xUpper) {

    if (!m_shadeUpper->isVisible ()) {
      m_shadeUpper->setVisible(true);
    }

    // Normal case - there is no overlap
    m_shadeLower->setRect (VIEW_PROFILE_X_MIN,
                           VIEW_PROFILE_Y_MIN,
                           m_xLower - VIEW_PROFILE_X_MIN,
                           VIEW_PROFILE_Y_MAX - VIEW_PROFILE_Y_MIN);
    m_shadeUpper->setRect (m_xUpper,
                           VIEW_PROFILE_Y_MIN,
                           VIEW_PROFILE_X_MAX - m_xUpper,
                           VIEW_PROFILE_Y_MAX);
  } else {

    // Rare case - there is overlap. Don't actually allow overlap or else the intersecting region is way too dark
    m_shadeLower->setRect (m_xUpper,
                           VIEW_PROFILE_Y_MIN,
                           m_xLower - m_xUpper,
                           VIEW_PROFILE_Y_MAX);
    m_shadeUpper->setVisible (false);
  }
}
