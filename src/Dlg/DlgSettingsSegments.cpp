#include "CmdMediator.h"
#include "CmdSettingsSegments.h"
#include "DlgSettingsSegments.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCheckBox>
#include <QComboBox>
#include <QIntValidator>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include "ViewPreview.h"

const int LINE_SIZE_MIN = 1;
const int LINE_SIZE_MAX = 10000;
const int MIN_LENGTH_MIN = 1;
const int MIN_LENGTH_MAX = 10000;
const int POINT_SEPARATION_MIN = 1;
const int POINT_SEPARATION_MAX = 10000;

DlgSettingsSegments::DlgSettingsSegments(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Segments", mainWindow),
  m_modelSegmentsBefore (0),
  m_modelSegmentsAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsSegments::createControls (QGridLayout *layout,
                                          int &row)
{
  QLabel *labelMinLength = new QLabel("Minimum length:");
  layout->addWidget(labelMinLength, row, 1);

  m_editMinLength = new QLineEdit;
  m_editMinLength->setWhatsThis (tr ("Select a minimum number of points in a segment.\n\n"
                                     "Only segments with more points will be created.\n\n"
                                     "This value should be as large as possible to reduce memory usage. This value has "
                                     "a lower limit"));
  m_editMinLength->setValidator (new QIntValidator (MIN_LENGTH_MIN, MIN_LENGTH_MAX));
  connect (m_editMinLength, SIGNAL (textChanged (const QString &)), this, SLOT (slotMinLength (const QString &)));
  layout->addWidget(m_editMinLength, row++, 2);

  QLabel *labelPointSeparation = new QLabel("Point separation:");
  layout->addWidget (labelPointSeparation, row, 1);

  m_editPointSeparation = new QLineEdit;
  m_editPointSeparation->setWhatsThis (tr ("Select a point separation in pixels.\n\n"
                                           "Successive points added to a segment will be separated by this number of pixels. "
                                           "If Fill Corners is enabled, then additional points will be inserted at corners so some points "
                                           "will be closer.\n\n"
                                           "This value has a lower limit"));
  m_editPointSeparation->setValidator (new QIntValidator (POINT_SEPARATION_MIN, POINT_SEPARATION_MAX));
  connect (m_editPointSeparation, SIGNAL (textChanged (const QString &)), this, SLOT (slotPointSeparation (const QString &)));
  layout->addWidget (m_editPointSeparation, row++, 2);

  QLabel *labelFillCorners = new QLabel ("Fill corners:");
  layout->addWidget (labelFillCorners, row, 1);

  m_chkFillCorners = new QCheckBox;
  m_chkFillCorners->setWhatsThis (tr ("Fill corners.\n\n"
                                      "In addition to the points placed at regular intervals, this option causes a point to be "
                                      "placed at each corner. This option can capture important information in piecewise linear graphs, "
                                      "but gradually curving graphs may not benefit from the additional points"));
  connect (m_chkFillCorners, SIGNAL (stateChanged (int)), this, SLOT (slotFillCorners (int)));
  layout->addWidget (m_chkFillCorners, row++, 2);

  QLabel *labelLineSize = new QLabel("Line size:");
  layout->addWidget (labelLineSize, row, 1);

  m_spinLineSize = new QSpinBox;
  m_spinLineSize->setWhatsThis (tr ("Select a size for the lines drawn along a segment"));
  m_spinLineSize->setMinimum(1);
  connect (m_spinLineSize, SIGNAL (valueChanged (int)), this, SLOT (slotLineSize (int)));
  layout->addWidget (m_spinLineSize, row++, 2);

  QLabel *labelLineColor = new QLabel("Line color:");
  layout->addWidget (labelLineColor, row, 1);

  m_cmbLineColor = new QComboBox;
  m_cmbLineColor->setWhatsThis (tr ("Select a color for the lines drawn along a segment"));
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
  layout->addWidget (m_cmbLineColor, row++, 2);
}

void DlgSettingsSegments::createPreview (QGridLayout *layout,
                                         int &row)
{
  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview, this);
  m_viewPreview->setWhatsThis (tr ("Preview window shows the shortest line that can be segment filled, "
                                   "and the effects of current settings on segments and points generated by segment fill"));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QWidget *DlgSettingsSegments::createSubPanel ()
{
  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch (0, 1); // Empty first column
  layout->setColumnStretch (1, 0); // Labels
  layout->setColumnStretch (2, 0); // User controls
  layout->setColumnStretch (3, 1); // Empty last column

  int row = 0;
  createControls(layout, row);
  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsSegments::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::handleOk";

  CmdSettingsSegments *cmd = new CmdSettingsSegments (mainWindow (),
                                                      cmdMediator ().document(),
                                                      *m_modelSegmentsBefore,
                                                      *m_modelSegmentsAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsSegments::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::load";

  setCmdMediator (cmdMediator);

  m_modelSegmentsBefore = new DocumentModelSegments (cmdMediator);
  m_modelSegmentsAfter = new DocumentModelSegments (cmdMediator);

  m_editPointSeparation->setText (QString::number(m_modelSegmentsAfter->pointSeparation()));
  m_editMinLength->setText (QString::number(m_modelSegmentsAfter->minLength()));
  m_chkFillCorners->setChecked (m_modelSegmentsAfter->fillCorners ());
  m_spinLineSize->setValue (m_modelSegmentsAfter->lineSize());

  int indexLineColor = m_cmbLineColor->findData(QVariant (m_modelSegmentsAfter->lineColor()));
  Q_ASSERT (indexLineColor >= 0);
  m_cmbLineColor->setCurrentIndex(indexLineColor);
}

void DlgSettingsSegments::slotFillCorners (int state)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::slotFillCorner";

  enableOk (true);
  m_modelSegmentsAfter->setFillCorners(state == Qt::Checked);
}

void DlgSettingsSegments::slotLineColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::slotLineColor";

  enableOk (true);

  m_modelSegmentsAfter->setLineColor((ColorPalette) m_cmbLineColor->currentData().toInt());
}

void DlgSettingsSegments::slotLineSize (int lineSize)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::slotLineSize";

  enableOk (true);

  m_modelSegmentsAfter->setLineSize(lineSize);
}

void DlgSettingsSegments::slotMinLength (const QString &minLength)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::slotMinLength";

  enableOk (true);

  m_modelSegmentsAfter->setMinLength(minLength.toDouble());
}

void DlgSettingsSegments::slotPointSeparation (const QString &pointSeparation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::slotPointSeparation";

  enableOk (true);

  m_modelSegmentsAfter->setPointSeparation(pointSeparation.toDouble());
}
