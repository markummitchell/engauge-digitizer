#include "CmdMediator.h"
#include "CmdSettingsExport.h"
#include "DlgModelExport.h"
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
  DlgSettingsAbstractBase ("Export", mainWindow),
  m_modelExportBefore (0),
  m_modelExportAfter (0)
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
  connect (m_btnInclude, SIGNAL (pressed ()), this, SLOT (slotInclude()));

  m_btnExclude = new QPushButton (tr ("Exclude>"));
  m_btnExclude->setEnabled (false);
  m_btnExclude->setWhatsThis (tr ("Move the currently selected curve(s) from the included list"));
  layout->addWidget (m_btnExclude, row++, 1);
  connect (m_btnExclude, SIGNAL (pressed ()), this, SLOT (slotExclude()));

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
  connect (m_btnDelimitersCommas, SIGNAL (pressed ()), this, SLOT (slotDelimitersCommas()));

  m_btnDelimitersSpaces = new QRadioButton (tr ("Spaces"));
  m_btnDelimitersSpaces->setWhatsThis (tr ("Exported file will have spaces between adjacent values"));
  layoutDelimiters->addWidget (m_btnDelimitersSpaces);
  connect (m_btnDelimitersSpaces, SIGNAL (pressed ()), this, SLOT (slotDelimitersSpaces()));

  m_btnDelimitersTabs = new QRadioButton (tr ("Tabs"));
  m_btnDelimitersTabs->setWhatsThis (tr ("Exported file will have tabs between adjacent values"));
  layoutDelimiters->addWidget (m_btnDelimitersTabs);
  connect (m_btnDelimitersTabs, SIGNAL (pressed ()), this, SLOT (slotDelimitersTabs()));
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
  connect (m_btnFunctionsLayoutAllCurves, SIGNAL (pressed()), this, SLOT (slotFunctionsLayoutAllCurves ()));

  m_btnFunctionsLayoutOneCurve = new QRadioButton (tr ("One curve on each line"));
  m_btnFunctionsLayoutOneCurve->setWhatsThis (tr ("Exported file will have all the points for "
                                                  "the first curve, with one X-Y pair on each line, then the points for the second curve,..."));
  layoutLayout->addWidget (m_btnFunctionsLayoutOneCurve);
  connect (m_btnFunctionsLayoutOneCurve, SIGNAL (pressed()), this, SLOT (slotFunctionsLayoutOneCurve ()));
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
  connect (m_btnFunctionsPointsAllCurves, SIGNAL (pressed()), this, SLOT (slotFunctionsPointsAllCurves()));

  m_btnFunctionsPointsFirstCurve = new QRadioButton (tr ("Interpolate Y's at X's from first curve"));
  m_btnFunctionsPointsFirstCurve->setWhatsThis (tr ("Exported file will have values at every unique X "
                                                    "value from the first curve. Y values will be linearly interpolated if necessary"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsFirstCurve, row++, 0, 1, 3);
  connect (m_btnFunctionsPointsFirstCurve, SIGNAL (pressed()), this, SLOT (slotFunctionsPointsFirstCurve()));

  m_btnFunctionsPointsEvenlySpaced = new QRadioButton (tr ("Interpolate Y's at evenly spaced X values."));
  m_btnFunctionsPointsEvenlySpaced->setWhatsThis (tr ("Exported file will have values at evenly spaced X values "
                                                      "starting with the first X value. If the last interval does not end at the last X value, "
                                                      "the last X value will be added. Y values will be linearly interpolated if necessary"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsEvenlySpaced, row++, 0, 1, 3);
  connect (m_btnFunctionsPointsEvenlySpaced, SIGNAL (pressed()), this, SLOT (slotFunctionsPointsEvenlySpaced()));

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
  connect (m_btnFunctionsPointsRaw, SIGNAL (pressed()), this, SLOT (slotFunctionsPointsRaw()));
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
  connect (m_btnHeaderNone, SIGNAL (pressed ()), this, SLOT (slotHeaderNone()));

  m_btnHeaderSimple = new QRadioButton (tr ("Simple"));
  m_btnHeaderSimple->setWhatsThis (tr ("Exported file will have simple header line"));
  layoutHeader->addWidget (m_btnHeaderSimple);
  connect (m_btnHeaderSimple, SIGNAL (pressed ()), this, SLOT (slotHeaderSimple()));

  m_btnHeaderGnuplot = new QRadioButton (tr ("Gnuplot"));
  m_btnHeaderGnuplot->setWhatsThis (tr ("Exported file will have gnuplot header line"));
  layoutHeader->addWidget (m_btnHeaderGnuplot);
  connect (m_btnHeaderGnuplot, SIGNAL (pressed()), this, SLOT (slotHeaderGnuplot()));
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
  connect (m_btnRelationsPointsEvenlySpaced, SIGNAL (pressed()), this, SLOT (slotRelationsPointsEvenlySpaced()));

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
  connect (m_btnRelationsPointsRaw, SIGNAL (pressed()), this, SLOT (slotRelationsPointsRaw()));
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
                                                  cmdMediator ().document(),
                                                  *m_modelExportBefore,
                                                  *m_modelExportAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsExport::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::load";

  setCmdMediator (cmdMediator);

  m_modelExportBefore = new DlgModelExport (cmdMediator);
  m_modelExportAfter = new DlgModelExport (cmdMediator);

  QStringList::const_iterator itr;
  for (itr = m_modelExportAfter->curveNamesNotExported().begin ();
       itr != m_modelExportAfter->curveNamesNotExported().end();
       ++itr) {

    QString curveNameNotExported = *itr;
    m_listExcluded->addItem (curveNameNotExported);
  }

  ExportPointsSelectionFunctions exportPointsSelectionFunctions = m_modelExportAfter->exportPointsSelectionFunctions();
  m_btnFunctionsPointsAllCurves->setChecked (exportPointsSelectionFunctions == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES);
  m_btnFunctionsPointsFirstCurve->setChecked (exportPointsSelectionFunctions == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE);
  m_btnFunctionsPointsEvenlySpaced->setChecked (exportPointsSelectionFunctions == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC);
  m_btnFunctionsPointsRaw->setChecked (exportPointsSelectionFunctions == EXPORT_POINTS_SELECTION_FUNCTIONS_RAW);

  ExportLayoutFunctions exportLayoutFunctions = m_modelExportAfter->exportLayoutFunctions ();
  m_btnFunctionsLayoutAllCurves->setChecked (exportLayoutFunctions == EXPORT_LAYOUT_ALL_PER_LINE);
  m_btnFunctionsLayoutOneCurve->setChecked (exportLayoutFunctions == EXPORT_LAYOUT_ONE_PER_LINE);

  ExportPointsSelectionRelations exportPointsSelectionRelations = m_modelExportAfter->exportPointsSelectionRelations();
  m_btnRelationsPointsEvenlySpaced->setChecked (exportPointsSelectionRelations == EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE);
  m_btnRelationsPointsRaw->setChecked (exportPointsSelectionRelations == EXPORT_POINTS_SELECTION_RELATIONS_RAW);

  ExportDelimiter exportDelimiter = m_modelExportAfter->exportDelimiter ();
  m_btnDelimitersCommas->setChecked (exportDelimiter == EXPORT_DELIMITER_COMMA);
  m_btnDelimitersSpaces->setChecked (exportDelimiter == EXPORT_DELIMITER_SPACE);
  m_btnDelimitersTabs->setChecked (exportDelimiter == EXPORT_DELIMITER_TAB);

  ExportHeader exportHeader = m_modelExportAfter->exportHeader ();
  m_btnHeaderNone->setChecked (exportHeader == EXPORT_HEADER_NONE);
  m_btnHeaderSimple->setChecked (exportHeader == EXPORT_HEADER_SIMPLE);
  m_btnHeaderGnuplot->setChecked (exportHeader == EXPORT_HEADER_GNUPLOT);
}

void DlgSettingsExport::slotDelimitersCommas()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotDelimitersCommas";

  enableOk (true);

  m_modelExportAfter->setExportDelimiter(EXPORT_DELIMITER_COMMA);
}

