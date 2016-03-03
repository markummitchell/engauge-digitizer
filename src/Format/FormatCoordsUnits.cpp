#include "DocumentModelCoords.h"
#include "FormatCoordsUnits.h"
#include "FormatCoordsUnitsStrategyNonPolarTheta.h"
#include "FormatCoordsUnitsStrategyPolarTheta.h"
#include "Logger.h"
#include "MainWindowModel.h"
#include "Transformation.h"

const bool IS_X_THETA = true;
const bool IS_NOT_X_THETA = false;

FormatCoordsUnits::FormatCoordsUnits() {
  LOG4CPP_DEBUG_S((*mainCat)) << "FormatCoordsUnits::FormatCoordsUnits";
}

void FormatCoordsUnits::formattedToUnformatted(
    const QString &xThetaFormatted, const QString &yRadiusFormatted,
    const DocumentModelCoords &modelCoords,
    const MainWindowModel &mainWindowModel, double &xThetaUnformatted,
    double &yRadiusUnformatted) const {
  LOG4CPP_DEBUG_S((*mainCat)) << "FormatCoordsUnits::formattedToUnformatted";

  FormatCoordsUnitsStrategyNonPolarTheta formatNonPolarTheta;
  FormatCoordsUnitsStrategyPolarTheta formatPolarTheta;

  if (modelCoords.coordsType() == COORDS_TYPE_CARTESIAN) {

    xThetaUnformatted = formatNonPolarTheta.formattedToUnformatted(
        xThetaFormatted, mainWindowModel.locale(), modelCoords.coordUnitsX(),
        modelCoords.coordUnitsDate(), modelCoords.coordUnitsTime());
    yRadiusUnformatted = formatNonPolarTheta.formattedToUnformatted(
        yRadiusFormatted, mainWindowModel.locale(), modelCoords.coordUnitsY(),
        modelCoords.coordUnitsDate(), modelCoords.coordUnitsTime());

  } else {

    xThetaUnformatted = formatPolarTheta.formattedToUnformatted(
        xThetaFormatted, mainWindowModel.locale(),
        modelCoords.coordUnitsTheta());
    yRadiusUnformatted = formatNonPolarTheta.formattedToUnformatted(
        yRadiusFormatted, mainWindowModel.locale(),
        modelCoords.coordUnitsRadius(), modelCoords.coordUnitsDate(),
        modelCoords.coordUnitsTime());
  }
}

void FormatCoordsUnits::unformattedToFormatted(
    double xThetaUnformatted, double yRadiusUnformatted,
    const DocumentModelCoords &modelCoords,
    const MainWindowModel &mainWindowModel, QString &xThetaFormatted,
    QString &yRadiusFormatted, const Transformation &transformation) const {
  LOG4CPP_DEBUG_S((*mainCat)) << "FormatCoordsUnits::unformattedToFormatted";

  FormatCoordsUnitsStrategyNonPolarTheta formatNonPolarTheta;
  FormatCoordsUnitsStrategyPolarTheta formatPolarTheta;

  if (modelCoords.coordsType() == COORDS_TYPE_CARTESIAN) {

    xThetaFormatted = formatNonPolarTheta.unformattedToFormatted(
        xThetaUnformatted, mainWindowModel.locale(), modelCoords.coordUnitsX(),
        modelCoords.coordUnitsDate(), modelCoords.coordUnitsTime(), IS_X_THETA,
        transformation, yRadiusUnformatted);
    yRadiusFormatted = formatNonPolarTheta.unformattedToFormatted(
        yRadiusUnformatted, mainWindowModel.locale(), modelCoords.coordUnitsY(),
        modelCoords.coordUnitsDate(), modelCoords.coordUnitsTime(),
        IS_NOT_X_THETA, transformation, xThetaUnformatted);

  } else {

    xThetaFormatted = formatPolarTheta.unformattedToFormatted(
        xThetaUnformatted, mainWindowModel.locale(),
        modelCoords.coordUnitsTheta(), transformation, yRadiusUnformatted);
    yRadiusFormatted = formatNonPolarTheta.unformattedToFormatted(
        yRadiusUnformatted, mainWindowModel.locale(),
        modelCoords.coordUnitsRadius(), modelCoords.coordUnitsDate(),
        modelCoords.coordUnitsTime(), IS_NOT_X_THETA, transformation,
        xThetaUnformatted);
  }
}
