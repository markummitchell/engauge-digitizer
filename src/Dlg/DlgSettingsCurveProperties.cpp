/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdSettingsCurveProperties.h"
#include "ColorPalette.h"
#include "DlgSettingsCurveProperties.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GeometryWindow.h"
#include "GraphicsPoint.h"
#include "GraphicsPointFactory.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <qmath.h>
#include <QPen>
#include <QPushButton>
#include <QSettings>
#include <QSpacerItem>
#include <QSpinBox>
#include <QTransform>
#include "Settings.h"
#include "SettingsForGraph.h"
#include "Spline.h"
#include "SplinePair.h"
#include <vector>
#include "ViewPreview.h"

using namespace std;

const QString CONNECT_AS_FUNCTION_SMOOTH_STR ("Function - Smooth");
const QString CONNECT_AS_FUNCTION_STRAIGHT_STR ("Function - Straight");
const QString CONNECT_AS_RELATION_SMOOTH_STR ("Relation - Smooth");
const QString CONNECT_AS_RELATION_STRAIGHT_STR ("Relation - Straight");

const double PREVIEW_WIDTH = 100.0;
const double PREVIEW_HEIGHT = 100.0;
const int MINIMUM_HEIGHT = 500;

const QPointF POS_LEFT (PREVIEW_WIDTH / 3.0,
                        PREVIEW_HEIGHT * 2.0 / 3.0);
const QPointF POS_CENTER (PREVIEW_WIDTH / 2.0,
                          PREVIEW_HEIGHT / 3.0);
const QPointF POS_RIGHT (2.0 * PREVIEW_WIDTH / 3.0,
                         PREVIEW_HEIGHT * 2.0 / 3.0);

DlgSettingsCurveProperties::DlgSettingsCurveProperties(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Curve Properties"),
                           "DlgSettingsCurveProperties",
                           mainWindow),
  m_modelMainWindow (mainWindow.modelMainWindow()),
  m_scenePreview (nullptr),
  m_viewPreview (nullptr),
  m_modelCurveStylesBefore (nullptr),
  m_modelCurveStylesAfter (nullptr)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::DlgSettingsCurveProperties";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);

  setMinimumWidth (740); // Override finishPanel width for room for m_cmbLineType and preview to be completely visible
}

DlgSettingsCurveProperties::~DlgSettingsCurveProperties()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::~DlgSettingsCurveProperties";
}

void DlgSettingsCurveProperties::createCurveName (QGridLayout *layout,
                                                      int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::createCurveName";

  QLabel *labelCurveName = new QLabel (QString ("%1:").arg (tr ("Curve Name")));
  layout->addWidget (labelCurveName, row, 1);

  m_cmbCurveName = new QComboBox ();
  m_cmbCurveName->setWhatsThis (tr ("Name of the curve that is currently selected for editing"));
  connect (m_cmbCurveName, SIGNAL (activated (const QString &)), this, SLOT (slotCurveName (const QString &))); // activated() ignores code changes
  layout->addWidget (m_cmbCurveName, row++, 2);
}

