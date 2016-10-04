/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Checker.h"
#include "CmdMediator.h"
#include "CmdSettingsAxesChecker.h"
#include "CoordScale.h"
#include "DlgSettingsAxesChecker.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QButtonGroup>
#include <QComboBox>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <qmath.h>
#include <QRadioButton>
#include "ViewPreview.h"

const int AXIS_WIDTH = 4;
const int MINIMUM_HEIGHT = 500;
const int RECT_WIDTH = 640;
const int RECT_HEIGHT = 480;
const int X_LEFT = RECT_WIDTH / 8;
const int X_RIGHT = RECT_WIDTH * 7 / 8;
const int Y_TOP = RECT_HEIGHT / 8;
const int Y_BOTTOM = RECT_HEIGHT * 7 / 8;
const int TICKS_PER_AXIS = 6;
const int TICK_MARK_LENGTH = 8;

DlgSettingsAxesChecker::DlgSettingsAxesChecker(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Axes Checker"),
                           "DlgSettingsAxesChecker",
                           mainWindow),
  m_checker (0),
  m_modelAxesCheckerBefore (0),
  m_modelAxesCheckerAfter (0),
  m_modelCoords (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::DlgSettingsAxesChecker";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsAxesChecker::~DlgSettingsAxesChecker()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::~DlgSettingsAxesChecker";
}

void DlgSettingsAxesChecker::createControls (QGridLayout *layout,
                                             int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::createControls";

  QGroupBox *groupBox = new QGroupBox (tr ("Axes Checker Lifetime"));
  layout->addWidget (groupBox, row++, 1, 1, 2);

  QGridLayout *layoutLifetime = new QGridLayout;
  groupBox->setLayout (layoutLifetime);

  int rowLifetime = 0;
  m_btnNever = new QRadioButton (tr ("Do not show"), groupBox);
  m_btnNever->setWhatsThis (tr ("Never show axes checker."));
  layoutLifetime->addWidget (m_btnNever, rowLifetime++, 0, 1, 2);

  m_btnNSeconds = new QRadioButton (tr ("Show for a number of seconds"), groupBox);
  m_btnNSeconds->setWhatsThis (tr ("Show axes checker for a number of seconds after changing axes points."));
  layoutLifetime->addWidget (m_btnNSeconds, rowLifetime, 0, 1, 1);

  m_cmbSeconds = new QComboBox;
  for (int seconds = 1; seconds <= 10; seconds++) {
    m_cmbSeconds->addItem (QString::number (seconds), QVariant (seconds));
  }
  layoutLifetime->addWidget (m_cmbSeconds, rowLifetime++, 1);
  connect (m_cmbSeconds, SIGNAL (activated (const QString &)), this, SLOT (slotSeconds (const QString &))); // activated() ignores code changes

  m_btnForever = new QRadioButton (tr ("Show always"), groupBox);
  m_btnForever->setWhatsThis (tr ("Always show axes checker."));
  layoutLifetime->addWidget (m_btnForever, rowLifetime++, 0, 1, 2);

  m_groupMode = new QButtonGroup;
  m_groupMode->addButton (m_btnNever);
  m_groupMode->addButton (m_btnNSeconds);
  m_groupMode->addButton (m_btnForever);
  connect (m_groupMode, SIGNAL (buttonReleased (QAbstractButton*)), this, SLOT (slotGroupMode (QAbstractButton*)));

  QLabel *labelLineColor = new QLabel (tr ("Line color:"));
  layout->addWidget (labelLineColor, row, 1);

  m_cmbLineColor = new QComboBox;
  m_cmbLineColor->setWhatsThis (tr ("Select a color for the highlight lines drawn at each axis point"));
  populateColorComboWithoutTransparent (*m_cmbLineColor);
  connect (m_cmbLineColor, SIGNAL (activated (const QString &)), this, SLOT (slotLineColor (const QString &))); // activated() ignores code changes
  layout->addWidget (m_cmbLineColor, row++, 2);
}

void DlgSettingsAxesChecker::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
}

void DlgSettingsAxesChecker::createPoints ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::createPoints";

  QBrush AXES_BRUSH (Qt::gray);

  m_checker = new Checker (*m_scenePreview);

  // Create an invisible rectangular item that will guarantee a margin all around the outside, since otherwise QGraphicsView
  // will zoom in on the points
  QGraphicsRectItem *itemRect = new QGraphicsRectItem (0,
                                                       0,
                                                       RECT_WIDTH,
                                                       RECT_HEIGHT);
  itemRect->setPen (Qt::NoPen);
  m_scenePreview->addItem (itemRect);

  // For a realistic background, draw a rectangle underneath (lower z value), and some tick marks
  QGraphicsRectItem *frameBox = new QGraphicsRectItem (X_LEFT,
                                                       Y_BOTTOM,
                                                       X_RIGHT - X_LEFT,
                                                       Y_TOP - Y_BOTTOM);
  frameBox->setPen (QPen (AXES_BRUSH, AXIS_WIDTH));
  frameBox->setZValue (-1);
  m_scenePreview->addItem (frameBox);
  for (int x = X_LEFT; x < X_RIGHT; x += (X_RIGHT - X_LEFT) / TICKS_PER_AXIS) {
    QGraphicsLineItem *tick = new QGraphicsLineItem (x, Y_BOTTOM, x, Y_BOTTOM + TICK_MARK_LENGTH);
    tick->setPen (QPen (AXES_BRUSH, AXIS_WIDTH));
    tick->setZValue (-1);
    m_scenePreview->addItem (tick);
  }
  for (int y = Y_TOP; y < Y_BOTTOM; y += (Y_BOTTOM - Y_TOP) / TICKS_PER_AXIS) {
    QGraphicsLineItem *tick = new QGraphicsLineItem (X_LEFT, y, X_LEFT + TICK_MARK_LENGTH, y);
    tick->setPen (QPen (AXES_BRUSH, AXIS_WIDTH));
    tick->setZValue (-1);
    m_scenePreview->addItem (tick);
  }
}

