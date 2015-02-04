#include "CmdMediator.h"
#include "CmdSettingsSegments.h"
#include "DlgSettingsSegments.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <qmath.h>
#include <QSpinBox>
#include "ViewPreview.h"

const int MIN_LENGTH_MIN = 1;
const int MIN_LENGTH_MAX = 10000;
const int POINT_SEPARATION_MIN = 5;
const int POINT_SEPARATION_MAX = 10000;

const int IMAGE_WIDTH = 400;
const int IMAGE_HEIGHT = 300;

const double TWOPI = 2.0 * 3.1415926535;

const double BRUSH_WIDTH = 2.0;

DlgSettingsSegments::DlgSettingsSegments(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Segments",
                           "DlgSettingsSegments",
                           mainWindow),
  m_scenePreview (0),
  m_viewPreview (0),
  m_modelSegmentsBefore (0),
  m_modelSegmentsAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsSegments::createControls (QGridLayout *layout,
                                          int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::createControls";

  QLabel *labelMinLength = new QLabel("Minimum length:");
  layout->addWidget(labelMinLength, row, 1);

  m_editMinLength = new QLineEdit;
  m_editMinLength->setWhatsThis (tr ("Select a minimum number of points in a segment.\n\n"
                                     "Only segments with more points will be created.\n\n"
                                     "This value should be as large as possible to reduce memory usage. This value has "
                                     "a lower limit"));
  m_validatorMinLength = new QIntValidator (MIN_LENGTH_MIN, MIN_LENGTH_MAX);
  m_editMinLength->setValidator (m_validatorMinLength);
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
  m_validatorPointSeparation = new QIntValidator (POINT_SEPARATION_MIN, POINT_SEPARATION_MAX);
  m_editPointSeparation->setValidator (m_validatorPointSeparation);
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

  QLabel *labelLineWidth = new QLabel("Line width:");
  layout->addWidget (labelLineWidth, row, 1);

  m_spinLineWidth = new QSpinBox;
  m_spinLineWidth->setWhatsThis (tr ("Select a size for the lines drawn along a segment"));
  m_spinLineWidth->setMinimum(1);
  connect (m_spinLineWidth, SIGNAL (valueChanged (int)), this, SLOT (slotLineWidth (int)));
  layout->addWidget (m_spinLineWidth, row++, 2);

  QLabel *labelLineColor = new QLabel("Line color:");
  layout->addWidget (labelLineColor, row, 1);

  m_cmbLineColor = new QComboBox;
  m_cmbLineColor->setWhatsThis (tr ("Select a color for the lines drawn along a segment"));
  populateColorComboWithTransparent (*m_cmbLineColor);
  connect (m_cmbLineColor, SIGNAL (activated (const QString &)), this, SLOT (slotLineColor (const QString &))); // activated() ignores code changes
  layout->addWidget (m_cmbLineColor, row++, 2);
}

void DlgSettingsSegments::createPreview (QGridLayout *layout,
                                         int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::createPreview";

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

void DlgSettingsSegments::createPreviewImage ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::createPreviewImage";

  QImage image (IMAGE_WIDTH,
                IMAGE_HEIGHT,
                QImage::Format_RGB32);
  image.fill (Qt::white);
  QPainter painter (&image);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen (QPen (QBrush (Qt::black), BRUSH_WIDTH));

  int margin = IMAGE_WIDTH / 15;
  int yCenter = IMAGE_HEIGHT / 2;
  int yHeight = IMAGE_HEIGHT / 4;
  int x, y, xLast, yLast;
  bool isFirst;

  // Draw sinusoid
  isFirst = true;
  int xStart = margin, xEnd = IMAGE_WIDTH / 2 - margin;
  for (x = xStart; x < xEnd; x++) {
    double s = (double) (x - xStart) / (double) (xEnd - xStart);
    int y = yCenter - yHeight * qSin (TWOPI * s);

    if (!isFirst) {
      painter.drawLine (xLast, yLast, x, y);
    }
    isFirst = false;
    xLast = x;
    yLast = y;
  }

  // Draw triangular waveform that looks like sinusoid straightened up into line segments
  isFirst = true;
  xStart = IMAGE_WIDTH / 2 + margin, xEnd = IMAGE_WIDTH - margin;
  for (x = xStart; x < xEnd; x++) {
    double s = (double) (x - xStart) / (double) (xEnd - xStart);
    if (s <= 0.25) {
      y = yCenter - yHeight * (4.0 * s);
    } else if (s < 0.75) {
      y = yCenter - yHeight * (1.0 - 4.0 * (s - 0.25));
    } else {
      y = yCenter + yHeight * (1.0 - 4 * (s - 0.75));
    }

    if (!isFirst) {
      painter.drawLine (xLast, yLast, x, y);
    }
    isFirst = false;
    xLast = x;
    yLast = y;
  }

  QPixmap pixmap = QPixmap::fromImage (image);
  m_scenePreview->addPixmap (pixmap);
}

