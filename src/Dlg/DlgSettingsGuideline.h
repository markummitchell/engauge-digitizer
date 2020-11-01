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
class QGridLayout;
class QPushButton;
class QSpinBox;

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

private slots:
  void slotLineColor (const QString &);
  void slotLineWidth (int lineWidth);

protected:
  virtual void handleOk ();

private:

  void createControls (QGridLayout *layout,
                       int &row);
  void killCentipede ();
  void updateControls();
  void updatePreview();

  QSpinBox *m_spinCreationCircleRadius;
  QComboBox *m_lineColor;
  QSpinBox *m_spinLineWidth;

  DocumentModelGuideline *m_modelGuidelineBefore;
  DocumentModelGuideline *m_modelGuidelineAfter;
};

#endif // DLG_SETTINGS_GUIDELINE_H