void DlgSettingsExport::slotDelimitersSpaces()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotDelimitersSpaces";

  enableOk (true);

  m_modelExportAfter->setExportDelimiter(EXPORT_DELIMITER_SPACE);
}

void DlgSettingsExport::slotDelimitersTabs()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotDelimitersTabs";

  enableOk (true);

  m_modelExportAfter->setExportDelimiter(EXPORT_DELIMITER_TAB);
}

void DlgSettingsExport::slotExclude ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotExclude";

  enableOk (true);
}

void DlgSettingsExport::slotFunctionsLayoutAllCurves()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsLayoutAllCurves";

  enableOk (true);

  m_modelExportAfter->setExportLayoutFunctions(EXPORT_LAYOUT_ALL_PER_LINE);
}

void DlgSettingsExport::slotFunctionsLayoutOneCurve()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsLayoutOneCurve";

  enableOk (true);

  m_modelExportAfter->setExportLayoutFunctions(EXPORT_LAYOUT_ONE_PER_LINE);
}

void DlgSettingsExport::slotFunctionsPointsAllCurves()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsAllCurves";

  enableOk (true);

  m_modelExportAfter->setExportPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES);
  updateControls();
}

void DlgSettingsExport::slotFunctionsPointsEvenlySpaced()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsEvenlySpaced";

  enableOk (true);

  m_modelExportAfter->setExportPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC);
  updateControls();
}

