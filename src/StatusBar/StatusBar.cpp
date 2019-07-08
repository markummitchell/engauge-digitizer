/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
#include "StatusBarMode.h"
#include "ZoomFactor.h"
#include "ZoomLabels.h"

const int TEMPORARY_MESSAGE_LIFETIME = 5000; // Milliseconds. Two seconds is too fast even when the text is anticipated

const int MIN_WIDTH_ZOOM = 110;
const int MIN_WIDTH_COMBO_UNITS = 160;
const int MIN_SIZE_EDIT_COORDS = 250; // Need lots of space in case date/time and degrees/minutes/seconds are used simultaneously
const int MAX_HEIGHT_EDIT_COORDS = 24;

StatusBar::StatusBar(QStatusBar &statusBar) :
  m_statusBar (statusBar),
  m_statusBarMode (STATUS_BAR_MODE_ALWAYS),
  m_timer (nullptr)
{
  createZoomLabels ();
  createZoom ();
  createZoomMaps ();
  createGroupUnits ();

  connect (&m_statusBar, SIGNAL (messageChanged (const QString &)), this, SLOT (slotStatusBarChanged (const QString &)));

  m_statusBar.setMaximumHeight (60);
  m_statusBar.hide();
}

StatusBar::~StatusBar ()
{
  delete m_timer;
}

void StatusBar::createGroupUnits ()
{
  m_cmbUnits = new QComboBox;
  m_cmbUnits->setEnabled (false); // Disabled until file is opened
  m_cmbUnits->addItem (labelCoordsScreen (), QVariant (STATUS_BAR_UNITS_COORDS_SCREEN));
  m_cmbUnits->addItem (labelCoordsGraph (), QVariant (STATUS_BAR_UNITS_COORDS_GRAPH));
  m_cmbUnits->addItem (labelResolutionGraph (), QVariant (STATUS_BAR_UNITS_RESOLUTION_GRAPH));
  m_cmbUnits->setCurrentText (labelCoordsGraph ());
  m_cmbUnits->setMinimumWidth (MIN_WIDTH_COMBO_UNITS);
  m_cmbUnits->setToolTip (tr ("Select cursor coordinate values to display."));
  m_cmbUnits->setWhatsThis (tr("Select Cursor Coordinate Values\n\n"
                               "Values at cursor coordinates to display. Coordinates are in screen (pixels) or "
                               "graph units. Resolution (which is the number of graph units per pixel) is "
                               "in graph units. Graph units are only available after axis points have been defined."));
  connect (m_cmbUnits, SIGNAL (activated(const QString &)), this, SLOT (slotComboUnits (const QString &))); // activated() ignores code changes

  m_editCoords = new QTextEdit;
  m_editCoords->setEnabled (false); // Disabled until file is opened
  m_editCoords->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_editCoords->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_editCoords->setMinimumSize (MIN_SIZE_EDIT_COORDS, MAX_HEIGHT_EDIT_COORDS);
  m_editCoords->setMaximumHeight (MAX_HEIGHT_EDIT_COORDS);
  m_editCoords->setReadOnly(true);
  m_editCoords->setToolTip (tr ("Cursor coordinate values."));
  m_editCoords->setWhatsThis (tr ("Cursor Coordinate Values\n\n"
                                  "Values at cursor coordinates. Coordinates are in screen (pixels) or "
                                  "graph units. Resolution (which is the number of graph units per pixel) is "
                                  "in graph units. Graph units are only available after axis points have been defined."));

  m_groupUnits = new QFrame;
  m_groupUnits->setFrameStyle (QFrame::Box);
  QPalette palette;
  palette.setColor (QPalette::Foreground, Qt::gray);
  m_groupUnits->setPalette (palette);

  QHBoxLayout *groupLayout = new QHBoxLayout;
  m_groupUnits->setLayout (groupLayout);
  groupLayout->setContentsMargins (0, 0, 0, 0);
  groupLayout->addWidget (m_cmbUnits);
  groupLayout->addWidget (m_editCoords);
  groupLayout->setMargin (2);

  m_statusBar.addPermanentWidget (m_groupUnits);
}

