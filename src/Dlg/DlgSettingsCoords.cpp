/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackBoundingRects.h"
#include "CmdMediator.h"
#include "CmdSettingsCoords.h"
#include "CoordUnitsDate.h"
#include "CoordUnitsTime.h"
#include "DlgSettingsCoords.h"
#include "DlgValidatorAbstract.h"
#include "DlgValidatorFactory.h"
#include "DocumentModelCoords.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <math.h>
#include <QComboBox>
#include <QDebug>
#include <QDoubleValidator>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QGroupBox>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
#include <QRadioButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "Transformation.h"
#include "ViewPreview.h"

const QString OVERRIDDEN_VALUE(""); // Values are overridden in updateControls

const int COLUMN_0 = 0;
const int COLUMN_1 = 1;

const int STEPS_PER_CYCLE = 4; // Repeat STEPS_PER_CYLE-1 unhighlighted steps plus 1 highlighted step in each cycle
const int STEPS_CYCLE_COUNT = 4; // Repeat one highlighted step + STEPS_UNHIGHLIGHTED_PER_HIGHLIGHTED steps this many times
const int NUM_COORD_STEPS = 1 + STEPS_PER_CYCLE * STEPS_CYCLE_COUNT;

const int MAX_WIDTH_EDIT_ORIGIN_RADIUS = 140;

const int CARTESIAN_COORD_MAX = 100;
const int CARTESIAN_COORD_MIN = -100;
const double CARTESIAN_COORD_STEP = (CARTESIAN_COORD_MAX - CARTESIAN_COORD_MIN) / (NUM_COORD_STEPS - 1.0);

const int POLAR_RADIUS = CARTESIAN_COORD_MAX;
const double POLAR_STEP = POLAR_RADIUS / (NUM_COORD_STEPS - 1.0);

const int POLAR_THETA_MAX = 360;
const int POLAR_THETA_MIN = 0;
const double POLAR_THETA_STEP = (POLAR_THETA_MAX - POLAR_THETA_MIN) / (NUM_COORD_STEPS - 1.0);

const double XCENTER = (CARTESIAN_COORD_MIN + CARTESIAN_COORD_MAX) / 2.0;
const double YCENTER = (CARTESIAN_COORD_MIN + CARTESIAN_COORD_MAX) / 2.0;

const double LINE_WIDTH_THIN = 0.0;
const double LINE_WIDTH_THICK = 2.0;

const double PI = 3.1415926535;
const double DEG_2_RAD = PI / 180.0;

const int FONT_SIZE = 6;

const double POWER_FOR_LOG = 10.0; // Need a larger power (certainly more than e) to make log gradient obvious

const int MINIMUM_DIALOG_WIDTH_COORDS = 800;
const int MINIMUM_HEIGHT = 540;

DlgSettingsCoords::DlgSettingsCoords(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Coordinates"),
                           "DlgSettingsCoords",
                           mainWindow),
  m_btnCartesian (0),
  m_btnPolar (0),
  m_validatorOriginRadius (0),
  m_cmbDate (0),
  m_cmbTime (0),
  m_scenePreview (0),
  m_viewPreview (0),
  m_modelCoordsBefore (0),
  m_modelCoordsAfter (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::DlgSettingsCoords";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel,
               MINIMUM_DIALOG_WIDTH_COORDS);
}

DlgSettingsCoords::~DlgSettingsCoords()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::~DlgSettingsCoords";
}

void DlgSettingsCoords::annotateAngles (const QFont &defaultFont) {

  // 0=+x, 1=+y, 2=-x, 3=-y
  for (int direction = 0; direction < 4; direction++) {

    QString angle;
    CoordUnitsPolarTheta thetaUnits = (CoordUnitsPolarTheta) m_cmbXThetaUnits->currentData().toInt();

    switch (thetaUnits) {
      case COORD_UNITS_POLAR_THETA_DEGREES:
      case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES:
      case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS:
        angle = QString::number (90.0 * direction);
        break;

      case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
        angle = QString::number (90.0 * direction);
        if (direction == 1) {
          angle = "90E";
        } else if (direction == 3) {
          angle = "90W";
        }
        break;

      case COORD_UNITS_POLAR_THETA_GRADIANS:
        angle = QString::number (100.0 * direction);
        break;

      case COORD_UNITS_POLAR_THETA_RADIANS:
        {
          static QString radiansUnits [] = {"0", "PI / 2", "PI", "3 * PI / 2"};
          ENGAUGE_ASSERT (direction < 4);
          angle = radiansUnits [direction];
        }
        break;

      case COORD_UNITS_POLAR_THETA_TURNS:
        {
          static QString turnsUnits [] = {"0", "1 / 4", "1 / 2", "3 / 4"};
          ENGAUGE_ASSERT (direction < 4);
          angle = turnsUnits [direction];
        }
        break;

      default:
       break;
    }

    QGraphicsTextItem *textAngle = m_scenePreview->addText (angle);
    textAngle->setFont (QFont (defaultFont.defaultFamily(), FONT_SIZE));
    double x = 0, y = 0; // Initialized to prevent compiler warning
    switch (direction) {
      case 0:
        x = CARTESIAN_COORD_MAX - textAngle->boundingRect().width ();
        break;
      case 1:
      case 3:
        x = XCENTER - textAngle->boundingRect().width () / 2.0;
        break;
      case 2:
        x = CARTESIAN_COORD_MIN;
        break;
    }
    switch (direction) {
      case 0:
      case 2:
        y = YCENTER;
        break;
      case 1:
        y = CARTESIAN_COORD_MIN;
        break;
      case 3:
        y = CARTESIAN_COORD_MAX - textAngle->boundingRect().height ();
        break;
    }

    textAngle->setPos (x, y);
  }
}

