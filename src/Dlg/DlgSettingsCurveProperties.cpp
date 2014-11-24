#include "CmdMediator.h"
#include "CmdSettingsCurveProperties.h"
#include "ColorPalette.h"
#include "DlgSettingsCurveProperties.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QComboBox>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include "ViewPreview.h"

DlgSettingsCurveProperties::DlgSettingsCurveProperties(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Curve Properties", mainWindow),
  m_modelCurveProperties (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsCurveProperties::createCurveName (QGridLayout *layout,
                                                      int &row)
{
  QLabel *labelCurveName = new QLabel ("Curve Name:");
  layout->addWidget (labelCurveName, row, 1);

  m_cmbCurveName = new QComboBox ();
  m_cmbCurveName->setWhatsThis (tr ("Name of the curve that is currently selected for editing"));
  connect (m_cmbCurveName, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotCurveName (const QString &)));
  layout->addWidget (m_cmbCurveName, row++, 2);
}

void DlgSettingsCurveProperties::createLine (QGridLayout *layout,
                                                 int &row)
{
  m_groupLine = new QGroupBox ("Line");
  layout->addWidget (m_groupLine, row++, 2);

  QGridLayout *layoutGroup = new QGridLayout;
  m_groupLine->setLayout (layoutGroup);

  QLabel *labelLineSize = new QLabel ("Size:");
  layoutGroup->addWidget (labelLineSize, 0, 0);

  m_cmbLineSize = new QComboBox (m_groupLine);
  m_cmbLineSize->setWhatsThis (tr ("Select a size for the lines drawn between points"));
  connect (m_cmbLineSize, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotLineSize (const QString &)));
  layoutGroup->addWidget (m_cmbLineSize, 0, 1);

  QLabel *labelLineColor = new QLabel ("Color:");
  layoutGroup->addWidget (labelLineColor, 1, 0);

  m_cmbLineColor = new QComboBox (m_groupLine);
  m_cmbLineColor->setWhatsThis (tr ("Select a color for the lines drawn between points"));
  m_cmbLineColor->addItem ("Blue", QVariant (COLOR_PALETTE_BLUE));
  m_cmbLineColor->addItem ("Red", QVariant (COLOR_PALETTE_RED));
  m_cmbLineColor->addItem ("Black", QVariant (COLOR_PALETTE_BLACK));
  m_cmbLineColor->addItem ("Cyan", QVariant (COLOR_PALETTE_CYAN));
  m_cmbLineColor->addItem ("Gold", QVariant (COLOR_PALETTE_GOLD));
  m_cmbLineColor->addItem ("Green", QVariant (COLOR_PALETTE_GREEN));
  m_cmbLineColor->addItem ("Magenta", QVariant (COLOR_PALETTE_MAGENTA));
  m_cmbLineColor->addItem ("Red", QVariant (COLOR_PALETTE_RED));
  m_cmbLineColor->addItem ("Yellow", QVariant (COLOR_PALETTE_YELLOW));
  m_cmbLineColor->addItem ("Transparent", QVariant (COLOR_PALETTE_TRANSPARENT));
  connect (m_cmbLineColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotLineColor (const QString &)));
  layoutGroup->addWidget (m_cmbLineColor, 1, 1);

  QLabel *labelLineType = new QLabel ("Connect as:");
  layoutGroup->addWidget (labelLineType, 2, 0);

  m_cmbLineType = new QComboBox (m_groupLine);
  m_cmbLineType->setWhatsThis (tr ("Select rule for connecting points with lines.\n\n"
                                   "If the curve is connected as a single-valued function then the points are ordered by "
                                   "increasing value of the independent variable.\n\n"
                                   "If the curve is connected as a closed contour, then the points are ordered by age, except for "
                                   "points placed along an existing line. Any point placed on top of any existing line is inserted "
                                   "between the two endpoints of that line - as if its age was between the ages of the two "
                                   "endpoints.\n\n"
                                   "Lines are drawn between successively ordered points"));
  connect (m_cmbLineType, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotLineType (const QString &)));
  layoutGroup->addWidget (m_cmbLineType, 2, 1);
}