void DlgSettingsCurveProperties::createLine (QGridLayout *layout,
                                             int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::createLine";

  m_groupLine = new QGroupBox (tr ("Line"));
  layout->addWidget (m_groupLine, row++, 2);

  QGridLayout *layoutGroup = new QGridLayout;
  m_groupLine->setLayout (layoutGroup);

  QLabel *labelLineWidth = new QLabel (QString ("%1:").arg (tr ("Width")));
  layoutGroup->addWidget (labelLineWidth, 0, 0);

  m_spinLineWidth = new QSpinBox (m_groupLine);
  m_spinLineWidth->setWhatsThis (tr ("Select a width for the lines drawn between points.\n\n"
                                     "This applies only to graph curves. No lines are ever drawn between axis points."));
  m_spinLineWidth->setMinimum(1);
  connect (m_spinLineWidth, SIGNAL (valueChanged (int)), this, SLOT (slotLineWidth (int)));
  layoutGroup->addWidget (m_spinLineWidth, 0, 1);

  QLabel *labelLineColor = new QLabel (QString ("%1:").arg (tr ("Color")));
  layoutGroup->addWidget (labelLineColor, 1, 0);

  m_cmbLineColor = new QComboBox (m_groupLine);
  m_cmbLineColor->setWhatsThis (tr ("Select a color for the lines drawn between points.\n\n"
                                    "This applies only to graph curves. No lines are ever drawn between axis points."));
  populateColorComboWithTransparent (*m_cmbLineColor);
  connect (m_cmbLineColor, SIGNAL (activated (const QString &)), this, SLOT (slotLineColor (const QString &))); // activated() ignores code changes
  layoutGroup->addWidget (m_cmbLineColor, 1, 1);

  QLabel *labelLineType = new QLabel (QString ("%1:").arg (tr ("Connect as")));
  layoutGroup->addWidget (labelLineType, 2, 0);

  m_cmbLineType = new QComboBox (m_groupLine);
  m_cmbLineType->addItem (CONNECT_AS_FUNCTION_STRAIGHT_STR, QVariant (CONNECT_AS_FUNCTION_STRAIGHT));
  m_cmbLineType->addItem (CONNECT_AS_FUNCTION_SMOOTH_STR, QVariant (CONNECT_AS_FUNCTION_SMOOTH));
  m_cmbLineType->addItem (CONNECT_AS_RELATION_STRAIGHT_STR, QVariant (CONNECT_AS_RELATION_STRAIGHT));
  m_cmbLineType->addItem (CONNECT_AS_RELATION_SMOOTH_STR, QVariant (CONNECT_AS_RELATION_SMOOTH));
  m_cmbLineType->setWhatsThis (tr ("Select rule for connecting points with lines.\n\n"
                                   "If the curve is connected as a single-valued function then the points are ordered by "
                                   "increasing value of the independent variable.\n\n"
                                   "If the curve is connected as a closed contour, then the points are ordered by age, except for "
                                   "points placed along an existing line. Any point placed on top of any existing line is inserted "
                                   "between the two endpoints of that line - as if its age was between the ages of the two "
                                   "endpoints.\n\n"
                                   "Lines are drawn between successively ordered points.\n\n"
                                   "Straight curves are drawn with straight lines between successive points. Smooth curves are drawn "
                                   "with smooth lines between successive points, using natural cubic splines of (x,y) pairs versus "
                                   "scalar ordinal (t) values.\n\n"
                                    "This applies only to graph curves. No lines are ever drawn between axis points."));
  connect (m_cmbLineType, SIGNAL (activated (const QString &)), this, SLOT (slotLineType (const QString &))); // activated() ignores code changes
  layoutGroup->addWidget (m_cmbLineType, 2, 1);
}