void DlgSettingsCoords::annotateRadiusAtOrigin(const QFont &defaultFont) {

  QGraphicsTextItem *textRadius = m_scenePreview->addText (m_editOriginRadius->text());
  textRadius->setFont (QFont (defaultFont.defaultFamily(), FONT_SIZE));
  textRadius->setPos (XCENTER - textRadius->boundingRect().width () / 2.0,
                      YCENTER);
}

QRectF DlgSettingsCoords::boundingRectGraph (CmdMediator &cmdMediator,
                                             bool &isEmpty) const
{
  CallbackBoundingRects ftor (mainWindow().transformation());

  Functor2wRet<const QString &, const Point&, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                    &CallbackBoundingRects::callback);

  // There may or may one, two or three axis points. Even if all three are not defined (so
  // transformation is not defined), we can still get coordinates if there are one or two
  cmdMediator.iterateThroughCurvePointsAxes (ftorWithCallback);

  // If the transformation is not defined, then there are no graph coordinates to extract
  // from the graph curves (and probably trigger an assert)
  if (mainWindow().transformIsDefined()) {
    cmdMediator.iterateThroughCurvesPointsGraphs (ftorWithCallback);
  }

  return ftor.boundingRectGraph(isEmpty);
}

void DlgSettingsCoords::createDateTime (QGridLayout *layout,
                                        int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::createDateTime";

  QLabel *label = new QLabel(tr ("Date/Time:"));
  layout->addWidget (label, row, 1);

  QWidget *widgetCombos = new QWidget;
  layout->addWidget (widgetCombos, row++, 2);
  QHBoxLayout *layoutCombos = new QHBoxLayout;
  widgetCombos->setLayout (layoutCombos);

  // Put date and time comboboxes into same widget
  m_cmbDate = new QComboBox;
  m_cmbDate->setWhatsThis (tr ("Date format to be used for date values, and date portion of mixed date/time values, "
                               "during input and output.\n\n"
                               "Setting the format to an empty value results in just the time portion appearing in output."));
  connect (m_cmbDate, SIGNAL (activated (const QString &)), this, SLOT (slotDate (const QString &)));
  layoutCombos->addWidget (m_cmbDate);

  m_cmbTime = new QComboBox;
  m_cmbTime->setWhatsThis (tr ("Time format to be used for time values, and time portion of mixed date/time values, "
                               "during input and output.\n\n"
                               "Setting the format to an empty value results in just the date portion appearing in output."));
  connect (m_cmbTime, SIGNAL (activated (const QString &)), this, SLOT (slotTime (const QString &)));
  layoutCombos->addWidget (m_cmbTime);
}

void DlgSettingsCoords::createGroupCoordsType (QGridLayout *layout,
                                               int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::createGroupCoordsType";

  m_boxCoordsType = new QGroupBox(tr ("Coordinates Types"));
  layout->addWidget (m_boxCoordsType, row++, 1, 1, 2);

  QVBoxLayout *layoutGroup = new QVBoxLayout (m_boxCoordsType);

  QString polarButtonText = QString(tr ("Polar") + " (") + THETA + QString(", " + tr ("R") + ")");

  m_btnCartesian = new QRadioButton (tr ("Cartesian (X, Y)"), m_boxCoordsType);
  m_btnCartesian->setWhatsThis (QString(tr("Select cartesian coordinates.\n\n"
                                           "The X and Y coordinates will be used")));
  connect (m_btnCartesian, SIGNAL (toggled(bool)), this, SLOT (slotCartesianPolar (bool)));
  layoutGroup->addWidget (m_btnCartesian);

  m_btnPolar = new QRadioButton (polarButtonText, m_boxCoordsType);
  m_btnPolar->setWhatsThis (QString(tr("Select polar coordinates.\n\n"
                                       "The Theta and R coordinates will be used.\n\n"
                                       "Polar coordinates are not allowed with log scale for Theta")));
  connect (m_btnPolar, SIGNAL (toggled(bool)), this, SLOT (slotCartesianPolar (bool)));
  layoutGroup->addWidget (m_btnPolar);
}

void DlgSettingsCoords::createGroupXTheta (QGridLayout *layout,
                                           int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::createGroupXTheta";

  m_boxXTheta = new QGroupBox(OVERRIDDEN_VALUE);
  layout->addWidget (m_boxXTheta, row, 1, 1, 1);

  QGridLayout *layoutXTheta = new QGridLayout (m_boxXTheta);
  m_boxXTheta->setLayout (layoutXTheta);
  int rowGroup = 0;

  QLabel *labelScale = new QLabel (tr ("Scale:"));
  layoutXTheta->addWidget (labelScale, rowGroup++, COLUMN_0);

  m_xThetaLinear = new QRadioButton (tr ("Linear"), m_boxXTheta);
  m_xThetaLinear->setWhatsThis (QString(tr("Specifies linear scale for the X or Theta coordinate")));
  connect (m_xThetaLinear, SIGNAL (released ()), this, SLOT (slotXThetaLinear()));
  layoutXTheta->addWidget (m_xThetaLinear, rowGroup++, COLUMN_0);

  m_xThetaLog = new QRadioButton (tr ("Log"), m_boxXTheta);
  m_xThetaLog->setWhatsThis (QString(tr("Specifies logarithmic scale for the X or Theta coordinate.\n\n"
                                        "Log scale is not allowed if there are negative coordinates.\n\n"
                                        "Log scale is not allowed for the Theta coordinate.")));
  connect (m_xThetaLog, SIGNAL (released ()), this, SLOT (slotXThetaLog()));
  layoutXTheta->addWidget (m_xThetaLog, rowGroup++, COLUMN_0);

  QLabel *labelThetaUnits = new QLabel(tr ("Units:"));
  layoutXTheta->addWidget (labelThetaUnits, rowGroup++, COLUMN_0);

  m_cmbXThetaUnits = new QComboBox;
  connect (m_cmbXThetaUnits, SIGNAL (activated (const QString &)), this, SLOT (slotUnitsXTheta(const QString &))); // activated() ignores code changes
  layoutXTheta->addWidget (m_cmbXThetaUnits, rowGroup++, COLUMN_0, 1, 2);
}

