/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_SEGMENTS_H
#define DLG_SETTINGS_SEGMENTS_H

#include "DlgSettingsAbstractBase.h"
#include "GraphicsPoint.h"
#include <QImage>
#include <QList>

class DocumentModelSegments;
class QCheckBox;
class QComboBox;
class QGridLayout;
class QGraphicsScene;
class QSpinBox;
class Segment;
class ViewPreview;

typedef QList<GraphicsPoint*> GraphicsPoints;

/// Dialog for editing Segments settings, for DigitizeStateSegment.
class DlgSettingsSegments : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsSegments(MainWindow &mainWindow);
  virtual ~DlgSettingsSegments();

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotFillCorners (int state);
  void slotLineColor (const QString &);
  void slotLineWidth (int);
  void slotMinLength (const QString &);
  void slotPointSeparation (const QString &);

protected:
  virtual void handleOk ();

private:

  void clearPoints();
  void createControls (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  QImage createPreviewImage () const;
  void updateControls();
  void updatePreview();

  QSpinBox *m_spinMinLength;
  QSpinBox *m_spinPointSeparation;
  QCheckBox *m_chkFillCorners;
  QSpinBox *m_spinLineWidth;
  QComboBox *m_cmbLineColor;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  DocumentModelSegments *m_modelSegmentsBefore;
  DocumentModelSegments *m_modelSegmentsAfter;

  QList<Segment*> m_segments; // Segments extracted from image
  GraphicsPoints m_points; // Points spread along the segments

  bool m_loading; // Flag that prevents multiple preview updates during loading while controls get loaded
};

#endif // DLG_SETTINGS_SEGMENTS_H
