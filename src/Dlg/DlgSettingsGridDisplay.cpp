#include "CmdMediator.h"
#include "CmdSettingsGridDisplay.h"
#include "CoordScale.h"
#include "DlgSettingsGridDisplay.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QComboBox>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <qmath.h>
#include "ViewPreview.h"

const int COUNT_MIN = 1;
const int COUNT_MAX = 100;
const int COUNT_DECIMALS = 0;

DlgSettingsGridDisplay::DlgSettingsGridDisplay(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Grid Display", mainWindow),
  m_modelGridDisplayBefore (0),
  m_modelGridDisplayAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsGridDisplay::createPreview (QGridLayout *layout,
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

QWidget *DlgSettingsGridDisplay::createSubPanel ()
{
  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // X
  layout->setColumnStretch(2, 0); // Y
  layout->setColumnStretch(3, 1); // Empty first column

  int row = 0;
  createX (layout, row);
  createY (layout, row);
  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsGridDisplay::createX (QGridLayout *layout,
                                      int &row)
{
  QString titleX = "X Grid Lines";
  if (false) {
    titleX = QString (QChar (0x98, 0x03)) + QString (" Grid Lines");
  }
  QGroupBox *groupX = new QGroupBox (titleX);
  layout->addWidget (groupX, row, 1);

  QGridLayout *layoutGroup = new QGridLayout (groupX);
  groupX->setLayout (layoutGroup);

  QLabel *labelDisable = new QLabel ("Disable:");
  layoutGroup->addWidget (labelDisable, 0, 0);

  m_cmbDisableX = new QComboBox;
  m_cmbDisableX->setWhatsThis (tr ("Disabled value.\n\nThe X grid lines are specified "
                                   "using only three values at a time. For flexibility, four values are offered so you must chose "
                                   "which value is disabled. Once disabled, that value is simply updated as the other values change"));
  m_cmbDisableX->addItem(DISABLE_COUNT, QVariant (GRID_COORD_DISABLE_COUNT));
  m_cmbDisableX->addItem(DISABLE_START, QVariant (GRID_COORD_DISABLE_START));
  m_cmbDisableX->addItem(DISABLE_STEP, QVariant (GRID_COORD_DISABLE_STEP));
  m_cmbDisableX->addItem(DISABLE_STOP, QVariant (GRID_COORD_DISABLE_STOP));
  connect (m_cmbDisableX, SIGNAL (currentIndexChanged (const QString &)), this, SLOT (slotDisableX (const QString &)));
  layoutGroup->addWidget (m_cmbDisableX, 0, 1);

  QLabel *labelCount = new QLabel ("Count:");
  layoutGroup->addWidget (labelCount, 1, 0);

  m_editCountX = new QLineEdit;
  m_editCountX->setWhatsThis (tr ("Number of X grid lines.\n\nThe number of X grid lines must "
                                  "be entered as an integer greater than zero"));
  m_editCountX->setValidator (new QDoubleValidator (COUNT_MIN, COUNT_MAX, COUNT_DECIMALS));
  connect (m_editCountX, SIGNAL (textChanged (const QString &)), this, SLOT  (slotCountX (const QString &)));
  layoutGroup->addWidget (m_editCountX, 1, 1);

  QLabel *labelStart = new QLabel ("Start:");
  layoutGroup->addWidget (labelStart, 2, 0);

  m_editStartX = new QLineEdit;
  m_editStartX->setWhatsThis (tr ("Value of the first X grid line.\n\nThe start value cannot "
                                  "be greater than the stop value"));
  m_editStartX->setValidator (new QDoubleValidator ());
  connect (m_editStartX, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStartX (const QString &)));
  layoutGroup->addWidget (m_editStartX, 2, 1);

  QLabel *labelStep = new QLabel ("Step:");
  layoutGroup->addWidget (labelStep, 3, 0);

  m_editStepX = new QLineEdit;
  m_editStepX->setWhatsThis (tr ("Difference in value between two successive X grid lines.\n\n"
                                 "The step value must be greater than zero"));
  m_editStepX->setValidator (new QDoubleValidator ());
  connect (m_editStepX, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStepX (const QString &)));
  layoutGroup->addWidget (m_editStepX, 3, 1);

  QLabel *labelStop = new QLabel ("Stop:");
  layoutGroup->addWidget (labelStop, 4, 0);

  m_editStopX = new QLineEdit;
  m_editStopX->setWhatsThis (tr ("Value of the last X grid line.\n\nThe stop value cannot "
                                 "be less than the start value"));
  m_editStopX->setValidator (new QDoubleValidator ());
  connect (m_editStopX, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStopX (const QString &)));
  layoutGroup->addWidget (m_editStopX, 4, 1);
}