void DlgSettingsCurveProperties::createPoint (QGridLayout *layout,
                                              int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::createPoint";

  m_groupPoint = new QGroupBox (tr ("Point"));
  layout->addWidget (m_groupPoint, row++, 1);

  QGridLayout *layoutGroup = new QGridLayout;
  m_groupPoint->setLayout (layoutGroup);

  QLabel *labelPointShape = new QLabel(QString ("%1:").arg (tr ("Shape")));
  layoutGroup->addWidget (labelPointShape, 0, 0);

  m_cmbPointShape = new QComboBox (m_groupPoint);
  m_cmbPointShape->setWhatsThis (tr ("Select a shape for the points"));
  m_cmbPointShape->addItem (pointShapeToString (POINT_SHAPE_CIRCLE),
                            POINT_SHAPE_CIRCLE);
  m_cmbPointShape->addItem (pointShapeToString (POINT_SHAPE_CROSS),
                            POINT_SHAPE_CROSS);
  m_cmbPointShape->addItem (pointShapeToString (POINT_SHAPE_DIAMOND),
                            POINT_SHAPE_DIAMOND);
  m_cmbPointShape->addItem (pointShapeToString (POINT_SHAPE_HOURGLASS),
                            POINT_SHAPE_HOURGLASS);  
  m_cmbPointShape->addItem (pointShapeToString (POINT_SHAPE_SQUARE),
                            POINT_SHAPE_SQUARE);
  m_cmbPointShape->addItem (pointShapeToString (POINT_SHAPE_TRIANGLE),
                            POINT_SHAPE_TRIANGLE);
  m_cmbPointShape->addItem (pointShapeToString (POINT_SHAPE_TRIANGLE2),
                            POINT_SHAPE_TRIANGLE2);
  m_cmbPointShape->addItem (pointShapeToString (POINT_SHAPE_X),
                            POINT_SHAPE_X);
  connect (m_cmbPointShape, SIGNAL (activated (const QString &)), this, SLOT (slotPointShape (const QString &))); // activated() ignores code changes
  layoutGroup->addWidget (m_cmbPointShape, 0, 1);

  QLabel *labelPointRadius = new QLabel (QString ("%1:").arg (tr ("Radius")));
  layoutGroup->addWidget (labelPointRadius, 1, 0);

  m_spinPointRadius = new QSpinBox (m_groupPoint);
  m_spinPointRadius->setWhatsThis (tr ("Select a radius, in pixels, for the points"));
  m_spinPointRadius->setMinimum (1);
  connect (m_spinPointRadius, SIGNAL (valueChanged (int)), this, SLOT (slotPointRadius (int)));
  layoutGroup->addWidget (m_spinPointRadius, 1, 1);

  QLabel *labelPointLineWidth = new QLabel (QString ("%1:").arg (tr ("Line width")));
  layoutGroup->addWidget (labelPointLineWidth, 2, 0);

  m_spinPointLineWidth = new QSpinBox (m_groupPoint);
  m_spinPointLineWidth->setWhatsThis (tr ("Select a line width, in pixels, for the points.\n\n"
                                          "A larger width results in a thicker line, with the exception of a value of zero "
                                          "which always results in a line that is one pixel wide (which is easy to see even "
                                          "when zoomed far out)"));
  m_spinPointLineWidth->setMinimum (0);
  connect (m_spinPointLineWidth, SIGNAL (valueChanged (int)), this, SLOT (slotPointLineWidth (int)));
  layoutGroup->addWidget (m_spinPointLineWidth, 2, 1);

  QLabel *labelPointColor = new QLabel (QString ("%1:").arg (tr ("Color")));
  layoutGroup->addWidget (labelPointColor, 3, 0);

  m_cmbPointColor = new QComboBox (m_groupPoint);
  m_cmbPointColor->setWhatsThis (tr ("Select a color for the line used to draw the point shapes"));
  populateColorComboWithoutTransparent (*m_cmbPointColor);
  connect (m_cmbPointColor, SIGNAL (activated (const QString &)), this, SLOT (slotPointColor (const QString &))); // activated() ignores code changes
  layoutGroup->addWidget (m_cmbPointColor, 3, 1);
}

void DlgSettingsCurveProperties::createOptionalSaveDefault (QHBoxLayout *layout)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::createOptionalSaveDefault";

  m_btnSaveDefault = new QPushButton ("Save As Default");
  m_btnSaveDefault->setWhatsThis (tr ("Save the visible curve settings for use as future defaults, according to the curve name selection.\n\n"
                                      "If the visible settings are for the axes curve, then they will be used for future "
                                      "axes curves, until new settings are saved as the defaults.\n\n"
                                      "If the visible settings are for the Nth graph curve in the curve list, then they will be used for future "
                                      "graph curves that are also the Nth graph curve in their curve list, until new settings are saved as the defaults."));
  connect (m_btnSaveDefault, SIGNAL (released ()), this, SLOT (slotSaveDefault ()));
  layout->addWidget (m_btnSaveDefault, 0, Qt::AlignLeft);
}

void DlgSettingsCurveProperties::createPreview (QGridLayout *layout,
                                                int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::createPreview";

  QLabel *labelPreview = new QLabel (tr ("Preview"));
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview,
                                   ViewPreview::VIEW_ASPECT_RATIO_ONE_TO_ONE,
                                   this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the points and line of the selected curve.\n\n"
                                   "The X coordinate is in the horizontal direction, and the Y coordinate is in the vertical direction. A "
                                   "function can have only one Y value, at most, for any X value, but a relation can have multiple Y values "
                                   "for one X value."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);
  m_viewPreview->setRenderHint (QPainter::Antialiasing);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QWidget *DlgSettingsCurveProperties::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::createSubPanel";

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  int row = 0;
  createCurveName (layout, row);

  int rowLeft = row, rowRight = row++;
  createPoint (layout, rowLeft);
  createLine (layout, rowRight);
  createPreview (layout, row);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // Point group
  layout->setColumnStretch(2, 0); // Line group
  layout->setColumnStretch(3, 1); // Empty last column

  layout->setRowStretch (0, 1); // Expand empty first row

  return subPanel;
}