void DlgSettingsCoords::createGroupYRadius (QGridLayout *layout,
                                            int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::createGroupYRadius";

  m_boxYRadius = new QGroupBox (OVERRIDDEN_VALUE);
  layout->addWidget (m_boxYRadius, row++, 2, 1, 1);

  QGridLayout *layoutYRadius = new QGridLayout (m_boxYRadius);
  m_boxYRadius->setLayout (layoutYRadius);
  int rowGroup = 0;

  QLabel *labelScale = new QLabel (tr ("Scale:"));
  layoutYRadius->addWidget (labelScale, rowGroup++, COLUMN_0);

  m_yRadiusLinear = new QRadioButton (tr ("Linear"), m_boxYRadius);
  m_yRadiusLinear->setWhatsThis (QString(tr("Specifies linear scale for the Y or R coordinate")));
  connect (m_yRadiusLinear, SIGNAL(released()), this, SLOT (slotYRadiusLinear()));
  layoutYRadius->addWidget (m_yRadiusLinear, rowGroup, COLUMN_0);

  QLabel *labelOriginRadius = new QLabel(tr ("Origin radius value:"));
  layoutYRadius->addWidget (labelOriginRadius, rowGroup++, COLUMN_1);

  m_yRadiusLog = new QRadioButton (tr ("Log"), m_boxYRadius);
  m_yRadiusLog->setWhatsThis (QString(tr("Specifies logarithmic scale for the Y or R coordinate\n\n"
                                         "Log scale is not allowed if there are negative coordinates.")));
  connect (m_yRadiusLog, SIGNAL(released ()), this, SLOT (slotYRadiusLog ()));
  layoutYRadius->addWidget (m_yRadiusLog, rowGroup, COLUMN_0);

  m_editOriginRadius = new QLineEdit (m_boxYRadius);
  m_editOriginRadius->setMaximumWidth (MAX_WIDTH_EDIT_ORIGIN_RADIUS);
  m_editOriginRadius->setWhatsThis (QString(tr("Specify radius value at origin.\n\n"
                                               "Normally the radius at the origin is 0, but a nonzero value may be applied in other cases "
                                               "(like when the radial units are decibels).")));
  connect (m_editOriginRadius, SIGNAL (textChanged (const QString &)), this, SLOT (slotPolarOriginRadius(const QString &)));
  layoutYRadius->addWidget (m_editOriginRadius, rowGroup++, COLUMN_1);

  QLabel *labelUnits = new QLabel(tr ("Units:"));
  layoutYRadius->addWidget (labelUnits, rowGroup++, COLUMN_0);
  
  m_cmbYRadiusUnits = new QComboBox;
  connect (m_cmbYRadiusUnits, SIGNAL (activated (const QString &)), this, SLOT (slotUnitsYRadius(const QString &))); // activated() ignores code changes
  layoutYRadius->addWidget (m_cmbYRadiusUnits, rowGroup++, COLUMN_0, 1, 2);
}

void DlgSettingsCoords::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
}

void DlgSettingsCoords::createPreview (QGridLayout *layout,
                                       int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::createPreview";

  QLabel *labelPreview = new QLabel (tr ("Preview"));
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview,
                                   ViewPreview::VIEW_ASPECT_RATIO_VARIABLE,
                                   this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the coordinate system."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QWidget *DlgSettingsCoords::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::createSubPanel";

  QWidget *subPanel = new QWidget ();

  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // Labels
  layout->setColumnStretch(2, 0); // User controls
  layout->setColumnStretch(3, 1); // Empty last column

  int row = 0;
  createGroupCoordsType(layout, row);
  createGroupXTheta (layout, row);
  createGroupYRadius (layout, row);
  createDateTime (layout, row);
  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsCoords::drawCartesianLinearX ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::drawCartesianLinearX";

  bool isAxis = true;
  for (int step = 0; step < NUM_COORD_STEPS; step++) {
    double x = CARTESIAN_COORD_MIN + step * CARTESIAN_COORD_STEP;
    QGraphicsLineItem *line = m_scenePreview->addLine (x, CARTESIAN_COORD_MIN, x, CARTESIAN_COORD_MAX);
    bool isHighlighted = (step % STEPS_PER_CYCLE == 0);
    line->setPen(QPen (QBrush ((isHighlighted ? Qt::gray : Qt::lightGray)),
                       LINE_WIDTH_THIN,
                       (isHighlighted ? Qt::SolidLine : Qt::DashLine)));
    if (isAxis) {
      line = m_scenePreview->addLine (x, CARTESIAN_COORD_MIN, x, CARTESIAN_COORD_MAX);
      line->setPen(QPen (QBrush (Qt::black),
                         LINE_WIDTH_THICK));
    }
    isAxis = false;
  }
}

