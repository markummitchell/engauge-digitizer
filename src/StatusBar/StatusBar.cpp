#include "EngaugeAssert.h"
#include "Logger.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QStatusBar>
#include <QTextEdit>
#include <QTimer>
#include <QWhatsThis>
#include "StatusBar.h"
#include "ZoomFactor.h"

const QString LABEL_COORDS_SCREEN ("Coordinates (pixels):");
const QString LABEL_COORDS_GRAPH ("Coordinates (graph):");
const QString LABEL_RESOLUTION_GRAPH ("Resolution (graph):");

const QString LABEL_ZOOM_16_TO_1 ("16:1");
const QString LABEL_ZOOM_8_TO_1 ("8:1");
const QString LABEL_ZOOM_4_TO_1 ("4:1");
const QString LABEL_ZOOM_2_TO_1 ("2:1");
const QString LABEL_ZOOM_1_TO_1 ("1:1");
const QString LABEL_ZOOM_1_TO_2 ("1:2");
const QString LABEL_ZOOM_1_TO_4 ("1:4");
const QString LABEL_ZOOM_1_TO_8 ("1:8");
const QString LABEL_ZOOM_1_TO_16 ("1:16");
const QString LABEL_ZOOM_FILL ("Fill");

const int TEMPORARY_MESSAGE_LIFETIME = 5000; // Milliseconds. Two seconds is too fast even when the text is anticipated

const int MIN_WIDTH_COMBO_UNITS = 160;
const int MAX_WIDTH_GROUP_UNITS = 400;
const int MAX_SIZE_EDIT_COORDS = 550; // Need lots of space in case date/time and degrees/minutes/seconds are used simultaneously
const int MAX_HEIGHT_EDIT_COORDS = 24;

StatusBar::StatusBar(QStatusBar &statusBar) :
  m_statusBar (statusBar),
  m_statusBarMode (STATUS_BAR_MODE_ALWAYS),
  m_timer (0)
{
  createZoom ();
  createGroupUnits ();

  connect (&m_statusBar, SIGNAL (messageChanged (const QString &)), this, SLOT (slotStatusBarChanged (const QString &)));

  m_statusBar.setMaximumHeight (60);
  m_statusBar.hide();
}

StatusBar::~StatusBar ()
{
  if (m_timer != 0) {
    delete m_timer;
    m_timer = 0;
  }
}

void StatusBar::createGroupUnits ()
{
  m_comboUnits = new QComboBox;
  m_comboUnits->setEnabled (false); // Disabled until file is opened
  m_comboUnits->addItem (LABEL_COORDS_SCREEN, QVariant (STATUS_BAR_UNITS_COORDS_SCREEN));
  m_comboUnits->addItem (LABEL_COORDS_GRAPH, QVariant (STATUS_BAR_UNITS_COORDS_GRAPH));
  m_comboUnits->addItem (LABEL_RESOLUTION_GRAPH, QVariant (STATUS_BAR_UNITS_RESOLUTION_GRAPH));
  m_comboUnits->setCurrentText (LABEL_COORDS_GRAPH);
  m_comboUnits->setMaximumWidth (MIN_WIDTH_COMBO_UNITS);
  m_comboUnits->setToolTip (tr ("Select cursor coordinate values to display."));
  m_comboUnits->setWhatsThis (tr("Select Cursor Coordinate Values\n\n"
                                 "Values at cursor coordinates to display. Coordinates are in screen (pixels) or "
                                 "graph units. Resolution (which is the number of graph units per pixel) is "
                                 "in graph units. Graph units are only available after axis points have been defined."));
  connect (m_comboUnits, SIGNAL (activated(const QString &)), this, SLOT (slotComboUnits (const QString &))); // activated() ignores code changes

  m_editCoords = new QTextEdit;
  m_editCoords->setEnabled (false); // Disabled until file is opened
  m_editCoords->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_editCoords->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_editCoords->setMinimumSize (MAX_SIZE_EDIT_COORDS, MAX_HEIGHT_EDIT_COORDS);
  m_editCoords->setMaximumSize (MAX_SIZE_EDIT_COORDS, MAX_HEIGHT_EDIT_COORDS);
  m_editCoords->setReadOnly(true);
  m_editCoords->setToolTip (tr ("Cursor coordinate values."));
  m_editCoords->setWhatsThis (tr ("Cursor Coordinate Values\n\n"
                                  "Values at cursor coordinates. Coordinates are in screen (pixels) or "
                                  "graph units. Resolution (which is the number of graph units per pixel) is "
                                  "in graph units. Graph units are only available after axis points have been defined."));

  m_groupUnits = new QFrame;
  m_groupUnits->setFrameStyle (QFrame::Box);
  QPalette *palette = new QPalette;
  palette->setColor (QPalette::Foreground, Qt::gray);
  m_groupUnits->setPalette (*palette);
  m_groupUnits->setMaximumWidth (MAX_WIDTH_GROUP_UNITS);

  QHBoxLayout *groupLayout = new QHBoxLayout;
  m_groupUnits->setLayout (groupLayout);
  groupLayout->setContentsMargins (0, 0, 0, 0);
  groupLayout->addWidget (m_comboUnits);
  groupLayout->addWidget (m_editCoords);
  groupLayout->setMargin (2);

  m_statusBar.addPermanentWidget (m_groupUnits);
}

