/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "DlgSettingsAbstractBase.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QColor>
#include <QComboBox>
#include <QPushButton>
#include <QSettings>
#include <QSpacerItem>
#include <QVBoxLayout>

int DlgSettingsAbstractBase::MINIMUM_DIALOG_WIDTH = 350;
int DlgSettingsAbstractBase::MINIMUM_PREVIEW_HEIGHT = 200;

DlgSettingsAbstractBase::DlgSettingsAbstractBase(const QString &title,
                                                 const QString &dialogName,
                                                 MainWindow &mainWindow) :
  QDialog (&mainWindow),
  m_mainWindow (mainWindow),
  m_cmdMediator (0),
  m_dialogName (dialogName),
  m_disableOkAtStartup (true)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAbstractBase::DlgSettingsAbstractBase"
                              << " name=" << m_dialogName.toLatin1().data();

  setWindowTitle (title);
  setModal (true);
}

DlgSettingsAbstractBase::~DlgSettingsAbstractBase()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAbstractBase::~DlgSettingsAbstractBase"
                              << " name=" << m_dialogName.toLatin1().data();
}

CmdMediator &DlgSettingsAbstractBase::cmdMediator ()
{
  ENGAUGE_CHECK_PTR (m_cmdMediator);

  return *m_cmdMediator;
}

void DlgSettingsAbstractBase::enableOk (bool enable)
{
  m_btnOk->setEnabled (enable);
}

void DlgSettingsAbstractBase::finishPanel (QWidget *subPanel)
{
  const int STRETCH_OFF = 0, STRETCH_ON = 1;

  QVBoxLayout *panelLayout = new QVBoxLayout (this);

  setMinimumWidth (MINIMUM_DIALOG_WIDTH);
  setLayout (panelLayout);

  panelLayout->addWidget (subPanel);
  panelLayout->setStretch (panelLayout->count () - 1, STRETCH_ON);

  QWidget *panelButtons = new QWidget (this);
  QHBoxLayout *buttonLayout = new QHBoxLayout (panelButtons);

  createOptionalSaveDefault(buttonLayout);

  QHBoxLayout *layoutRightSide = new QHBoxLayout;

  QWidget *widgetRightSide = new QWidget;
  widgetRightSide->setLayout (layoutRightSide);
  buttonLayout->addWidget (widgetRightSide);

  QSpacerItem *spacerExpanding = new QSpacerItem (40, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
  layoutRightSide->addItem (spacerExpanding);

  m_btnOk = new QPushButton (tr ("Ok"));
  m_btnOk->setEnabled (false); // Nothing to save initially
  layoutRightSide->addWidget (m_btnOk, 0, Qt::AlignRight);
  connect (m_btnOk, SIGNAL (released ()), this, SLOT (slotOk ()));

  QSpacerItem *spacerFixed = new QSpacerItem (40, 5, QSizePolicy::Fixed, QSizePolicy::Fixed);
  layoutRightSide->addItem (spacerFixed);

  m_btnCancel = new QPushButton (tr ("Cancel"));
  layoutRightSide->addWidget (m_btnCancel, 0, Qt::AlignRight);
  connect (m_btnCancel, SIGNAL (released ()), this, SLOT (slotCancel ()));

  panelLayout->addWidget (panelButtons, STRETCH_ON);
  panelLayout->setStretch (panelLayout->count () - 1, STRETCH_OFF);
}

MainWindow &DlgSettingsAbstractBase::mainWindow ()
{
  return m_mainWindow;
}

const MainWindow &DlgSettingsAbstractBase::mainWindow () const
{
  return m_mainWindow;
}

void DlgSettingsAbstractBase::populateColorComboWithoutTransparent (QComboBox &combo)
{
  combo.addItem (colorPaletteToString (COLOR_PALETTE_BLUE),
                 QVariant (COLOR_PALETTE_BLUE));
  combo.addItem (colorPaletteToString (COLOR_PALETTE_BLACK),
                 QVariant (COLOR_PALETTE_BLACK));
  combo.addItem (colorPaletteToString (COLOR_PALETTE_CYAN),
                 QVariant (COLOR_PALETTE_CYAN));
  combo.addItem (colorPaletteToString (COLOR_PALETTE_GOLD),
                 QVariant (COLOR_PALETTE_GOLD));
  combo.addItem (colorPaletteToString (COLOR_PALETTE_GREEN),
                 QVariant (COLOR_PALETTE_GREEN));
  combo.addItem (colorPaletteToString (COLOR_PALETTE_MAGENTA),
                 QVariant (COLOR_PALETTE_MAGENTA));
  combo.addItem (colorPaletteToString (COLOR_PALETTE_RED),
                 QVariant (COLOR_PALETTE_RED));
  combo.addItem (colorPaletteToString (COLOR_PALETTE_YELLOW),
                 QVariant (COLOR_PALETTE_YELLOW));
}

void DlgSettingsAbstractBase::populateColorComboWithTransparent (QComboBox &combo)
{
  populateColorComboWithoutTransparent (combo);
  combo.addItem ("Transparent", QVariant (COLOR_PALETTE_TRANSPARENT));
}

void DlgSettingsAbstractBase::saveGeometryToSettings()
{
  // Store the settings for use by showEvent
  QSettings settings;
  settings.setValue (m_dialogName, saveGeometry ());
}

void DlgSettingsAbstractBase::setCmdMediator (CmdMediator &cmdMediator)
{
  m_cmdMediator = &cmdMediator;
}

void DlgSettingsAbstractBase::setDisableOkAtStartup(bool disableOkAtStartup)
{
  m_disableOkAtStartup = disableOkAtStartup;
}

void DlgSettingsAbstractBase::showEvent (QShowEvent * /* event */)
{
  if (m_disableOkAtStartup) {
    m_btnOk->setEnabled (false);
  }

  QSettings settings;
  if (settings.contains (m_dialogName)) {

    // Restore the settings that were stored by the last call to saveGeometryToSettings
    restoreGeometry (settings.value (m_dialogName).toByteArray ());
  }
}

void DlgSettingsAbstractBase::slotCancel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAbstractBase::slotCancel";

  saveGeometryToSettings();
  hide();
}

void DlgSettingsAbstractBase::slotOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsAbstractBase::slotOk";

  saveGeometryToSettings();

  // Forward to leaf class
  handleOk ();
}
