#include "CmdMediator.h"
#include "CmdSettingsCurveProperties.h"
#include "ColorPalette.h"
#include "DlgSettingsCurveProperties.h"
#include "DlgSpinBoxDouble.h"
#include "DlgSpinBoxInt.h"
#include "EnumsToQt.h"
#include "GraphicsPoint.h"
#include "GraphicsPointFactory.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QComboBox>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPen>
#include <QPushButton>
#include <QTransform>
#include "ViewPreview.h"

const QString CONNECT_AS_FUNCTION_STR ("Function");
const QString CONNECT_AS_RELATION_STR ("Relation");

const double PREVIEW_WIDTH = 100.0;
const double PREVIEW_HEIGHT = 100.0;

DlgSettingsCurveProperties::DlgSettingsCurveProperties(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Curve Properties",
                           "DlgSettingsCurveProperties",
                           mainWindow),
  m_scenePreview (0),
  m_viewPreview (0),
  m_modelCurvePropertiesBefore (0),
  m_modelCurvePropertiesAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsCurveProperties::createCurveName (QGridLayout *layout,
                                                      int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::createCurveName";

  QLabel *labelCurveName = new QLabel ("Curve Name:");
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

  m_groupLine = new QGroupBox ("Line");
  layout->addWidget (m_groupLine, row++, 2);

  QGridLayout *layoutGroup = new QGridLayout;
  m_groupLine->setLayout (layoutGroup);

  QLabel *labelLineWidth = new QLabel ("Width:");
  layoutGroup->addWidget (labelLineWidth, 0, 0);

  m_spinLineWidth = new DlgSpinBoxInt (m_groupLine);
  m_spinLineWidth->setWhatsThis (tr ("Select a width for the lines drawn between points"));
  m_spinLineWidth->setMinimum(1);
  connect (m_spinLineWidth, SIGNAL (textChanged (const QString &)), this, SLOT (slotLineWidth (const QString &)));
  layoutGroup->addWidget (m_spinLineWidth, 0, 1);

  QLabel *labelLineColor = new QLabel ("Color:");
  layoutGroup->addWidget (labelLineColor, 1, 0);

  m_cmbLineColor = new QComboBox (m_groupLine);
  m_cmbLineColor->setWhatsThis (tr ("Select a color for the lines drawn between points"));
  populateColorComboWithTransparent (*m_cmbLineColor);
  connect (m_cmbLineColor, SIGNAL (activated (const QString &)), this, SLOT (slotLineColor (const QString &))); // activated() ignores code changes
  layoutGroup->addWidget (m_cmbLineColor, 1, 1);

  QLabel *labelLineType = new QLabel ("Connect as:");
  layoutGroup->addWidget (labelLineType, 2, 0);

  m_cmbLineType = new QComboBox (m_groupLine);
  m_cmbLineType->addItem (CONNECT_AS_FUNCTION_STR, QVariant (CONNECT_AS_FUNCTION));
  m_cmbLineType->addItem (CONNECT_AS_RELATION_STR, QVariant (CONNECT_AS_RELATION));
  m_cmbLineType->setWhatsThis (tr ("Select rule for connecting points with lines.\n\n"
                                   "If the curve is connected as a single-valued function then the points are ordered by "
                                   "increasing value of the independent variable.\n\n"
                                   "If the curve is connected as a closed contour, then the points are ordered by age, except for "
                                   "points placed along an existing line. Any point placed on top of any existing line is inserted "
                                   "between the two endpoints of that line - as if its age was between the ages of the two "
                                   "endpoints.\n\n"
                                   "Lines are drawn between successively ordered points"));
  connect (m_cmbLineType, SIGNAL (activated (const QString &)), this, SLOT (slotLineType (const QString &))); // activated() ignores code changes
  layoutGroup->addWidget (m_cmbLineType, 2, 1);
}