void StatusBar::createZoom ()
{
  m_cmbZoom = new QComboBox ();
  m_cmbZoom->setEnabled (false); // Disabled until file is opened
  m_cmbZoom->setMinimumWidth (MIN_WIDTH_ZOOM);
  m_cmbZoom->addItem (*LABEL_ZOOM_16_TO_1);
  m_cmbZoom->addItem (*LABEL_ZOOM_16_TO_1_FARTHER);
  m_cmbZoom->addItem (*LABEL_ZOOM_8_TO_1_CLOSER);
  m_cmbZoom->addItem (*LABEL_ZOOM_8_TO_1);
  m_cmbZoom->addItem (*LABEL_ZOOM_8_TO_1_FARTHER);
  m_cmbZoom->addItem (*LABEL_ZOOM_4_TO_1_CLOSER);
  m_cmbZoom->addItem (*LABEL_ZOOM_4_TO_1);
  m_cmbZoom->addItem (*LABEL_ZOOM_4_TO_1_FARTHER);
  m_cmbZoom->addItem (*LABEL_ZOOM_2_TO_1_CLOSER);
  m_cmbZoom->addItem (*LABEL_ZOOM_2_TO_1);
  m_cmbZoom->addItem (*LABEL_ZOOM_2_TO_1_FARTHER);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_1_CLOSER);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_1);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_1_FARTHER);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_2_CLOSER);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_2);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_2_FARTHER);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_4_CLOSER);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_4);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_4_FARTHER);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_8_CLOSER);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_8);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_8_FARTHER);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_16_CLOSER);
  m_cmbZoom->addItem (*LABEL_ZOOM_1_TO_16);
  m_cmbZoom->addItem (*LABEL_ZOOM_FILL);
  m_cmbZoom->setCurrentText (*LABEL_ZOOM_1_TO_1);
  m_cmbZoom->setMaximumWidth (80);
  m_cmbZoom->setToolTip (tr ("Select zoom."));
  m_cmbZoom->setWhatsThis (tr("Select Zoom\n\n"
                                "Points can be more accurately placed by zooming in."));
  // Zoom combobox must use currentTextChanged rather than activated or else fill-zoom-at-startup never takes effect
  connect (m_cmbZoom, SIGNAL (currentTextChanged(const QString &)), this, SLOT (slotComboZoom (const QString &)));

  m_statusBar.addPermanentWidget (m_cmbZoom);
}

void StatusBar::createZoomLabels ()
{
  LABEL_ZOOM_16_TO_1= new QString (tr ("16:1"));
  LABEL_ZOOM_16_TO_1_FARTHER= new QString (tr ("16:1 farther"));
  LABEL_ZOOM_8_TO_1_CLOSER= new QString (tr ("8:1 closer"));
  LABEL_ZOOM_8_TO_1= new QString (tr ("8:1"));
  LABEL_ZOOM_8_TO_1_FARTHER= new QString (tr ("8:1 farther"));
  LABEL_ZOOM_4_TO_1_CLOSER= new QString (tr ("4:1 closer"));
  LABEL_ZOOM_4_TO_1= new QString (tr ("4:1"));
  LABEL_ZOOM_4_TO_1_FARTHER= new QString (tr ("4:1 farther"));
  LABEL_ZOOM_2_TO_1_CLOSER= new QString (tr ("2:1 closer"));
  LABEL_ZOOM_2_TO_1= new QString (tr ("2:1"));
  LABEL_ZOOM_2_TO_1_FARTHER= new QString (tr ("2:1 farther"));
  LABEL_ZOOM_1_TO_1_CLOSER= new QString (tr ("1:1 closer"));
  LABEL_ZOOM_1_TO_1= new QString (tr ("1:1"));
  LABEL_ZOOM_1_TO_1_FARTHER= new QString (tr ("1:1 farther"));
  LABEL_ZOOM_1_TO_2_CLOSER= new QString (tr ("1:2 closer"));
  LABEL_ZOOM_1_TO_2= new QString (tr ("1:2"));
  LABEL_ZOOM_1_TO_2_FARTHER= new QString (tr ("1:2 farther"));
  LABEL_ZOOM_1_TO_4_CLOSER= new QString (tr ("1:4 closer"));
  LABEL_ZOOM_1_TO_4= new QString (tr ("1:4"));
  LABEL_ZOOM_1_TO_4_FARTHER= new QString (tr ("1:4 farther"));
  LABEL_ZOOM_1_TO_8_CLOSER= new QString (tr ("1:8 closer"));
  LABEL_ZOOM_1_TO_8= new QString (tr ("1:8"));
  LABEL_ZOOM_1_TO_8_FARTHER= new QString (tr ("1:8 farther"));
  LABEL_ZOOM_1_TO_16_CLOSER= new QString (tr ("1:16 closer"));
  LABEL_ZOOM_1_TO_16= new QString (tr ("1:16"));
  LABEL_ZOOM_FILL= new QString (tr ("Fill"));
  LABEL_ZOOM_PREVIOUS= new QString (tr ("Previous"));
}

