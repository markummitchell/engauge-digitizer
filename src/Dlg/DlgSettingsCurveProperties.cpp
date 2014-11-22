#include "CmdMediator.h"
#include "DlgSettingsCurveProperties.h"
#include "Logger.h"
#include <QComboBox>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include "ViewPreview.h"

DlgSettingsCurveProperties::DlgSettingsCurveProperties(QWidget *parent) :
  DlgSettingsAbstractBase ("Curve Properties", parent)
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
  connect (m_cmbPointShape, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotPointShape (const QString &)));
  layoutGroup->addWidget (m_cmbPointShape, 0, 1);

  QLabel *labelPointSize = new QLabel ("Size:");
  layoutGroup->addWidget (labelPointSize, 1, 0);

  m_cmbPointSize = new QComboBox (m_groupPoint);
  m_cmbPointSize->setWhatsThis (tr ("Select an overall size for the points"));
  connect (m_cmbPointSize, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotPointSize (const QString &)));
  layoutGroup->addWidget (m_cmbPointSize, 1, 1);

  QLabel *labelPointLineSize = new QLabel ("Line Size:");
  layoutGroup->addWidget (labelPointLineSize, 2, 0);

  m_cmbPointLineSize = new QComboBox (m_groupPoint);
  m_cmbPointLineSize->setWhatsThis (tr ("Select a size for the line used to draw the point shapes"));
  connect (m_cmbPointLineSize, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotPointLineSize (const QString &)));
  layoutGroup->addWidget (m_cmbPointLineSize, 2, 1);

  QLabel *labelPointLineColor = new QLabel ("Line Color:");
  layoutGroup->addWidget (labelPointLineColor, 3, 0);

  m_cmbPointLineColor = new QComboBox (m_groupPoint);
  m_cmbPointLineColor->setWhatsThis (tr ("Select a color for the line used to draw the point shapes"));
  connect (m_cmbPointLineColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotPointLineColor (const QString &)));
  layoutGroup->addWidget (m_cmbPointLineColor, 3, 1);

  QLabel *labelPointInteriorColor = new QLabel ("Interior Color:");
  layoutGroup->addWidget (labelPointInteriorColor, 4, 0);

  m_cmbPointInteriorColor = new QComboBox (m_groupPoint);
  m_cmbPointInteriorColor->setWhatsThis (tr ("Select a color for the interior of the point shapes"));
  connect (m_cmbPointInteriorColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotPointInteriorColor (const QString &)));
  layoutGroup->addWidget (m_cmbPointInteriorColor, 4, 1);
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

void DlgSettingsCurveProperties::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::load";

  setCmdMediator (cmdMediator);
}

void DlgSettingsCurveProperties::slotLineColor(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineColor";
}

void DlgSettingsCurveProperties::slotLineSize(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineSize";
}

void DlgSettingsCurveProperties::slotLineType(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotLineType";
}

void DlgSettingsCurveProperties::slotPointLineColor(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointLineColor";
}

void DlgSettingsCurveProperties::slotPointLineSize(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointLineSize";
}

void DlgSettingsCurveProperties::slotPointInteriorColor(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointInteriorColor";
}

void DlgSettingsCurveProperties::slotPointShape(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointShape";
}

void DlgSettingsCurveProperties::slotPointSize(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveProperties::slotPointSize";
}