void DlgSettingsAxesChecker::createPreview (QGridLayout *layout,
                                            int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::createPreview";

  QLabel *labelPreview = new QLabel (tr ("Preview"));
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview,
                                   ViewPreview::VIEW_ASPECT_RATIO_VARIABLE,
                                   this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the displayed axes checker"));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QWidget *DlgSettingsAxesChecker::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::createSubPanel";

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // X
  layout->setColumnStretch(2, 0); // Y
  layout->setColumnStretch(3, 1); // Empty first column

  int row = 0;
  createControls (layout, row);
  createPreview (layout, row);

  createPoints ();

  return subPanel;
}

void DlgSettingsAxesChecker::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::handleOk";

  CmdSettingsAxesChecker *cmd = new CmdSettingsAxesChecker (mainWindow (),
                                                            cmdMediator ().document(),
                                                            *m_modelAxesCheckerBefore,
                                                            *m_modelAxesCheckerAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsAxesChecker::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelAxesCheckerBefore != 0) {
    delete m_modelAxesCheckerBefore;
  }
  if (m_modelAxesCheckerAfter != 0) {
    delete m_modelAxesCheckerAfter;
  }
  if (m_modelCoords != 0) {
    delete m_modelCoords;
  }

  // Save new data
  m_modelAxesCheckerBefore = new DocumentModelAxesChecker (cmdMediator.document());
  m_modelAxesCheckerAfter = new DocumentModelAxesChecker (cmdMediator.document());
  m_modelCoords = new DocumentModelCoords (cmdMediator.document());

  // Populate controls
  CheckerMode checkerMode = m_modelAxesCheckerAfter->checkerMode();
  m_btnNever->setChecked (checkerMode == CHECKER_MODE_NEVER);
  m_btnNSeconds->setChecked (checkerMode == CHECKER_MODE_N_SECONDS);
  m_btnForever->setChecked (checkerMode == CHECKER_MODE_FOREVER);
  int indexSeconds = m_cmbSeconds->findData (QVariant (m_modelAxesCheckerAfter->checkerSeconds()));
  ENGAUGE_ASSERT (indexSeconds >= 0);
  m_cmbSeconds->setCurrentIndex(indexSeconds);

  int indexLineColor = m_cmbLineColor->findData (QVariant (m_modelAxesCheckerAfter->lineColor()));
  ENGAUGE_ASSERT (indexLineColor >= 0);
  m_cmbLineColor->setCurrentIndex (indexLineColor);

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsAxesChecker::setSmallDialogs(bool smallDialogs)
{
  if (!smallDialogs) {
    setMinimumHeight (MINIMUM_HEIGHT);
  }
}

void DlgSettingsAxesChecker::slotGroupMode (QAbstractButton*)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::slotGroupMode";

  if (m_btnNever->isChecked ()) {
    m_modelAxesCheckerAfter->setCheckerMode(CHECKER_MODE_NEVER);
  } else if (m_btnNSeconds->isChecked ()) {
    m_modelAxesCheckerAfter->setCheckerMode(CHECKER_MODE_N_SECONDS);
  } else {
    m_modelAxesCheckerAfter->setCheckerMode(CHECKER_MODE_FOREVER);
  }

  updateControls ();
  updatePreview();
}

void DlgSettingsAxesChecker::slotLineColor(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::slotLineColor";

  m_modelAxesCheckerAfter->setLineColor ((ColorPalette) m_cmbLineColor->currentData().toInt());
  updateControls();
  updatePreview();
}

void DlgSettingsAxesChecker::slotSeconds (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesChecker::slotLineColor";

  m_modelAxesCheckerAfter->setCheckerSeconds(m_cmbSeconds->currentData().toInt());
  updateControls();
}

void DlgSettingsAxesChecker::updateControls ()
{
  enableOk (true);

  m_cmbSeconds->setEnabled (m_btnNSeconds->isChecked ());
}

void DlgSettingsAxesChecker::updatePreview()
{
  const int ZERO_RADIUS_SINCE_NO_POINTS = 0;

  QVector<QPointF> points;
  points.push_back (QPointF (X_LEFT, Y_TOP));
  points.push_back (QPointF (X_LEFT, Y_BOTTOM));
  points.push_back (QPointF (X_RIGHT, Y_BOTTOM));

  QPolygonF polygon (points);

  ENGAUGE_ASSERT (m_checker != 0);
  m_checker->prepareForDisplay (polygon,
                                ZERO_RADIUS_SINCE_NO_POINTS,
                                *m_modelAxesCheckerAfter,
                                *m_modelCoords,
                                mainWindow().cmdMediator()->document().documentAxesPointsRequired());
}
