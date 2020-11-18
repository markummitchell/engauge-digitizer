/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_GUIDELINE_H
#define DLG_SETTINGS_GUIDELINE_H

#include "DlgSettingsAbstractBase.h"
#include <QString>
#include <QStringList>

class ButtonWhatsThis;
class DocumentModelGuideline;
class QComboBox;
class QGraphicsEllipseItem;
class QGraphicsItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QGridLayout;
class QPushButton;
class QSpinBox;
class ViewPreview;

/// Dialog for editing guideline settings
class DlgSettingsGuideline : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsGuideline(MainWindow &mainWindow);
  virtual ~DlgSettingsGuideline();

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);
  virtual void setSmallDialogs (bool smallDialogs);
                                                  
private slots:
  void slotCreationCircleRadius (int radius);
  void slotLineColor (const QString &);
  void slotLineWidthActive (int lineWidth);
  void slotLineWidthInactive (int lineWidth);  
  void slotWhatsThis();
  
protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout,
                       int &row);
  void createLines();
  void createLinesCartesian();
  void createLinesPolar();
  void createPreview (QGridLayout *layout, int &row);
  void killCentipede ();
  void removeOldWidgetsActive();
  void removeOldWidgetsInactive();
  void safeSetLine (QGraphicsLineItem *item,
                    const QPointF &posStart,
                    const QPointF &posStop) const;
  void safeSetLineStyle (QGraphicsLineItem *line,
                          double width);
  void updateControls();
  void updatePreview();
  void updatePreviewGeometry();
  void updatePreviewGeometryCentipedeCartesian (const QPointF &posClickScreen,
                                                double xMin,
                                                double xMax,
                                                double yMin,
                                                double yMax);
  void updatePreviewGeometryCentipedePolar (const QPointF &posClickScreen,
                                            double xMin,
                                            double xMax,
                                            double yMin,
                                            double yMax);
  void updatePreviewGeometryGuidelineCartesian (const QPointF &posClickScreen,
                                                double xMin,
                                                double xMax,
                                                double yMin,
                                                double yMax);
  void updatePreviewGeometryGuidelinePolar (const QPointF &posClickScreen,
                                            double xMin,
                                            double xMax,
                                            double yMin,
                                            double yMax);
  void updatePreviewStyle();

  ButtonWhatsThis *m_btnWhatsThis;
  
  QSpinBox *m_spinCreationCircleRadius;
  QComboBox *m_lineColor;
  QSpinBox *m_spinLineWidthActive;
  QSpinBox *m_spinLineWidthInactive;  

  QGraphicsScene *m_scenePreviewActive;
  ViewPreview *m_viewPreviewActive;

  QGraphicsScene *m_scenePreviewInactive;
  ViewPreview *m_viewPreviewInactive;

  // Drawn widgets for active
  QGraphicsLineItem *m_itemGuidelineXTActive;
  QGraphicsLineItem *m_itemGuidelineYActive;
  QGraphicsEllipseItem *m_itemGuidelineRActive;
  QGraphicsLineItem *m_itemCentipedeXTActive;
  QGraphicsLineItem *m_itemCentipedeYActive;
  QGraphicsEllipseItem *m_itemCentipedeRActive;
  QGraphicsEllipseItem *m_itemCentipedeCircleActive;

  // Drawn widgets for inactive. Note that a centipede can never be inactive
  QGraphicsLineItem *m_itemGuidelineXTInactive;
  QGraphicsLineItem *m_itemGuidelineYInactive;
  QGraphicsEllipseItem *m_itemGuidelineRInactive;
  DocumentModelGuideline *m_modelGuidelineBefore;
  DocumentModelGuideline *m_modelGuidelineAfter;
};

#endif // DLG_SETTINGS_GUIDELINE_H
