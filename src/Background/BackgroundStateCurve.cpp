#include "BackgroundStateContext.h"
#include "BackgroundStateCurve.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include <QPixmap>

BackgroundStateCurve::BackgroundStateCurve(BackgroundStateContext &context,
                                           GraphicsScene &scene) :
  BackgroundStateAbstractBase(context,
                              scene)
{
}

void BackgroundStateCurve::begin()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::begin";
}

void BackgroundStateCurve::end()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::end";
}

void BackgroundStateCurve::setPixmap (const QPixmap &pixmap)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::setPixmap";


  // Empty background
  QPixmap pixmapNone (pixmap);
  pixmapNone.fill (Qt::white);
//  m_imageNone = m_scene->addPixmap (pixmapNone);
//  m_imageNone->setData (DATA_KEY_IDENTIFIER, "view");
//  m_imageNone->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_IMAGE);

  // Unfiltered original image
//  m_imageUnfiltered = m_scene->addPixmap (pixmap);
//  m_imageUnfiltered->setData (DATA_KEY_IDENTIFIER, "view");
//  m_imageUnfiltered->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_IMAGE);

  // Filtered image
//  ColorFilter filter;
//  QImage imageUnfiltered (pixmap.toImage ());
//  QImage imageFiltered (pixmap.width (),
//                        pixmap.height (),
//                        QImage::Format_RGB32);
//  QRgb rgbBackground = filter.marginColor (&imageUnfiltered);
//  filter.filterImage (imageUnfiltered,
//                      imageFiltered,
//                      cmdMediator().document().modelColorFilter().colorFilterMode(selectedGraphCurve ()),
//                      cmdMediator().document().modelColorFilter().low(selectedGraphCurve ()),
//                      cmdMediator().document().modelColorFilter().high(selectedGraphCurve ()),
//                      rgbBackground);
//
//  m_imageFiltered = m_scene->addPixmap (QPixmap::fromImage (imageFiltered));
//  m_imageFiltered->setData (DATA_KEY_IDENTIFIER, "view");
//  m_imageFiltered->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_IMAGE);
}

void BackgroundStateCurve::updateColorFilter (const DocumentModelColorFilter & /* colorFilter */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateCurve::updateColorFilter";
}