void StatusBar::createZoom ()
{
  m_comboZoom = new QComboBox ();
  m_comboZoom->setEnabled (false); // Disabled until file is opened
  m_comboZoom->addItem (LABEL_ZOOM_16_TO_1);
  m_comboZoom->addItem (LABEL_ZOOM_8_TO_1);
  m_comboZoom->addItem (LABEL_ZOOM_4_TO_1);
  m_comboZoom->addItem (LABEL_ZOOM_2_TO_1);
  m_comboZoom->addItem (LABEL_ZOOM_1_TO_1);
  m_comboZoom->addItem (LABEL_ZOOM_1_TO_2);
  m_comboZoom->addItem (LABEL_ZOOM_1_TO_4);
  m_comboZoom->addItem (LABEL_ZOOM_1_TO_8);
  m_comboZoom->addItem (LABEL_ZOOM_1_TO_16);
  m_comboZoom->addItem (LABEL_ZOOM_FILL);
  m_comboZoom->setCurrentText (LABEL_ZOOM_1_TO_1);
  m_comboZoom->setMaximumWidth (80);
  m_comboZoom->setToolTip (tr ("Select zoom."));
  m_comboZoom->setWhatsThis (tr("Select Zoom\n\n"
                                "Points can be more accurately placed by zooming in."));
  // Zoom combobox must use currentTextChanged rather than activated or else fill-zoom-at-startup never takes effect
  connect (m_comboZoom, SIGNAL (currentTextChanged(const QString &)), this, SLOT (slotComboZoom (const QString &)));

  m_statusBar.addPermanentWidget (m_comboZoom);
}

void StatusBar::setCoordinates (const QString &coordsScreen,
                                const QString &coordsGraph,
                                const QString &resolutionGraph)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "StatusBar::setCoordinates"
//                               << " screen=" << coordsScreen.toLatin1 ().data ()
//                               << " graph=" << coordsGraph.toLatin1 ().data ()
//                               << " resolution=" << resolutionGraph.toLatin1 ().data ();

  if (m_comboUnits->isEnabled ()) {

    m_coordsScreen = coordsScreen;
    m_coordsGraph = coordsGraph;
    m_resolutionGraph = resolutionGraph;

    updateCoordsText();
  }
}

void StatusBar::setStatusBarMode(StatusBarMode statusBarMode)
{
  m_statusBarMode = statusBarMode;
  if (m_statusBarMode == STATUS_BAR_MODE_ALWAYS) {
    m_statusBar.show();
  } else {
    m_statusBar.hide();
  }
}

void StatusBar::showTemporaryMessage(const QString &message)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "StatusBar::showTemporaryMessage message=" << message.toLatin1 ().data ();

  if (m_statusBarMode != STATUS_BAR_MODE_NEVER) {
    if (m_statusBarMode == STATUS_BAR_MODE_TEMPORARY) {
      // Calling m_statusBar.show here will have no effect since this is called while processing a signal. Use a timer to
      // show the status bar as soon as possible
      m_timer = new QTimer;
      connect (m_timer, SIGNAL (timeout ()), this, SLOT (slotTimeout()));
      m_timer->setSingleShot(true);
      m_timer->start (0);
    }
    m_statusBar.showMessage (message, TEMPORARY_MESSAGE_LIFETIME);
  }
}

void StatusBar::slotComboUnits (const QString &text)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "StatusBar::slotComboUnits text=" << text.toLatin1 ().data ();

  updateCoordsText();
}

