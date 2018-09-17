/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgImportAdvanced.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QSpinBox>

const int MINIMUM_DIALOG_WIDTH_COORDS = 800;

DlgImportAdvanced::DlgImportAdvanced(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Import Advanced"),
                           "DlgImportAdvanced",
                           mainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportAdvanced::DlgImportAdvanced";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel,
               MINIMUM_DIALOG_WIDTH_COORDS);

  // Accept even the default value without any additional actions, rather than delay the Ok button to after a change
  enableOk (true);
  setDisableOkAtStartup (false);
}

void DlgImportAdvanced::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportAdvanced::createOptionalSaveDefault";
}

QWidget *DlgImportAdvanced::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportAdvanced::createSubPanel";

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  int row = 0;

  // Coordinate system count
  QLabel *labelCoordCount = new QLabel (QString ("%1:").arg (tr ("Coordinate System Count")));
  layout->addWidget (labelCoordCount, row, 1);

  m_spinCoordSystemCount = new QSpinBox;
  m_spinCoordSystemCount->setMinimum (1);
  m_spinCoordSystemCount->setValue (1);
  m_spinCoordSystemCount->setWhatsThis (tr ("Coordinate System Count\n\n"
                                            "Specifies the total number of coordinate systems that will be used in the imported image. "
                                            "There can be one or more graphs in the image, and each graph can have one or more "
                                            "coordinate systems. Each coordinate system is defined by a pair of coordinate axes."));
  connect (m_spinCoordSystemCount, SIGNAL (valueChanged (const QString &)), this, SLOT (slotCoordSystemCount (const QString &)));
  layout->addWidget (m_spinCoordSystemCount, row++, 2);

  // Axes point count
  QLabel *labelPointCount = new QLabel (QString ("%1:").arg (tr ("Graph Coordinates Definition")));
  layout->addWidget (labelPointCount, row, 1);

  m_btnAxesPointCount2 = new QRadioButton (tr ("1 scale bar - Used for maps with a scale bar defining the map scale"));
  m_btnAxesPointCount2->setWhatsThis (tr ("The two endpoints of the scale bar will define the scale of a map. The scale bar can "
                                          "edited to set its length.\n\n"
                                          "This setting is used when importing a map that has only a scale bar "
                                          "to define distance, rather than a graph with axes that define two coordinates."));
  connect (m_btnAxesPointCount2, SIGNAL (toggled (bool)), this, SLOT (slotAxesPointCount (bool)));
  layout->addWidget (m_btnAxesPointCount2, row++, 2);

  m_btnAxesPointCount3 = new QRadioButton (tr ("3 axis points - Used for graphs with both coordinates defined on each axis"));
  m_btnAxesPointCount3->setChecked (true); // This is the traditional setting, and so is used as the default
  m_btnAxesPointCount3->setWhatsThis (tr ("Three axes points will define the coordinate system. Each will have both "
                                          "x and y coordinates.\n\n"
                                          "This setting is always used when importing images in non-advanced mode.\n\n"
                                          "In total, there will be three points as (x1,y1), (x2,y2) "
                                          "and (x3,y3)."));
  connect (m_btnAxesPointCount3, SIGNAL (toggled (bool)), this, SLOT (slotAxesPointCount (bool)));
  layout->addWidget (m_btnAxesPointCount3, row++, 2);

  m_btnAxesPointCount4 = new QRadioButton (tr ("4 axis points - Used for graphs with only one coordinate defined on each axis"));
  m_btnAxesPointCount4->setWhatsThis (tr ("Four axes points will define the coordinate system. Each will have a single "
                                          "x or y coordinate.\n\n"
                                          "This setting is required when the x coordinate of the y axis is unknown, and/or "
                                          "the y coordinate of the x axis is unknown.\n\n"
                                          "In total, there will be two points on the x axis as (x1) and "
                                          "(x2), and two points on the y axis as (y1) and (y2)."));
  connect (m_btnAxesPointCount4, SIGNAL (toggled (bool)), this, SLOT (slotAxesPointCount (bool)));
  layout->addWidget (m_btnAxesPointCount4, row++, 2);

  return subPanel;
}

DocumentAxesPointsRequired DlgImportAdvanced::documentAxesPointsRequired () const
{
  if (m_btnAxesPointCount2->isChecked ()) {
    return DOCUMENT_AXES_POINTS_REQUIRED_2;
  } else if (m_btnAxesPointCount3->isChecked ()) {
    return DOCUMENT_AXES_POINTS_REQUIRED_3;
  } else {
    return DOCUMENT_AXES_POINTS_REQUIRED_4;
  }
}

void DlgImportAdvanced::handleOk()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportAdvanced::handleOk";

  setResult (QDialog::Accepted); // Set return value so Ok button is not handled like the Cancel button

  hide ();
}

void DlgImportAdvanced::load(CmdMediator & /* cmdMediator */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgImportAdvanced::load";
}

unsigned int DlgImportAdvanced::numberCoordSystem () const
{
  return m_spinCoordSystemCount->value ();
}

void DlgImportAdvanced::setSmallDialogs(bool /* smallDialogs */)
{
}

void DlgImportAdvanced::slotAxesPointCount (bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgCoordSystem::slotAxesPointCount";
}

void DlgImportAdvanced::slotCoordSystemCount (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgCoordSystem::slotImportAdvanced";
}