void DlgSettingsExport::slotFunctionsPointsEvenlySpacedInterval()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsEvenlySpacedInterval";

  enableOk (true);
}

void DlgSettingsExport::slotFunctionsPointsFirstCurve()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsFirstCurve";

  enableOk (true);

  m_modelExportAfter->setExportPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE);
  updateControls();
}

void DlgSettingsExport::slotFunctionsPointsRaw()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsRaw";

  enableOk (true);

  m_modelExportAfter->setExportPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_RAW);
  updateControls();
}

void DlgSettingsExport::slotHeaderGnuplot()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotHeaderGnuplot";

  enableOk (true);

  m_modelExportAfter->setExportHeader(EXPORT_HEADER_GNUPLOT);
}

void DlgSettingsExport::slotHeaderNone()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotHeaderNone";

  enableOk (true);

  m_modelExportAfter->setExportHeader(EXPORT_HEADER_NONE);
}

void DlgSettingsExport::slotHeaderSimple()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotHeaderSimple";

  enableOk (true);

  m_modelExportAfter->setExportHeader(EXPORT_HEADER_SIMPLE);
}

void DlgSettingsExport::slotInclude ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotInclude";

  enableOk (true);
}

void DlgSettingsExport::slotListExcluded()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotListExcluded";

  enableOk (true);
  updateControls ();
}

void DlgSettingsExport::slotListIncluded()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotListIncluded";

  enableOk (true);
  updateControls ();
}

void DlgSettingsExport::slotRelationsPointsEvenlySpaced()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotRelationsPointsEvenlySpaced";

  enableOk (true);

  m_modelExportAfter->setExportPointsSelectionRelations(EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE);
  updateControls ();
}

void DlgSettingsExport::slotRelationsPointsEvenlySpacedInterval()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotRelationsPointsEvenlySpacedInterval";

  enableOk (true);
}

void DlgSettingsExport::slotRelationsPointsRaw()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotRelationsPointsRaw";

  enableOk (true);

  m_modelExportAfter->setExportPointsSelectionRelations(EXPORT_POINTS_SELECTION_RELATIONS_RAW);
  updateControls ();
}

void DlgSettingsExport::slotXLabel()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotXLabel";

  enableOk (true);
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
