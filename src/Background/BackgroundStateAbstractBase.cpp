#include "BackgroundStateAbstractBase.h"
#include "DataKey.h"
#include "EngaugeAssert.h"
#include "GraphicsItemType.h"
#include "GraphicsScene.h"
#include "Logger.h"

BackgroundStateAbstractBase::BackgroundStateAbstractBase(BackgroundStateContext &context,
                                                         GraphicsScene &scene) :
  m_context (context),
  m_scene (scene),
  m_imageItem (0)
{
  // Create an image but do not show it until the appropriate state is reached
  QPixmap dummy;
  m_imageItem = m_scene.addPixmap (dummy);
  m_imageItem->setVisible (false);
  m_imageItem->setData (DATA_KEY_IDENTIFIER, "view");
  m_imageItem->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_IMAGE);
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

QImage BackgroundStateAbstractBase::image () const
{
  return m_image;
}

QGraphicsPixmapItem &BackgroundStateAbstractBase::imageItem () const
{
  return *m_imageItem;
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
  m_imageItem->setVisible (visible);
}

void BackgroundStateAbstractBase::setProcessedPixmap (const QPixmap &pixmap)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateAbstractBase::setProcessedPixmap"
                              << " map=(" << pixmap.width() << "x" << pixmap.height() << ")";

  ENGAUGE_CHECK_PTR (m_imageItem);

  m_imageItem->setPixmap (pixmap);

  // Reset scene rectangle or else small image after large image will be off-center
  m_scene.setSceneRect (m_imageItem->boundingRect ());

  m_image = pixmap.toImage();
}
