#include "CmdSettingsMainWindow.h"
#include "DlgSettingsMainWindow.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <QComboBox>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <qmath.h>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include "Settings.h"
#include "ZoomControl.h"
#include "ZoomFactorInitial.h"
#include "ZoomLabels.h"

DlgSettingsMainWindow::DlgSettingsMainWindow(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("MainWindow",
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

  QLabel *labelZoomFactor = new QLabel ("Initial zoom:");
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

  QLabel *labelZoomControl = new QLabel ("Zoom control:");
  layout->addWidget (labelZoomControl, row, 1);

  m_cmbZoomControl = new QComboBox;
  m_cmbZoomControl->addItem ("Menu only"                     , QVariant (ZOOM_CONTROL_MENU_ONLY));
  m_cmbZoomControl->addItem ("Menu and mouse wheel"          , QVariant (ZOOM_CONTROL_MENU_WHEEL));
  m_cmbZoomControl->addItem ("Menu and +/- keys"             , QVariant (ZOOM_CONTROL_MENU_PLUSMINUS));
  m_cmbZoomControl->addItem ("Menu, mouse wheel and +/- keys", QVariant (ZOOM_CONTROL_MENU_WHEEL_PLUSMINUS));
  m_cmbZoomControl->setWhatsThis (tr ("Zoom Control\n\n"
                                      "Select which inputs are used to zoom in and out."));
  connect (m_cmbZoomControl, SIGNAL (currentTextChanged (const QString)), this, SLOT (slotZoomControl(const QString)));
  layout->addWidget (m_cmbZoomControl, row++, 2);

  QLabel *labelLocale = new QLabel ("Locale:");
    layout->addWidget (labelLocale, row, 1);

    // Initialization of combobox is liberated from Qt Calendar example
    m_cmbLocale = new QComboBox;
    m_cmbLocale->setWhatsThis(tr ("Locale\n\n"
                                  "Select the locale that will be used when converting between numbers and strings. "
                                  "This affects the use of commas or periods as group delimiters in each number entered "
                                  "by the user, displayed in the user interface, or exported to a file."));
    for (int indexLang = QLocale::C; indexLang <= QLocale::LastLanguage; indexLang++) {
      QLocale::Language lang = static_cast<QLocale::Language> (indexLang);
      QList<QLocale::Country> countries = QLocale::countriesForLanguage(lang);
      for (int indexCountry = 0; indexCountry < countries.count(); indexCountry++) {
        QLocale::Country country = countries.at(indexCountry);
        QString label = localeLabel (lang,
                                     country);
        QLocale locale (lang, country);
        m_cmbLocale->addItem (label, locale);
      }
    }
    m_cmbLocale->model()->sort(COLUMN0); // Sort the new entries
    connect (m_cmbLocale, SIGNAL (currentIndexChanged (int)), this, SLOT (slotLocale (int)));
    layout->addWidget (m_cmbLocale, row++, 2);

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

  CmdSettingsMainWindow *cmd = new CmdSettingsMainWindow (mainWindow (),
                                                                cmdMediator ().document(),
                                                                *m_modelMainWindowBefore,
                                                                *m_modelMainWindowAfter);
  cmdMediator ().push (cmd);

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
  QString locLabel = localeLabel (m_modelMainWindowAfter->locale().language(),
                                  m_modelMainWindowBefore->locale().country());
  index = m_cmbLocale->findText (locLabel);
  m_cmbLocale->setCurrentIndex(index);

  updateControls ();
  enableOk (false); // Disable Ok button since there not yet any changes
}

QString DlgSettingsMainWindow::localeLabel (QLocale::Language lang,
                                            QLocale::Country country) const
{
  return QString ("%1/%2")
      .arg (QLocale::languageToString (lang))
      .arg (QLocale::countryToString(country));
}

void DlgSettingsMainWindow::slotLocale (int index)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsMainWindow::slotLocale";

  m_modelMainWindowAfter->setLocale (m_cmbLocale->itemData (index).toLocale());
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
