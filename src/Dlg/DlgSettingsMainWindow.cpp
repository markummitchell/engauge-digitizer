/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgSettingsMainWindow.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <QCheckBox>
#include <QComboBox>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <qmath.h>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include "QtToString.h"
#include "Settings.h"
#include "ZoomControl.h"
#include "ZoomFactorInitial.h"
#include "ZoomLabels.h"

DlgSettingsMainWindow::DlgSettingsMainWindow(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Main Window"),
                           "DlgSettingsMainWindow",
                           mainWindow),
  m_modelMainWindowBefore (0),
  m_modelMainWindowAfter (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::DlgSettingsMainWindow";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsMainWindow::~DlgSettingsMainWindow()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::~DlgSettingsMainWindow";
}

void DlgSettingsMainWindow::createControls (QGridLayout *layout,
                                            int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::createControls";

  const int COLUMN0 = 0;

  QLabel *labelZoomFactor = new QLabel (tr ("Initial zoom:"));
  layout->addWidget (labelZoomFactor, row, 1);

  m_cmbZoomFactor = new QComboBox;
  m_cmbZoomFactor->addItem (LABEL_ZOOM_16_TO_1  , QVariant (ZOOM_INITIAL_16_TO_1));
  m_cmbZoomFactor->addItem (LABEL_ZOOM_8_TO_1   , QVariant (ZOOM_INITIAL_8_TO_1));
  m_cmbZoomFactor->addItem (LABEL_ZOOM_4_TO_1   , QVariant (ZOOM_INITIAL_4_TO_1));
  m_cmbZoomFactor->addItem (LABEL_ZOOM_2_TO_1   , QVariant (ZOOM_INITIAL_2_TO_1));
  m_cmbZoomFactor->addItem (LABEL_ZOOM_1_TO_1   , QVariant (ZOOM_INITIAL_1_TO_1));
  m_cmbZoomFactor->addItem (LABEL_ZOOM_1_TO_2   , QVariant (ZOOM_INITIAL_1_TO_2));
  m_cmbZoomFactor->addItem (LABEL_ZOOM_1_TO_4   , QVariant (ZOOM_INITIAL_1_TO_4));
  m_cmbZoomFactor->addItem (LABEL_ZOOM_1_TO_8   , QVariant (ZOOM_INITIAL_1_TO_8));
  m_cmbZoomFactor->addItem (LABEL_ZOOM_1_TO_16  , QVariant (ZOOM_INITIAL_1_TO_16));
  m_cmbZoomFactor->addItem (LABEL_ZOOM_FILL     , QVariant (ZOOM_INITIAL_FILL));
  m_cmbZoomFactor->addItem (LABEL_ZOOM_PREVIOUS , QVariant (ZOOM_INITIAL_PREVIOUS));
  m_cmbZoomFactor->setWhatsThis(tr ("Initial Zoom\n\n"
                                    "Select the initial zoom factor when a new document is loaded. Either the previous "
                                    "zoom can be kept, or the specified zoom can be applied."));
  connect (m_cmbZoomFactor, SIGNAL (currentTextChanged (const QString)), this, SLOT (slotZoomFactor(const QString)));
  layout->addWidget (m_cmbZoomFactor, row++, 2);

  QLabel *labelZoomControl = new QLabel (tr ("Zoom control:"));
  layout->addWidget (labelZoomControl, row, 1);

  m_cmbZoomControl = new QComboBox;
  m_cmbZoomControl->addItem (tr ("Menu only"                     ), QVariant (ZOOM_CONTROL_MENU_ONLY));
  m_cmbZoomControl->addItem (tr ("Menu and mouse wheel"          ), QVariant (ZOOM_CONTROL_MENU_WHEEL));
  m_cmbZoomControl->addItem (tr ("Menu and +/- keys"             ), QVariant (ZOOM_CONTROL_MENU_PLUSMINUS));
  m_cmbZoomControl->addItem (tr ("Menu, mouse wheel and +/- keys"), QVariant (ZOOM_CONTROL_MENU_WHEEL_PLUSMINUS));
  m_cmbZoomControl->setWhatsThis (tr ("Zoom Control\n\n"
                                      "Select which inputs are used to zoom in and out."));
  connect (m_cmbZoomControl, SIGNAL (currentTextChanged (const QString)), this, SLOT (slotZoomControl(const QString)));
  layout->addWidget (m_cmbZoomControl, row++, 2);

  QLabel *labelLocale = new QLabel (tr ("Locale:"));
  layout->addWidget (labelLocale, row, 1);

  // Initialization of combobox is liberated from Qt Calendar example
  m_cmbLocale = new QComboBox;
  m_cmbLocale->setWhatsThis(tr ("Locale\n\n"
                                "Select the locale that will be used in numbers (immediately), and the language in the user "
                                "interface (after restart).\n\n"
                                "The locale determines how numbers are formatted. Specifically, either commas or "
                                "periods will be used as group delimiters in each number entered "
                                "by the user, displayed in the user interface, or exported to a file."));
  for (int indexLang = QLocale::C; indexLang <= QLocale::LastLanguage; indexLang++) {
    QLocale::Language lang = static_cast<QLocale::Language> (indexLang);
    QList<QLocale::Country> countries = QLocale::countriesForLanguage(lang);
    for (int indexCountry = 0; indexCountry < countries.count(); indexCountry++) {
      QLocale::Country country = countries.at(indexCountry);
      QLocale locale (lang, country);
      QString label = QLocaleToString (locale);
      m_cmbLocale->addItem (label, locale);
    }
  }
  m_cmbLocale->model()->sort(COLUMN0); // Sort the new entries
  connect (m_cmbLocale, SIGNAL (currentIndexChanged (int)), this, SLOT (slotLocale (int)));
  layout->addWidget (m_cmbLocale, row++, 2);

#ifdef ENGAUGE_PDF
  QLabel *labelPdfResolution = new QLabel (tr ("Import PDF resolution (dots per inch):"));
  layout->addWidget (labelPdfResolution, row, 1);

  m_cmbPdfResolution = new QComboBox;
  m_cmbPdfResolution->setWhatsThis (tr ("Import PDF Resolution\n\n"
                                        "Imported Portable Document Format (PDF) files will be converted to this pixel resolution "
                                        "in dots per inch (DPI), where each pixel is one dot. A higher value increases the picture resolution "
                                        "and may also improve numeric digitizing accuracy. However, a very high value can make the image so "
                                        "large that Engauge will slow down."));
  m_cmbPdfResolution->addItem ("75", 75);
  m_cmbPdfResolution->addItem ("100", 100);
  m_cmbPdfResolution->addItem ("150", 150);
  m_cmbPdfResolution->addItem ("200", 200);
  m_cmbPdfResolution->addItem ("250", 250);
  m_cmbPdfResolution->addItem ("300", 300);
  connect (m_cmbPdfResolution, SIGNAL (currentTextChanged (QString)), this, SLOT (slotPdfResolution (QString)));
  layout->addWidget (m_cmbPdfResolution, row++, 2);
#endif

  QLabel *labelRecent = new QLabel (tr ("Recent file list:"));
  layout->addWidget (labelRecent, row, 1);

  m_btnRecentClear = new QPushButton (tr ("Clear"));
  m_btnRecentClear->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_btnRecentClear->setWhatsThis (tr ("Recent File List Clear\n\n"
                                      "Clear the recent file list in the File menu."));
  connect (m_btnRecentClear, SIGNAL (pressed ()), &mainWindow(), SLOT (slotRecentFileClear ()));
  connect (m_btnRecentClear, SIGNAL (pressed ()), this, SLOT (slotRecentFileClear()));
  layout->addWidget (m_btnRecentClear, row++, 2);

  QLabel *labelTitleBarFormat = new QLabel (tr ("Include title bar path:"));
  layout->addWidget (labelTitleBarFormat, row, 1);

  m_chkTitleBarFormat = new QCheckBox;
  m_chkTitleBarFormat->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_chkTitleBarFormat->setWhatsThis (tr ("Title Bar Filename\n\n"
                                         "Includes or excludes the path and file extension from the filename in the title bar."));
  connect (m_chkTitleBarFormat, SIGNAL (toggled (bool)), this, SLOT (slotTitleBarFormat(bool)));
  layout->addWidget (m_chkTitleBarFormat, row++, 2);
}

