#include "DocumentModelCoords.h"
#include "FormatCoordsUnits.h"
#include "FormatCoordsUnitsNonPolarTheta.h"
#include "FormatCoordsUnitsPolarTheta.h"
#include "Logger.h"

const bool IS_X_THETA = true;
const bool IS_NOT_X_THETA = false;

FormatCoordsUnits::FormatCoordsUnits()
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatCoordsUnits::FormatCoordsUnits";
}

void FormatCoordsUnits::formattedToUnformatted (const QString &xThetaFormatted,
                                                const QString &yRadiusFormatted,
                                                const DocumentModelCoords &modelCoords,
                                                double &xThetaUnformatted,
                                                double &yRadiusUnformatted) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatCoordsUnits::formattedToUnformatted";

  FormatCoordsUnitsNonPolarTheta formatNonPolarTheta;
  FormatCoordsUnitsPolarTheta formatPolarTheta;

  if (modelCoords.coordsType() == COORDS_TYPE_CARTESIAN) {

    xThetaUnformatted = formatNonPolarTheta.formattedToUnformatted (xThetaFormatted,
                                                                    modelCoords.coordUnitsX(),
                                                                    modelCoords.coordUnitsDate(),
                                                                    modelCoords.coordUnitsTime());
    yRadiusUnformatted = formatNonPolarTheta.formattedToUnformatted (yRadiusFormatted,
                                                                     modelCoords.coordUnitsY(),
                                                                     modelCoords.coordUnitsDate(),
                                                                     modelCoords.coordUnitsTime());

  } else {

    xThetaUnformatted = formatPolarTheta.formattedToUnformatted (xThetaFormatted,
                                                                 modelCoords.coordUnitsTheta());
    yRadiusUnformatted = formatNonPolarTheta.formattedToUnformatted (yRadiusFormatted,
                                                                     modelCoords.coordUnitsRadius(),
                                                                     modelCoords.coordUnitsDate(),
                                                                     modelCoords.coordUnitsTime());

  }
}

void FormatCoordsUnits::unformattedToFormatted (double xThetaUnformatted,
                                                double yRadiusUnformatted,
                                                const DocumentModelCoords &modelCoords,
                                                QString &xThetaFormatted,
                                                QString &yRadiusFormatted,
                                                int precisionDigitsForRawNumber) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatCoordsUnits::unformattedToFormatted";

  FormatCoordsUnitsNonPolarTheta formatNonPolarTheta;
  FormatCoordsUnitsPolarTheta formatPolarTheta;

  if (modelCoords.coordsType() == COORDS_TYPE_CARTESIAN) {

    xThetaFormatted = formatNonPolarTheta.unformattedToFormatted (xThetaUnformatted,
                                                                  modelCoords.coordUnitsX(),
                                                                  modelCoords.coordUnitsDate(),
                                                                  modelCoords.coordUnitsTime(),
                                                                  IS_X_THETA,
                                                                  precisionDigitsForRawNumber);
    yRadiusFormatted = formatNonPolarTheta.unformattedToFormatted (yRadiusUnformatted,
                                                                   modelCoords.coordUnitsY(),
                                                                   modelCoords.coordUnitsDate(),
                                                                   modelCoords.coordUnitsTime(),
                                                                   IS_NOT_X_THETA,
                                                                   precisionDigitsForRawNumber);
    
  } else {
    
    xThetaFormatted = formatPolarTheta.unformattedToFormatted (xThetaUnformatted,
                                                               modelCoords.coordUnitsTheta(),
                                                               precisionDigitsForRawNumber);
    yRadiusFormatted = formatNonPolarTheta.unformattedToFormatted (yRadiusUnformatted,
                                                                   modelCoords.coordUnitsRadius(),
                                                                   modelCoords.coordUnitsDate(),
                                                                   modelCoords.coordUnitsTime(),
                                                                   IS_NOT_X_THETA,
                                                                   precisionDigitsForRawNumber);
  }
}