QWidget *DlgSettingsSegments::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::createSubPanel";

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
  createPreviewImage ();

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

  // Flush old data
  if (m_modelSegmentsBefore != 0) {
    delete m_modelSegmentsBefore;
  }
  if (m_modelSegmentsAfter != 0) {
    delete m_modelSegmentsAfter;
  }

  // Save new data
  m_modelSegmentsBefore = new DocumentModelSegments (cmdMediator.document());
  m_modelSegmentsAfter = new DocumentModelSegments (cmdMediator.document());

  // Sanity checks. Incoming defaults must be acceptable to the local limits
  Q_ASSERT (MIN_LENGTH_MIN <= m_modelSegmentsAfter->minLength ());
  Q_ASSERT (MIN_LENGTH_MAX >= m_modelSegmentsAfter->minLength ());
  Q_ASSERT (POINT_SEPARATION_MIN <= m_modelSegmentsAfter->pointSeparation());
  Q_ASSERT (POINT_SEPARATION_MAX >= m_modelSegmentsAfter->pointSeparation());

  // Populate controls
  m_editPointSeparation->setText (QString::number(m_modelSegmentsAfter->pointSeparation()));
  m_editMinLength->setText (QString::number(m_modelSegmentsAfter->minLength()));
  m_chkFillCorners->setChecked (m_modelSegmentsAfter->fillCorners ());
  m_spinLineWidth->setValue (m_modelSegmentsAfter->lineWidth());

  int indexLineColor = m_cmbLineColor->findData(QVariant (m_modelSegmentsAfter->lineColor()));
  Q_ASSERT (indexLineColor >= 0);
  m_cmbLineColor->setCurrentIndex(indexLineColor);

  updateControls();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsSegments::slotFillCorners (int state)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::slotFillCorner";

  m_modelSegmentsAfter->setFillCorners(state == Qt::Checked);
  updateControls();
  updatePreview();
}

void DlgSettingsSegments::slotLineColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::slotLineColor";

  m_modelSegmentsAfter->setLineColor((ColorPalette) m_cmbLineColor->currentData().toInt());
  updateControls();
  updatePreview();
}

void DlgSettingsSegments::slotLineWidth (int lineWidth)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::slotLineWidth";

  m_modelSegmentsAfter->setLineWidth(lineWidth);
  updateControls();
  updatePreview();
}

void DlgSettingsSegments::slotMinLength (const QString &minLength)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::slotMinLength";

  m_modelSegmentsAfter->setMinLength(minLength.toDouble());
  updateControls();
  updatePreview();
}

void DlgSettingsSegments::slotPointSeparation (const QString &pointSeparation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::slotPointSeparation";

  m_modelSegmentsAfter->setPointSeparation(pointSeparation.toDouble());
  updateControls();
  updatePreview();
}

void DlgSettingsSegments::updateControls()
{
  QString textMinLength = m_editMinLength->text();
  QString textPointSeparation = m_editPointSeparation->text();
  int pos;
  bool isOk = (m_validatorMinLength->validate (textMinLength, pos) == QValidator::Acceptable) &&
              (m_validatorPointSeparation->validate (textPointSeparation, pos) == QValidator::Acceptable);
  enableOk (isOk);
}

void DlgSettingsSegments::updatePreview()
{

}