void StatusBar::createZoomMaps ()
{
  m_zoomMapToLabel [ZOOM_16_TO_1] = *LABEL_ZOOM_16_TO_1;
  m_zoomMapToLabel [ZOOM_16_TO_1_FARTHER] = *LABEL_ZOOM_16_TO_1_FARTHER;
  m_zoomMapToLabel [ZOOM_8_TO_1_CLOSER] = *LABEL_ZOOM_8_TO_1_CLOSER;
  m_zoomMapToLabel [ZOOM_8_TO_1] = *LABEL_ZOOM_8_TO_1;
  m_zoomMapToLabel [ZOOM_8_TO_1_FARTHER] = *LABEL_ZOOM_8_TO_1_FARTHER;
  m_zoomMapToLabel [ZOOM_4_TO_1_CLOSER] = *LABEL_ZOOM_4_TO_1_CLOSER;
  m_zoomMapToLabel [ZOOM_4_TO_1] = *LABEL_ZOOM_4_TO_1;
  m_zoomMapToLabel [ZOOM_4_TO_1_FARTHER] = *LABEL_ZOOM_4_TO_1_FARTHER;
  m_zoomMapToLabel [ZOOM_2_TO_1_CLOSER] = *LABEL_ZOOM_2_TO_1_CLOSER;
  m_zoomMapToLabel [ZOOM_2_TO_1] = *LABEL_ZOOM_2_TO_1;
  m_zoomMapToLabel [ZOOM_2_TO_1_FARTHER] = *LABEL_ZOOM_2_TO_1_FARTHER;
  m_zoomMapToLabel [ZOOM_1_TO_1_CLOSER] = *LABEL_ZOOM_1_TO_1_CLOSER;
  m_zoomMapToLabel [ZOOM_1_TO_1] = *LABEL_ZOOM_1_TO_1;
  m_zoomMapToLabel [ZOOM_1_TO_1_FARTHER] = *LABEL_ZOOM_1_TO_1_FARTHER;
  m_zoomMapToLabel [ZOOM_1_TO_2_CLOSER] = *LABEL_ZOOM_1_TO_2_CLOSER;
  m_zoomMapToLabel [ZOOM_1_TO_2] = *LABEL_ZOOM_1_TO_2;
  m_zoomMapToLabel [ZOOM_1_TO_2_FARTHER] = *LABEL_ZOOM_1_TO_2_FARTHER;
  m_zoomMapToLabel [ZOOM_1_TO_4_CLOSER] = *LABEL_ZOOM_1_TO_4_CLOSER;
  m_zoomMapToLabel [ZOOM_1_TO_4] = *LABEL_ZOOM_1_TO_4;
  m_zoomMapToLabel [ZOOM_1_TO_4_FARTHER] = *LABEL_ZOOM_1_TO_4_FARTHER;
  m_zoomMapToLabel [ZOOM_1_TO_8_CLOSER] = *LABEL_ZOOM_1_TO_8_CLOSER;
  m_zoomMapToLabel [ZOOM_1_TO_8] = *LABEL_ZOOM_1_TO_8;
  m_zoomMapToLabel [ZOOM_1_TO_8_FARTHER] = *LABEL_ZOOM_1_TO_8_FARTHER;
  m_zoomMapToLabel [ZOOM_1_TO_16_CLOSER] = *LABEL_ZOOM_1_TO_16_CLOSER;
  m_zoomMapToLabel [ZOOM_1_TO_16] = *LABEL_ZOOM_1_TO_16;
  m_zoomMapToLabel [ZOOM_FILL] = *LABEL_ZOOM_FILL;

  m_zoomMapFromLabel [*LABEL_ZOOM_16_TO_1] = ZOOM_16_TO_1;
  m_zoomMapFromLabel [*LABEL_ZOOM_16_TO_1_FARTHER] = ZOOM_16_TO_1_FARTHER;
  m_zoomMapFromLabel [*LABEL_ZOOM_8_TO_1_CLOSER] = ZOOM_8_TO_1_CLOSER;
  m_zoomMapFromLabel [*LABEL_ZOOM_8_TO_1] = ZOOM_8_TO_1;
  m_zoomMapFromLabel [*LABEL_ZOOM_8_TO_1_FARTHER] = ZOOM_8_TO_1_FARTHER;
  m_zoomMapFromLabel [*LABEL_ZOOM_4_TO_1_CLOSER] = ZOOM_4_TO_1_CLOSER;
  m_zoomMapFromLabel [*LABEL_ZOOM_4_TO_1] = ZOOM_4_TO_1;
  m_zoomMapFromLabel [*LABEL_ZOOM_4_TO_1_FARTHER] = ZOOM_4_TO_1_FARTHER;
  m_zoomMapFromLabel [*LABEL_ZOOM_2_TO_1_CLOSER] = ZOOM_2_TO_1_CLOSER;
  m_zoomMapFromLabel [*LABEL_ZOOM_2_TO_1] = ZOOM_2_TO_1;
  m_zoomMapFromLabel [*LABEL_ZOOM_2_TO_1_FARTHER] = ZOOM_2_TO_1_FARTHER;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_1_CLOSER] = ZOOM_1_TO_1_CLOSER;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_1] = ZOOM_1_TO_1;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_1_FARTHER] = ZOOM_1_TO_1_FARTHER;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_2_CLOSER] = ZOOM_1_TO_2_CLOSER;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_2] = ZOOM_1_TO_2;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_2_FARTHER] = ZOOM_1_TO_2_FARTHER;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_4_CLOSER] = ZOOM_1_TO_4_CLOSER;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_4] = ZOOM_1_TO_4;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_4_FARTHER] = ZOOM_1_TO_4_FARTHER;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_8_CLOSER] = ZOOM_1_TO_8_CLOSER;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_8] = ZOOM_1_TO_8;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_8_FARTHER] = ZOOM_1_TO_8_FARTHER;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_16_CLOSER] = ZOOM_1_TO_16_CLOSER;
  m_zoomMapFromLabel [*LABEL_ZOOM_1_TO_16] = ZOOM_1_TO_16;
  m_zoomMapFromLabel [*LABEL_ZOOM_FILL] = ZOOM_FILL;
}

