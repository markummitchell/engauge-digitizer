#include "DlgCoordSystemCount.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>

DlgCoordSystemCount::DlgCoordSystemCount(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Coordinate System Count",
                           "DlgCoordSystemCount",
                           mainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgCoordSystemCount::DlgCoordSystemCount";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);

  // Accept even the default value without any additional actions, rather than delay the Ok button to after a change
  enableOk (true);
  setDisableOkAtStartup (false);
}

void DlgCoordSystemCount::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgCoordSystemCount::createOptionalSaveDefault";
}

QWidget *DlgCoordSystemCount::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgCoordSystemCount::createSubPanel";

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  int row = 0;

  QLabel *labelCount = new QLabel ("Coordinate System Count:");
  layout->addWidget (labelCount, row, 1);

  m_spinCount = new QSpinBox;
  m_spinCount->setMinimum (1);
  m_spinCount->setValue (1);
  m_spinCount->setWhatsThis (tr ("Coordinate System Count\n\n"
                                 "Specifies the total number of coordinate systems that will be used in the imported image. "
                                 "There can be one or more graphs in the image, and each graph can have one or more "
                                 "coordinate systems. Each coordinate system is defined by a pair of coordinate axes."));
  connect (m_spinCount, SIGNAL (valueChanged (const QString &)), this, SLOT (slotCount (const QString &)));
  layout->addWidget (m_spinCount, row++, 2);

  return subPanel;
}

void DlgCoordSystemCount::handleOk()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgCoordSystemCount::handleOk";

  setResult (QDialog::Accepted); // Set return value so Ok button is not handled like the Cancel button

  hide ();
}

void DlgCoordSystemCount::load(CmdMediator & /* cmdMediator */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgCoordSystemCount::load";
}

unsigned int DlgCoordSystemCount::numberCoordSystem () const
{
  return m_spinCount->value ();
}

void DlgCoordSystemCount::slotCount (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgCoordSystem::slotCount";
}
