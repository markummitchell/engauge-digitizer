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

class ButtonWhatsThis;
class DocumentModelSegments;
class QCheckBox;
class QComboBox;
class QGridLayout;
class QGraphicsScene;
class QSpinBox;
class Segment;
class ViewPreview;

typedef QList<GraphicsPoint*> GraphicsPoints;

/// Dialog for editing Segments settings, for DigitizeStateSegment. This uses a timer
/// for the inactive opacity previewing so changing that settings results in preview
/// window temporarily showing the inactive opacity color, then the regular color
/// returns
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
  virtual void setSmallDialogs (bool smallDialogs);

private slots:
  void slotFillCorners (int state);
  void slotInactiveOpacity (const QString &);
  void slotLineColor (const QString &);
  void slotLineWidthActive (int);
  void slotLineWidthInactive (int);  
  void slotMinLength (const QString &);
  void slotPointSeparation (const QString &);
  void slotWhatsThis();
  
protected:
  virtual void handleOk ();

private:

  enum HoverState {
    HOVER_ACTIVE,
    HOVER_INACTIVE
  };

  void clearPointsOneScene (GraphicsPoints &points);
  void createControls (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  QImage createPreviewImage () const;
  void updateControls();
  void updatePreview();
  void updatePreviewOneScene (QGraphicsScene *scenePreview,
                              QList<Segment*> &segments,
                              GraphicsPoints &points,
                              HoverState hoverState);

  ButtonWhatsThis *m_btnWhatsThis;
  QSpinBox *m_spinMinLength;
  QSpinBox *m_spinPointSeparation;
  QCheckBox *m_chkFillCorners;
  QSpinBox *m_spinLineWidthActive;
  QSpinBox *m_spinLineWidthInactive;  
  QComboBox *m_cmbLineColor;
  QComboBox *m_cmbInactiveOpacity;

  QGraphicsScene *m_scenePreviewActive;
  QGraphicsScene *m_scenePreviewInactive;
  ViewPreview *m_viewPreviewActive;
  ViewPreview *m_viewPreviewInactive;

  DocumentModelSegments *m_modelSegmentsBefore;
  DocumentModelSegments *m_modelSegmentsAfter;

  QList<Segment*> m_segmentsActive; // Segments extracted from image
  QList<Segment*> m_segmentsInactive; // Segments extracted from image
  GraphicsPoints m_pointsActive; // Points spread along the segments
  GraphicsPoints m_pointsInactive; // Points spread along the segments

  bool m_loading; // Flag that prevents multiple preview updates during loading while controls get loaded
};

#endif // DLG_SETTINGS_SEGMENTS_H