void DlgSettingsCurveProperties::drawLine (bool isRelation,
                                           const LineStyle &lineStyle)
{
  const double Z_LINE = -1.0; // Looks nicer if line goes under the points, so points are unobscured

  // Line between points. Start with function connection
  QPainterPath path;
  QPointF p0 (POS_LEFT), p1 (POS_CENTER), p2 (POS_RIGHT);
  if (isRelation) {

    // Relation connection
    p1 = POS_RIGHT;
    p2 = POS_CENTER;
  }

  // Draw straight or smooth
  if (lineStyle.curveConnectAs() == CONNECT_AS_FUNCTION_SMOOTH ||
      lineStyle.curveConnectAs() == CONNECT_AS_RELATION_SMOOTH) {

    vector<double> t;
    vector<SplinePair> xy;
    t.push_back(0);
    t.push_back(1);
    t.push_back(2);
    xy.push_back (SplinePair (p0.x(), p0.y()));
    xy.push_back (SplinePair (p1.x(), p1.y()));
    xy.push_back (SplinePair (p2.x(), p2.y()));
    Spline spline (t, xy);
    path.moveTo (p0);
    path.cubicTo (QPointF (spline.p1(0).x(),
                           spline.p1(0).y()),
                  QPointF (spline.p2(0).x(),
                           spline.p2(0).y()),
                  p1);
    path.cubicTo (QPointF (spline.p1(1).x(),
                           spline.p1(1).y()),
                  QPointF (spline.p2(1).x(),
                           spline.p2(1).y()),
                  p2);
  } else {
    path.moveTo (p0);
    path.lineTo (p1);
    path.lineTo (p2);
  }

  QGraphicsPathItem *line = new QGraphicsPathItem (path);
  line->setPen (QPen (QBrush (ColorPaletteToQColor (lineStyle.paletteColor())),
                      lineStyle.width()));
  line->setZValue (Z_LINE);
  m_scenePreview->addItem (line);
}

void DlgSettingsCurveProperties::drawPoints (const PointStyle &pointStyle)
{
  const QString NULL_IDENTIFIER;
  GeometryWindow *NULL_GEOMETRY_WINDOW = nullptr;

  GraphicsPointFactory pointFactory;

  // Left point
  GraphicsPoint *pointLeft = pointFactory.createPoint (*m_scenePreview,
                                                       NULL_IDENTIFIER,
                                                       POS_LEFT,
                                                       pointStyle,
                                                       NULL_GEOMETRY_WINDOW);
  pointLeft->setPointStyle (pointStyle);

  // Center point
  GraphicsPoint *pointCenter = pointFactory.createPoint (*m_scenePreview,
                                                         NULL_IDENTIFIER,
                                                         POS_CENTER,
                                                         pointStyle,
                                                         NULL_GEOMETRY_WINDOW);
  pointCenter->setPointStyle (pointStyle);

  // Right point
  GraphicsPoint *pointRight = pointFactory.createPoint (*m_scenePreview,
                                                        NULL_IDENTIFIER,
                                                        POS_RIGHT,
                                                        pointStyle,
                                                        NULL_GEOMETRY_WINDOW);
  pointRight->setPointStyle (pointStyle);
}

void DlgSettingsCurveProperties::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::handleOk";

  ENGAUGE_CHECK_PTR (m_modelCurveStylesBefore);
  ENGAUGE_CHECK_PTR (m_modelCurveStylesAfter);

  CmdSettingsCurveProperties *cmd = new CmdSettingsCurveProperties (mainWindow (),
                                                                    cmdMediator ().document(),
                                                                    *m_modelCurveStylesBefore,
                                                                    *m_modelCurveStylesAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsCurveProperties::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  delete m_modelCurveStylesBefore;
  delete m_modelCurveStylesAfter;

  // Save new data
  m_modelCurveStylesBefore = new CurveStyles (cmdMediator.coordSystem());
  m_modelCurveStylesAfter = new CurveStyles (cmdMediator.coordSystem());

  // Populate controls. First load curve name combobox. The curve-specific controls get loaded in slotCurveName
  m_cmbCurveName->clear ();
  m_cmbCurveName->addItem (AXIS_CURVE_NAME);
  QStringList curveNames = cmdMediator.curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin (); itr != curveNames.end (); itr++) {

    QString curveName = *itr;
    m_cmbCurveName->addItem (curveName);
  }

  loadForCurveName (mainWindow().selectedGraphCurve());

  m_isDirty = false;
  enableOk (false); // Disable Ok button since there not yet any changes
}

