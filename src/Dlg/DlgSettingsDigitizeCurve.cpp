/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdSettingsDigitizeCurve.h"
#include "CursorFactory.h"
#include "CursorSize.h"
#include "DlgSettingsDigitizeCurve.h"
#include "DocumentModelDigitizeCurve.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include "PointStyle.h"
#include <QCheckBox>
#include <QComboBox>
#include <QGraphicsPixmapItem>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QLabel>
#include <qmath.h>
#include <QRadioButton>
#include <QSpinBox>
#include "Segment.h"
#include "SegmentFactory.h"
#include "ViewPreview.h"

const int IMAGE_WIDTH = 100;
const int IMAGE_HEIGHT = 100;
const int MINIMUM_HEIGHT = 450;
const int INNER_RADIUS_MAX = 64;
const int INNER_RADIUS_MIN = 0;
const int LINE_LENGTH_MIN = 2; // Min length of one line in the cursor, in pixels
const int LINE_WIDTH_MAX = 32;
const int LINE_WIDTH_MIN = 1;

DlgSettingsDigitizeCurve::DlgSettingsDigitizeCurve(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Digitize Curve"),
                           "DlgSettingsDigitizeCurve",
                           mainWindow),
  m_scenePreview (0),
  m_viewPreview (0),
  m_modelDigitizeCurveBefore (0),
  m_modelDigitizeCurveAfter (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::DlgSettingsDigitizeCurve";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsDigitizeCurve::~DlgSettingsDigitizeCurve()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::~DlgSettingsDigitizeCurve";
}

void DlgSettingsDigitizeCurve::createControls (QGridLayout *layout,
                                               int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::createControls";

  m_boxCursor = new QGroupBox (tr ("Cursor"));
  layout->addWidget (m_boxCursor, row++, 1, 1, 2);

  // Layout inside cursor group box
  QGridLayout *layoutCursor = new QGridLayout;
  m_boxCursor->setLayout (layoutCursor);
  int rowCursor = 0;

  QLabel *labelCursorType = new QLabel(tr ("Type:"));
  layoutCursor->addWidget (labelCursorType, rowCursor, 0);

  m_btnStandard = new QRadioButton (tr ("Standard cross"));
  m_btnStandard->setWhatsThis (tr ("Selects the standard cross cursor"));
  layoutCursor->addWidget (m_btnStandard, rowCursor++, 1);
  connect (m_btnStandard, SIGNAL (toggled (bool)), this, SLOT (slotCursorStandard(bool)));

  m_btnCustom = new QRadioButton (tr ("Custom cross"));
  m_btnCustom->setWhatsThis (tr ("Selects a custom cursor based on the settings selected below"));
  layoutCursor->addWidget (m_btnCustom, rowCursor++, 1);
  connect (m_btnCustom, SIGNAL (toggled (bool)), this, SLOT (slotCursorCustom(bool)));

  QLabel *labelSize = new QLabel(tr ("Size (pixels):"));
  layoutCursor->addWidget (labelSize, rowCursor, 0);

  m_cmbSize = new QComboBox;
  m_cmbSize->addItem (QString::number (CursorSizeToPixels (CURSOR_SIZE_16)), QVariant (CURSOR_SIZE_16));
  m_cmbSize->addItem (QString::number (CursorSizeToPixels (CURSOR_SIZE_32)), QVariant (CURSOR_SIZE_32));
  m_cmbSize->addItem (QString::number (CursorSizeToPixels (CURSOR_SIZE_48)), QVariant (CURSOR_SIZE_48));
  m_cmbSize->addItem (QString::number (CursorSizeToPixels (CURSOR_SIZE_64)), QVariant (CURSOR_SIZE_64));
  ENGAUGE_ASSERT (m_cmbSize->count() == NUM_CURSOR_SIZES);
  m_cmbSize->setWhatsThis (tr ("Horizontal and vertical size of the cursor in pixels"));
  layoutCursor->addWidget (m_cmbSize, rowCursor++, 1);
  connect (m_cmbSize, SIGNAL (currentIndexChanged (const QString &)), this, SLOT (slotCursorSize (const QString &)));

  QLabel *labelInnerRadius = new QLabel(tr ("Inner radius (pixels):"));
  layoutCursor->addWidget (labelInnerRadius, rowCursor, 0);

  m_spinInnerRadius = new QSpinBox;
  m_spinInnerRadius->setRange (INNER_RADIUS_MIN, INNER_RADIUS_MAX);
  m_spinInnerRadius->setWhatsThis (tr ("Radius of circle at the center of the cursor that will remain empty"));
  layoutCursor->addWidget (m_spinInnerRadius, rowCursor++, 1);
  connect (m_spinInnerRadius, SIGNAL (valueChanged(const QString &)), this, SLOT (slotCursorInnerRadius (const QString &)));

  QLabel *labelLineWidth = new QLabel(tr ("Line width (pixels):"));
  layoutCursor->addWidget (labelLineWidth, rowCursor, 0);

  m_spinLineWidth = new QSpinBox;
  m_spinLineWidth->setRange (LINE_WIDTH_MIN, LINE_WIDTH_MAX);
  m_spinLineWidth->setWhatsThis (tr ("Width of each arm of the cross of the cursor"));
  layoutCursor->addWidget (m_spinLineWidth, rowCursor++, 1);
  connect (m_spinLineWidth, SIGNAL (valueChanged(const QString &)), this, SLOT (slotCursorLineWidth (const QString &)));
}