void DlgSettingsMainWindow::createOptionalSaveDefault (QHBoxLayout * /* layout */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::createOptionalSaveDefault";
}

QWidget *DlgSettingsMainWindow::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::createSubPanel";

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty first column
  layout->setColumnStretch(1, 0); // Labels
  layout->setColumnStretch(2, 0); // Values
  layout->setColumnStretch(3, 1); // Empty first column

  int row = 0;
  createControls (layout, row);

  return subPanel;
}

void DlgSettingsMainWindow::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::handleOk";

  mainWindow().updateSettingsMainWindow (*m_modelMainWindowAfter);

  hide ();
}
void DlgSettingsMainWindow::load (CmdMediator & /* cmdMediator */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::load";

  ENGAUGE_ASSERT (false);
}

void DlgSettingsMainWindow::loadMainWindowModel (CmdMediator &cmdMediator,
                                                 const MainWindowModel &modelMainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::loadMainWindowModel";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelMainWindowBefore != 0) {
    delete m_modelMainWindowBefore;
  }
  if (m_modelMainWindowAfter != 0) {
    delete m_modelMainWindowAfter;
  }

  // Save new data
  m_modelMainWindowBefore = new MainWindowModel (modelMainWindow);
  m_modelMainWindowAfter = new MainWindowModel (modelMainWindow);

  // Populate controls
  int index = m_cmbZoomFactor->findData (m_modelMainWindowAfter->zoomFactorInitial());
  m_cmbZoomFactor->setCurrentIndex (index);
  index = m_cmbZoomControl->findData (m_modelMainWindowAfter->zoomControl());
  m_cmbZoomControl->setCurrentIndex (index);
  QString locLabel = QLocaleToString (m_modelMainWindowAfter->locale());
  index = m_cmbLocale->findText (locLabel);
  m_cmbLocale->setCurrentIndex(index);
  m_chkTitleBarFormat->setChecked (m_modelMainWindowAfter->mainTitleBarFormat() == MAIN_TITLE_BAR_FORMAT_PATH);
  index = m_cmbPdfResolution->findData (m_modelMainWindowAfter->pdfResolution());
  m_cmbPdfResolution->setCurrentIndex(index);

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
}

