#include "HighlightsPoint.h"
#include "CmdMediator.h"
#include "CmdSettingsAxesHighlights.h"
#include "CoordScale.h"
#include "DlgSettingsAxesHighlights.h"
#include "EnumsToQt.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QButtonGroup>
#include <QComboBox>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <qmath.h>
#include <QRadioButton>
#include "ViewPreview.h"

const int AXIS_WIDTH = 4;
const int RECT_WIDTH = 640;
const int RECT_HEIGHT = 480;
const int X_LEFT = RECT_WIDTH / 8;
const int X_RIGHT = RECT_WIDTH * 7 / 8;
const int Y_TOP = RECT_HEIGHT / 8;
const int Y_BOTTOM = RECT_HEIGHT * 7 / 8;

DlgSettingsAxesHighlights::DlgSettingsAxesHighlights(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Axes Highlight", mainWindow),
  m_highlightsPoint0 (0),
  m_highlightsPoint1 (0),
  m_highlightsPoint2 (0),
  m_modelAxesHighlightsBefore (0),
  m_modelAxesHighlightsAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsAxesHighlights::createControls (QGridLayout *layout,
                                                int &row)
{
  QGroupBox *groupBox = new QGroupBox (tr ("Axes Highlights Lifetime"));
  layout->addWidget (groupBox, row++, 1, 1, 2);

  QGridLayout *layoutLifetime = new QGridLayout;
  groupBox->setLayout (layoutLifetime);

  int rowLifetime = 0;
  m_btnNever = new QRadioButton ("Do not show", groupBox);
  m_btnNever->setWhatsThis (tr ("Never show axes highlights."));
  layoutLifetime->addWidget (m_btnNever, rowLifetime++, 0, 1, 2);

  m_btnNSeconds = new QRadioButton ("Show for a number of seconds", groupBox);
  m_btnNSeconds->setWhatsThis (tr ("Show axes highlights for a number of seconds after changing axes points."));
  layoutLifetime->addWidget (m_btnNSeconds, rowLifetime, 0, 1, 1);

  m_cmbSeconds = new QComboBox;
  for (int seconds = 1; seconds <= 10; seconds++) {
    m_cmbSeconds->addItem (QString::number (seconds), QVariant (seconds));
  }
  layoutLifetime->addWidget (m_cmbSeconds, rowLifetime++, 1);
  connect (m_cmbSeconds, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotSeconds (const QString &)));

  m_btnForever = new QRadioButton ("Show always", groupBox);
  m_btnForever->setWhatsThis (tr ("Always show axes highlights."));
  layoutLifetime->addWidget (m_btnForever, rowLifetime++, 0, 1, 2);

  m_groupMode = new QButtonGroup;
  m_groupMode->addButton (m_btnNever);
  m_groupMode->addButton (m_btnNSeconds);
  m_groupMode->addButton (m_btnForever);
  connect (m_groupMode, SIGNAL (buttonReleased (QAbstractButton*)), this, SLOT (slotGroupMode (QAbstractButton*)));

  QLabel *labelLineColor = new QLabel ("Line color:");
  layout->addWidget (labelLineColor, row, 1);

  m_cmbLineColor = new QComboBox;
  m_cmbLineColor->setWhatsThis (tr ("Select a color for the highlight lines drawn at each axis point"));
  populateColorComboWithTransparent (*m_cmbLineColor);
  connect (m_cmbLineColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotLineColor (const QString &)));
  layout->addWidget (m_cmbLineColor, row++, 2);
}

void DlgSettingsAxesHighlights::createPoints ()
{
  m_highlightsPoint0 = new HighlightsPoint;
  m_highlightsPoint1 = new HighlightsPoint;
  m_highlightsPoint2 = new HighlightsPoint;

  m_scenePreview->addItem (m_highlightsPoint0);
  m_scenePreview->addItem (m_highlightsPoint1);
  m_scenePreview->addItem (m_highlightsPoint2);

  // Create an invisible rectangular item that will guarantee a margin all around the outside, since otherwise QGraphicsView
  // will zoom in on the points
  QGraphicsRectItem *itemRect = new QGraphicsRectItem (0,
                                                       0,
                                                       RECT_WIDTH,
                                                       RECT_HEIGHT);
  itemRect->setPen (Qt::NoPen);
  m_scenePreview->addItem (itemRect);

  // Since the typical image is wider than it is high, there are usually two points at the bottom and one point up high
  // on the left. We will position these points the same way
  m_highlightsPoint0->setPos (QPointF (X_LEFT, Y_BOTTOM));
  m_highlightsPoint1->setPos (QPointF (X_RIGHT, Y_BOTTOM));
  m_highlightsPoint2->setPos (QPointF (X_LEFT, Y_TOP));

  // For a realistic background, draw two black axis lines underneath (lower z value)
  QGraphicsLineItem *axisHorizontal = new QGraphicsLineItem (X_LEFT, Y_BOTTOM, X_RIGHT, Y_BOTTOM);
  QGraphicsLineItem *axisVertical = new QGraphicsLineItem (X_LEFT, Y_BOTTOM, X_LEFT, Y_TOP);
  axisHorizontal->setPen (QPen (QBrush (Qt::black), AXIS_WIDTH));
  axisVertical->setPen (QPen (QBrush (Qt::black), AXIS_WIDTH));
  axisHorizontal->setZValue (-1);
  axisVertical->setZValue (-1);
  m_scenePreview->addItem (axisHorizontal);
  m_scenePreview->addItem (axisVertical);
}

