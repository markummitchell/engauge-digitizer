#include "BackgroundStateAbstractBase.h"
#include "GraphicsScene.h"

BackgroundStateAbstractBase::BackgroundStateAbstractBase(BackgroundStateContext &context,
                                                         GraphicsScene &scene) :
  m_context (context),
  m_scene (scene)
{
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
  return m_image;
}

GraphicsScene &BackgroundStateAbstractBase::scene()
{
  return m_scene;
}

const GraphicsScene &BackgroundStateAbstractBase::scene() const
{
  return m_scene;
}