void DlgSettingsCoords::drawCartesianLinearY ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::drawCartesianLinearY";

  bool isAxis = true;
  for (int step = NUM_COORD_STEPS - 1; step >= 0; step--) {
    double y = CARTESIAN_COORD_MIN + step * CARTESIAN_COORD_STEP;
    QGraphicsLineItem *line = m_scenePreview->addLine (CARTESIAN_COORD_MIN, y, CARTESIAN_COORD_MAX, y);
    bool isHighlighted = (step % STEPS_PER_CYCLE == 0);
    line->setPen(QPen (QBrush (isHighlighted ? Qt::gray : Qt::lightGray),
                       LINE_WIDTH_THIN,
                       (isHighlighted ? Qt::SolidLine : Qt::DashLine)));
    if (isAxis) {
      line = m_scenePreview->addLine (CARTESIAN_COORD_MIN, y, CARTESIAN_COORD_MAX, y);
      line->setPen(QPen (QBrush (Qt::black),
                         LINE_WIDTH_THICK));
    }
    isAxis = false;
  }
}

void DlgSettingsCoords::drawCartesianLogX ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::drawCartesianLogX";

  bool isAxis = true;
  for (int step = 0; step < NUM_COORD_STEPS; step++) {
    double s = (exp (step / (NUM_COORD_STEPS - 1.0)) - 1.0) /
               (exp (1.0) - 1.0);
    double x = (1.0 - s) * CARTESIAN_COORD_MIN + s * CARTESIAN_COORD_MAX;
    QGraphicsLineItem *line = m_scenePreview->addLine (x, CARTESIAN_COORD_MIN, x, CARTESIAN_COORD_MAX);
    bool isHighlighted = (step % STEPS_PER_CYCLE == 0);
    line->setPen(QPen (QBrush (isHighlighted ? Qt::gray : Qt::lightGray),
                       LINE_WIDTH_THIN,
                       (isHighlighted ? Qt::SolidLine : Qt::DashLine)));
    if (isAxis) {
      line = m_scenePreview->addLine (x, CARTESIAN_COORD_MIN, x, CARTESIAN_COORD_MAX);
      line->setPen(QPen (QBrush (Qt::black),
                         LINE_WIDTH_THICK));
    }
    isAxis = false;
  }
}

void DlgSettingsCoords::drawCartesianLogY ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::drawCartesianLogY";

  bool isAxis = true;
  for (int step = 0; step < NUM_COORD_STEPS; step++) {
    double s = (pow (POWER_FOR_LOG, step / (NUM_COORD_STEPS - 1.0)) - 1.0) /
               (pow (POWER_FOR_LOG, 1.0) - 1.0);
    double y = (1.0 - s) * CARTESIAN_COORD_MAX + s * CARTESIAN_COORD_MIN; // Invert y coordinate (min<->max)
    QGraphicsLineItem *line = m_scenePreview->addLine (CARTESIAN_COORD_MIN, y, CARTESIAN_COORD_MAX, y);
    bool isHighlighted = (step % STEPS_PER_CYCLE == 0);
    line->setPen(QPen (QBrush (isHighlighted ? Qt::gray : Qt::lightGray),
                       LINE_WIDTH_THIN,
                       (isHighlighted ? Qt::SolidLine : Qt::DashLine)));
    if (isAxis) {
      line = m_scenePreview->addLine (CARTESIAN_COORD_MIN, y, CARTESIAN_COORD_MAX, y);
      line->setPen(QPen (QBrush (Qt::black),
                         LINE_WIDTH_THICK));
    }
    isAxis = false;
  }
}

void DlgSettingsCoords::drawPolarLinearRadius ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::drawPolarLinearRadius";

  for (int step = 0; step < NUM_COORD_STEPS; step++) {
    double radius = step * POLAR_STEP;
    QGraphicsEllipseItem *line = m_scenePreview->addEllipse (XCENTER - radius,
                                                             YCENTER - radius,
                                                             2.0 * radius,
                                                             2.0 * radius);
    bool isHighlighted = (step % STEPS_PER_CYCLE == 0);
    line->setPen(QPen (QBrush (isHighlighted ? Qt::gray : Qt::lightGray),
                               LINE_WIDTH_THIN,
                               (isHighlighted ? Qt::SolidLine : Qt::DashLine)));
  }
}

void DlgSettingsCoords::drawPolarLogRadius ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::drawPolarLogRadius";

  for (int step = 0; step < NUM_COORD_STEPS; step++) {
    double s = (pow (POWER_FOR_LOG, step / (NUM_COORD_STEPS - 1.0)) - 1.0) /
               (pow (POWER_FOR_LOG, 1.0) - 1.0);
    double radius = (s * (NUM_COORD_STEPS - 1.0)) * POLAR_STEP;
    QGraphicsEllipseItem *line = m_scenePreview->addEllipse (XCENTER - radius,
                                                             YCENTER - radius,
                                                             2.0 * radius,
                                                             2.0 * radius);
    bool isHighlighted = (step % STEPS_PER_CYCLE == 0);
    line->setPen(QPen (QBrush (isHighlighted ? Qt::gray : Qt::lightGray),
                       LINE_WIDTH_THIN,
                       (isHighlighted ? Qt::SolidLine : Qt::DashLine)));
  }
}

