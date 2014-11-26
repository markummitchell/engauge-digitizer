#include "CmdMediator.h"
#include "CmdSettingsCoords.h"
#include "DlgModelCoords.h"
#include "DlgSettingsCoords.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QComboBox>
#include <QDoubleValidator>
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
  connect (m_btnCartesian, SIGNAL (pressed()), this, SLOT (slotCartesian ()));
  layoutGroup->addWidget (m_btnCartesian);

  m_btnPolar = new QRadioButton (polarButtonText, m_boxCoordsType);
  m_btnPolar->setWhatsThis (QString(tr("Select polar coordinates.\n\n"
                                       "The Theta and R coordinates will be used.\n\n"
                                       "Polar coordinates are not allowed with log scale for Theta")));
  connect (m_btnPolar, SIGNAL (pressed()), this, SLOT (slotPolar ()));
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
  m_cmbPolarUnits->addItem (POLAR_UNITS_DEGREES);
  m_cmbPolarUnits->addItem (POLAR_UNITS_DEGREES_MINUTES);
  m_cmbPolarUnits->addItem (POLAR_UNITS_DEGREES_MINUTES_SECONDS);
  m_cmbPolarUnits->addItem (POLAR_UNITS_GRADIANS);
  m_cmbPolarUnits->addItem (POLAR_UNITS_RADIANS);
  m_cmbPolarUnits->addItem (POLAR_UNITS_TURNS);
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
  connect (m_editOriginRadius, SIGNAL (editingFinished ()), this, SLOT (slotPolarOriginRadius()));
  layoutPolar->addWidget (m_editOriginRadius, 1, 1);
}

void DlgSettingsCoords::createGroupScale (QGridLayout *layout,
                                          int &row)
{
  m_boxXTheta = new QGroupBox(QString("X/") + QChar (0x98, 0x03) + QString (" Scale"));
  layout->addWidget (m_boxXTheta, row, 1);

  QVBoxLayout *layoutXTheta = new QVBoxLayout (m_boxXTheta);
  m_boxXTheta->setLayout (layoutXTheta);

  m_xThetaLinear = new QRadioButton ("Linear", m_boxXTheta);
  m_xThetaLinear->setWhatsThis (QString(tr("Specifies linear scale for the X or Theta coordinate")));
  connect (m_xThetaLinear, SIGNAL (pressed ()), this, SLOT (slotXThetaLinear()));
  layoutXTheta->addWidget (m_xThetaLinear);

  m_xThetaLog = new QRadioButton ("Log", m_boxXTheta);
  m_xThetaLog->setWhatsThis (QString(tr("Specifies logarithmic scale for the X coordinate.\n\n"
                                        "Log scale is not allowed for the Theta coordinate")));
  connect (m_xThetaLog, SIGNAL (pressed ()), this, SLOT (slotXThetaLog()));
  layoutXTheta->addWidget (m_xThetaLog);

  m_boxYRadius = new QGroupBox ("Y/R Scale");
  layout->addWidget (m_boxYRadius, row++, 2);

  QVBoxLayout *layoutYRadius = new QVBoxLayout (m_boxYRadius);
  m_boxYRadius->setLayout (layoutYRadius);

  m_yRadiusLinear = new QRadioButton ("Linear", m_boxYRadius);
  m_yRadiusLinear->setWhatsThis (QString(tr("Specifies linear scale for the Y or R coordinate")));
  connect (m_yRadiusLinear, SIGNAL(pressed()), this, SLOT (slotYRadiusLinear()));
  layoutYRadius->addWidget (m_yRadiusLinear);

  m_yRadiusLog = new QRadioButton ("Log", m_boxYRadius);
  m_yRadiusLog->setWhatsThis (QString(tr("Specifies logarithmic scale for the Y or R coordinate")));
  connect (m_yRadiusLog, SIGNAL(pressed ()), this, SLOT (slotYRadiusLog ()));
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

void DlgSettingsCoords::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::handleOk";

  CmdSettingsCoords *cmd = new CmdSettingsCoords (mainWindow (),
                                                  cmdMediator ().document());
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsCoords::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::load";

  setCmdMediator (cmdMediator);

  m_modelCoordsBefore = new DlgModelCoords (cmdMediator.document().dlgModelCoords());
  m_modelCoordsAfter = new DlgModelCoords (cmdMediator.document().dlgModelCoords());

  m_btnCartesian->setChecked (m_modelCoordsAfter->coordsType() == COORDS_TYPE_CARTESIAN);
  m_btnPolar->setChecked (m_modelCoordsAfter->coordsType() == COORDS_TYPE_POLAR);
  m_editOriginRadius->setText (QString::number (m_modelCoordsAfter->originRadius ()));

  updateControls ();
}

void DlgSettingsCoords::loadPixmap (const QString &image)
{
  if (m_scenePreview->items().count () > 0) {
    m_scenePreview->removeItem (m_scenePreview->items().first());
  }

  QPixmap pixmap (image);
  m_scenePreview->addPixmap (pixmap);
}

void DlgSettingsCoords::slotCartesian ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotCartesian";

  enableOk (true);

  m_modelCoordsAfter->setCoordsType (COORDS_TYPE_CARTESIAN);
  loadPixmap (":/engauge/img/plot_cartesian.png");
  updateControls();
}

void DlgSettingsCoords::slotPolar ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotPolar";

  enableOk (true);

  m_modelCoordsAfter->setCoordsType(COORDS_TYPE_POLAR);
  loadPixmap (":/engauge/img/plot_polar.png");
  updateControls();
}

void DlgSettingsCoords::slotPolarOriginRadius()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotPolarOriginRadius";

  enableOk (true);

  m_modelCoordsAfter->setOriginRadius(m_editOriginRadius->text ().toDouble ());
  updateControls();
}

void DlgSettingsCoords::slotPolarUnits(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotPolarUnits";

  enableOk (true);
  updateControls ();
}

void DlgSettingsCoords::slotXThetaLinear()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotXThetaLinear";

  enableOk (true);
  updateControls ();
}

void DlgSettingsCoords::slotXThetaLog()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotXThetaLog";

  enableOk (true);
  updateControls ();
}

void DlgSettingsCoords::slotYRadiusLinear()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotYRadiusLinear";

  enableOk (true);
  updateControls ();
}

void DlgSettingsCoords::slotYRadiusLog()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCoords::slotYRadiusLog";

  enableOk (true);
  updateControls ();
}

void DlgSettingsCoords::updateControls ()
{
  m_btnPolar->setEnabled (!m_xThetaLog->isChecked ());

  m_xThetaLog->setEnabled (!m_btnPolar->isChecked ());
  m_xThetaLinear->setChecked (m_modelCoordsAfter->coordScaleXTheta() == COORD_SCALE_LINEAR);
  m_xThetaLog->setChecked (m_modelCoordsAfter->coordScaleXTheta() == COORD_SCALE_LOG);

  m_cmbPolarUnits->setEnabled (m_btnPolar->isChecked ());

  m_yRadiusLinear->setChecked (m_modelCoordsAfter->coordScaleYRadius() == COORD_SCALE_LINEAR);
  m_yRadiusLinear->setChecked (m_modelCoordsAfter->coordScaleYRadius() == COORD_SCALE_LOG);

  m_editOriginRadius->setEnabled (m_btnPolar->isChecked ());
}