void DlgSettingsMainWindow::slotLocale (int index)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::slotLocale";

  m_modelMainWindowAfter->setLocale (m_cmbLocale->itemData (index).toLocale());
  updateControls();
}

void DlgSettingsMainWindow::slotPdfResolution(const QString)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWIndow::slotPdfResolution";

  m_modelMainWindowAfter->setPdfResolution(m_cmbPdfResolution->currentData().toInt());
  updateControls();
}

void DlgSettingsMainWindow::slotRecentFileClear()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::slotRecentFileClear";

  // The signal that triggered the call to this method was also sent to MainWindow to clear the list there
  updateControls();
}

void DlgSettingsMainWindow::slotTitleBarFormat(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::slotTitleBarFormat";

  m_modelMainWindowAfter->setMainTitleBarFormat(m_chkTitleBarFormat->isChecked() ?
                                                MAIN_TITLE_BAR_FORMAT_PATH :
                                                MAIN_TITLE_BAR_FORMAT_NO_PATH);
  updateControls();
}

void DlgSettingsMainWindow::slotZoomControl(const QString)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::slotZoomControl";

  m_modelMainWindowAfter->setZoomControl ((ZoomControl) m_cmbZoomControl->currentData().toInt());
  updateControls();
}

void DlgSettingsMainWindow::slotZoomFactor(const QString)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWIndow::slotZoomFactor";

  m_modelMainWindowAfter->setZoomFactorInitial((ZoomFactorInitial) m_cmbZoomFactor->currentData().toInt());
  updateControls();
}

void DlgSettingsMainWindow::updateControls ()
{
  enableOk (true);
}
