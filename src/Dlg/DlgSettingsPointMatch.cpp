/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdSettingsPointMatch.h"
#include "DlgSettingsPointMatch.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QComboBox>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>
#include <qmath.h>
#include <QPen>
#include <QSpinBox>
#include "ViewPreview.h"

const int MINIMUM_HEIGHT = 480;
const int POINT_SIZE_MAX = 1024;
const int POINT_SIZE_MIN = 5;

DlgSettingsPointMatch::DlgSettingsPointMatch(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Point Match"),
                           "DlgSettingsPointMatch",
                           mainWindow),
  m_scenePreview (0),
  m_viewPreview (0),
  m_circle (0),
  m_modelPointMatchBefore (0),
  m_modelPointMatchAfter (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::DlgSettingsPointMatch";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsPointMatch::~DlgSettingsPointMatch()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::~DlgSettingsPointMatch";
}

QPointF DlgSettingsPointMatch::boxPositionConstraint(const QPointF &posIn)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::boxPositionConstraint";

  double radius = radiusAlongDiagonal();
  double diameter = 2.0 * radius;

  // Do not move any part outside the preview window or else ugly, and unwanted, shifting will occur
  QPointF pos (posIn);
  if (pos.x() - radius < 0) {
    pos.setX (radius);
  }

  if (pos.y() - radius < 0) {
    pos.setY (radius);
  }

  if (pos.x() + diameter > m_scenePreview->sceneRect().width ()) {
    pos.setX (m_scenePreview->sceneRect().width() - diameter);
  }

  if (pos.y() + diameter > m_scenePreview->sceneRect().height ()) {
    pos.setY (m_scenePreview->sceneRect().height() - diameter);
  }

  return pos;
}

void DlgSettingsPointMatch::createControls (QGridLayout *layout,
                                            int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::createControls";

  QLabel *labelPointSize = new QLabel (QString ("%1:").arg (tr ("Maximum point size (pixels)")));
  layout->addWidget (labelPointSize, row, 1);

  m_spinPointSize = new QSpinBox;
  m_spinPointSize->setWhatsThis (tr ("Select a maximum point size in pixels.\n\n"
                                     "Sample match points must fit within a square box, around the cursor, having width and height "
                                     "equal to this maximum.\n\n"
                                     "This size is also used to determine if a region of pixels that are on, in the processed image, "
                                     "should be ignored since that region is wider or taller than this limit.\n\n"
                                     "This value has a lower limit"));
  m_spinPointSize->setMinimum (POINT_SIZE_MIN);
  m_spinPointSize->setMaximum (POINT_SIZE_MAX);
  connect (m_spinPointSize, SIGNAL (valueChanged (int)), this, SLOT (slotMaxPointSize (int)));
  layout->addWidget (m_spinPointSize, row++, 2);

  QLabel *labelAcceptedPointColor = new QLabel (QString ("%1:").arg (tr ("Accepted point color")));
  layout->addWidget (labelAcceptedPointColor, row, 1);

  m_cmbAcceptedPointColor = new QComboBox;
  m_cmbAcceptedPointColor->setWhatsThis (tr ("Select a color for matched points that are accepted"));
  populateColorComboWithTransparent (*m_cmbAcceptedPointColor);
  connect (m_cmbAcceptedPointColor, SIGNAL (activated (const QString &)), this, SLOT (slotAcceptedPointColor (const QString &))); // activated() ignores code changes
  layout->addWidget (m_cmbAcceptedPointColor, row++, 2);

  QLabel *labelRejectedPointColor = new QLabel (QString ("%1:").arg (tr ("Rejected point color")));
  layout->addWidget (labelRejectedPointColor, row, 1);

  m_cmbRejectedPointColor = new QComboBox;
  m_cmbRejectedPointColor->setWhatsThis (tr ("Select a color for matched points that are rejected"));
  populateColorComboWithTransparent (*m_cmbRejectedPointColor);
  connect (m_cmbRejectedPointColor, SIGNAL (activated (const QString &)), this, SLOT (slotRejectedPointColor (const QString &))); // activated() ignores code changes
  layout->addWidget (m_cmbRejectedPointColor, row++, 2);

  QLabel *labelCandidatePointColor = new QLabel (QString ("%1:").arg (tr ("Candidate point color")));
  layout->addWidget (labelCandidatePointColor, row, 1);

  m_cmbCandidatePointColor = new QComboBox;
  m_cmbCandidatePointColor->setWhatsThis (tr ("Select a color for the point being decided upon"));
  populateColorComboWithTransparent (*m_cmbCandidatePointColor);
  connect (m_cmbCandidatePointColor, SIGNAL (activated (const QString &)), this, SLOT (slotCandidatePointColor (const QString &))); // activated() ignores code changes
  layout->addWidget (m_cmbCandidatePointColor, row++, 2);
}

void DlgSettingsPointMatch::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
}

void DlgSettingsPointMatch::createPreview (QGridLayout *layout,
                                           int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::createPreview";

  QLabel *labelPreview = new QLabel (tr ("Preview"));
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview,
                                   ViewPreview::VIEW_ASPECT_RATIO_VARIABLE,
                                   this);
  m_viewPreview->setWhatsThis (tr ("Preview window shows how current settings affect "
                                   "point matching, and how the marked and candidate points are displayed.\n\nThe points are separated "
                                   "by the point separation value, and the maximum point size is shown as a box in the center"));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);
  connect (m_viewPreview, SIGNAL (signalMouseMove (QPointF)), this, SLOT (slotMouseMove (QPointF)));

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QWidget *DlgSettingsPointMatch::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::createSubPanel";

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty column
  layout->setColumnStretch(1, 0); // Labels
  layout->setColumnStretch(2, 0); // Controls
  layout->setColumnStretch(3, 1); // Empty column

  int row = 0;
  createControls (layout, row);
  createPreview (layout, row);
  createTemplate ();

  return subPanel;
}

