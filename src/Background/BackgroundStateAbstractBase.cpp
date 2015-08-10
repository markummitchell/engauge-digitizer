#include "BackgroundStateAbstractBase.h"
#include "DataKey.h"
#include "EngaugeAssert.h"
#include "GraphicsItemType.h"
#include "GraphicsScene.h"

BackgroundStateAbstractBase::BackgroundStateAbstractBase(BackgroundStateContext &context,
                                                         GraphicsScene &scene) :
  m_context (context),
  m_scene (scene),
  m_image (0)
{
  // Create an image but do not show it until the appropriate state is reached
  QPixmap dummy;
  m_image = m_scene.addPixmap (dummy);
  m_image->setVisible (false);
  m_image->setData (DATA_KEY_IDENTIFIER, "view");
  m_image->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_IMAGE);
}

BackgroundStateAbstractBase::~BackgroundStateAbstractBase()
{
}

BackgroundStateContext &BackgroundStateAbstractBase::context()
{
  return m_context;
}

const BackgroundStateContext &BackgroundStateAbstractBase::context() const
{
  return m_context;
}

QGraphicsPixmapItem &BackgroundStateAbstractBase::image ()
{
  return *m_image;
}

GraphicsScene &BackgroundStateAbstractBase::scene()
{
  return m_scene;
}

const GraphicsScene &BackgroundStateAbstractBase::scene() const
{
  return m_scene;
}

void BackgroundStateAbstractBase::setImageVisible (bool visible)
{
  m_image->setVisible (visible);
}

void BackgroundStateAbstractBase::setProcessedPixmap (const QPixmap &pixmap)
{
  ENGAUGE_CHECK_PTR (m_image);

  m_image->setPixmap (pixmap);
}