void DlgSettingsCoords::drawPolarTheta ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::drawPolarTheta";

  bool isAxis = true;
  for (int step = 0; step < NUM_COORD_STEPS; step++) {
    double theta = POLAR_THETA_MIN + step * POLAR_THETA_STEP;
    double x = POLAR_RADIUS * cos (theta * DEG_2_RAD);
    double y = POLAR_RADIUS * sin (theta * DEG_2_RAD);
    QGraphicsLineItem *line = m_scenePreview->addLine (XCENTER, YCENTER, XCENTER + x, YCENTER + y);
    bool isHighlighted = (step % STEPS_PER_CYCLE == 0);
    line->setPen(QPen (QBrush (isHighlighted ? Qt::gray : Qt::lightGray),
                       LINE_WIDTH_THIN,
                       (isHighlighted ? Qt::SolidLine : Qt::DashLine)));
    if (isAxis) {
      line = m_scenePreview->addLine (XCENTER, YCENTER, XCENTER + x, YCENTER + y);
      line->setPen(QPen (QBrush (Qt::black),
                         LINE_WIDTH_THICK));
    }
    isAxis = false;
  }
}

void DlgSettingsCoords::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::handleOk";

  CmdSettingsCoords *cmd = new CmdSettingsCoords (mainWindow (),
                                                  cmdMediator ().document(),
                                                  *m_modelCoordsBefore,
                                                  *m_modelCoordsAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsCoords::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::load";

  setCmdMediator (cmdMediator);

  // Remove if coordinates are log so later constraints can be applied
  bool isEmpty;
  QRectF rectGraph = boundingRectGraph (cmdMediator,
                                        isEmpty);
  bool xThetaGoesNegative = !isEmpty && (rectGraph.x() <= 0);
  bool yRGoesNegative = !isEmpty && (rectGraph.y() <= 0);
  m_xThetaLinear->setEnabled (!xThetaGoesNegative);
  m_xThetaLog->setEnabled (!xThetaGoesNegative);
  m_yRadiusLinear->setEnabled (!yRGoesNegative);
  m_yRadiusLog->setEnabled (!yRGoesNegative);

  // Flush old data
  if (m_modelCoordsBefore != 0) {
    delete m_modelCoordsBefore;
  }
  if (m_modelCoordsAfter != 0) {
    delete m_modelCoordsAfter;
  }

  // Save new data
  m_modelCoordsBefore = new DocumentModelCoords (cmdMediator.document().modelCoords());
  m_modelCoordsAfter = new DocumentModelCoords (cmdMediator.document().modelCoords());

  // Populate controls
  DlgValidatorFactory dlgValidatorFactory;
  m_validatorOriginRadius = dlgValidatorFactory.createWithNonPolar (m_modelCoordsAfter->coordScaleYRadius(),
                                                                    m_modelCoordsAfter->coordUnitsRadius(),
                                                                    m_modelCoordsAfter->coordUnitsDate(),
                                                                    m_modelCoordsAfter->coordUnitsTime(),
                                                                    mainWindow().modelMainWindow().locale());
  m_editOriginRadius->setValidator (m_validatorOriginRadius); // Set before call to setText so validator is defined in updateControls
  m_editOriginRadius->setText (QString::number (m_modelCoordsAfter->originRadius ()));

  if (m_modelCoordsAfter->coordsType() == COORDS_TYPE_CARTESIAN) {
    m_btnCartesian->setChecked (true);
  } else {
    m_btnPolar->setChecked (true);
  }

  updateCoordUnits(); // Call after checking m_btnCartesian or m_btnPolar
  loadComboBoxDate();
  loadComboBoxTime ();

  m_xThetaLinear->setChecked (m_modelCoordsAfter->coordScaleXTheta() == COORD_SCALE_LINEAR);
  m_xThetaLog->setChecked (m_modelCoordsAfter->coordScaleXTheta() == COORD_SCALE_LOG);
  m_yRadiusLinear->setChecked (m_modelCoordsAfter->coordScaleYRadius() == COORD_SCALE_LINEAR);
  m_yRadiusLog->setChecked (m_modelCoordsAfter->coordScaleYRadius() == COORD_SCALE_LOG);

  updateControls (); // Probably redundant due to the setChecked just above
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsCoords::loadComboBoxDate()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::loadComboBoxDate";

  m_cmbDate->clear ();

  m_cmbDate->addItem (coordUnitsDateToString (COORD_UNITS_DATE_SKIP),
                      QVariant (COORD_UNITS_DATE_SKIP));
  m_cmbDate->addItem (coordUnitsDateToString (COORD_UNITS_DATE_MONTH_DAY_YEAR),
                      QVariant (COORD_UNITS_DATE_MONTH_DAY_YEAR));
  m_cmbDate->addItem (coordUnitsDateToString (COORD_UNITS_DATE_DAY_MONTH_YEAR),
                      QVariant (COORD_UNITS_DATE_DAY_MONTH_YEAR));
  m_cmbDate->addItem (coordUnitsDateToString (COORD_UNITS_DATE_YEAR_MONTH_DAY),
                      QVariant (COORD_UNITS_DATE_YEAR_MONTH_DAY));

  ENGAUGE_ASSERT (m_cmbDate->count() == NUM_COORD_UNITS_DATE);

  int index = m_cmbDate->findData (QVariant (m_modelCoordsAfter->coordUnitsDate()));
  m_cmbDate->setCurrentIndex (index);
}