void DlgSettingsAxesHighlights::createPreview (QGridLayout *layout,
                                               int &row)
{
  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview, this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the displayed axes highlights"));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QWidget *DlgSettingsAxesHighlights::createSubPanel ()
{
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

void DlgSettingsAxesHighlights::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesHighlights::handleOk";

  CmdSettingsAxesHighlights *cmd = new CmdSettingsAxesHighlights (mainWindow (),
                                                                  cmdMediator ().document(),
                                                                  *m_modelAxesHighlightsBefore,
                                                                  *m_modelAxesHighlightsAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsAxesHighlights::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesHighlights::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelAxesHighlightsBefore != 0) {
    delete m_modelAxesHighlightsBefore;
  }
  if (m_modelAxesHighlightsAfter != 0) {
    delete m_modelAxesHighlightsAfter;
  }

  // Save new data
  m_modelAxesHighlightsBefore = new DocumentModelAxesHighlights (cmdMediator.document());
  m_modelAxesHighlightsAfter = new DocumentModelAxesHighlights (cmdMediator.document());

  HighlightsMode highlightsMode = m_modelAxesHighlightsAfter->highlightsMode();
  m_btnNever->setChecked (highlightsMode == HIGHLIGHTS_MODE_NEVER);
  m_btnNSeconds->setChecked (highlightsMode == HIGHLIGHTS_MODE_N_SECONDS);
  m_btnForever->setChecked (highlightsMode == HIGHLIGHTS_MODE_FOREVER);
  int indexSeconds = m_cmbSeconds->findData (QVariant (m_modelAxesHighlightsAfter->highlightsSeconds()));
  Q_ASSERT (indexSeconds >= 0);
  m_cmbSeconds->setCurrentIndex(indexSeconds);

  int indexLineColor = m_cmbLineColor->findData (QVariant (m_modelAxesHighlightsAfter->lineColor()));
  Q_ASSERT (indexLineColor >= 0);
  m_cmbLineColor->setCurrentIndex (indexLineColor);

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsAxesHighlights::slotGroupMode (QAbstractButton*)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesHighlights::slotGroupMode";

  if (m_btnNever->isChecked ()) {
    m_modelAxesHighlightsAfter->setHighlightsMode(HIGHLIGHTS_MODE_NEVER);
  } else if (m_btnNSeconds->isChecked ()) {
    m_modelAxesHighlightsAfter->setHighlightsMode(HIGHLIGHTS_MODE_N_SECONDS);
  } else {
    m_modelAxesHighlightsAfter->setHighlightsMode(HIGHLIGHTS_MODE_FOREVER);
  }

  updateControls ();
  updatePreview();
}

void DlgSettingsAxesHighlights::slotLineColor(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesHighlights::slotLineColor";

  m_modelAxesHighlightsAfter->setLineColor ((ColorPalette) m_cmbLineColor->currentData().toInt());
  updatePreview();
}

void DlgSettingsAxesHighlights::slotSeconds (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesHighlights::slotLineColor";

  m_modelAxesHighlightsAfter->setHighlightsSeconds(m_cmbSeconds->currentData().toInt());
  updateControls();
}

void DlgSettingsAxesHighlights::updateControls ()
{
  enableOk (true);

  m_cmbSeconds->setEnabled (m_btnNSeconds->isChecked ());
}

void DlgSettingsAxesHighlights::updatePreview()
{
  QColor lineColor = ColorPaletteToQColor (m_modelAxesHighlightsAfter->lineColor ());
  Q_ASSERT (m_highlightsPoint0 != 0 && m_highlightsPoint1 != 0 && m_highlightsPoint2 != 0);
  m_highlightsPoint0->setLineColor (lineColor);
  m_highlightsPoint1->setLineColor (lineColor);
  m_highlightsPoint2->setLineColor (lineColor);
}