void DlgSettingsDigitizeCurve::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
}

void DlgSettingsDigitizeCurve::createPreview (QGridLayout *layout,
                                         int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::createPreview";

  QLabel *labelPreview = new QLabel (tr ("Preview"));
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_scenePreview->setSceneRect(0,
                               0,
                               IMAGE_WIDTH,
                               IMAGE_HEIGHT);

  m_viewPreview = new ViewPreview (m_scenePreview,
                                   ViewPreview::VIEW_ASPECT_RATIO_VARIABLE,
                                   this);
  m_viewPreview->setWhatsThis (tr ("Preview window showing the currently selected cursor.\n\n"
                                   "Drag the cursor over this area to see the effects of the current settings on the cursor shape."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QWidget *DlgSettingsDigitizeCurve::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::createSubPanel";

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch (0, 1); // Empty first column
  layout->setColumnStretch (1, 0); // Labels
  layout->setColumnStretch (2, 0); // User controls
  layout->setColumnStretch (3, 1); // Empty last column

  int row = 0;
  createControls(layout, row);
  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsDigitizeCurve::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::handleOk";

  CmdSettingsDigitizeCurve *cmd = new CmdSettingsDigitizeCurve (mainWindow (),
                                                                cmdMediator ().document(),
                                                                *m_modelDigitizeCurveBefore,
                                                                *m_modelDigitizeCurveAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsDigitizeCurve::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelDigitizeCurveBefore != 0) {
    delete m_modelDigitizeCurveBefore;
  }
  if (m_modelDigitizeCurveAfter != 0) {
    delete m_modelDigitizeCurveAfter;
  }

  // Save new data
  m_modelDigitizeCurveBefore = new DocumentModelDigitizeCurve (cmdMediator.document());
  m_modelDigitizeCurveAfter = new DocumentModelDigitizeCurve (cmdMediator.document());

  // Sanity checks. Incoming defaults must be acceptable to the local limits
  ENGAUGE_ASSERT (INNER_RADIUS_MIN <= m_modelDigitizeCurveAfter->cursorInnerRadius ());
  ENGAUGE_ASSERT (INNER_RADIUS_MAX >= m_modelDigitizeCurveAfter->cursorInnerRadius ());
  ENGAUGE_ASSERT (LINE_WIDTH_MIN <= m_modelDigitizeCurveAfter->cursorLineWidth ());
  ENGAUGE_ASSERT (LINE_WIDTH_MAX >= m_modelDigitizeCurveAfter->cursorLineWidth ());

  // Populate controls
  m_btnStandard->setChecked (m_modelDigitizeCurveAfter->cursorStandardCross());
  m_btnCustom->setChecked (!m_modelDigitizeCurveAfter->cursorStandardCross());
  m_spinInnerRadius->setValue (m_modelDigitizeCurveAfter->cursorInnerRadius());
  int index = m_cmbSize->findData (QVariant (m_modelDigitizeCurveAfter->cursorSize()));
  m_cmbSize->setCurrentIndex (index);
  m_spinLineWidth->setValue (m_modelDigitizeCurveAfter->cursorLineWidth());

  updateControls();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsDigitizeCurve::setSmallDialogs(bool smallDialogs)
{
  if (!smallDialogs) {
    setMinimumHeight (MINIMUM_HEIGHT);
  }
}

void DlgSettingsDigitizeCurve::slotCursorCustom (bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::slotCursorCustom";

  m_modelDigitizeCurveAfter->setCursorStandardCross(false);
  updateControls();
  updatePreview();
}

void DlgSettingsDigitizeCurve::slotCursorInnerRadius (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::slotCursorInnerRadius";

  m_modelDigitizeCurveAfter->setCursorInnerRadius (m_spinInnerRadius->value());
  updateControls();
  updatePreview();
}

void DlgSettingsDigitizeCurve::slotCursorLineWidth (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::slotCursorLineWidth";

  m_modelDigitizeCurveAfter->setCursorLineWidth (m_spinLineWidth->value());
  updateControls();
  updatePreview();
}

void DlgSettingsDigitizeCurve::slotCursorSize (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::slotCursorSize";

  m_modelDigitizeCurveAfter->setCursorSize ((CursorSize) m_cmbSize->currentData().toInt());
  updateControls();
  updatePreview();
}

void DlgSettingsDigitizeCurve::slotCursorStandard (bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::slotCursorStandard";

  m_modelDigitizeCurveAfter->setCursorStandardCross(true);
  updateControls();
  updatePreview();
}

void DlgSettingsDigitizeCurve::updateControls()
{
  // Cursor has to fit into current extent
  bool isGoodState = 2 * (m_modelDigitizeCurveAfter->cursorInnerRadius() + LINE_LENGTH_MIN) <=
                     CursorSizeToPixels (m_modelDigitizeCurveAfter->cursorSize());
  enableOk (isGoodState);

  m_spinInnerRadius->setEnabled (m_btnCustom->isChecked());
  m_cmbSize->setEnabled (m_btnCustom->isChecked());
  m_spinLineWidth->setEnabled (m_btnCustom->isChecked());
}

void DlgSettingsDigitizeCurve::updatePreview()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsDigitizeCurve::updatePreview";

  CursorFactory cursorFactory;
  QCursor cursor = cursorFactory.generate (*m_modelDigitizeCurveAfter);
  m_viewPreview->setCursor (cursor);
}