void DlgSettingsCoords::loadComboBoxTime()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::loadComboBoxTime";

  m_cmbTime->clear ();

  m_cmbTime->addItem (coordUnitsTimeToString (COORD_UNITS_TIME_SKIP),
                      QVariant (COORD_UNITS_TIME_SKIP));
  m_cmbTime->addItem (coordUnitsTimeToString (COORD_UNITS_TIME_HOUR_MINUTE),
                      QVariant (COORD_UNITS_TIME_HOUR_MINUTE));
  m_cmbTime->addItem (coordUnitsTimeToString (COORD_UNITS_TIME_HOUR_MINUTE_SECOND),
                      QVariant (COORD_UNITS_TIME_HOUR_MINUTE_SECOND));

  ENGAUGE_ASSERT (m_cmbTime->count() == NUM_COORD_UNITS_TIME);

  int index = m_cmbTime->findData (QVariant (m_modelCoordsAfter->coordUnitsTime()));
  m_cmbTime->setCurrentIndex (index);
}

void DlgSettingsCoords::loadComboBoxUnitsNonPolar (QComboBox &cmb,
                                                   CoordUnitsNonPolarTheta coordUnits)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::loadComboBoxUnitsNonPolar";

  cmb.clear();

  cmb.addItem (coordUnitsNonPolarThetaToString (COORD_UNITS_NON_POLAR_THETA_NUMBER),
               QVariant (COORD_UNITS_NON_POLAR_THETA_NUMBER));
  cmb.addItem (coordUnitsNonPolarThetaToString (COORD_UNITS_NON_POLAR_THETA_DATE_TIME),
               QVariant (COORD_UNITS_NON_POLAR_THETA_DATE_TIME));
  cmb.addItem (coordUnitsNonPolarThetaToString (COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS),
               QVariant (COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS));
  cmb.addItem (coordUnitsNonPolarThetaToString (COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW),
               QVariant (COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW));

  ENGAUGE_ASSERT (cmb.count() == NUM_COORD_UNITS_NON_POLAR_THETA);

  cmb.setWhatsThis (QString (tr ("Numbers have the simplest and most general format.\n\n"
                                 "Date and time values have date and/or time components.\n\n"
                                 "Degrees Minutes Seconds (DDD MM SS.S) format uses two integer number for degrees and minutes, and a real number for "
                                 "seconds. There are 60 seconds per minute. During input, spaces must be inserted between the three numbers.")));

  int index = cmb.findData (coordUnits);
  cmb.setCurrentIndex (index);
}

void DlgSettingsCoords::loadComboBoxUnitsPolar (QComboBox &cmb,
                                                CoordUnitsPolarTheta coordUnits)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::loadComboBoxUnitsPolar";

  cmb.clear();

  cmb.addItem (coordUnitsPolarThetaToString (COORD_UNITS_POLAR_THETA_DEGREES),
                                             QVariant (COORD_UNITS_POLAR_THETA_DEGREES));
  cmb.addItem (coordUnitsPolarThetaToString (COORD_UNITS_POLAR_THETA_DEGREES_MINUTES),
                                             QVariant (COORD_UNITS_POLAR_THETA_DEGREES_MINUTES));
  cmb.addItem (coordUnitsPolarThetaToString (COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS),
                                             QVariant (COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS));
  cmb.addItem (coordUnitsPolarThetaToString (COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW),
                                             QVariant (COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW));
  cmb.addItem (coordUnitsPolarThetaToString (COORD_UNITS_POLAR_THETA_GRADIANS),
                                             QVariant (COORD_UNITS_POLAR_THETA_GRADIANS));
  cmb.addItem (coordUnitsPolarThetaToString (COORD_UNITS_POLAR_THETA_RADIANS),
                                             QVariant (COORD_UNITS_POLAR_THETA_RADIANS));
  cmb.addItem (coordUnitsPolarThetaToString (COORD_UNITS_POLAR_THETA_TURNS),
                                             QVariant (COORD_UNITS_POLAR_THETA_TURNS));

  ENGAUGE_ASSERT (cmb.count() == NUM_COORD_UNITS_POLAR_THETA);

  cmb.setWhatsThis (QString (tr ("Degrees (DDD.DDDDD) format uses a single real number. One complete revolution is 360 degrees.\n\n"
                                 "Degrees Minutes (DDD MM.MMM) format uses one integer number for degrees, and a real number for minutes. There are "
                                 "60 minutes per degree. During input, a space must be inserted between the two numbers.\n\n"
                                 "Degrees Minutes Seconds (DDD MM SS.S) format uses two integer number for degrees and minutes, and a real number for "
                                 "seconds. There are 60 seconds per minute. During input, spaces must be inserted between the three numbers.\n\n"
                                 "Gradians format uses a single real number. One complete revolution is 400 gradians.\n\n"
                                 "Radians format uses a single real number. One complete revolution is 2*pi radians.\n\n"
                                 "Turns format uses a single real number. One complete revolution is one turn.")));

  int index = cmb.findData (coordUnits);
  cmb.setCurrentIndex (index);
}

void DlgSettingsCoords::resetSceneRectangle ()
{
  QRect rect (CARTESIAN_COORD_MIN - CARTESIAN_COORD_STEP / 2.0,
              CARTESIAN_COORD_MIN - CARTESIAN_COORD_STEP / 2.0,
              CARTESIAN_COORD_MAX - CARTESIAN_COORD_MIN + CARTESIAN_COORD_STEP,
              CARTESIAN_COORD_MAX - CARTESIAN_COORD_MIN + CARTESIAN_COORD_STEP);

  QGraphicsRectItem *itemPerimeter = new QGraphicsRectItem(rect);
  itemPerimeter->setVisible(false);
  m_scenePreview->addItem (itemPerimeter);
  m_viewPreview->centerOn (QPointF (0.0, 0.0));
}