void StatusBar::slotComboZoom (const QString &text)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "StatusBar::slotComboZoom text=" << text.toLatin1 ().data ();

  if  (text == LABEL_ZOOM_16_TO_1) {
    emit signalZoom (ZOOM_16_TO_1);
  } else if (text == LABEL_ZOOM_8_TO_1) {
    emit signalZoom (ZOOM_8_TO_1);
  } else if (text == LABEL_ZOOM_4_TO_1) {
    emit signalZoom (ZOOM_4_TO_1);
  } else if (text == LABEL_ZOOM_2_TO_1) {
    emit signalZoom (ZOOM_2_TO_1);
  } else if (text == LABEL_ZOOM_1_TO_1) {
    emit signalZoom (ZOOM_1_TO_1);
  } else if (text == LABEL_ZOOM_1_TO_2) {
    emit signalZoom (ZOOM_1_TO_2);
  } else if (text == LABEL_ZOOM_1_TO_4) {
    emit signalZoom (ZOOM_1_TO_4);
  } else if (text ==  LABEL_ZOOM_1_TO_8) {
    emit signalZoom (ZOOM_1_TO_8);
  } else if (text == LABEL_ZOOM_1_TO_16) {
    emit signalZoom (ZOOM_1_TO_16);
  } else if (text == LABEL_ZOOM_FILL) {
    emit signalZoom (ZOOM_FILL);
  } else {
    ENGAUGE_ASSERT (false);
  }
}

void StatusBar::slotStatusBarChanged(const QString &message)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "StatusBar::slotStatusBarChanged message=" << message.toLatin1 ().data ();

  if (m_statusBarMode == STATUS_BAR_MODE_TEMPORARY) {
    m_statusBar.hide();
  }
}

void StatusBar::slotTimeout()
{
  LOG4CPP_INFO_S ((*mainCat)) << "StatusBar::slotTimeout";

  delete m_timer;
  m_timer = 0;

  m_statusBar.show();
}

void StatusBar::slotZoom(int zoom)
{
  LOG4CPP_INFO_S ((*mainCat)) << "StatusBar::slotZoom zoom=" << zoom;

  // Show string for the numeric zoom value
  switch ((ZoomFactor) zoom) {
    case ZOOM_16_TO_1:
      m_comboZoom->setCurrentText (LABEL_ZOOM_16_TO_1);
      break;
    case ZOOM_8_TO_1:
      m_comboZoom->setCurrentText (LABEL_ZOOM_8_TO_1);
      break;
    case ZOOM_4_TO_1:
      m_comboZoom->setCurrentText (LABEL_ZOOM_4_TO_1);
      break;
    case ZOOM_2_TO_1:
      m_comboZoom->setCurrentText (LABEL_ZOOM_2_TO_1);
      break;
    case ZOOM_1_TO_1:
      m_comboZoom->setCurrentText (LABEL_ZOOM_1_TO_1);
      break;
    case ZOOM_1_TO_2:
      m_comboZoom->setCurrentText (LABEL_ZOOM_1_TO_2);
      break;
    case ZOOM_1_TO_4:
      m_comboZoom->setCurrentText (LABEL_ZOOM_1_TO_4);
      break;
    case ZOOM_1_TO_8:
      m_comboZoom->setCurrentText (LABEL_ZOOM_1_TO_8);
      break;
    case ZOOM_1_TO_16:
      m_comboZoom->setCurrentText (LABEL_ZOOM_1_TO_16);
      break;
    case ZOOM_FILL:
      m_comboZoom->setCurrentText (LABEL_ZOOM_FILL);
  }
}

void StatusBar::updateCoordsText()
{
  if (m_comboUnits->currentText() == LABEL_COORDS_SCREEN) {
    m_editCoords->setText (m_coordsScreen);
  } else if (m_comboUnits->currentText()  == LABEL_COORDS_GRAPH) {
    m_editCoords->setText (m_coordsGraph);
  } else {
    m_editCoords->setText (m_resolutionGraph);
  }
}

void StatusBar::wakeUp ()
{
  if (!m_comboUnits->isEnabled ()) {

    // First file has just been read in, so enable the widgets
    m_comboZoom->setEnabled (true);
    m_comboUnits->setEnabled (true);
    m_editCoords->setEnabled (true);
  }
}
