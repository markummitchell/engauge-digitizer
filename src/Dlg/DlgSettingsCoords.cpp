#include "CmdMediator.h"
#include "CmdSettingsCoords.h"
#include "DlgSettingsCoords.h"
#include "DocumentModelCoords.h"
#include "Logger.h"
#include "MainWindow.h"
#include <math.h>
#include <QComboBox>
#include <QDebug>
#include <QDoubleValidator>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QGroupBox>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "ViewPreview.h"

const QString POLAR_UNITS_DEGREES = QString("Degrees (DDD.DDDDD") + QChar(0260) + QString (")");
const QString POLAR_UNITS_DEGREES_MINUTES = QString("Degrees Minutes (DDD") + QChar(0260) +
                                            QString(" MM.MMM") + QChar(0x2032) +
                                            QString(")");
const QString POLAR_UNITS_DEGREES_MINUTES_SECONDS = QString("Degrees Minutes Seconds (DDD") + QChar(0260) +
                                                    QString(" MM") + QChar(0x2032) +
                                                    QString(" SS.S") + QChar(0x2033) + QString(")");
const QString POLAR_UNITS_GRADIANS = "Gradians";
const QString POLAR_UNITS_RADIANS = "Radians";
const QString POLAR_UNITS_TURNS = "Turns";

const int STEPS_PER_CYCLE = 4; // Repeat STEPS_PER_CYLE-1 unhighlighted steps plus 1 highlighted step in each cycle
const int STEPS_CYCLE_COUNT = 4; // Repeat one highlighted step + STEPS_UNHIGHLIGHTED_PER_HIGHLIGHTED steps this many times
const int NUM_COORD_STEPS = 1 + STEPS_PER_CYCLE * STEPS_CYCLE_COUNT;

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

