/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdSettingsSegments.h"
#include "DlgSettingsSegments.h"
#include "EngaugeAssert.h"
#include "GeometryWindow.h"
#include "Logger.h"
#include "MainWindow.h"
#include "PointStyle.h"
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QLabel>
#include <qmath.h>
#include <QSpinBox>
#include "Segment.h"
#include "SegmentFactory.h"
#include "ViewPreview.h"

const int MINIMUM_HEIGHT = 540;
const int MIN_LENGTH_MIN = 1;
const int MIN_LENGTH_MAX = 10000;
const int POINT_SEPARATION_MIN = 5;
const int POINT_SEPARATION_MAX = 10000;

const int IMAGE_WIDTH = 400;
const int IMAGE_HEIGHT = 350;

const double TWOPI = 2.0 * 3.1415926535;

const double BRUSH_WIDTH = 2.0;

DlgSettingsSegments::DlgSettingsSegments(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Segment Fill"),
                           "DlgSettingsSegments",
                           mainWindow),
  m_scenePreview (nullptr),
  m_viewPreview (nullptr),
  m_modelSegmentsBefore (nullptr),
  m_modelSegmentsAfter (nullptr),
  m_loading (false)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::DlgSettingsSegments";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsSegments::~DlgSettingsSegments()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::~DlgSettingsSegments";
}

void DlgSettingsSegments::clearPoints ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::clearPoints";

  QList<GraphicsPoint*>::iterator itrP;
  for (itrP = m_points.begin(); itrP != m_points.end(); itrP++) {
    GraphicsPoint *point = *itrP;
    delete point;
  }

  m_points.clear();
}

void DlgSettingsSegments::createControls (QGridLayout *layout,
                                          int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::createControls";

  QLabel *labelMinLength = new QLabel(QString ("%1:").arg (tr ("Minimum length (points)")));
  layout->addWidget(labelMinLength, row, 1);

  m_spinMinLength = new QSpinBox;
  m_spinMinLength->setRange (MIN_LENGTH_MIN, MIN_LENGTH_MAX);
  m_spinMinLength->setWhatsThis (tr ("Select a minimum number of points in a segment.\n\n"
                                     "Only segments with more points will be created.\n\n"
                                     "This value should be as large as possible to reduce memory usage. This value has "
                                     "a lower limit"));
  connect (m_spinMinLength, SIGNAL (valueChanged (const QString &)), this, SLOT (slotMinLength (const QString &)));
  layout->addWidget(m_spinMinLength, row++, 2);

  QLabel *labelPointSeparation = new QLabel(QString ("%1:").arg (tr ("Point separation (pixels)")));
  layout->addWidget (labelPointSeparation, row, 1);

  m_spinPointSeparation = new QSpinBox;
  m_spinPointSeparation->setRange (POINT_SEPARATION_MIN, POINT_SEPARATION_MAX);
  m_spinPointSeparation->setWhatsThis (tr ("Select a point separation in pixels.\n\n"
                                           "Successive points added to a segment will be separated by this number of pixels. "
                                           "If Fill Corners is enabled, then additional points will be inserted at corners so some points "
                                           "will be closer.\n\n"
                                           "This value has a lower limit"));
  connect (m_spinPointSeparation, SIGNAL (valueChanged (const QString &)), this, SLOT (slotPointSeparation (const QString &)));
  layout->addWidget (m_spinPointSeparation, row++, 2);

  QLabel *labelFillCorners = new QLabel (QString ("%1:").arg (tr ("Fill corners")));
  layout->addWidget (labelFillCorners, row, 1);

  m_chkFillCorners = new QCheckBox;
  m_chkFillCorners->setWhatsThis (tr ("Fill corners.\n\n"
                                      "In addition to the points placed at regular intervals, this option causes a point to be "
                                      "placed at each corner. This option can capture important information in piecewise linear graphs, "
                                      "but gradually curving graphs may not benefit from the additional points"));
  connect (m_chkFillCorners, SIGNAL (stateChanged (int)), this, SLOT (slotFillCorners (int)));
  layout->addWidget (m_chkFillCorners, row++, 2);

  QLabel *labelLineWidth = new QLabel(QString ("%1:").arg (tr ("Line width")));
  layout->addWidget (labelLineWidth, row, 1);

  m_spinLineWidth = new QSpinBox;
  m_spinLineWidth->setWhatsThis (tr ("Select a size for the lines drawn along a segment"));
  m_spinLineWidth->setMinimum(1);
  connect (m_spinLineWidth, SIGNAL (valueChanged (int)), this, SLOT (slotLineWidth (int)));
  layout->addWidget (m_spinLineWidth, row++, 2);

  QLabel *labelLineColor = new QLabel(QString ("%1:").arg (tr ("Line color")));
  layout->addWidget (labelLineColor, row, 1);

  m_cmbLineColor = new QComboBox;
  m_cmbLineColor->setWhatsThis (tr ("Select a color for the lines drawn along a segment"));
  populateColorComboWithTransparent (*m_cmbLineColor);
  connect (m_cmbLineColor, SIGNAL (activated (const QString &)), this, SLOT (slotLineColor (const QString &))); // activated() ignores code changes
  layout->addWidget (m_cmbLineColor, row++, 2);
}

void DlgSettingsSegments::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
}

