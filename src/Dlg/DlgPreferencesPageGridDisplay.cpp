#include "CmdMediator.h"
#include "DlgPreferencesPageGridDisplay.h"
#include "Logger.h"
#include <QComboBox>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include "ViewPreview.h"

const int COUNT_MIN = 1;
const int COUNT_MAX = 100;
const int COUNT_DECIMALS = 0;

DlgPreferencesPageGridDisplay::DlgPreferencesPageGridDisplay(CmdMediator &cmdMediator,
                                                             QWidget *parent) :
  DlgPreferencesPageAbstractBase (cmdMediator,
                                  parent)
{
  QGridLayout *layout = new QGridLayout (this);
  setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // X
  layout->setColumnStretch(2, 0); // Y
  layout->setColumnStretch(3, 1); // Empty first column

  int row = 0;
  createX (layout, row);
  createY (layout, row);
  createPreview (layout, row);
}

void DlgPreferencesPageGridDisplay::createPreview (QGridLayout *layout,
                                                   int &row)
{
  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview, this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the displayed grid lines."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

void DlgPreferencesPageGridDisplay::createX (QGridLayout *layout,
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

void DlgPreferencesPageGridDisplay::createY (QGridLayout *layout,
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

void DlgPreferencesPageGridDisplay::load ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::load";
}

void DlgPreferencesPageGridDisplay::slotCountX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::slotCountX";
}

void DlgPreferencesPageGridDisplay::slotCountY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::slotCountY";
}

void DlgPreferencesPageGridDisplay::slotDisableX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::slotDisableX";
}

void DlgPreferencesPageGridDisplay::slotDisableY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::slotDisableY";
}

void DlgPreferencesPageGridDisplay::slotStartX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::slotStartX";
}

void DlgPreferencesPageGridDisplay::slotStartY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::slotStartY";
}

void DlgPreferencesPageGridDisplay::slotStepX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::slotStepX";
}

void DlgPreferencesPageGridDisplay::slotStepY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::slotStepY";
}

void DlgPreferencesPageGridDisplay::slotStopX(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::slotStopX";
}

void DlgPreferencesPageGridDisplay::slotStopY(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageGridDisplay::slotStopY";
}
