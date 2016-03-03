/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <QComboBox>
#include <QObject>
#include "StatusBarMode.h"

class QFrame;
class QStatusBar;
class QTextEdit;
class QTimer;

/// Wrapper around QStatusBar to manage permanent widgets. This class does not inherit from QStatusBar since QApplication
/// automatically sets up its own QStatusBar
class StatusBar : public QObject
{
  Q_OBJECT;

public:
  /// Single constructor that accepts the previously-constructed standard QStatusBar.
  StatusBar(QStatusBar &statusBar);
  ~StatusBar();

  /// Populate the coordinates fields. Unavailable values are empty. Html-encoding to highlight with colors is supported
  void setCoordinates (const QString &coordsScreen,
                       const QString &coordsGraph,
                       const QString &resolutionGraph);

  /// Set the status bar visibility mode.
  void setStatusBarMode (StatusBarMode statusBarMode);

  /// Show temporary message in status bar. After a short interval the message will disappear
  void showTemporaryMessage(const QString &message);

  /// Current mode for status bar visibility. This is tracked locally so this class knows when to hide/show the status bar
  StatusBarMode statusBarMode() const { return m_statusBarMode; }

  /// Enable all widgets in the status bar. This is called just after a Document becomes active.
  void wakeUp ();

public slots:
  /// Receive zoom selection from MainWindow.
  void slotZoom(int);

private slots:
  /// Receive new selection of coordinate units.
  void slotComboUnits (const QString &);

  /// Receive zoom selection from StatusBar
  void slotComboZoom (const QString &);

  /// Receive signal that message just changed. Transitions from hidden-to-visible are handled elsewhere, but this
  /// method handles visible-to-invisible transitions
  void slotStatusBarChanged(const QString &message);

  /// Receive timeout after displaying temporary message. The status bar gets hidden
  void slotTimeout();

signals:
  /// Send zoom factor, that was just selected in the status bar, to MainWindow.
  void signalZoom (int);

private:
  StatusBar();

  void createGroupUnits ();
  void createZoom ();
  void updateCoordsText ();

  enum StatusBarUnits {
    STATUS_BAR_UNITS_COORDS_SCREEN,
    STATUS_BAR_UNITS_COORDS_GRAPH,
    STATUS_BAR_UNITS_RESOLUTION_GRAPH
  };

  QStatusBar &m_statusBar;

  QComboBox *m_cmbZoom;

  QFrame *m_groupUnits; /// Use this like a QGroupBox but without external padding
  QComboBox *m_cmbUnits;
  QTextEdit *m_editCoords;

  QString m_coordsScreen; /// Text for m_editCoords
  QString m_coordsGraph; /// Text for m_editCoords
  QString m_resolutionGraph; /// Text for m_editCoords

  StatusBarMode m_statusBarMode;

  QTimer *m_timer;
};

#endif // STATUS_BAR_H
