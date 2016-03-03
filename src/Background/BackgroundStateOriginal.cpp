#include "BackgroundStateContext.h"
#include "BackgroundStateOriginal.h"
#include "DocumentModelColorFilter.h"
#include "DocumentModelGridRemoval.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include <QPixmap>
#include "Transformation.h"

BackgroundStateOriginal::BackgroundStateOriginal(
    BackgroundStateContext &context, GraphicsScene &scene)
    : BackgroundStateAbstractBase(context, scene) {}

void BackgroundStateOriginal::begin() {
  LOG4CPP_INFO_S((*mainCat)) << "BackgroundStateOriginal::begin";

  setImageVisible(true);
}

void BackgroundStateOriginal::end() {
  LOG4CPP_INFO_S((*mainCat)) << "BackgroundStateOriginal::end";

  setImageVisible(false);
}

void BackgroundStateOriginal::fitInView(GraphicsView &view) {
  LOG4CPP_INFO_S((*mainCat)) << "BackgroundStateOriginal::fitInView";

  view.fitInView(imageItem().boundingRect());
}

void BackgroundStateOriginal::setCurveSelected(
    const Transformation & /* transformation */,
    const DocumentModelGridRemoval & /* modelGridRemoval */,
    const DocumentModelColorFilter & /* modelColorFilter */,
    const QString & /* curveSelected */) {
  LOG4CPP_INFO_S((*mainCat)) << "BackgroundStateOriginal::setCurveSelected";
}

void BackgroundStateOriginal::setPixmap(
    const Transformation & /* transformation */,
    const DocumentModelGridRemoval & /* modelGridRemoval */,
    const DocumentModelColorFilter & /* modelColorFilter */,
    const QPixmap &pixmapOriginal) {
  LOG4CPP_INFO_S((*mainCat)) << "BackgroundStateOriginal::setPixmap";

  // Unfiltered original image
  setProcessedPixmap(pixmapOriginal);
}

QString BackgroundStateOriginal::state() const {
  return "BackgroundStateOriginal";
}

void BackgroundStateOriginal::updateColorFilter(
    const Transformation & /* transformation */,
    const DocumentModelGridRemoval & /* modelGridRemoval */,
    const DocumentModelColorFilter & /* modelColorFilter */) {
  LOG4CPP_INFO_S((*mainCat)) << "BackgroundStateOriginal::updateColorFilter";
}
