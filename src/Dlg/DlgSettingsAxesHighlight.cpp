#include "CmdMediator.h"
#include "CmdSettingsAxesHighlight.h"
#include "CoordScale.h"
#include "DlgSettingsAxesHighlight.h"
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

DlgSettingsAxesHighlight::DlgSettingsAxesHighlight(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Axes Highlight", mainWindow),
  m_modelAxesHighlightBefore (0),
  m_modelAxesHighlightAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsAxesHighlight::createPreview (QGridLayout *layout,
                                              int &row)
{
  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview, this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the displayed grid lines."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QWidget *DlgSettingsAxesHighlight::createSubPanel ()
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

  return subPanel;
}

void DlgSettingsAxesHighlight::createControls (QGridLayout *layout,
                                               int &row)
{  
  QGroupBox *groupBox = new QGroupBox (tr ("Axes Highlight Lifetime"));
  layout->addWidget (groupBox, row++, 1);

  QVBoxLayout *layoutLifetime = new QVBoxLayout;
  groupBox->setLayout (layoutLifetime);

  m_btnNever = new QRadioButton ("Do not show", groupBox);
  m_btnNever->setWhatsThis (tr ("Do not show axes highlight after changing axes points."));
  layoutLifetime->addWidget (m_btnNever);

  m_btn2Seconds = new QRadioButton ("Show for 2 seconds", groupBox);
  m_btn2Seconds->setWhatsThis (tr ("Show axes highlight for 2 seconds after changing axes points."));
  layoutLifetime->addWidget (m_btn2Seconds);

  m_btn10Seconds = new QRadioButton ("Show for 10 seconds", groupBox);
  m_btn10Seconds->setWhatsThis (tr ("Show axes highlight for 10 seconds after changing axes points."));
  layoutLifetime->addWidget (m_btn10Seconds);

  m_btnAlways = new QRadioButton ("Show always", groupBox);
  m_btnAlways->setWhatsThis (tr ("Always show axes highlight."));
  layoutLifetime->addWidget (m_btnAlways);

  m_groupLifetime = new QButtonGroup;
  m_groupLifetime->addButton (m_btnNever);
  m_groupLifetime->addButton (m_btn2Seconds);
  m_groupLifetime->addButton (m_btn10Seconds);
  m_groupLifetime->addButton (m_btnAlways);
  connect (m_groupLifetime, SIGNAL (buttonReleased (QAbstractButton*)), this, SLOT (slotGroupLifetime (QAbstractButton*)));
}

void DlgSettingsAxesHighlight::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesHighlight::handleOk";

  CmdSettingsAxesHighlight *cmd = new CmdSettingsAxesHighlight (mainWindow (),
                                                                cmdMediator ().document(),
                                                                *m_modelAxesHighlightBefore,
                                                                *m_modelAxesHighlightAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsAxesHighlight::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesHighlight::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelAxesHighlightBefore != 0) {
    delete m_modelAxesHighlightBefore;
  }
  if (m_modelAxesHighlightAfter != 0) {
    delete m_modelAxesHighlightAfter;
  }

  // Save new data
  m_modelAxesHighlightBefore = new DocumentModelAxesHighlight (cmdMediator.document());
  m_modelAxesHighlightAfter = new DocumentModelAxesHighlight (cmdMediator.document());

  switch (m_modelAxesHighlightAfter->axesHighlight())
  {
    case AXES_HIGHLIGHT_NONE:
      m_btnNever->setChecked (true);
      break;

    case AXES_HIGHLIGHT_2_SECONDS:
      m_btn2Seconds->setChecked (true);
      break;

    case AXES_HIGHLIGHT_10_SECONDS:
      m_btn10Seconds->setChecked (true);
      break;

    case AXES_HIGHLIGHT_FOREVER:
      m_btnAlways->setChecked (true);
      break;

    default:
      Q_ASSERT (false);
  }

  m_scenePreview->clear();
  m_scenePreview->addPixmap (cmdMediator.document().pixmap());

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsAxesHighlight::slotGroupLifetime (QAbstractButton* btn)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAxesHighlight::slotGroupLifetime";

  if (btn == dynamic_cast<QAbstractButton*> (m_btnNever)) {
    m_modelAxesHighlightAfter->setAxesHighlight(AXES_HIGHLIGHT_NONE);
  } else if (btn == dynamic_cast<QAbstractButton*> (m_btn2Seconds)) {
    m_modelAxesHighlightAfter->setAxesHighlight(AXES_HIGHLIGHT_2_SECONDS);
  } else if (btn == dynamic_cast<QAbstractButton*> (m_btn10Seconds)) {
    m_modelAxesHighlightAfter->setAxesHighlight(AXES_HIGHLIGHT_10_SECONDS);
  } else {
    m_modelAxesHighlightAfter->setAxesHighlight(AXES_HIGHLIGHT_FOREVER);
  }

  updateControls ();
  updatePreview();
}

void DlgSettingsAxesHighlight::updateControls ()
{
  enableOk (true);
}

void DlgSettingsAxesHighlight::updatePreview()
{

}