void DlgSettingsPointMatch::createTemplate ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::createTemplate";

  QPen pen (QBrush (Qt::black), 0);

  m_circle = new QGraphicsEllipseItem;
  m_circle->setPen (pen);
  m_circle->setZValue (100);
  m_scenePreview->addItem (m_circle);
}

void DlgSettingsPointMatch::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::handleOk";

  CmdSettingsPointMatch *cmd = new CmdSettingsPointMatch (mainWindow (),
                                                          cmdMediator ().document(),
                                                          *m_modelPointMatchBefore,
                                                          *m_modelPointMatchAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsPointMatch::initializeBox ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::initializeBox";

  m_circle->setPos (cmdMediator().document().pixmap().width () / 2.0,
                    cmdMediator().document().pixmap().height () / 2.0); // Initially box is in center of preview
}

void DlgSettingsPointMatch::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  delete m_modelPointMatchBefore;
  delete m_modelPointMatchAfter;

  // Save new data
  m_modelPointMatchBefore = new DocumentModelPointMatch (cmdMediator.document());
  m_modelPointMatchAfter = new DocumentModelPointMatch (cmdMediator.document());

  // Sanity checks. Incoming defaults must be acceptable to the local limits
  ENGAUGE_ASSERT (POINT_SIZE_MIN <= m_modelPointMatchAfter->maxPointSize());
  ENGAUGE_ASSERT (POINT_SIZE_MAX > m_modelPointMatchAfter->maxPointSize());

  // Populate controls
  m_spinPointSize->setValue(m_modelPointMatchAfter->maxPointSize());

  int indexAccepted = m_cmbAcceptedPointColor->findData(QVariant(m_modelPointMatchAfter->paletteColorAccepted()));
  ENGAUGE_ASSERT (indexAccepted >= 0);
  m_cmbAcceptedPointColor->setCurrentIndex(indexAccepted);

  int indexCandidate = m_cmbCandidatePointColor->findData(QVariant(m_modelPointMatchAfter->paletteColorCandidate()));
  ENGAUGE_ASSERT (indexCandidate >= 0);
  m_cmbCandidatePointColor->setCurrentIndex(indexCandidate);

  int indexRejected = m_cmbRejectedPointColor->findData(QVariant(m_modelPointMatchAfter->paletteColorRejected()));
  ENGAUGE_ASSERT (indexRejected >= 0);
  m_cmbRejectedPointColor->setCurrentIndex(indexRejected);

  initializeBox ();

  // Fix the preview size using an invisible boundary
  QGraphicsRectItem *boundary = m_scenePreview->addRect (QRect (0,
                                                                0,
                                                                cmdMediator.document().pixmap().width (),
                                                                cmdMediator.document().pixmap().height ()));
  boundary->setVisible (false);

  m_scenePreview->addPixmap (cmdMediator.document().pixmap());

  updateControls();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

double DlgSettingsPointMatch::radiusAlongDiagonal () const
{
  double maxPointSize = m_modelPointMatchAfter->maxPointSize();

  return qSqrt (2.0) * maxPointSize / 2.0;
}

void DlgSettingsPointMatch::setSmallDialogs(bool smallDialogs)
{
  if (!smallDialogs) {
    setMinimumHeight (MINIMUM_HEIGHT);
  }
}

void DlgSettingsPointMatch::slotAcceptedPointColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::slotAcceptedPointColor";

  m_modelPointMatchAfter->setPaletteColorAccepted((ColorPalette) m_cmbAcceptedPointColor->currentData().toInt());

  updateControls();
  updatePreview();
}

void DlgSettingsPointMatch::slotCandidatePointColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::slotCandidatePointColor";

  m_modelPointMatchAfter->setPaletteColorCandidate((ColorPalette) m_cmbCandidatePointColor->currentData().toInt());
  updateControls();
  updatePreview();
}

void DlgSettingsPointMatch::slotMaxPointSize (int maxPointSize)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::slotMaxPointSize";

  m_modelPointMatchAfter->setMaxPointSize(maxPointSize);
  updateControls();
  updatePreview();
}

void DlgSettingsPointMatch::slotMouseMove (QPointF pos)
{
  // Move the box so it follows the mouse move, making sure to keep it entirely inside the view to
  // prevent autoresizing by QGraphicsView
  pos = boxPositionConstraint (pos);

  m_circle->setPos (pos);
}

void DlgSettingsPointMatch::slotRejectedPointColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::slotRejectedPointColor";

  m_modelPointMatchAfter->setPaletteColorRejected((ColorPalette) m_cmbRejectedPointColor->currentData().toInt());
  updateControls();
  updatePreview();
}

void DlgSettingsPointMatch::updateControls()
{
  // All controls in this dialog are always fully validated so the ok button is always enabled (after the first change)
  enableOk (true);
}

void DlgSettingsPointMatch::updatePreview()
{
  // Geometry parameters
  double maxPointSize = m_modelPointMatchAfter->maxPointSize();

  double xLeft = -1.0 * maxPointSize / 2.0;
  double yTop = -1.0 * maxPointSize / 2.0;

  // Update circle size
  m_circle->setRect (xLeft,
                     yTop,
                     maxPointSize,
                     maxPointSize);
}
