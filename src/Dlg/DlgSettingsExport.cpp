#include "CmdMediator.h"
#include "CmdSettingsExport.h"
#include "DlgSettingsExport.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QDoubleValidator>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>

const int MIN_INDENT_COLUMN_WIDTH = 20;
const int MIN_EDIT_WIDTH = 110;
const int MAX_EDIT_WIDTH = 180;

DlgSettingsExport::DlgSettingsExport(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Export", mainWindow)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsExport::createCurveSelection (QGridLayout *layout, int &row)
{
  QLabel *labelIncluded = new QLabel (tr ("Included"));
  layout->addWidget (labelIncluded, row, 0);

  QLabel *labelExcluded = new QLabel (tr ("Not included"));
  layout->addWidget (labelExcluded, row++, 2);

  m_listIncluded = new QListWidget;
  m_listIncluded->setWhatsThis (tr ("List of curves to be included in the exported file"));
  layout->addWidget (m_listIncluded, row, 0, 4, 1);
  connect (m_listIncluded, SIGNAL (itemSelectionChanged ()), this, SLOT (slotListIncluded()));

  m_listExcluded = new QListWidget;
  m_listExcluded->setWhatsThis (tr ("List of curves to be excluded from the exported file"));
  layout->addWidget (m_listExcluded, row++, 2, 4, 1);
  connect (m_listExcluded, SIGNAL (itemSelectionChanged ()), this, SLOT (slotListExcluded()));

  m_btnInclude = new QPushButton (tr ("<<Include"));
  m_btnInclude->setEnabled (false);
  m_btnInclude->setWhatsThis (tr ("Move the currently selected curve(s) from the excluded list"));
  layout->addWidget (m_btnInclude, row++, 1);
  connect (m_btnInclude, SIGNAL (toggled (bool)), this, SLOT (slotInclude()));

  m_btnExclude = new QPushButton (tr ("Exclude>"));
  m_btnExclude->setEnabled (false);
  m_btnExclude->setWhatsThis (tr ("Move the currently selected curve(s) from the included list"));
  layout->addWidget (m_btnExclude, row++, 1);
  connect (m_btnExclude, SIGNAL (toggled (bool)), this, SLOT (slotExclude()));

  row++;
}

void DlgSettingsExport::createDelimiters (QHBoxLayout *layoutMisc)
{
  QGroupBox *groupDelimiters = new QGroupBox (tr ("Delimiters"));
  layoutMisc->addWidget (groupDelimiters, 1);

  QVBoxLayout *layoutDelimiters = new QVBoxLayout;
  groupDelimiters->setLayout (layoutDelimiters);

  m_btnDelimitersCommas = new QRadioButton (tr ("Commas"));
  m_btnDelimitersCommas->setWhatsThis (tr ("Exported file will have commas between adjacent values"));
  layoutDelimiters->addWidget (m_btnDelimitersCommas);
  connect (m_btnDelimitersCommas, SIGNAL (toggled (bool)), this, SLOT (slotDelimitersCommas(bool)));

  m_btnDelimitersSpaces = new QRadioButton (tr ("Spaces"));
  m_btnDelimitersSpaces->setWhatsThis (tr ("Exported file will have spaces between adjacent values"));
  layoutDelimiters->addWidget (m_btnDelimitersSpaces);
  connect (m_btnDelimitersSpaces, SIGNAL (toggled (bool)), this, SLOT (slotDelimitersSpaces(bool)));

  m_btnDelimitersTabs = new QRadioButton (tr ("Tabs"));
  m_btnDelimitersTabs->setWhatsThis (tr ("Exported file will have tabs between adjacent values"));
  layoutDelimiters->addWidget (m_btnDelimitersTabs);
  connect (m_btnDelimitersTabs, SIGNAL (toggled (bool)), this, SLOT (slotDelimitersTabs(bool)));
}

void DlgSettingsExport::createFunctionsLayout (QHBoxLayout *layoutFunctions)
{
  QGroupBox *groupLayout = new QGroupBox (tr ("Layout"));
  layoutFunctions->addWidget (groupLayout, 1);

  QVBoxLayout *layoutLayout = new QVBoxLayout;
  groupLayout->setLayout (layoutLayout);

  m_btnFunctionsLayoutAllCurves = new QRadioButton (tr ("All curves on each line"));
  m_btnFunctionsLayoutAllCurves->setWhatsThis (tr ("Exported file will have, on each line, "
                                                   "an X value, the Y value for the first curve, the Y value for the second curve,..."));
  layoutLayout->addWidget (m_btnFunctionsLayoutAllCurves);
  connect (m_btnFunctionsLayoutAllCurves, SIGNAL (toggled (bool)), this, SLOT (slotFunctionsLayoutAllCurves (bool)));

  m_btnFunctionsLayoutOneCurve = new QRadioButton (tr ("One curve on each line"));
  m_btnFunctionsLayoutOneCurve->setWhatsThis (tr ("Exported file will have all the points for "
                                                  "the first curve, with one X-Y pair on each line, then the points for the second curve,..."));
  layoutLayout->addWidget (m_btnFunctionsLayoutOneCurve);
  connect (m_btnFunctionsLayoutOneCurve, SIGNAL (toggled (bool)), this, SLOT (slotFunctionsLayoutOneCurve (bool)));
}

void DlgSettingsExport::createFunctionsPointsSelection (QHBoxLayout *layoutFunctions)
{
  QGroupBox *groupPointsSelection = new QGroupBox (tr ("Points Selection"));
  layoutFunctions->addWidget (groupPointsSelection, 1);

  QGridLayout *layoutPointsSelections = new QGridLayout;
  groupPointsSelection->setLayout (layoutPointsSelections);

  layoutPointsSelections->setColumnMinimumWidth(0, MIN_INDENT_COLUMN_WIDTH);
  layoutPointsSelections->setColumnStretch (0, 0);
  layoutPointsSelections->setColumnStretch (1, 0);
  layoutPointsSelections->setColumnStretch (2, 1);

  int row = 0;
  m_btnFunctionsPointsAllCurves = new QRadioButton (tr ("Interpolate Y's at X's from all curves"));
  m_btnFunctionsPointsAllCurves->setWhatsThis (tr ("Exported file will have values at every unique X "
                                                   "value from every curve. Y values will be linearly interpolated if necessary"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsAllCurves, row++, 0, 1, 3);
  connect (m_btnFunctionsPointsAllCurves, SIGNAL (toggled (bool)), this, SLOT (slotFunctionsPointsAllCurves(bool)));

  m_btnFunctionsPointsFirstCurve = new QRadioButton (tr ("Interpolate Y's at X's from first curve"));
  m_btnFunctionsPointsFirstCurve->setWhatsThis (tr ("Exported file will have values at every unique X "
                                                    "value from the first curve. Y values will be linearly interpolated if necessary"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsFirstCurve, row++, 0, 1, 3);
  connect (m_btnFunctionsPointsFirstCurve, SIGNAL (toggled (bool)), this, SLOT (slotFunctionsPointsFirstCurve(bool)));

  m_btnFunctionsPointsEvenlySpaced = new QRadioButton (tr ("Interpolate Y's at evenly spaced X values."));
  m_btnFunctionsPointsEvenlySpaced->setWhatsThis (tr ("Exported file will have values at evenly spaced X values "
                                                      "starting with the first X value. If the last interval does not end at the last X value, "
                                                      "the last X value will be added. Y values will be linearly interpolated if necessary"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsEvenlySpaced, row++, 0, 1, 3);
  connect (m_btnFunctionsPointsEvenlySpaced, SIGNAL (toggled (bool)), this, SLOT (slotFunctionsPointsEvenlySpaced(bool)));

  QLabel *labelInterval = new QLabel ("Interval:");
  layoutPointsSelections->addWidget (labelInterval, row, 1, 1, 1, Qt::AlignRight);

  m_editFunctionsPointsEvenlySpacing = new QLineEdit;
  m_editFunctionsPointsEvenlySpacing->setValidator (new QDoubleValidator());
  m_editFunctionsPointsEvenlySpacing->setMinimumWidth (MIN_EDIT_WIDTH);
  m_editFunctionsPointsEvenlySpacing->setMaximumWidth (MAX_EDIT_WIDTH);
  m_editFunctionsPointsEvenlySpacing->setWhatsThis (tr ("Interval between successive X values when exporting at evenly spaced X values"));
  layoutPointsSelections->addWidget (m_editFunctionsPointsEvenlySpacing, row++, 2, 1, 1, Qt::AlignLeft);
  connect (m_editFunctionsPointsEvenlySpacing, SIGNAL (editingFinished()), this, SLOT (slotFunctionsPointsEvenlySpacedInterval()));

  m_btnFunctionsPointsRaw = new QRadioButton (tr ("Raw X's and Y's"));
  m_btnFunctionsPointsRaw->setWhatsThis (tr ("Exported file will have only original X and Y values"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsRaw, row++, 0, 1, 3);
  connect (m_btnFunctionsPointsRaw, SIGNAL (toggled (bool)), this, SLOT (slotFunctionsPointsRaw(bool)));
}

void DlgSettingsExport::createHeader (QHBoxLayout *layoutMisc)
{
  QGroupBox *groupHeader = new QGroupBox (tr ("Header"));
  layoutMisc->addWidget (groupHeader, 1);

  QVBoxLayout *layoutHeader = new QVBoxLayout;
  groupHeader->setLayout (layoutHeader);

  m_btnHeaderNone = new QRadioButton (tr ("None"));
  m_btnHeaderNone->setWhatsThis (tr ("Exported file will have no header line"));
  layoutHeader->addWidget (m_btnHeaderNone);
  connect (m_btnHeaderNone, SIGNAL (toggled (bool)), this, SLOT (slotHeaderNone(bool)));

  m_btnHeaderSimple = new QRadioButton (tr ("Simple"));
  m_btnHeaderSimple->setWhatsThis (tr ("Exported file will have simple header line"));
  layoutHeader->addWidget (m_btnHeaderSimple);
  connect (m_btnHeaderSimple, SIGNAL (toggled (bool)), this, SLOT (slotHeaderSimple(bool)));

  m_btnHeaderGnuplot = new QRadioButton (tr ("Gnuplot"));
  m_btnHeaderGnuplot->setWhatsThis (tr ("Exported file will have gnuplot header line"));
  layoutHeader->addWidget (m_btnHeaderGnuplot);
  connect (m_btnHeaderGnuplot, SIGNAL (toggled (bool)), this, SLOT (slotHeaderGnuplot(bool)));
}

void DlgSettingsExport::createPreview(QGridLayout *layout, int &row)
{
  QLabel *label = new QLabel (tr ("Preview"));
  layout->addWidget (label, row++, 0);

  m_editPreview = new QTextEdit;
  m_editPreview->setReadOnly (true);
  m_editPreview->setWhatsThis (tr ("Preview window shows how current settings affect the exported file"));
  m_editPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_editPreview, row++, 0, 1, 3);
}

void DlgSettingsExport::createRelationsPointsSelection (QHBoxLayout *layoutRelations)
{
  QGroupBox *groupPointsSelection = new QGroupBox (tr ("Points Selection"));
  layoutRelations->addWidget (groupPointsSelection);

  QGridLayout *layoutPointsSelections = new QGridLayout;
  groupPointsSelection->setLayout (layoutPointsSelections);

  layoutPointsSelections->setColumnMinimumWidth(0, MIN_INDENT_COLUMN_WIDTH);
  layoutPointsSelections->setColumnStretch (0, 0);
  layoutPointsSelections->setColumnStretch (1, 0);
  layoutPointsSelections->setColumnStretch (2, 1);

  int row = 0;
  m_btnRelationsPointsEvenlySpaced = new QRadioButton (tr ("Interpolate X's and Y's at evenly spaced intervals."));
  m_btnRelationsPointsEvenlySpaced->setWhatsThis (tr ("Exported file will have points evenly spaced along each relation, using interpolation "
                                                      "for both X and Y. If the last interval does not end at the last point, the last "
                                                      "point will be added"));
  layoutPointsSelections->addWidget (m_btnRelationsPointsEvenlySpaced, row++, 0, 1, 3);
  connect (m_btnRelationsPointsEvenlySpaced, SIGNAL (toggled (bool)), this, SLOT (slotRelationsPointsEvenlySpaced(bool)));

  QLabel *labelInterval = new QLabel ("Interval:");
  layoutPointsSelections->addWidget (labelInterval, row, 1, 1, 1, Qt::AlignRight);

  m_editRelationsPointsEvenlySpacing = new QLineEdit;
  m_editRelationsPointsEvenlySpacing->setValidator (new QDoubleValidator());
  m_editRelationsPointsEvenlySpacing->setMinimumWidth (MIN_EDIT_WIDTH);
  m_editRelationsPointsEvenlySpacing->setMaximumWidth (MAX_EDIT_WIDTH);
  layoutPointsSelections->addWidget (m_editRelationsPointsEvenlySpacing, row++, 2, 1, 1, Qt::AlignLeft);
  connect (m_editRelationsPointsEvenlySpacing, SIGNAL (editingFinished()), this, SLOT (slotRelationsPointsEvenlySpacedInterval()));

  m_btnRelationsPointsRaw = new QRadioButton (tr ("Raw X's and Y's"));
  m_btnRelationsPointsRaw->setWhatsThis (tr ("Exported file will have only original X and Y values"));
  layoutPointsSelections->addWidget (m_btnRelationsPointsRaw, row++, 0, 1, 3);
  connect (m_btnRelationsPointsRaw, SIGNAL (toggled (bool)), this, SLOT (slotRelationsPointsRaw(bool)));
}

QWidget *DlgSettingsExport::createSubPanel ()
{
  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  int row = 0;
  createCurveSelection (layout, row);

  QHBoxLayout *layoutFunctions, *layoutRelations;
  createTabWidget (layout,
                   layoutFunctions,
                   layoutRelations,
                   row);

  createFunctionsPointsSelection (layoutFunctions);
  createFunctionsLayout (layoutFunctions);

  createRelationsPointsSelection (layoutRelations);

  QWidget *widgetMisc = new QWidget;
  layout->addWidget (widgetMisc, row++, 0, 1, 3);
  QHBoxLayout *layoutMisc = new QHBoxLayout;
  widgetMisc->setLayout (layoutMisc);

  createDelimiters (layoutMisc);
  createHeader (layoutMisc);
  createXLabel (layoutMisc);

  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsExport::createTabWidget (QGridLayout *layout,
                                         QHBoxLayout *&layoutFunctions,
                                         QHBoxLayout *&layoutRelations,
                                         int &row)
{
  QTabWidget *tabWidget = new QTabWidget;
  layout->addWidget (tabWidget, row++, 0, 1, 3);

  QWidget *widgetFunctions = new QWidget;
  tabWidget->addTab (widgetFunctions, tr ("Functions"));
  layoutFunctions = new QHBoxLayout;
  widgetFunctions->setLayout (layoutFunctions);

  QWidget *widgetRelations = new QWidget;
  tabWidget->addTab (widgetRelations, tr ("Relations"));
  layoutRelations = new QHBoxLayout;
  widgetRelations->setLayout (layoutRelations);
}

void DlgSettingsExport::createXLabel (QHBoxLayout *layoutMisc)
{
  QWidget *widgetXLabel = new QWidget;
  layoutMisc->addWidget (widgetXLabel, 1);

  QVBoxLayout *layoutXLabel = new QVBoxLayout;
  layoutXLabel->setAlignment (Qt::AlignCenter);
  widgetXLabel->setLayout (layoutXLabel);

  QLabel *title;
  if (true) {
    title = new QLabel (tr ("Header X Label"));
  } else {
    title = new QLabel (tr ("Header Theta Label"));
  }
  layoutXLabel->addWidget (title);

  m_editXLabel = new QLineEdit;
  if (true) {
    m_editXLabel->setWhatsThis (tr ("Label in the header for x values"));
  } else {
    m_editXLabel->setWhatsThis (tr ("Label in the header for theta values"));
  }
  layoutXLabel->addWidget (m_editXLabel);
  connect (m_editXLabel, SIGNAL (editingFinished ()), this, SLOT (slotXLabel()));
}

void DlgSettingsExport::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::handleOk";

  CmdSettingsExport *cmd = new CmdSettingsExport (mainWindow (),
                                                  cmdMediator ().document());
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsExport::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::load";

  setCmdMediator (cmdMediator);
}

void DlgSettingsExport::slotDelimitersCommas(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotDelimitersCommas";
}

void DlgSettingsExport::slotDelimitersSpaces(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotDelimitersSpaces";
}

void DlgSettingsExport::slotDelimitersTabs(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotDelimitersTabs";
}

void DlgSettingsExport::slotExclude ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotExclude";
}

void DlgSettingsExport::slotFunctionsLayoutAllCurves(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsLayoutAllCurves";
}

void DlgSettingsExport::slotFunctionsLayoutOneCurve(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsLayoutOneCurve";
}

void DlgSettingsExport::slotFunctionsPointsAllCurves(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsAllCurves";

  updateControls();
}

void DlgSettingsExport::slotFunctionsPointsEvenlySpaced(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsEvenlySpaced";

  updateControls();
}

void DlgSettingsExport::slotFunctionsPointsEvenlySpacedInterval()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsEvenlySpacedInterval";
}

void DlgSettingsExport::slotFunctionsPointsFirstCurve(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsFirstCurve";

  updateControls();
}

void DlgSettingsExport::slotFunctionsPointsRaw(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsRaw";

  updateControls();
}

void DlgSettingsExport::slotHeaderGnuplot(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotHeaderGnuplot";
}

void DlgSettingsExport::slotHeaderNone(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotHeaderNone";
}

void DlgSettingsExport::slotHeaderSimple(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotHeaderSimple";
}

void DlgSettingsExport::slotInclude ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotInclude";
}

void DlgSettingsExport::slotListExcluded()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotListExcluded";

  updateControls ();
}