void DlgSettingsCurveProperties::loadForCurveName (const QString &curveName)
{
  int indexCurveName = m_cmbCurveName->findText(curveName);
  ENGAUGE_ASSERT (indexCurveName >= 0);
  m_cmbCurveName->setCurrentIndex(indexCurveName);

  int indexPointShape = m_cmbPointShape->findData (QVariant (m_modelCurveStylesAfter->pointShape (curveName)));
  ENGAUGE_ASSERT (indexPointShape >= 0);
  m_cmbPointShape->setCurrentIndex (indexPointShape);

  m_spinPointRadius->setValue (m_modelCurveStylesAfter->pointRadius(curveName));
  m_spinPointLineWidth->setValue (m_modelCurveStylesAfter->pointLineWidth(curveName));

  int indexPointColor = m_cmbPointColor->findData (QVariant (m_modelCurveStylesAfter->pointColor(curveName)));
  ENGAUGE_ASSERT (indexPointColor >= 0);
  m_cmbPointColor->setCurrentIndex (indexPointColor);

  int indexLineColor = m_cmbLineColor->findData (QVariant (m_modelCurveStylesAfter->lineColor(curveName)));
  ENGAUGE_ASSERT (indexLineColor >= 0);
  m_cmbLineColor->setCurrentIndex (indexLineColor);

  m_spinLineWidth->setValue (m_modelCurveStylesAfter->lineWidth(curveName));

  int indexCurveConnectAs = m_cmbLineType->findData (QVariant (m_modelCurveStylesAfter->lineConnectAs (curveName)));
  if (indexCurveConnectAs >= 0) {
    // Value is not CONNECT_SKIP_FOR_AXIS_CURVE
    m_cmbLineType->setCurrentIndex (indexCurveConnectAs);
  }

  // Disable line controls for axis curve since connecting with visible lines is better handled by Checker class
  m_cmbLineColor->setEnabled (curveName != AXIS_CURVE_NAME);
  m_spinLineWidth->setEnabled (curveName != AXIS_CURVE_NAME);
  m_cmbLineType->setEnabled (curveName != AXIS_CURVE_NAME);

  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::resetSceneRectangle ()
{

  QRect rect (0,
              0,
              qFloor (PREVIEW_WIDTH),
              qFloor (PREVIEW_HEIGHT));

  QGraphicsRectItem *itemPerimeter = new QGraphicsRectItem(rect);
  itemPerimeter->setVisible(false);
  m_scenePreview->addItem (itemPerimeter);
  m_viewPreview->centerOn (QPointF (0.0, 0.0));
}

void DlgSettingsCurveProperties::setCurveName (const QString &curveName)
{
  m_cmbCurveName->setCurrentText (curveName);
  loadForCurveName (curveName);
}

void DlgSettingsCurveProperties::setSmallDialogs(bool smallDialogs)
{
  if (!smallDialogs) {
    setMinimumHeight (MINIMUM_HEIGHT);
  }
}

void DlgSettingsCurveProperties::slotCurveName(const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotCurveName";

  // Dirty flag is not set when simply changing to new curve

  // Do nothing if combobox is getting cleared, or load has not been called yet
  if (!curveName.isEmpty () && (m_modelCurveStylesAfter != nullptr)) {

    loadForCurveName (curveName);
  }
}

void DlgSettingsCurveProperties::slotLineColor(const QString &lineColor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineColor color=" << lineColor.toLatin1().data();

  m_isDirty = true;

  m_modelCurveStylesAfter->setLineColor(m_cmbCurveName->currentText(),
                                        static_cast<ColorPalette> (m_cmbLineColor->currentData().toInt()));
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotLineWidth(int width)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineWidth width=" << width;

  m_isDirty = true;

  m_modelCurveStylesAfter->setLineWidth(m_cmbCurveName->currentText(),
                                        width);
  updateControls ();
  updatePreview();
}

void DlgSettingsCurveProperties::slotLineType(const QString &lineType)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineType lineType=" << lineType.toLatin1().data();

  m_isDirty = true;

  m_modelCurveStylesAfter->setLineConnectAs(m_cmbCurveName->currentText(),
                                            static_cast<CurveConnectAs> (m_cmbLineType->currentData().toInt ()));
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotPointColor(const QString &pointColor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointColor pointColor=" << pointColor.toLatin1().data();

  m_isDirty = true;

  m_modelCurveStylesAfter->setPointColor(m_cmbCurveName->currentText(),
                                         static_cast<ColorPalette> (m_cmbPointColor->currentData().toInt ()));
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotPointLineWidth(int lineWidth)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointLineWidth lineWidth=" << lineWidth;

  m_isDirty = true;

  m_modelCurveStylesAfter->setPointLineWidth(m_cmbCurveName->currentText(),
                                             lineWidth);
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotPointRadius(int radius)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointRadius radius=" << radius;

  m_isDirty = true;

  m_modelCurveStylesAfter->setPointRadius(m_cmbCurveName->currentText(),
                                          radius);
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotPointShape(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointShape";

  m_isDirty = true;

  m_modelCurveStylesAfter->setPointShape(m_cmbCurveName->currentText(),
                                         static_cast<PointShape> (m_cmbPointShape->currentData().toInt ()));
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotSaveDefault()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotSaveDefault";

  QString curve = m_cmbCurveName->currentText ();

  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  if (curve == AXIS_CURVE_NAME) {

    settings.beginGroup (SETTINGS_GROUP_CURVE_AXES);

  } else {

    SettingsForGraph settingsForGraph;
    QString groupName = settingsForGraph.groupNameForNthCurve(m_cmbCurveName->currentIndex());
    settings.beginGroup (groupName);

  }

  settings.setValue (SETTINGS_CURVE_POINT_SHAPE,
                     m_modelCurveStylesAfter->pointShape(curve));
  settings.setValue (SETTINGS_CURVE_LINE_COLOR,
                     m_modelCurveStylesAfter->lineColor(curve));
  settings.setValue (SETTINGS_CURVE_LINE_CONNECT_AS,
                     m_modelCurveStylesAfter->lineConnectAs(curve));
  settings.setValue (SETTINGS_CURVE_LINE_WIDTH,
                     m_modelCurveStylesAfter->lineWidth(curve));
  settings.setValue (SETTINGS_CURVE_POINT_COLOR,
                     m_modelCurveStylesAfter->pointColor (curve));
  settings.setValue (SETTINGS_CURVE_POINT_LINE_WIDTH,
                     m_modelCurveStylesAfter->pointLineWidth(curve));
  settings.setValue (SETTINGS_CURVE_POINT_RADIUS,
                     m_modelCurveStylesAfter->pointRadius(curve));
  settings.endGroup ();
}

void DlgSettingsCurveProperties::updateControls()
{
  bool isGoodState = !m_spinPointRadius->text().isEmpty () &&
                     !m_spinPointLineWidth->text().isEmpty () &&
                     !m_spinLineWidth->text().isEmpty ();
  m_cmbCurveName->setEnabled (isGoodState); // User needs to fix state before switching curves
  enableOk (isGoodState && m_isDirty);
}

void DlgSettingsCurveProperties::updatePreview()
{
  m_scenePreview->clear();

  QString currentCurve = m_cmbCurveName->currentText();

  const PointStyle pointStyle = m_modelCurveStylesAfter->curveStyle (currentCurve).pointStyle();
  const LineStyle lineStyle = m_modelCurveStylesAfter->curveStyle (currentCurve).lineStyle();

  // Function or relation?
  bool isRelation = (lineStyle.curveConnectAs() == CONNECT_AS_RELATION_SMOOTH ||
                     lineStyle.curveConnectAs() == CONNECT_AS_RELATION_STRAIGHT);

  drawPoints (pointStyle);
  drawLine (isRelation,
            lineStyle);

  resetSceneRectangle();
}