void DlgSettingsCurveProperties::createPoint (QGridLayout *layout,
                                              int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::createPoint";

  m_groupPoint = new QGroupBox ("Point");
  layout->addWidget (m_groupPoint, row++, 1);

  QGridLayout *layoutGroup = new QGridLayout;
  m_groupPoint->setLayout (layoutGroup);

  QLabel *labelPointShape = new QLabel("Shape:");
  layoutGroup->addWidget (labelPointShape, 0, 0);

  m_cmbPointShape = new QComboBox (m_groupPoint);
  m_cmbPointShape->setWhatsThis (tr ("Select a shape for the points"));
  m_cmbPointShape->addItem ("Circle", POINT_SHAPE_CIRCLE);
  m_cmbPointShape->addItem ("Cross", POINT_SHAPE_CROSS);
  m_cmbPointShape->addItem ("Diamond", POINT_SHAPE_DIAMOND);
  m_cmbPointShape->addItem ("Square", POINT_SHAPE_SQUARE);
  m_cmbPointShape->addItem ("Triangle", POINT_SHAPE_TRIANGLE);
  m_cmbPointShape->addItem ("X", POINT_SHAPE_X);
  connect (m_cmbPointShape, SIGNAL (activated (const QString &)), this, SLOT (slotPointShape (const QString &))); // activated() ignores code changes
  layoutGroup->addWidget (m_cmbPointShape, 0, 1);

  QLabel *labelPointRadius = new QLabel ("Radius:");
  layoutGroup->addWidget (labelPointRadius, 1, 0);

  m_spinPointRadius = new DlgSpinBoxInt (m_groupPoint);
  m_spinPointRadius->setWhatsThis (tr ("Select a radius for the points"));
  m_spinPointRadius->setMinimum (1);
  connect (m_spinPointRadius, SIGNAL (textChanged (const QString &)), this, SLOT (slotPointRadius (const QString &)));
  layoutGroup->addWidget (m_spinPointRadius, 1, 1);

  QLabel *labelPointLineWidth = new QLabel ("Line width:");
  layoutGroup->addWidget (labelPointLineWidth, 2, 0);

  m_spinPointLineWidth = new DlgSpinBoxDouble (m_groupPoint);
  m_spinPointLineWidth->setWhatsThis (tr ("Select a line width for the points.\n\n"
                                          "A larger width results in a thicker line, with the exception of a value of zero "
                                          "which always results in a line that is one pixel wide (which is easy to see even "
                                          "when zoomed far out)"));
  m_spinPointLineWidth->setMinimum (0);
  m_spinPointLineWidth->setSingleStep (0.1);
  m_spinPointLineWidth->setDecimals (1);
  connect (m_spinPointLineWidth, SIGNAL (textChanged (const QString &)), this, SLOT (slotPointLineWidth (const QString &)));
  layoutGroup->addWidget (m_spinPointLineWidth, 2, 1);

  QLabel *labelPointColor = new QLabel ("Color:");
  layoutGroup->addWidget (labelPointColor, 3, 0);

  m_cmbPointColor = new QComboBox (m_groupPoint);
  m_cmbPointColor->setWhatsThis (tr ("Select a color for the line used to draw the point shapes"));
  populateColorComboWithoutTransparent (*m_cmbPointColor);
  connect (m_cmbPointColor, SIGNAL (activated (const QString &)), this, SLOT (slotPointColor (const QString &))); // activated() ignores code changes
  layoutGroup->addWidget (m_cmbPointColor, 3, 1);
}

void DlgSettingsCurveProperties::createPreview (QGridLayout *layout,
                                                       int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::createPreview";

  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview, this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the points and line of the selected curve."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

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

  int rowLeft = row, rowRight = row;
  createPoint (layout, rowLeft);
  createLine (layout, rowRight);

  row = qMax (rowLeft, rowRight);
  createPreview (layout, row);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // Point group
  layout->setColumnStretch(2, 0); // Line group
  layout->setColumnStretch(3, 1); // Empty last column

  layout->setRowStretch (0, 1); // Expand empty first row

  return subPanel;
}

void DlgSettingsCurveProperties::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::handleOk";

  Q_CHECK_PTR (m_modelCurvePropertiesBefore);
  Q_CHECK_PTR (m_modelCurvePropertiesAfter);

  CmdSettingsCurveProperties *cmd = new CmdSettingsCurveProperties (mainWindow (),
                                                                    cmdMediator ().document(),
                                                                    *m_modelCurvePropertiesBefore,
                                                                    *m_modelCurvePropertiesAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsCurveProperties::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelCurvePropertiesBefore != 0) {
    delete m_modelCurvePropertiesBefore;
  }
  if (m_modelCurvePropertiesAfter != 0) {
    delete m_modelCurvePropertiesAfter;
  }

  // Save new data
  m_modelCurvePropertiesBefore = new DocumentModelCurveProperties (cmdMediator.document());
  m_modelCurvePropertiesAfter = new DocumentModelCurveProperties (cmdMediator.document());

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

  enableOk (false); // Disable Ok button since there not yet any changes
}