void DlgSettingsSegments::createPreview (QGridLayout *layout,
                                         int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::createPreview";

  QLabel *labelPreview = new QLabel (tr ("Preview"));
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview,
                                   ViewPreview::VIEW_ASPECT_RATIO_VARIABLE,
                                   this);
  m_viewPreview->setWhatsThis (tr ("Preview window shows the shortest line that can be segment filled, "
                                   "and the effects of current settings on segments and points generated by segment fill"));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QImage DlgSettingsSegments::createPreviewImage () const
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
  int x, y, xLast = 0, yLast = 0;
  bool isFirst;

  // Draw sinusoid
  isFirst = true;
  int xStart = margin, xEnd = IMAGE_WIDTH / 2 - margin;
  for (x = xStart; x < xEnd; x++) {
    double s = double (x - xStart) / double (xEnd - xStart);
    int y = qFloor (yCenter - yHeight * qSin (TWOPI * s));

    if (!isFirst) {
      painter.drawLine (xLast, yLast, x, y);
    }
    isFirst = false;
    xLast = x;
    yLast = y;
  }

  // Draw triangular waveform that looks like sinusoid straightened up into line segments
  isFirst = true;
  xStart = IMAGE_WIDTH / 2 + margin;
  xEnd = IMAGE_WIDTH - margin;
  for (x = xStart; x < xEnd; x++) {
    double s = double (x - xStart) / double (xEnd - xStart);
    if (s <= 0.25) {
      y = qFloor (yCenter - yHeight * (4.0 * s));
    } else if (s < 0.75) {
      y = qFloor (yCenter - yHeight * (1.0 - 4.0 * (s - 0.25)));
    } else {
      y = qFloor (yCenter + yHeight * (1.0 - 4 * (s - 0.75)));
    }

    if (!isFirst) {
      painter.drawLine (xLast, yLast, x, y);
    }
    isFirst = false;
    xLast = x;
    yLast = y;
  }

  return image;
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
  QPixmap pixmap = QPixmap::fromImage (createPreviewImage());
  m_scenePreview->addPixmap (pixmap);

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

  // Loading starts here
  m_loading = true;

  setCmdMediator (cmdMediator);

  // Flush old data
  delete m_modelSegmentsBefore;
  delete m_modelSegmentsAfter;

  // Save new data
  m_modelSegmentsBefore = new DocumentModelSegments (cmdMediator.document());
  m_modelSegmentsAfter = new DocumentModelSegments (cmdMediator.document());

  // Sanity checks. Incoming defaults must be acceptable to the local limits
  ENGAUGE_ASSERT (MIN_LENGTH_MIN <= m_modelSegmentsAfter->minLength ());
  ENGAUGE_ASSERT (MIN_LENGTH_MAX >= m_modelSegmentsAfter->minLength ());
  ENGAUGE_ASSERT (POINT_SEPARATION_MIN <= m_modelSegmentsAfter->pointSeparation());
  ENGAUGE_ASSERT (POINT_SEPARATION_MAX >= m_modelSegmentsAfter->pointSeparation());

  // Populate controls
  m_spinPointSeparation->setValue (qFloor (m_modelSegmentsAfter->pointSeparation()));
  m_spinMinLength->setValue (qFloor (m_modelSegmentsAfter->minLength()));
  m_chkFillCorners->setChecked (m_modelSegmentsAfter->fillCorners ());
  m_spinLineWidth->setValue (qFloor (m_modelSegmentsAfter->lineWidth()));

  int indexLineColor = m_cmbLineColor->findData(QVariant (m_modelSegmentsAfter->lineColor()));
  ENGAUGE_ASSERT (indexLineColor >= 0);
  m_cmbLineColor->setCurrentIndex(indexLineColor);

  // Loading finishes here
  m_loading = false;

  updateControls();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsSegments::setSmallDialogs(bool smallDialogs)
{
  if (!smallDialogs) {
    setMinimumHeight (MINIMUM_HEIGHT);
  }
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

  m_modelSegmentsAfter->setLineColor(static_cast<ColorPalette> (m_cmbLineColor->currentData().toInt()));
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
  enableOk (true);
}

void DlgSettingsSegments::updatePreview()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsSegments::updatePreview"
                              << " loading=" << (m_loading ? "true" : "false");

  const QString ARBITRARY_IDENTIFIER ("");
  const QColor COLOR (Qt::blue);
  const int RADIUS = 5;
  GeometryWindow *NULL_GEOMETRY_WINDOW = nullptr;

  if (!m_loading) {

    SegmentFactory segmentFactory (*m_scenePreview,
                                   mainWindow().isGnuplot());

    clearPoints();
    segmentFactory.clearSegments (m_segments);

    // Create new segments
    segmentFactory.makeSegments (createPreviewImage(),
                                 *m_modelSegmentsAfter,
                                 m_segments);

    // Make the segment visible
    QList<Segment*>::iterator itrS;
    for (itrS = m_segments.begin(); itrS != m_segments.end(); itrS++) {
      Segment *segment = *itrS;
      segment->slotHover (true);
    }

    // Create some points
    PointStyle pointStyle (POINT_SHAPE_CROSS,
                           RADIUS,
                           qFloor (BRUSH_WIDTH),
                           COLOR_PALETTE_BLUE);
    QPolygonF polygon = pointStyle.polygon();
    QList<QPoint> points = segmentFactory.fillPoints (*m_modelSegmentsAfter,
                                                      m_segments);
    QList<QPoint>::iterator itrP;
    for (itrP = points.begin(); itrP != points.end(); itrP++) {
      QPoint pos = *itrP;
      GraphicsPoint *graphicsPoint = new GraphicsPoint (*m_scenePreview,
                                                        ARBITRARY_IDENTIFIER,
                                                        pos,
                                                        COLOR,
                                                        polygon,
                                                        BRUSH_WIDTH,
                                                        NULL_GEOMETRY_WINDOW);

      m_points.push_back (graphicsPoint);
    }
  }
}