void DlgSettingsCurveProperties::createPoint (QGridLayout *layout,
                                                  int &row)
{
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
  connect (m_cmbPointShape, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotPointShape (const QString &)));
  layoutGroup->addWidget (m_cmbPointShape, 0, 1);

  QLabel *labelPointSize = new QLabel ("Size:");
  layoutGroup->addWidget (labelPointSize, 1, 0);

  m_cmbPointSize = new QComboBox (m_groupPoint);
  m_cmbPointSize->setWhatsThis (tr ("Select an overall size for the points"));
  connect (m_cmbPointSize, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotPointSize (const QString &)));
  layoutGroup->addWidget (m_cmbPointSize, 1, 1);

  QLabel *labelPointColor = new QLabel ("Color:");
  layoutGroup->addWidget (labelPointColor, 2, 0);

  m_cmbPointColor = new QComboBox (m_groupPoint);
  m_cmbPointColor->setWhatsThis (tr ("Select a color for the line used to draw the point shapes"));
  m_cmbPointColor->addItem ("Blue", QVariant (COLOR_PALETTE_BLUE));
  m_cmbPointColor->addItem ("Red", QVariant (COLOR_PALETTE_RED));
  m_cmbPointColor->addItem ("Black", QVariant (COLOR_PALETTE_BLACK));
  m_cmbPointColor->addItem ("Cyan", QVariant (COLOR_PALETTE_CYAN));
  m_cmbPointColor->addItem ("Gold", QVariant (COLOR_PALETTE_GOLD));
  m_cmbPointColor->addItem ("Green", QVariant (COLOR_PALETTE_GREEN));
  m_cmbPointColor->addItem ("Magenta", QVariant (COLOR_PALETTE_MAGENTA));
  m_cmbPointColor->addItem ("Red", QVariant (COLOR_PALETTE_RED));
  m_cmbPointColor->addItem ("Yellow", QVariant (COLOR_PALETTE_YELLOW));
  connect (m_cmbPointColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotPointLineColor (const QString &)));
  layoutGroup->addWidget (m_cmbPointColor, 2, 1);
}

void DlgSettingsCurveProperties::createPreview (QGridLayout *layout,
                                                       int &row)
{
  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0);

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

  Q_ASSERT (m_modelCurveProperties != 0);
  CmdSettingsCurveProperties *cmd = new CmdSettingsCurveProperties (mainWindow (),
                                                                    cmdMediator ().document(),
                                                                    *m_modelCurveProperties);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsCurveProperties::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::load";

  setCmdMediator (cmdMediator);

  // Load curve name combobox
  m_cmbCurveName->clear ();
  m_cmbCurveName->addItem (AXIS_CURVE_NAME);
  QStringList curveNames = cmdMediator.curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin (); itr != curveNames.end (); itr++) {

    QString curveName = *itr;
    m_cmbCurveName->addItem (curveName);
  }

  m_modelCurveProperties = new DlgModelCurveProperties (cmdMediator);
}

void DlgSettingsCurveProperties::slotCurveName(const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotCurveName";

  // Do nothing if combobox is getting cleared, or load has not been called yet
  if (!curveName.isEmpty () && (m_modelCurveProperties != 0)) {

    LineStyle lineStyle = m_modelCurveProperties->lineStyleForCurveName (curveName);
    PointStyle pointStyle = m_modelCurveProperties->pointStyleForCurveName (curveName);

    int indexPointShape = m_cmbPointShape->findData (QVariant (pointStyle.pointShape ()));
    m_cmbPointShape->setCurrentIndex (indexPointShape);

    int indexPointColor = m_cmbPointColor->findData (QVariant (pointStyle.paletteColor()));
    m_cmbPointColor->setCurrentIndex (indexPointColor);

    int indexLineColor = m_cmbLineColor->findData (QVariant (lineStyle.paletteColor()));
    m_cmbLineColor->setCurrentIndex (indexLineColor);
  }
}

void DlgSettingsCurveProperties::setCurveName (const QString &curveName)
{
  m_cmbCurveName->setCurrentText (curveName);
}

void DlgSettingsCurveProperties::slotLineColor(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineColor";

  enableOk (true);
}

void DlgSettingsCurveProperties::slotLineSize(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineSize";

  enableOk (true);
}

void DlgSettingsCurveProperties::slotLineType(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineType";

  enableOk (true);
}

void DlgSettingsCurveProperties::slotPointColor(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointColor";

  enableOk (true);
}

void DlgSettingsCurveProperties::slotPointShape(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointShape";

  enableOk (true);
}

void DlgSettingsCurveProperties::slotPointSize(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointSize";

  enableOk (true);
}