QString StatusBar::labelCoordsGraph () const
{
  return QString ("%1:").arg (QObject::tr ("Coordinates (graph)"));
}

QString StatusBar::labelCoordsScreen () const
{
  return QString ("%1:").arg (QObject::tr ("Coordinates (pixels)"));
}

QString StatusBar::labelResolutionGraph () const
{
  return QString ("%1:").arg (QObject::tr ("Resolution (graph)"));
}

void StatusBar::setCoordinates (const QString &coordsScreen,
                                const QString &coordsGraph,
                                const QString &resolutionGraph)
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "StatusBar::setCoordinates"
//                               << " screen=" << coordsScreen.toLatin1 ().data ()
//                               << " graph=" << coordsGraph.toLatin1 ().data ()
//                               << " resolution=" << resolutionGraph.toLatin1 ().data ();

  if (m_cmbUnits->isEnabled ()) {

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
  LOG4CPP_DEBUG_S ((*mainCat)) << "StatusBar::showTemporaryMessage"
                               << " mode=" << statusBarModeToString (m_statusBarMode).toLatin1 ().data ()
                               << " message=" << message.toLatin1 ().data ();

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

  ENGAUGE_ASSERT (m_zoomMapFromLabel.contains (text));
  ZoomFactor zoomFactor = m_zoomMapFromLabel [text];
  emit signalZoom (zoomFactor);
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
  m_timer = nullptr;

  m_statusBar.show();
}

void StatusBar::slotZoom(int zoom)
{
  LOG4CPP_INFO_S ((*mainCat)) << "StatusBar::slotZoom zoom=" << zoom;

  // Show string for the numeric zoom value
  ZoomFactor zoomFactor = static_cast<ZoomFactor> (zoom);
  ENGAUGE_ASSERT (m_zoomMapToLabel.contains (zoomFactor));
  m_cmbZoom->setCurrentText (m_zoomMapToLabel [zoomFactor]);
}

void StatusBar::updateCoordsText()
{
  if (m_cmbUnits->currentText() == labelCoordsScreen ()) {
    m_editCoords->setText (m_coordsScreen);
  } else if (m_cmbUnits->currentText()  == labelCoordsGraph ()) {
    m_editCoords->setText (m_coordsGraph);
  } else {
    m_editCoords->setText (m_resolutionGraph);
  }
}

void StatusBar::wakeUp ()
{
  if (!m_cmbUnits->isEnabled ()) {

    // First file has just been read in, so enable the widgets
    m_cmbZoom->setEnabled (true);
    m_cmbUnits->setEnabled (true);
    m_editCoords->setEnabled (true);
  }
}