void DlgSettingsCoords::setSmallDialogs(bool smallDialogs)
{
  if (!smallDialogs) {
    setMinimumHeight (MINIMUM_HEIGHT);
  }
}

void DlgSettingsCoords::slotCartesianPolar (bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotCartesian";

  if (m_btnCartesian->isChecked ()) {
    m_modelCoordsAfter->setCoordsType (COORDS_TYPE_CARTESIAN);
  } else {
    m_modelCoordsAfter->setCoordsType(COORDS_TYPE_POLAR);
  }
  updateCoordUnits();
  updateControls();
  updatePreview();
}

void DlgSettingsCoords::slotDate(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotDate";

  CoordUnitsDate coordUnits = (CoordUnitsDate) m_cmbDate->currentData ().toInt();
  m_modelCoordsAfter->setCoordUnitsDate(coordUnits);
  updateControls();
  updatePreview();
}

void DlgSettingsCoords::slotPolarOriginRadius(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotPolarOriginRadius";

  QString numberText = m_editOriginRadius->text();

  m_modelCoordsAfter->setOriginRadius(numberText.toDouble ());
  updateControls();
  updatePreview();
}

void DlgSettingsCoords::slotTime(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotTime";

  CoordUnitsTime coordUnits = (CoordUnitsTime) m_cmbTime->currentData ().toInt();
  m_modelCoordsAfter->setCoordUnitsTime(coordUnits);
  updateControls();
  updatePreview();
}

void DlgSettingsCoords::slotUnitsXTheta(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotUnitsXTheta";

  if (m_modelCoordsAfter->coordsType() == COORDS_TYPE_CARTESIAN) {
    CoordUnitsNonPolarTheta coordUnits = (CoordUnitsNonPolarTheta) m_cmbXThetaUnits->currentData ().toInt ();
    m_modelCoordsAfter->setCoordUnitsX(coordUnits);
  } else {
    CoordUnitsPolarTheta coordUnits = (CoordUnitsPolarTheta) m_cmbXThetaUnits->currentData ().toInt ();
    m_modelCoordsAfter->setCoordUnitsTheta(coordUnits);
  }
  updateControls ();
  updatePreview();
}

void DlgSettingsCoords::slotUnitsYRadius(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotUnitsYRadius";

  CoordUnitsNonPolarTheta coordUnits = (CoordUnitsNonPolarTheta) m_cmbYRadiusUnits->currentData ().toInt ();
  if (m_modelCoordsAfter->coordsType() == COORDS_TYPE_CARTESIAN) {
    m_modelCoordsAfter->setCoordUnitsY(coordUnits);
  } else {
    m_modelCoordsAfter->setCoordUnitsRadius(coordUnits);
  }
  updateControls ();
  updatePreview();
}

void DlgSettingsCoords::slotXThetaLinear()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotXThetaLinear";

  m_modelCoordsAfter->setCoordScaleXTheta(COORD_SCALE_LINEAR);
  updateControls ();
  updatePreview();
}

void DlgSettingsCoords::slotXThetaLog()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotXThetaLog";

  m_modelCoordsAfter->setCoordScaleXTheta(COORD_SCALE_LOG);
  updateControls ();
  updatePreview();
}

void DlgSettingsCoords::slotYRadiusLinear()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotYRadiusLinear";

  delete m_validatorOriginRadius;

  DlgValidatorFactory dlgValidatorFactory;
  m_validatorOriginRadius = dlgValidatorFactory.createWithNonPolar (COORD_SCALE_LINEAR,
                                                                    m_modelCoordsAfter->coordUnitsRadius(),
                                                                    m_modelCoordsAfter->coordUnitsDate(),
                                                                    m_modelCoordsAfter->coordUnitsTime(),
                                                                    mainWindow().modelMainWindow().locale());
  m_editOriginRadius->setValidator (m_validatorOriginRadius);

  m_modelCoordsAfter->setCoordScaleYRadius((COORD_SCALE_LINEAR));
  updateControls ();
  updatePreview();
}

void DlgSettingsCoords::slotYRadiusLog()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotYRadiusLog";

  delete m_validatorOriginRadius;

  DlgValidatorFactory dlgValidatorFactory;
  m_validatorOriginRadius = dlgValidatorFactory.createWithNonPolar (COORD_SCALE_LOG,
                                                                    m_modelCoordsAfter->coordUnitsRadius(),
                                                                    m_modelCoordsAfter->coordUnitsDate(),
                                                                    m_modelCoordsAfter->coordUnitsTime(),
                                                                    mainWindow().modelMainWindow().locale());
  m_editOriginRadius->setValidator (m_validatorOriginRadius);

  m_modelCoordsAfter->setCoordScaleYRadius(COORD_SCALE_LOG);
  updateControls ();
  updatePreview();
}