void DlgSettingsExport::slotListIncluded()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotListIncluded";

  updateControls ();
}

void DlgSettingsExport::slotRelationsPointsEvenlySpaced(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotRelationsPointsEvenlySpaced";

  updateControls ();
}

void DlgSettingsExport::slotRelationsPointsEvenlySpacedInterval()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotRelationsPointsEvenlySpacedInterval";
}

void DlgSettingsExport::slotRelationsPointsRaw(bool)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotRelationsPointsRaw";

  updateControls ();
}

void DlgSettingsExport::slotXLabel()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotXLabel";
}

void DlgSettingsExport::updateControls ()
{
  int selectedForInclude = m_listExcluded->selectedItems().count();
  int selectedForExclude = m_listIncluded->selectedItems().count();
  int inInclude = m_listIncluded->count();

  m_btnInclude->setEnabled (selectedForInclude > 0); // Need at least one selection
  m_btnExclude->setEnabled ((selectedForExclude > 0) && (inInclude - selectedForExclude > 0)); // Need at least one selection, and one left after the move

  m_editFunctionsPointsEvenlySpacing->setEnabled (m_btnFunctionsPointsEvenlySpaced->isChecked ());
  m_editRelationsPointsEvenlySpacing->setEnabled (m_btnRelationsPointsEvenlySpaced->isChecked ());
}