void DlgSettingsCurveProperties::loadForCurveName (const QString &curveName)
{
  int indexCurveName = m_cmbCurveName->findText(curveName);
  Q_ASSERT (indexCurveName >= 0);
  m_cmbCurveName->setCurrentIndex(indexCurveName);

  int indexPointShape = m_cmbPointShape->findData (QVariant (m_modelCurvePropertiesAfter->pointShape (curveName)));
  Q_ASSERT (indexPointShape >= 0);
  m_cmbPointShape->setCurrentIndex (indexPointShape);

  m_spinPointRadius->setValue (m_modelCurvePropertiesAfter->pointRadius(curveName));
  m_spinPointLineWidth->setValue (m_modelCurvePropertiesAfter->pointLineWidth(curveName));

  int indexPointColor = m_cmbPointColor->findData (QVariant (m_modelCurvePropertiesAfter->pointColor(curveName)));
  Q_ASSERT (indexPointColor >= 0);
  m_cmbPointColor->setCurrentIndex (indexPointColor);

  int indexLineColor = m_cmbLineColor->findData (QVariant (m_modelCurvePropertiesAfter->lineColor(curveName)));
  Q_ASSERT (indexLineColor >= 0);
  m_cmbLineColor->setCurrentIndex (indexLineColor);

  m_spinLineWidth->setValue (m_modelCurvePropertiesAfter->lineWidth(curveName));

  int indexCurveConnectAs = m_cmbLineType->findData (QVariant (m_modelCurvePropertiesAfter->lineConnectAs (curveName)));
  Q_ASSERT (indexCurveConnectAs >= 0);
  m_cmbLineType->setCurrentIndex (indexCurveConnectAs);

  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::resetSceneRectangle () {

  QRect rect (0.0,
              0.0,
              PREVIEW_WIDTH,
              PREVIEW_HEIGHT);

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

void DlgSettingsCurveProperties::slotCurveName(const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotCurveName";

  // Do nothing if combobox is getting cleared, or load has not been called yet
  if (!curveName.isEmpty () && (m_modelCurvePropertiesAfter != 0)) {

    loadForCurveName (curveName);
  }
}

void DlgSettingsCurveProperties::slotLineColor(const QString & /* lineColor */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineColor";

  m_modelCurvePropertiesAfter->setLineColor(m_cmbCurveName->currentText(),
                                            (ColorPalette) m_cmbLineColor->currentData().toInt());
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotLineWidth(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineWidth";

  m_modelCurvePropertiesAfter->setLineWidth(m_cmbCurveName->currentText(),
                                            m_spinLineWidth->text().toDouble());
  updateControls ();
  updatePreview();
}

void DlgSettingsCurveProperties::slotLineType(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineType";

  m_modelCurvePropertiesAfter->setLineConnectAs(m_cmbCurveName->currentText(),
                                                (CurveConnectAs) m_cmbLineType->currentData().toInt ());
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotPointColor(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointColor";

  m_modelCurvePropertiesAfter->setPointColor(m_cmbCurveName->currentText(),
                                             (ColorPalette) m_cmbPointColor->currentData().toInt ());
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotPointLineWidth(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointLineWidth";

  m_modelCurvePropertiesAfter->setPointLineWidth(m_cmbCurveName->currentText(),
                                                 m_spinPointLineWidth->text().toDouble());
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotPointRadius(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointRadius";

  m_modelCurvePropertiesAfter->setPointRadius(m_cmbCurveName->currentText(),
                                              m_spinPointRadius->text().toInt());
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::slotPointShape(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointShape";

  m_modelCurvePropertiesAfter->setPointShape(m_cmbCurveName->currentText(),
                                             (PointShape) m_cmbPointShape->currentData().toInt ());
  updateControls();
  updatePreview();
}

void DlgSettingsCurveProperties::updateControls()
{
  bool isGoodState = !m_spinPointRadius->text().isEmpty () &&
                     !m_spinPointLineWidth->text().isEmpty () &&
                     !m_spinLineWidth->text().isEmpty ();
  m_cmbCurveName->setEnabled (isGoodState); // User needs to fix state before switching curves
  enableOk (isGoodState);
}

void DlgSettingsCurveProperties::updatePreview()
{
  const QString NULL_IDENTIFIER;
  const int ORDINAL_0 = 0, ORDINAL_1 = 1;

  m_scenePreview->clear();

  QString currentCurve = m_cmbCurveName->currentText();

  GraphicsPointFactory pointFactory;
  const PointStyle pointStyle = m_modelCurvePropertiesAfter->pointStyle (currentCurve);

  // Left point
  QPointF posLeft (PREVIEW_WIDTH / 3.0,
                   PREVIEW_HEIGHT / 2.0);
  pointFactory.createPoint (*m_scenePreview,
                            NULL_IDENTIFIER,
                            posLeft,
                            pointStyle,
                            ORDINAL_0);

  // Right point
  QPointF posRight (2.0 * PREVIEW_WIDTH / 3.0,
                    PREVIEW_HEIGHT / 2.0);
  pointFactory.createPoint (*m_scenePreview,
                            NULL_IDENTIFIER,
                            posRight,
                            pointStyle,
                            ORDINAL_1);

  // Line between points
  QGraphicsLineItem *itemLine = new QGraphicsLineItem (posLeft.x(),
                                                       posLeft.y(),
                                                       posRight.x(),
                                                       posRight.y());
  itemLine->setPen (QPen (QBrush (ColorPaletteToQColor (m_modelCurvePropertiesAfter->lineColor (currentCurve))),
                    m_modelCurvePropertiesAfter->lineWidth(currentCurve)));
  itemLine->setZValue (-1.0);
  m_scenePreview->addItem (itemLine);

  resetSceneRectangle();
}