void DlgSettingsCoords::updateControls ()
{
  // LOG4CPP_INFO_S is below

  QString textOriginRadius = m_editOriginRadius->text();
  int posOriginRadius = 0;

  bool goodOriginRadius = true; // Cartesian coordinates do not use origin radius
  if (m_editOriginRadius->isEnabled ()) {

    // Origin radius must be greater than zero
    goodOriginRadius = (m_validatorOriginRadius->validate (textOriginRadius,
                                                           posOriginRadius) == QValidator::Acceptable);
  }

  enableOk (goodOriginRadius);

  m_boxCoordsType->setEnabled (!m_xThetaLog->isChecked ());

  m_xThetaLinear->setEnabled (!m_btnPolar->isChecked ());
  m_xThetaLog->setEnabled (!m_btnPolar->isChecked ());
  if (m_btnCartesian->isChecked()) {
    m_yRadiusLinear->setEnabled (true);
    m_yRadiusLog->setEnabled (true);
  } else {

    // Use temporary validator to see if current origin radius would be correct in OTHER linear/log mode
    DlgValidatorFactory dlgValidatorFactory;
    DlgValidatorAbstract *dlg = dlgValidatorFactory.createWithNonPolar (m_yRadiusLinear->isChecked () ? COORD_SCALE_LOG : COORD_SCALE_LINEAR,
                                                                        m_modelCoordsAfter->coordUnitsRadius(),
                                                                        m_modelCoordsAfter->coordUnitsDate(),
                                                                        m_modelCoordsAfter->coordUnitsTime(),
                                                                        mainWindow().modelMainWindow().locale());
    int posOriginRadiusOther;
    bool goodOriginRadiusOther = (dlg->validate (textOriginRadius, posOriginRadiusOther) == QValidator::Acceptable);

    delete dlg; // Deallocate

    m_yRadiusLinear->setEnabled (goodOriginRadius && goodOriginRadiusOther);
    m_yRadiusLog->setEnabled (goodOriginRadius && goodOriginRadiusOther);
  }
  m_editOriginRadius->setEnabled (m_btnPolar->isChecked ());

  QString captionXTheta = (m_btnCartesian->isChecked () ?
                             QString (tr ("X")) :
                             THETA) + QString (" %1")
                          .arg (tr ("Coordinates"));
  QString captionYRadius = (m_btnCartesian->isChecked () ?
                              QString (tr ("Y")) :
                              QString (tr ("R"))) + QString (" %1")
                           .arg (tr ("Coordinates"));

  if (m_boxXTheta->title() != captionXTheta) {
    m_boxXTheta->setTitle (captionXTheta);
  }

  if (m_boxYRadius->title () != captionYRadius) {
    m_boxYRadius->setTitle (captionYRadius);
  }

  bool enableDateTime;
  if (m_btnCartesian->isChecked()) {
    enableDateTime = (((CoordUnitsNonPolarTheta) m_cmbXThetaUnits->currentData ().toInt() == COORD_UNITS_NON_POLAR_THETA_DATE_TIME) ||
                      ((CoordUnitsNonPolarTheta) m_cmbYRadiusUnits->currentData ().toInt() == COORD_UNITS_NON_POLAR_THETA_DATE_TIME));
  } else {
    enableDateTime = ((CoordUnitsNonPolarTheta) m_cmbYRadiusUnits->currentData ().toInt() == COORD_UNITS_NON_POLAR_THETA_DATE_TIME);
  }
  m_cmbDate->setEnabled (enableDateTime);
  m_cmbTime->setEnabled (enableDateTime);

  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::updateControls"
                              << " textOriginRadius=" << textOriginRadius.toLatin1().data()
                              << " goodOriginRadius=" << (goodOriginRadius ? "true" : "false")
                              << " originRadius=" << posOriginRadius
                              << " btnPolarChecked=" << (m_btnPolar->isChecked() ? "true" : "false")
                              << " enableDateTime=" << (enableDateTime ? "true" : "false");
}

void DlgSettingsCoords::updateCoordUnits()
{
  // X and Y units
  if (m_btnCartesian->isChecked()) {
    loadComboBoxUnitsNonPolar (*m_cmbXThetaUnits,
                               m_modelCoordsAfter->coordUnitsX());
    loadComboBoxUnitsNonPolar (*m_cmbYRadiusUnits,
                               m_modelCoordsAfter->coordUnitsY());
  } else {
    loadComboBoxUnitsPolar (*m_cmbXThetaUnits,
                            m_modelCoordsAfter->coordUnitsTheta());
    loadComboBoxUnitsNonPolar (*m_cmbYRadiusUnits,
                               m_modelCoordsAfter->coordUnitsRadius());
  }
}

void DlgSettingsCoords::updatePreview()
{
  m_scenePreview->clear();

  // General approach
  // 1) Axis lines are extra thick, but since they sometimes disappear as the preview window is rescaled, we keep the
  //    constant-pixel line under each axis line
  // 2) Every STEPS_UNHIGHLIGHTED_PER_HIGHLIGHTED out of STEPS_UNHIGHLIGHTED_PER_HIGHLIGHTED+1 lines are dashed to make
  //    them more subtle

  if (m_btnCartesian->isChecked()) {

    // Cartesian
    if (m_xThetaLinear->isChecked()) {
      drawCartesianLinearX ();
    } else {
      drawCartesianLogX ();
    }

    if (m_yRadiusLinear->isChecked()) {
      drawCartesianLinearY ();
    } else {
      drawCartesianLogY ();
    }

  } else {

    // Polar
    drawPolarTheta ();
    if (m_yRadiusLinear->isChecked()) {
      drawPolarLinearRadius ();
    } else {
      drawPolarLogRadius ();
    }

    QFont defaultFont;
    annotateRadiusAtOrigin (defaultFont);
    annotateAngles (defaultFont);
  }

  resetSceneRectangle();
}
