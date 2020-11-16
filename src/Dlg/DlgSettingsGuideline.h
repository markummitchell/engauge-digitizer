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

class DocumentModelGuideline;
class QComboBox;
class QGraphicsEllipseItem;
class QGraphicsItem;
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

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout,
                       int &row);
  void createPreview (QGridLayout *layout, int &row);
  void killCentipede ();
  void updateControls();
  void updatePreview();

  QSpinBox *m_spinCreationCircleRadius;
  QComboBox *m_lineColor;
  QSpinBox *m_spinLineWidthActive;
  QSpinBox *m_spinLineWidthInactive;  

  QGraphicsScene *m_scenePreviewActive;
  ViewPreview *m_viewPreviewActive;

  QGraphicsScene *m_scenePreviewInactive;
  ViewPreview *m_viewPreviewInactive;

  // Drawn widgets for active
  QGraphicsItem *m_itemGuidelineXTActive;
  QGraphicsItem *m_itemGuidelineYRActive;
  QGraphicsEllipseItem *m_itemCircleActive;
  QGraphicsItem *m_itemCentipedeXTActive;
  QGraphicsItem *m_itemCentipdedYRActive;

  // Drawn widgets for inactive
  QGraphicsItem *m_itemGuidelineXTInactive;
  QGraphicsItem *m_itemGuidelineYRInactive;
  QGraphicsEllipseItem *m_itemCircleInactive;
  QGraphicsItem *m_itemCentipedeXTInactive;
  QGraphicsItem *m_itemCentipdedYRInactive;

  DocumentModelGuideline *m_modelGuidelineBefore;
  DocumentModelGuideline *m_modelGuidelineAfter;
};

#endif // DLG_SETTINGS_GUIDELINE_H