void DlgSettingsGridDisplay::createY (QGridLayout *layout,
                                      int &row)
{
  QString titleY =  "Y Grid Lines";
  if (false) {
    titleY = QString ("R Grid Lines");
  }
  QGroupBox *groupY = new QGroupBox (titleY);
  layout->addWidget (groupY, row++, 2);

  QGridLayout *layoutGroup = new QGridLayout (groupY);
  groupY->setLayout (layoutGroup);

  QLabel *labelDisable = new QLabel ("Disable:");
  layoutGroup->addWidget (labelDisable, 0, 0);

  m_cmbDisableY = new QComboBox;
  m_cmbDisableY->setWhatsThis (tr ("Disabled value.\n\nThe Y grid lines are specified "
                                   "using only three values at a time. For flexibility, four values are offered so you must chose "
                                   "which value is disabled. Once disabled, that value is simply updated as the other values change"));
  m_cmbDisableY->addItem(DISABLE_COUNT, QVariant (GRID_COORD_DISABLE_COUNT));
  m_cmbDisableY->addItem(DISABLE_START, QVariant (GRID_COORD_DISABLE_START));
  m_cmbDisableY->addItem(DISABLE_STEP, QVariant (GRID_COORD_DISABLE_STEP));
  m_cmbDisableY->addItem(DISABLE_STOP, QVariant (GRID_COORD_DISABLE_STOP));
  connect (m_cmbDisableY, SIGNAL (currentTextChanged (const QString &)), this, SLOT  (slotDisableY (const QString &)));
  layoutGroup->addWidget (m_cmbDisableY, 0, 1);

  QLabel *labelCount = new QLabel ("Count:");
  layoutGroup->addWidget (labelCount, 1, 0);

  m_editCountY = new QLineEdit;
  m_editCountY->setWhatsThis (tr ("Number of Y grid lines.\n\nThe number of Y grid lines must "
                                  "be entered as an integer greater than zero"));
  m_editCountY->setValidator (new QDoubleValidator (COUNT_MIN, COUNT_MAX, COUNT_DECIMALS));
  connect (m_editCountY, SIGNAL (textChanged (const QString &)), this, SLOT  (slotCountY (const QString &)));
  layoutGroup->addWidget (m_editCountY, 1, 1);

  QLabel *labelStart = new QLabel ("Start:");
  layoutGroup->addWidget (labelStart, 2, 0);

  m_editStartY = new QLineEdit;
  m_editStartY->setWhatsThis (tr ("Value of the first Y grid line.\n\nThe start value cannot "
                                  "be greater than the stop value"));
  m_editStartY->setValidator (new QDoubleValidator ());
  connect (m_editStartY, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStartY (const QString &)));
  layoutGroup->addWidget (m_editStartY, 2, 1);

  QLabel *labelStep = new QLabel ("Step:");
  layoutGroup->addWidget (labelStep, 3, 0);

  m_editStepY = new QLineEdit;
  m_editStepY->setWhatsThis (tr ("Difference in value between two successive Y grid lines.\n\n"
                                 "The step value must be greater than zero"));
  m_editStepY->setValidator (new QDoubleValidator ());
  connect (m_editStepY, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStepY (const QString &)));
  layoutGroup->addWidget (m_editStepY, 3, 1);

  QLabel *labelStop = new QLabel ("Stop:");
  layoutGroup->addWidget (labelStop, 4, 0);

  m_editStopY = new QLineEdit;
  m_editStopY->setWhatsThis (tr ("Value of the last Y grid line.\n\nThe stop value cannot "
                                 "be less than the start value"));
  m_editStopY->setValidator (new QDoubleValidator ());
  connect (m_editStopY, SIGNAL (textChanged (const QString &)), this, SLOT  (slotStopY (const QString &)));
  layoutGroup->addWidget (m_editStopY, 4, 1);
}