DlgSettingsCoords::DlgSettingsCoords(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Coordinates", mainWindow),
  m_btnCartesian (0),
  m_btnPolar (0),
  m_modelCoordsBefore (0),
  m_modelCoordsAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsCoords::annotateAngles (const QFont &defaultFont) {

  // 0=+x, 1=+y, 2=-x, 3=-y
  for (int direction = 0; direction < 4; direction++) {

    QString angle;
    CoordThetaUnits thetaUnits = (CoordThetaUnits) m_cmbPolarUnits->currentData().toInt();

    switch (thetaUnits) {
      case COORD_THETA_UNITS_DEGREES:
      case COORD_THETA_UNITS_DEGREES_MINUTES:
      case COORD_THETA_UNITS_DEGREES_MINUTES_SECONDS:
        angle = QString::number (90.0 * direction);
        break;

       case COORD_THETA_UNITS_GRADIANS:
        angle = QString::number (100.0 * direction);
        break;

      case COORD_THETA_UNITS_RADIANS:
        static QString radiansUnits [] = {"0", "PI / 2", "PI", "3 * PI / 2"};
        Q_ASSERT (direction < 4);
        angle = radiansUnits [direction];
        break;

      case COORD_THETA_UNITS_TURNS:
        static QString turnsUnits [] = {"0", "1 / 4", "1 / 2", "3 / 4"};
        Q_ASSERT (direction < 4);
        angle = turnsUnits [direction];
        break;

      default:
       break;
    }

    QGraphicsTextItem *textAngle = m_scenePreview->addText (angle);
    textAngle->setFont (QFont (defaultFont.defaultFamily(), FONT_SIZE));
    double x, y;
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

void DlgSettingsCoords::createGroupCoordsType (QGridLayout *layout,
                                               int &row)
{
  m_boxCoordsType = new QGroupBox("Coordinates Types");
  layout->addWidget (m_boxCoordsType, row++, 1, 1, 2);

  QVBoxLayout *layoutGroup = new QVBoxLayout (m_boxCoordsType);

  QString polarButtonText = QString("Polar (R, ") + QChar(0x98, 0x03) + QString(")");

  m_btnCartesian = new QRadioButton ("Cartesian (X, Y)", m_boxCoordsType);
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

void DlgSettingsCoords::createGroupPolar(QGridLayout *layout,
                                         int &row)
{
  m_boxPolarCoords = new QGroupBox ("Polar Coordinates");
  layout->addWidget (m_boxPolarCoords, row++, 1, 1, 2);

  QGridLayout *layoutPolar = new QGridLayout (m_boxPolarCoords);
  m_boxPolarCoords->setLayout (layoutPolar);

  QLabel *labelThetaUnits = new QLabel(QChar (0x98, 0x03) + QString (" Units:"));
  layoutPolar->addWidget (labelThetaUnits, 0, 0);

  m_cmbPolarUnits = new QComboBox;
  m_cmbPolarUnits->addItem (POLAR_UNITS_DEGREES, QVariant (COORD_THETA_UNITS_DEGREES));
  m_cmbPolarUnits->addItem (POLAR_UNITS_DEGREES_MINUTES, QVariant (COORD_THETA_UNITS_DEGREES_MINUTES));
  m_cmbPolarUnits->addItem (POLAR_UNITS_DEGREES_MINUTES_SECONDS, QVariant (COORD_THETA_UNITS_DEGREES_MINUTES_SECONDS));
  m_cmbPolarUnits->addItem (POLAR_UNITS_GRADIANS, QVariant (COORD_THETA_UNITS_GRADIANS));
  m_cmbPolarUnits->addItem (POLAR_UNITS_RADIANS, QVariant (COORD_THETA_UNITS_RADIANS));
  m_cmbPolarUnits->addItem (POLAR_UNITS_TURNS, QVariant (COORD_THETA_UNITS_TURNS));
  m_cmbPolarUnits->setWhatsThis (QString (tr ("Degrees (DDD.DDDDD) format uses a single real number. One complete revolution is 360 degrees.\n\n"
                                              "Degrees Minutes (DDD MM.MMM) format uses one integer number for degrees, and a real number for minutes. There are "
                                              "60 minutes per degree. During input, a space must be inserted between the two numbers.\n\n"
                                              "Degrees Minutes Seconds (DDD MM SS.S) format uses two integer number for degrees and minutes, and a real number for "
                                              "seconds. There are 60 seconds per minute. During input, spaces must be inserted between the three numbers.\n\n"
                                              "Gradians format uses a single real number. One complete revolution is 400 gradians.\n\n"
                                              "Radians format uses a single real number. One complete revolution is 2*pi radians.\n\n"
                                              "Turns format uses a single real number. One complete revolution is one turn.")));
  connect (m_cmbPolarUnits, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotPolarUnits(const QString &)));
  layoutPolar->addWidget (m_cmbPolarUnits, 0, 1);

  QLabel *labelOriginRadius = new QLabel("Origin radius value:");
  layoutPolar->addWidget (labelOriginRadius, 1, 0);

  m_editOriginRadius = new QLineEdit (m_boxPolarCoords);
  m_editOriginRadius->setValidator (new QDoubleValidator);
  m_editOriginRadius->setWhatsThis (QString(tr("Specify radius value at origin.\n\n"
                                               "Normally the radius at the origin is 0, but a nonzero value may be applied in other cases "
                                               "(like when the radial units are decibels).")));
  connect (m_editOriginRadius, SIGNAL (textChanged (const QString &)), this, SLOT (slotPolarOriginRadius(const QString &)));
  layoutPolar->addWidget (m_editOriginRadius, 1, 1);
}

void DlgSettingsCoords::createGroupScale (QGridLayout *layout,
                                          int &row)
{
  const QString OVERRIDDEN_VALUE(""); // Values are overridden in updateControls

  m_boxXTheta = new QGroupBox(OVERRIDDEN_VALUE);
  layout->addWidget (m_boxXTheta, row, 1);

  QVBoxLayout *layoutXTheta = new QVBoxLayout (m_boxXTheta);
  m_boxXTheta->setLayout (layoutXTheta);

  m_xThetaLinear = new QRadioButton ("Linear", m_boxXTheta);
  m_xThetaLinear->setWhatsThis (QString(tr("Specifies linear scale for the X or Theta coordinate")));
  connect (m_xThetaLinear, SIGNAL (released ()), this, SLOT (slotXThetaLinear()));
  layoutXTheta->addWidget (m_xThetaLinear);

  m_xThetaLog = new QRadioButton ("Log", m_boxXTheta);
  m_xThetaLog->setWhatsThis (QString(tr("Specifies logarithmic scale for the X coordinate.\n\n"
                                        "Log scale is not allowed for the Theta coordinate")));
  connect (m_xThetaLog, SIGNAL (released ()), this, SLOT (slotXThetaLog()));
  layoutXTheta->addWidget (m_xThetaLog);

  m_boxYRadius = new QGroupBox (OVERRIDDEN_VALUE);
  layout->addWidget (m_boxYRadius, row++, 2);

  QVBoxLayout *layoutYRadius = new QVBoxLayout (m_boxYRadius);
  m_boxYRadius->setLayout (layoutYRadius);

  m_yRadiusLinear = new QRadioButton ("Linear", m_boxYRadius);
  m_yRadiusLinear->setWhatsThis (QString(tr("Specifies linear scale for the Y or R coordinate")));
  connect (m_yRadiusLinear, SIGNAL(released()), this, SLOT (slotYRadiusLinear()));
  layoutYRadius->addWidget (m_yRadiusLinear);

  m_yRadiusLog = new QRadioButton ("Log", m_boxYRadius);
  m_yRadiusLog->setWhatsThis (QString(tr("Specifies logarithmic scale for the Y or R coordinate")));
  connect (m_yRadiusLog, SIGNAL(released ()), this, SLOT (slotYRadiusLog ()));
  layoutYRadius->addWidget (m_yRadiusLog);
}

void DlgSettingsCoords::createPreview (QGridLayout *layout,
                                       int &row)
{
  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview, this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the coordinate system."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QWidget *DlgSettingsCoords::createSubPanel ()
{
  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // Labels
  layout->setColumnStretch(2, 0); // User controls
  layout->setColumnStretch(3, 1); // Empty last column

  int row = 0;
  createGroupCoordsType(layout, row);
  createGroupScale (layout, row);
  createGroupPolar (layout, row);
  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsCoords::drawCartesianLinearX () {

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

void DlgSettingsCoords::drawCartesianLinearY () {

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

void DlgSettingsCoords::drawCartesianLogX () {

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

void DlgSettingsCoords::drawCartesianLogY () {

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

void DlgSettingsCoords::drawPolarLinearRadius () {

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

void DlgSettingsCoords::drawPolarLogRadius () {

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

void DlgSettingsCoords::drawPolarTheta () {

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

  m_modelCoordsBefore = new DocumentModelCoords (cmdMediator.document().modelCoords());
  m_modelCoordsAfter = new DocumentModelCoords (cmdMediator.document().modelCoords());

  m_editOriginRadius->setText (QString::number (m_modelCoordsAfter->originRadius ()));

  if (m_modelCoordsAfter->coordsType() == COORDS_TYPE_CARTESIAN) {
    m_btnCartesian->setChecked (true);
  } else {
    m_btnPolar->setChecked (true);
  }

  int indexPolarUnits = m_cmbPolarUnits->findData (QVariant (m_modelCoordsAfter->coordThetaUnits()));
  m_cmbPolarUnits->setCurrentIndex (indexPolarUnits);

  m_xThetaLinear->setChecked (m_modelCoordsAfter->coordScaleXTheta() == COORD_SCALE_LINEAR);
  m_xThetaLog->setChecked (m_modelCoordsAfter->coordScaleXTheta() == COORD_SCALE_LOG);
  m_yRadiusLinear->setChecked (m_modelCoordsAfter->coordScaleYRadius() == COORD_SCALE_LINEAR);
  m_yRadiusLog->setChecked (m_modelCoordsAfter->coordScaleYRadius() == COORD_SCALE_LOG);

  updateControls (); // Probably redundant due to the setChecked just above
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsCoords::resetSceneRectangle () {

  QRect rect (CARTESIAN_COORD_MIN - CARTESIAN_COORD_STEP / 2.0,
              CARTESIAN_COORD_MIN - CARTESIAN_COORD_STEP / 2.0,
              CARTESIAN_COORD_MAX - CARTESIAN_COORD_MIN + CARTESIAN_COORD_STEP,
              CARTESIAN_COORD_MAX - CARTESIAN_COORD_MIN + CARTESIAN_COORD_STEP);

  QGraphicsRectItem *itemPerimeter = new QGraphicsRectItem(rect);
  itemPerimeter->setVisible(false);
  m_scenePreview->addItem (itemPerimeter);
  m_viewPreview->centerOn (QPointF (0.0, 0.0));
}

void DlgSettingsCoords::slotCartesianPolar (bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotCartesian";

  if (m_btnCartesian->isChecked ()) {
    m_modelCoordsAfter->setCoordsType (COORDS_TYPE_CARTESIAN);
  } else {
    m_modelCoordsAfter->setCoordsType(COORDS_TYPE_POLAR);
  }
  updateControls();
  updatePreview();
}

void DlgSettingsCoords::slotPolarOriginRadius(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotPolarOriginRadius";

  m_modelCoordsAfter->setOriginRadius(m_editOriginRadius->text ().toDouble ());
  updateControls();
  updatePreview();
}

void DlgSettingsCoords::slotPolarUnits(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotPolarUnits";

  CoordThetaUnits coordThetaUnits = (CoordThetaUnits) m_cmbPolarUnits->currentData ().toInt ();
  m_modelCoordsAfter->setCoordThetaUnits(coordThetaUnits);
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

  m_modelCoordsAfter->setCoordScaleYRadius((COORD_SCALE_LINEAR));
  updateControls ();
  updatePreview();
}

void DlgSettingsCoords::slotYRadiusLog()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotYRadiusLog";

  m_modelCoordsAfter->setCoordScaleYRadius(COORD_SCALE_LOG);
  updateControls ();
  updatePreview();
}

void DlgSettingsCoords::updateControls ()
{
  bool isGoodState = !(m_btnPolar->isChecked() && m_editOriginRadius->text().isEmpty());
  enableOk (isGoodState);

  m_btnPolar->setEnabled (!m_xThetaLog->isChecked ());
  m_xThetaLog->setEnabled (!m_btnPolar->isChecked ());
  m_cmbPolarUnits->setEnabled (m_btnPolar->isChecked ());
  m_editOriginRadius->setEnabled (m_btnPolar->isChecked ());

  QString captionXTheta = (m_btnCartesian->isChecked () ?
                             QString ("X") :
                             QChar (0x98, 0x03)) + QString (" Scale");
  QString captionYRadius = (m_btnCartesian->isChecked () ?
                              QString ("Y") :
                              QString ("R")) + QString (" Scale");

  if (m_boxXTheta->title() != captionXTheta) {
    m_boxXTheta->setTitle (captionXTheta);
  }

  if (m_boxYRadius->title () != captionYRadius) {
    m_boxYRadius->setTitle (captionYRadius);
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