void DlgSettingsGridDisplay::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::handleOk";

  CmdSettingsGridDisplay *cmd = new CmdSettingsGridDisplay (mainWindow (),
                                                            cmdMediator ().document(),
                                                            *m_modelGridDisplayBefore,
                                                            *m_modelGridDisplayAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsGridDisplay::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::load";

  setCmdMediator (cmdMediator);

  if (m_modelGridDisplayBefore != 0) {
    delete m_modelGridDisplayBefore;
  }
  if (m_modelGridDisplayAfter != 0) {
    delete m_modelGridDisplayAfter;
  }

  m_modelGridDisplayBefore = new DocumentModelGridDisplay (cmdMediator.document());
  m_modelGridDisplayAfter = new DocumentModelGridDisplay (cmdMediator.document());

  int indexDisableX = m_cmbDisableX->findData (QVariant (m_modelGridDisplayAfter->gridCoordDisableX()));
  m_cmbDisableX->setCurrentIndex (indexDisableX);

  m_editCountX->setText(QString::number(m_modelGridDisplayAfter->countX()));
  m_editStartX->setText(QString::number(m_modelGridDisplayAfter->startX()));
  m_editStepX->setText(QString::number(m_modelGridDisplayAfter->stepX()));
  m_editStopX->setText(QString::number(m_modelGridDisplayAfter->stopX()));

  int indexDisableY = m_cmbDisableX->findData (QVariant (m_modelGridDisplayAfter->gridCoordDisableY()));
  m_cmbDisableY->setCurrentIndex (indexDisableY);

  m_editCountY->setText(QString::number(m_modelGridDisplayAfter->countY()));
  m_editStartY->setText(QString::number(m_modelGridDisplayAfter->startY()));
  m_editStepY->setText(QString::number(m_modelGridDisplayAfter->stepY()));
  m_editStopY->setText(QString::number(m_modelGridDisplayAfter->stopY()));

  m_scenePreview->clear();
  m_scenePreview->addPixmap (cmdMediator.document().pixmap());

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsGridDisplay::slotCountX(const QString &countX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotCountX";

  m_modelGridDisplayAfter->setCountX(countX.toInt());
  updateDependentParameterX ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotCountY(const QString &countY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotCountY";

  m_modelGridDisplayAfter->setCountY(countY.toInt());
  updateDependentParameterY ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotDisableX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotDisableX";

  GridCoordDisable gridCoordDisable = (GridCoordDisable) m_cmbDisableX->currentData().toInt();
  m_modelGridDisplayAfter->setGridCoordDisableX(gridCoordDisable);
  updateDependentParameterX ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotDisableY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotDisableY";

  GridCoordDisable gridCoordDisable = (GridCoordDisable) m_cmbDisableY->currentData().toInt();
  m_modelGridDisplayAfter->setGridCoordDisableY(gridCoordDisable);
  updateDependentParameterY ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStartX(const QString &startX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStartX";

  m_modelGridDisplayAfter->setStartX(startX.toDouble());
  updateDependentParameterX ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStartY(const QString &startY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStartY";

  m_modelGridDisplayAfter->setStartY(startY.toDouble());
  updateDependentParameterY ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStepX(const QString &stepX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStepX";

  m_modelGridDisplayAfter->setStepX(stepX.toDouble());
  updateDependentParameterX ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStepY(const QString &stepY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStepY";

  m_modelGridDisplayAfter->setStepY(stepY.toDouble());
  updateDependentParameterY ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStopX(const QString &stopX)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStopX";

  m_modelGridDisplayAfter->setStopX(stopX.toDouble());
  updateDependentParameterX ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::slotStopY(const QString &stopY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::slotStopY";

  m_modelGridDisplayAfter->setStopY(stopY.toDouble());
  updateDependentParameterY ();
  updateControls ();
  updatePreview();
}

void DlgSettingsGridDisplay::updateControls ()
{
  GridCoordDisable disableX = (GridCoordDisable) m_cmbDisableX->currentData().toInt();
  m_editCountX->setEnabled (disableX != GRID_COORD_DISABLE_COUNT);
  m_editStartX->setEnabled (disableX != GRID_COORD_DISABLE_START);
  m_editStepX->setEnabled (disableX != GRID_COORD_DISABLE_STEP);
  m_editStopX->setEnabled (disableX != GRID_COORD_DISABLE_STOP);

  GridCoordDisable disableY = (GridCoordDisable) m_cmbDisableY->currentData().toInt();
  m_editCountY->setEnabled (disableY != GRID_COORD_DISABLE_COUNT);
  m_editStartY->setEnabled (disableY != GRID_COORD_DISABLE_START);
  m_editStepY->setEnabled (disableY != GRID_COORD_DISABLE_STEP);
  m_editStopY->setEnabled (disableY != GRID_COORD_DISABLE_STOP);

  enableOk (!m_editCountX->text().isEmpty () &&
            !m_editCountY->text().isEmpty () &&
            !m_editStartX->text().isEmpty () &&
            !m_editStartY->text().isEmpty () &&
            !m_editStepX->text().isEmpty () &&
            !m_editStepY->text().isEmpty () &&
            !m_editStopX->text().isEmpty () &&
            !m_editStopY->text().isEmpty ());
}

void DlgSettingsGridDisplay::updateDependentParameterX ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::updateDependentParameterX";

  CoordScale coordScale = cmdMediator().document().modelCoords().coordScaleXTheta();
  double count = m_modelGridDisplayAfter->countX ();
  double start = m_modelGridDisplayAfter->startX ();
  double step = m_modelGridDisplayAfter->stepX ();
  double stop = m_modelGridDisplayAfter->stopX ();

  switch (m_modelGridDisplayAfter->gridCoordDisableX())
  {
    case GRID_COORD_DISABLE_COUNT:
      {
        bool computationSucceeded = false;
        if (coordScale == COORD_SCALE_LINEAR) {
          if (step != 0) {
            count = 1 + (int) (0.5 + (stop - start) / step);
            computationSucceeded = true;
          }
        } else {
          if (step > 0) {
            count = 1 + (int) ((qLn(stop) - qLn(start)) / qLn(step));
            computationSucceeded = true;
          }
        }
        Q_ASSERT(m_editCountX != 0);
        if (computationSucceeded) {
          m_editCountX->setText(QString("%1").arg(count));
          m_modelGridDisplayAfter->setCountX (count);
        } else {
          m_editCountX->setText ("");
        }
      }
      break;

    case GRID_COORD_DISABLE_START:
      if (coordScale == COORD_SCALE_LINEAR) {
        start = stop - (count - 1.0) * step;
      } else {
        start = exp(qLn(stop) - (count - 1.0) * qLn(step));
      }
      Q_ASSERT(m_editStartX != 0);
      m_editStartX->setText(QString("%1").arg(start));
      m_modelGridDisplayAfter->setStartX (start);
      break;

    case GRID_COORD_DISABLE_STEP:
      if (coordScale == COORD_SCALE_LINEAR) {
        step = (stop - start) / (count - 1.0);
      } else {
        step = exp((qLn(stop) - qLn(start)) / (count - 1.0));
      }
      Q_ASSERT(m_editStepX != 0);
      m_editStepX->setText(QString("%1").arg(step));
      m_modelGridDisplayAfter->setStepX (step);
      break;

    case GRID_COORD_DISABLE_STOP:
      if (coordScale == COORD_SCALE_LINEAR) {
        stop = start + (count - 1.0) * step;
      } else {
        stop = exp(qLn(start) + (count - 1.0) * qLn(step));
      }
      Q_ASSERT(m_editStopX != 0);
      m_editStopX->setText(QString("%1").arg(stop));
      m_modelGridDisplayAfter->setStopX (stop);
      break;
  }
}

void DlgSettingsGridDisplay::updateDependentParameterY ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsGridDisplay::updateDependentParameterY";

  CoordScale coordScale = cmdMediator().document().modelCoords().coordScaleYRadius();
  double count = m_modelGridDisplayAfter->countY ();
  double start = m_modelGridDisplayAfter->startY ();
  double step = m_modelGridDisplayAfter->stepY ();
  double stop = m_modelGridDisplayAfter->stopY ();

  switch (m_modelGridDisplayAfter->gridCoordDisableY())
  {
    case GRID_COORD_DISABLE_COUNT:
      {
        bool computationSucceeded = false;
        if (coordScale == COORD_SCALE_LINEAR) {
          if (step != 0) {
            count = 1 + (int) (0.5 + (stop - start) / step);
            computationSucceeded = true;
          }
        } else {
          if (step > 0) {
            count = 1 + (int) ((qLn(stop) - qLn(start)) / qLn(step));
            computationSucceeded = true;
          }
        }
        Q_ASSERT(m_editCountY != 0);
        if (computationSucceeded) {
          m_editCountY->setText(QString("%1").arg(count));
          m_modelGridDisplayAfter->setCountY (count);
        } else {
          m_editCountY->setText ("");
        }
      }
      break;

    case GRID_COORD_DISABLE_START:
      if (coordScale == COORD_SCALE_LINEAR) {
        start = stop - (count - 1.0) * step;
      } else {
        start = exp(qLn(stop) - (count - 1.0) * qLn(step));
      }
      Q_ASSERT(m_editStartY != 0);
      m_editStartY->setText(QString("%1").arg(start));
      m_modelGridDisplayAfter->setStartY (start);
      break;

    case GRID_COORD_DISABLE_STEP:
      if (coordScale == COORD_SCALE_LINEAR) {
        step = (stop - start) / (count - 1.0);
      } else {
        step = exp((qLn(stop) - qLn(start)) / (count - 1.0));
      }
      Q_ASSERT(m_editStepY != 0);
      m_editStepY->setText(QString("%1").arg(step));
      m_modelGridDisplayAfter->setStepY (step);
      break;

    case GRID_COORD_DISABLE_STOP:
      if (coordScale == COORD_SCALE_LINEAR) {
        stop = start + (count - 1.0) * step;
      } else {
        stop = exp(qLn(start) + (count - 1.0) * qLn(step));
      }
      Q_ASSERT(m_editStopY != 0);
      m_editStopY->setText(QString("%1").arg(stop));
      m_modelGridDisplayAfter->setStopY (stop);
      break;
  }
}

void DlgSettingsGridDisplay::updatePreview()
{

}
