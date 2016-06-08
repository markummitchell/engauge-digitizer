/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackBoundingRects.h"
#include "CmdMediator.h"
#include "CmdSettingsExportFormat.h"
#include "DocumentModelExportFormat.h"
#include "DlgSettingsExportFormat.h"
#include "ExportFileFunctions.h"
#include "ExportFileRelations.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleValidator>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollBar>
#include <QSettings>
#include <QTabWidget>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>
#include "Settings.h"
#include "Transformation.h"

const int MIN_INDENT_COLUMN_WIDTH = 20;
const int MIN_HEADER_EMPTY_COLUMN_WIDTH = 10;
const int MIN_EDIT_WIDTH = 110;
const int MAX_EDIT_WIDTH = 180;

const int TAB_WIDGET_INDEX_FUNCTIONS = 0;
//const int TAB_WIDGET_INDEX_RELATIONS = 1;

const QString EMPTY_PREVIEW;

DlgSettingsExportFormat::DlgSettingsExportFormat(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Export Format"),
                           "DlgSettingsExportFormat",
                           mainWindow),
  m_modelExportBefore (0),
  m_modelExportAfter (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::DlgSettingsExportFormat";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsExportFormat::~DlgSettingsExportFormat()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::~DlgSettingsExportFormat";
}

void DlgSettingsExportFormat::createCurveSelection (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createCurveSelection";

  QLabel *labelIncluded = new QLabel (tr ("Included"));
  layout->addWidget (labelIncluded, row, 0);

  QLabel *labelExcluded = new QLabel (tr ("Not included"));
  layout->addWidget (labelExcluded, row++, 2);

  m_listIncluded = new QListWidget;
  m_listIncluded->setWhatsThis (tr ("List of curves to be included in the exported file.\n\n"
                                    "The order of the curves here does not affect the order in the exported file. That "
                                    "order is determined by the Curves settings."));
  m_listIncluded->setSelectionMode (QAbstractItemView::MultiSelection);
  layout->addWidget (m_listIncluded, row, 0, 4, 1);
  connect (m_listIncluded, SIGNAL (itemSelectionChanged ()), this, SLOT (slotListIncluded()));

  m_listExcluded = new QListWidget;
  m_listExcluded->setWhatsThis (tr ("List of curves to be excluded from the exported file"));
  m_listExcluded->setSelectionMode (QAbstractItemView::MultiSelection);
  layout->addWidget (m_listExcluded, row++, 2, 4, 1);
  connect (m_listExcluded, SIGNAL (itemSelectionChanged ()), this, SLOT (slotListExcluded()));

  m_btnInclude = new QPushButton (tr ("<<Include"));
  m_btnInclude->setEnabled (false);
  m_btnInclude->setWhatsThis (tr ("Move the currently selected curve(s) from the excluded list"));
  layout->addWidget (m_btnInclude, row++, 1);
  connect (m_btnInclude, SIGNAL (released ()), this, SLOT (slotInclude()));

  m_btnExclude = new QPushButton (tr ("Exclude>>"));
  m_btnExclude->setEnabled (false);
  m_btnExclude->setWhatsThis (tr ("Move the currently selected curve(s) from the included list"));
  layout->addWidget (m_btnExclude, row++, 1);
  connect (m_btnExclude, SIGNAL (released ()), this, SLOT (slotExclude()));

  row++;
}

void DlgSettingsExportFormat::createDelimiters (QHBoxLayout *layoutMisc)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createDelimiters";

  QGroupBox *groupDelimiters = new QGroupBox (tr ("Delimiters"));
  layoutMisc->addWidget (groupDelimiters, 1);

  QVBoxLayout *layoutDelimiters = new QVBoxLayout;
  groupDelimiters->setLayout (layoutDelimiters);

  m_btnDelimitersCommas = new QRadioButton (exportDelimiterToString (EXPORT_DELIMITER_COMMA));
  m_btnDelimitersCommas->setWhatsThis (tr ("Exported file will have commas between adjacent values, unless overridden by tabs in TSV files."));
  layoutDelimiters->addWidget (m_btnDelimitersCommas);
  connect (m_btnDelimitersCommas, SIGNAL (released ()), this, SLOT (slotDelimitersCommas()));

  m_btnDelimitersSpaces = new QRadioButton (exportDelimiterToString (EXPORT_DELIMITER_SPACE));
  m_btnDelimitersSpaces->setWhatsThis (tr ("Exported file will have spaces between adjacent values, unless overridden by commas in CSV files, "
                                           "or tabs in TSV files."));
  layoutDelimiters->addWidget (m_btnDelimitersSpaces);
  connect (m_btnDelimitersSpaces, SIGNAL (released ()), this, SLOT (slotDelimitersSpaces()));

  m_btnDelimitersTabs = new QRadioButton (exportDelimiterToString (EXPORT_DELIMITER_TAB));
  m_btnDelimitersTabs->setWhatsThis (tr ("Exported file will have tabs between adjacent values, unless overridden by commas in CSV files."));
  layoutDelimiters->addWidget (m_btnDelimitersTabs);
  connect (m_btnDelimitersTabs, SIGNAL (released ()), this, SLOT (slotDelimitersTabs()));

  m_chkOverrideCsvTsv = new QCheckBox (tr ("Override in CSV/TSV files"));
  m_chkOverrideCsvTsv->setWhatsThis (tr ("Comma-separated value (CSV) files and tab-separated value (TSV) files will use commas and tabs "
                                         "respectively, unless this setting is selected. Selecting this setting will apply the delimiter setting "
                                         "to every file."));
  connect (m_chkOverrideCsvTsv, SIGNAL (stateChanged (int)), this, SLOT (slotOverrideCsvTsv(int)));
  layoutDelimiters->addWidget (m_chkOverrideCsvTsv);
}

void DlgSettingsExportFormat::createFileLayout (QHBoxLayout *layoutMisc)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createFileLayout";

  QGroupBox *groupLayout = new QGroupBox (tr ("Layout"));
  layoutMisc->addWidget (groupLayout, 1);

  QVBoxLayout *layoutLayout = new QVBoxLayout;
  groupLayout->setLayout (layoutLayout);

  m_btnFunctionsLayoutAllCurves = new QRadioButton (tr ("All curves on each line"));
  m_btnFunctionsLayoutAllCurves->setWhatsThis (tr ("Exported file will have, on each line, "
                                                   "an X value, the Y value for the first curve, the Y value for the second curve,..."));
  layoutLayout->addWidget (m_btnFunctionsLayoutAllCurves);
  connect (m_btnFunctionsLayoutAllCurves, SIGNAL (released()), this, SLOT (slotFunctionsLayoutAllCurves ()));

  m_btnFunctionsLayoutOneCurve = new QRadioButton (tr ("One curve on each line"));
  m_btnFunctionsLayoutOneCurve->setWhatsThis (tr ("Exported file will have all the points for "
                                                  "the first curve, with one X-Y pair on each line, then the points for the second curve,..."));
  layoutLayout->addWidget (m_btnFunctionsLayoutOneCurve);
  connect (m_btnFunctionsLayoutOneCurve, SIGNAL (released()), this, SLOT (slotFunctionsLayoutOneCurve ()));
}

void DlgSettingsExportFormat::createFunctionsPointsSelection (QHBoxLayout *layoutFunctions)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createFunctionsPointsSelection";

  QGroupBox *groupPointsSelection = new QGroupBox (tr ("Points Selection"));
  layoutFunctions->addWidget (groupPointsSelection, 1);

  QGridLayout *layoutPointsSelections = new QGridLayout;
  groupPointsSelection->setLayout (layoutPointsSelections);

  layoutPointsSelections->setColumnMinimumWidth(0, MIN_INDENT_COLUMN_WIDTH);
  layoutPointsSelections->setColumnStretch (0, 0);
  layoutPointsSelections->setColumnStretch (1, 0);
  layoutPointsSelections->setColumnStretch (2, 0);
  layoutPointsSelections->setColumnStretch (3, 1);

  int row = 0;
  m_btnFunctionsPointsAllCurves = new QRadioButton (tr ("Interpolate Ys at Xs from all curves"));
  m_btnFunctionsPointsAllCurves->setWhatsThis (tr ("Exported file will have values at every unique X "
                                                   "value from every curve. Y values will be linearly interpolated if necessary"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsAllCurves, row++, 0, 1, 4);
  connect (m_btnFunctionsPointsAllCurves, SIGNAL (released()), this, SLOT (slotFunctionsPointsAllCurves()));

  m_btnFunctionsPointsFirstCurve = new QRadioButton (tr ("Interpolate Ys at Xs from first curve"));
  m_btnFunctionsPointsFirstCurve->setWhatsThis (tr ("Exported file will have values at every unique X "
                                                    "value from the first curve. Y values will be linearly interpolated if necessary"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsFirstCurve, row++, 0, 1, 4);
  connect (m_btnFunctionsPointsFirstCurve, SIGNAL (released()), this, SLOT (slotFunctionsPointsFirstCurve()));

  m_btnFunctionsPointsEvenlySpaced = new QRadioButton (tr ("Interpolate Ys at evenly spaced X values."));
  m_btnFunctionsPointsEvenlySpaced->setWhatsThis (tr ("Exported file will have values at evenly spaced X values, separated by the interval selected below."));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsEvenlySpaced, row++, 0, 1, 4);
  connect (m_btnFunctionsPointsEvenlySpaced, SIGNAL (released()), this, SLOT (slotFunctionsPointsEvenlySpaced()));

  QLabel *labelInterval = new QLabel (tr ("Interval:"));
  layoutPointsSelections->addWidget (labelInterval, row, 1, 1, 1, Qt::AlignRight);

  m_editFunctionsPointsEvenlySpacing = new QLineEdit;
  m_validatorFunctionsPointsEvenlySpacing = new QDoubleValidator; // Minimum value, to prevent overflow, is set later according to settings
  m_editFunctionsPointsEvenlySpacing->setValidator (m_validatorFunctionsPointsEvenlySpacing);
  m_editFunctionsPointsEvenlySpacing->setMinimumWidth (MIN_EDIT_WIDTH);
  m_editFunctionsPointsEvenlySpacing->setMaximumWidth (MAX_EDIT_WIDTH);
  m_editFunctionsPointsEvenlySpacing->setWhatsThis (tr ("Interval, in the units of X, between successive points in the X direction.\n\n"
                                                        "If the scale is linear, then this interval is added to successive X values. If the scale is "
                                                        "logarithmic, then this interval is multiplied to successive X values.\n\n"
                                                        "The X values will be automatically aligned along simple numbers. If the first and/or last "
                                                        "points are not along the aligned X values, then one or two additional points are added "
                                                        "as necessary."));
  layoutPointsSelections->addWidget (m_editFunctionsPointsEvenlySpacing, row, 2, 1, 1, Qt::AlignLeft);
  connect (m_editFunctionsPointsEvenlySpacing, SIGNAL (textChanged(const QString &)), this, SLOT (slotFunctionsPointsEvenlySpacedInterval(const QString &)));

  m_cmbFunctionsPointsEvenlySpacingUnits = new QComboBox;
  m_cmbFunctionsPointsEvenlySpacingUnits->setWhatsThis (tr ("Units for spacing interval.\n\n"
                                                            "Pixel units are preferred when the spacing is to be independent of the X scale. The spacing will be "
                                                            "consistent across the graph, even if the X scale is logarithmic.\n\n"
                                                            "Graph units are preferred when the spacing is to depend on the X scale."));
  m_cmbFunctionsPointsEvenlySpacingUnits->addItem(exportPointsIntervalUnitsToString (EXPORT_POINTS_INTERVAL_UNITS_GRAPH),
                                                                                     QVariant (EXPORT_POINTS_INTERVAL_UNITS_GRAPH));
  m_cmbFunctionsPointsEvenlySpacingUnits->addItem(exportPointsIntervalUnitsToString (EXPORT_POINTS_INTERVAL_UNITS_SCREEN),
                                                                                     QVariant (EXPORT_POINTS_INTERVAL_UNITS_SCREEN));
  connect (m_cmbFunctionsPointsEvenlySpacingUnits, SIGNAL (activated (const QString &)),
           this, SLOT (slotFunctionsPointsEvenlySpacedIntervalUnits (const QString &))); // activated() ignores code changes
  layoutPointsSelections->addWidget (m_cmbFunctionsPointsEvenlySpacingUnits, row++, 3, 1, 1, Qt::AlignLeft);

  m_btnFunctionsPointsRaw = new QRadioButton (tr ("Raw Xs and Ys"));
  m_btnFunctionsPointsRaw->setWhatsThis (tr ("Exported file will have only original X and Y values"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsRaw, row++, 0, 1, 4);
  connect (m_btnFunctionsPointsRaw, SIGNAL (released()), this, SLOT (slotFunctionsPointsRaw()));
}

void DlgSettingsExportFormat::createHeader (QHBoxLayout *layoutMisc)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createHeader";

  const int COLUMN_RADIO_BUTTONS = 0, COLUMN_EMPTY = 1, COLUMN_LABEL = 2;

  QGroupBox *groupHeader = new QGroupBox (tr ("Header"));
  layoutMisc->addWidget (groupHeader, 1);

  QGridLayout *layoutHeader = new QGridLayout;
  layoutHeader->setColumnMinimumWidth(COLUMN_EMPTY,
                                      MIN_HEADER_EMPTY_COLUMN_WIDTH);
  groupHeader->setLayout (layoutHeader);
  int row = 0;

  m_btnHeaderNone = new QRadioButton (exportHeaderToString (EXPORT_HEADER_NONE));
  m_btnHeaderNone->setWhatsThis (tr ("Exported file will have no header line"));
  layoutHeader->addWidget (m_btnHeaderNone, row++, COLUMN_RADIO_BUTTONS, 1, 1);
  connect (m_btnHeaderNone, SIGNAL (released ()), this, SLOT (slotHeaderNone()));

  m_btnHeaderSimple = new QRadioButton (exportHeaderToString (EXPORT_HEADER_SIMPLE));
  m_btnHeaderSimple->setWhatsThis (tr ("Exported file will have simple header line"));
  layoutHeader->addWidget (m_btnHeaderSimple, row++, COLUMN_RADIO_BUTTONS, 1, 1);
  connect (m_btnHeaderSimple, SIGNAL (released ()), this, SLOT (slotHeaderSimple()));

  m_btnHeaderGnuplot = new QRadioButton (exportHeaderToString (EXPORT_HEADER_GNUPLOT));
  m_btnHeaderGnuplot->setWhatsThis (tr ("Exported file will have gnuplot header line"));
  layoutHeader->addWidget (m_btnHeaderGnuplot, row++, COLUMN_RADIO_BUTTONS, 1, 1);
  connect (m_btnHeaderGnuplot, SIGNAL (released()), this, SLOT (slotHeaderGnuplot()));

  createXLabel (layoutHeader,
                COLUMN_LABEL);
}

void DlgSettingsExportFormat::createOptionalSaveDefault (QHBoxLayout *layout)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createOptionalSaveDefault";

  m_btnSaveDefault = new QPushButton (tr ("Save As Default"));
  m_btnSaveDefault->setWhatsThis (tr ("Save the settings for use as future defaults."));
  connect (m_btnSaveDefault, SIGNAL (released ()), this, SLOT (slotSaveDefault ()));
  layout->addWidget (m_btnSaveDefault, 0, Qt::AlignLeft);
}

void DlgSettingsExportFormat::createPreview(QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createPreview";

  QLabel *label = new QLabel (tr ("Preview"));
  layout->addWidget (label, row++, 0, 1, 3);

  m_editPreview = new QTextEdit;
  m_editPreview->setReadOnly (true);
  m_editPreview->setWhatsThis (tr ("Preview window shows how current settings affect the exported file"));
  m_editPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_editPreview, row++, 0, 1, 3);
}

void DlgSettingsExportFormat::createRelationsPointsSelection (QHBoxLayout *layoutRelations)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createRelationsPointsSelection";

  QGroupBox *groupPointsSelection = new QGroupBox (tr ("Points Selection"));
  layoutRelations->addWidget (groupPointsSelection);

  QGridLayout *layoutPointsSelections = new QGridLayout;
  groupPointsSelection->setLayout (layoutPointsSelections);

  layoutPointsSelections->setColumnMinimumWidth(0, MIN_INDENT_COLUMN_WIDTH);
  layoutPointsSelections->setColumnStretch (0, 0);
  layoutPointsSelections->setColumnStretch (1, 0);
  layoutPointsSelections->setColumnStretch (2, 0);
  layoutPointsSelections->setColumnStretch (3, 1);

  int row = 0;
  m_btnRelationsPointsEvenlySpaced = new QRadioButton (tr ("Interpolate Xs and Ys at evenly spaced intervals."));
  m_btnRelationsPointsEvenlySpaced->setWhatsThis (tr ("Exported file will have points evenly spaced along each relation, separated by the interval "
                                                      "selected below. If the last interval does not end at the last point, then a shorter last interval "
                                                      "is added that ends on the last point."));
  layoutPointsSelections->addWidget (m_btnRelationsPointsEvenlySpaced, row++, 0, 1, 4);
  connect (m_btnRelationsPointsEvenlySpaced, SIGNAL (released()), this, SLOT (slotRelationsPointsEvenlySpaced()));

  QLabel *labelInterval = new QLabel (tr ("Interval:"));
  layoutPointsSelections->addWidget (labelInterval, row, 1, 1, 1, Qt::AlignRight);

  m_editRelationsPointsEvenlySpacing = new QLineEdit;
  m_validatorRelationsPointsEvenlySpacing = new QDoubleValidator; // Minimum value, to prevent overflow, is set later according to settings
  m_editRelationsPointsEvenlySpacing->setValidator (m_validatorRelationsPointsEvenlySpacing);
  m_editRelationsPointsEvenlySpacing->setMinimumWidth (MIN_EDIT_WIDTH);
  m_editRelationsPointsEvenlySpacing->setMaximumWidth (MAX_EDIT_WIDTH);
  m_editRelationsPointsEvenlySpacing->setWhatsThis (tr ("Interval between successive points when "
                                                        "exporting at evenly spaced (X,Y) coordinates."));
  layoutPointsSelections->addWidget (m_editRelationsPointsEvenlySpacing, row, 2, 1, 1, Qt::AlignLeft);
  connect (m_editRelationsPointsEvenlySpacing, SIGNAL (textChanged(const QString &)), this, SLOT (slotRelationsPointsEvenlySpacedInterval(const QString &)));

  m_cmbRelationsPointsEvenlySpacingUnits = new QComboBox;
  m_cmbRelationsPointsEvenlySpacingUnits->setWhatsThis (tr ("Units for spacing interval.\n\n"
                                                            "Pixel units are preferred when the spacing is to be independent of the X and Y scales. The spacing will be "
                                                            "consistent across the graph, even if a scale is logarithmic or the X and Y scales are different.\n\n"
                                                            "Graph units are usually preferred when the X and Y scales are identical."));
  m_cmbRelationsPointsEvenlySpacingUnits->addItem(exportPointsIntervalUnitsToString (EXPORT_POINTS_INTERVAL_UNITS_GRAPH),
                                                                                     QVariant (EXPORT_POINTS_INTERVAL_UNITS_GRAPH));
  m_cmbRelationsPointsEvenlySpacingUnits->addItem(exportPointsIntervalUnitsToString (EXPORT_POINTS_INTERVAL_UNITS_SCREEN),
                                                                                     QVariant (EXPORT_POINTS_INTERVAL_UNITS_SCREEN));
  connect (m_cmbRelationsPointsEvenlySpacingUnits, SIGNAL (activated (const QString &)),
           this, SLOT (slotRelationsPointsEvenlySpacedIntervalUnits (const QString &))); // activated() ignores code changes
  layoutPointsSelections->addWidget (m_cmbRelationsPointsEvenlySpacingUnits, row++, 3, 1, 1, Qt::AlignLeft);

  m_btnRelationsPointsRaw = new QRadioButton (tr ("Raw Xs and Ys"));
  m_btnRelationsPointsRaw->setWhatsThis (tr ("Exported file will have only original X and Y values"));
  layoutPointsSelections->addWidget (m_btnRelationsPointsRaw, row++, 0, 1, 4);
  connect (m_btnRelationsPointsRaw, SIGNAL (released()), this, SLOT (slotRelationsPointsRaw()));
}

QWidget *DlgSettingsExportFormat::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createSubPanel";

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  int row = 0;
  createCurveSelection (layout, row);

  createTabWidget (layout,
                   row);

  QWidget *widgetMisc = new QWidget;
  layout->addWidget (widgetMisc, row++, 0, 1, 3);
  QHBoxLayout *layoutMisc = new QHBoxLayout;
  widgetMisc->setLayout (layoutMisc);

  createDelimiters (layoutMisc); // One row of radio buttons
  createHeader (layoutMisc); // Two rows with radio buttons and then header label
  createFileLayout (layoutMisc); // One row of radio buttons

  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsExportFormat::createTabWidget (QGridLayout *layout,
                                         int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createTabWidget";

  m_tabWidget = new QTabWidget;
  // This gets connected below, after the tabs have been added
  layout->addWidget (m_tabWidget, row++, 0, 1, 3);

  QWidget *widgetFunctions = new QWidget;
  int indexFunctions = m_tabWidget->addTab (widgetFunctions, tr ("Functions"));
  QWidget *tabFunctions = m_tabWidget->widget (indexFunctions);
  tabFunctions->setWhatsThis (tr ("Functions Tab\n\n"
                                  "Controls for specifying the format of functions during export"));
  QHBoxLayout *layoutFunctions = new QHBoxLayout;
  widgetFunctions->setLayout (layoutFunctions);

  QWidget *widgetRelations = new QWidget;
  int indexRelations = m_tabWidget->addTab (widgetRelations, tr ("Relations"));
  QWidget *tabRelations = m_tabWidget->widget (indexRelations);
  tabRelations->setWhatsThis (tr ("Relations Tab\n\n"
                                  "Controls for specifying the format of relations during export"));
  QHBoxLayout *layoutRelations = new QHBoxLayout;
  widgetRelations->setLayout (layoutRelations);

  // Now that the tabs have been added we can connect this signal
  connect (m_tabWidget, SIGNAL (currentChanged (int)), this, SLOT (slotTabChanged (int)));

  createFunctionsPointsSelection (layoutFunctions);
  createRelationsPointsSelection (layoutRelations);
}

void DlgSettingsExportFormat::createXLabel (QGridLayout *layoutHeader,
                                      int colLabel)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::createXLabel";

  int row = 1; // Skip first row

  QLabel *title;
  if (true) {
    title = new QLabel (tr ("X Label:"));
  } else {
    title = new QLabel (tr ("Theta Label:"));
  }
  layoutHeader->addWidget (title, row++, colLabel, 1, 1);

  m_editXLabel = new QLineEdit;
  if (true) {
    m_editXLabel->setWhatsThis (tr ("Label in the header for x values"));
  } else {
    m_editXLabel->setWhatsThis (tr ("Label in the header for theta values"));
  }
  layoutHeader->addWidget (m_editXLabel, row++, colLabel, 1, 1);
  connect (m_editXLabel, SIGNAL (textChanged (const QString &)), this, SLOT (slotXLabel(const QString &)));
}

bool DlgSettingsExportFormat::goodIntervalFunctions() const
{
  // LOG4CPP_INFO_S is below

  QString textFunctions = m_editFunctionsPointsEvenlySpacing->text();
  int posFunctions;

  bool isGood = (m_validatorFunctionsPointsEvenlySpacing->validate (textFunctions, posFunctions) == QValidator::Acceptable);

  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::goodIntervalFunctions"
                              << " text=" << textFunctions.toLatin1().data()
                              << " good=" << (isGood ? "true" : "false")
                              << " bottom=" << m_validatorFunctionsPointsEvenlySpacing->bottom()
                              << " top=" << m_validatorFunctionsPointsEvenlySpacing->top();

  return isGood;
}

bool DlgSettingsExportFormat::goodIntervalRelations() const
{
  // LOG4CPP_INFO_S is below

  QString textRelations = m_editRelationsPointsEvenlySpacing->text();
  int posRelations;

  bool isGood = (m_validatorRelationsPointsEvenlySpacing->validate (textRelations, posRelations) == QValidator::Acceptable);

  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::goodIntervalRelations"
                              << " text=" << textRelations.toLatin1().data()
                              << " good=" << (isGood ? "true" : "false")
                              << " bottom=" << m_validatorRelationsPointsEvenlySpacing->bottom()
                              << " top=" << m_validatorRelationsPointsEvenlySpacing->top();

  return isGood;
}

void DlgSettingsExportFormat::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::handleOk";

  CmdSettingsExportFormat *cmd = new CmdSettingsExportFormat (mainWindow (),
                                                  cmdMediator ().document(),
                                                  *m_modelExportBefore,
                                                  *m_modelExportAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsExportFormat::initializeIntervalConstraints ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::initializeIntervalConstraints";

  const int MAX_POINTS_ACROSS_RANGE = 5000;

  // Get min and max of graph and screen coordinates
  CallbackBoundingRects ftor (mainWindow().transformation());

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackBoundingRects::callback);
  cmdMediator().iterateThroughCurvesPointsGraphs (ftorWithCallback);

  // If there are no points, then interval will be zero. That special case must be handled downstream to prevent infinite loops
  bool isEmpty;
  double maxSizeGraph = qMax (ftor.boundingRectGraph(isEmpty).width(),
                              ftor.boundingRectGraph(isEmpty).height());
  double maxSizeScreen = qMax (ftor.boundingRectScreen(isEmpty).width(),
                               ftor.boundingRectScreen(isEmpty).height());
  m_minIntervalGraph = maxSizeGraph / MAX_POINTS_ACROSS_RANGE;
  m_minIntervalScreen = maxSizeScreen / MAX_POINTS_ACROSS_RANGE;
}

void DlgSettingsExportFormat::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::load";

  setCmdMediator (cmdMediator);

  // Flush old data
  if (m_modelExportBefore != 0) {
    delete m_modelExportBefore;
  }
  if (m_modelExportAfter != 0) {
    delete m_modelExportAfter;
  }

  // Save new data
  m_modelExportBefore = new DocumentModelExportFormat (cmdMediator.document());
  m_modelExportAfter = new DocumentModelExportFormat (cmdMediator.document());

  // Populate controls. First load excluded curves
  m_listExcluded->clear();
  QStringList curveNamesExcluded = m_modelExportAfter->curveNamesNotExported();
  QStringList::const_iterator itr;
  for (itr = curveNamesExcluded.begin (); itr != curveNamesExcluded.end(); ++itr) {
    QString curveNameNotExported = *itr;
    m_listExcluded->addItem (curveNameNotExported);
  }

  // Include curves that are not excluded
  m_listIncluded->clear();
  QStringList curveNamesAll = cmdMediator.document().curvesGraphsNames();
  for (itr = curveNamesAll.begin (); itr != curveNamesAll.end(); itr++) {
    QString curveName = *itr;
    if (!curveNamesExcluded.contains (curveName)) {
      m_listIncluded->addItem (curveName);
    }
  }

  ExportPointsSelectionFunctions pointsSelectionFunctions = m_modelExportAfter->pointsSelectionFunctions();
  m_btnFunctionsPointsAllCurves->setChecked (pointsSelectionFunctions == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES);
  m_btnFunctionsPointsFirstCurve->setChecked (pointsSelectionFunctions == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE);
  m_btnFunctionsPointsEvenlySpaced->setChecked (pointsSelectionFunctions == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC);
  m_btnFunctionsPointsRaw->setChecked (pointsSelectionFunctions == EXPORT_POINTS_SELECTION_FUNCTIONS_RAW);

  ExportLayoutFunctions layoutFunctions = m_modelExportAfter->layoutFunctions ();
  m_btnFunctionsLayoutAllCurves->setChecked (layoutFunctions == EXPORT_LAYOUT_ALL_PER_LINE);
  m_btnFunctionsLayoutOneCurve->setChecked (layoutFunctions == EXPORT_LAYOUT_ONE_PER_LINE);

  ExportPointsSelectionRelations pointsSelectionRelations = m_modelExportAfter->pointsSelectionRelations();
  m_btnRelationsPointsEvenlySpaced->setChecked (pointsSelectionRelations == EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE);
  m_btnRelationsPointsRaw->setChecked (pointsSelectionRelations == EXPORT_POINTS_SELECTION_RELATIONS_RAW);

  ExportDelimiter delimiter = m_modelExportAfter->delimiter ();
  m_btnDelimitersCommas->setChecked (delimiter == EXPORT_DELIMITER_COMMA);
  m_btnDelimitersSpaces->setChecked (delimiter == EXPORT_DELIMITER_SPACE);
  m_btnDelimitersTabs->setChecked (delimiter == EXPORT_DELIMITER_TAB);

  m_chkOverrideCsvTsv->setChecked (m_modelExportAfter->overrideCsvTsv());

  ExportHeader header = m_modelExportAfter->header ();
  m_btnHeaderNone->setChecked (header == EXPORT_HEADER_NONE);
  m_btnHeaderSimple->setChecked (header == EXPORT_HEADER_SIMPLE);
  m_btnHeaderGnuplot->setChecked (header == EXPORT_HEADER_GNUPLOT);

  m_editXLabel->setText (m_modelExportAfter->xLabel());

  m_editFunctionsPointsEvenlySpacing->setText (QString::number (m_modelExportAfter->pointsIntervalFunctions()));
  m_editRelationsPointsEvenlySpacing->setText (QString::number (m_modelExportAfter->pointsIntervalRelations()));

  ExportPointsIntervalUnits pointsIntervalUnitsFunctions = m_modelExportAfter->pointsIntervalUnitsFunctions();
  ExportPointsIntervalUnits pointsIntervalUnitsRelations = m_modelExportAfter->pointsIntervalUnitsRelations();
  int indexFunctions = m_cmbFunctionsPointsEvenlySpacingUnits->findData (QVariant (pointsIntervalUnitsFunctions));
  int indexRelations = m_cmbRelationsPointsEvenlySpacingUnits->findData (QVariant (pointsIntervalUnitsRelations));
  m_cmbFunctionsPointsEvenlySpacingUnits->setCurrentIndex (indexFunctions);
  m_cmbRelationsPointsEvenlySpacingUnits->setCurrentIndex (indexRelations);

  initializeIntervalConstraints ();

  updateControls();
  updateIntervalConstraints();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsExportFormat::slotDelimitersCommas()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotDelimitersCommas";

  m_modelExportAfter->setDelimiter(EXPORT_DELIMITER_COMMA);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotDelimitersSpaces()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotDelimitersSpaces";

  m_modelExportAfter->setDelimiter(EXPORT_DELIMITER_SPACE);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotDelimitersTabs()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotDelimitersTabs";

  m_modelExportAfter->setDelimiter(EXPORT_DELIMITER_TAB);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotExclude ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotExclude";

  // Perform forward pass to get excluded curves in the proper order
  int i;
  QStringList excluded;
  for (i = 0; i < m_listIncluded->count(); i++) {
    if (m_listIncluded->item(i)->isSelected()) {
      excluded += m_listIncluded->item(i)->text();
    }
  }

  // Add the excluded curves to the excluded list
  for (i = 0; i < excluded.count(); i++) {
    QString curveName = excluded.at (i);
    m_listExcluded->addItem (curveName);
  }

  // Perform backwards pass to remove the excluded curves from the included list
  for (i = m_listIncluded->count() - 1; i>= 0; i--) {
    QString curveName = m_listIncluded->item(i)->text();
    if (excluded.contains (curveName)) {
      QListWidgetItem *item = m_listIncluded->item (i);
      m_listIncluded->removeItemWidget (item);
      delete item;
    }
  }

  m_modelExportAfter->setCurveNamesNotExported(excluded);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotFunctionsLayoutAllCurves()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotFunctionsLayoutAllCurves";

  m_modelExportAfter->setLayoutFunctions(EXPORT_LAYOUT_ALL_PER_LINE);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotFunctionsLayoutOneCurve()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotFunctionsLayoutOneCurve";

  m_modelExportAfter->setLayoutFunctions(EXPORT_LAYOUT_ONE_PER_LINE);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotFunctionsPointsAllCurves()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotFunctionsPointsAllCurves";

  m_modelExportAfter->setPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotFunctionsPointsEvenlySpaced()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotFunctionsPointsEvenlySpaced";

  m_modelExportAfter->setPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotFunctionsPointsEvenlySpacedInterval(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotFunctionsPointsEvenlySpacedInterval";

  // Prevent infinite loop on empty and "-" values which get treated as zero interval
  if (goodIntervalFunctions()) {
    m_modelExportAfter->setPointsIntervalFunctions(m_editFunctionsPointsEvenlySpacing->text().toDouble());
    updateControls();
    updatePreview();
  } else {
    m_editPreview->setText(EMPTY_PREVIEW);
  }
}

void DlgSettingsExportFormat::slotFunctionsPointsEvenlySpacedIntervalUnits(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotFunctionsPointsEvenlySpacedIntervalUnits";

  int index = m_cmbFunctionsPointsEvenlySpacingUnits->currentIndex();
  ExportPointsIntervalUnits units = (ExportPointsIntervalUnits) m_cmbFunctionsPointsEvenlySpacingUnits->itemData (index).toInt();

  m_modelExportAfter->setPointsIntervalUnitsFunctions(units);
  updateIntervalConstraints(); // Call this before updateControls so constraint checking is updated for ok button
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotFunctionsPointsFirstCurve()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotFunctionsPointsFirstCurve";

  m_modelExportAfter->setPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotFunctionsPointsRaw()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotFunctionsPointsRaw";

  m_modelExportAfter->setPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_RAW);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotHeaderGnuplot()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotHeaderGnuplot";

  m_modelExportAfter->setHeader(EXPORT_HEADER_GNUPLOT);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotHeaderNone()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotHeaderNone";

  m_modelExportAfter->setHeader(EXPORT_HEADER_NONE);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotHeaderSimple()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotHeaderSimple";

  m_modelExportAfter->setHeader(EXPORT_HEADER_SIMPLE);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotInclude ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotInclude";

  // Perform forward pass to get included curves in the proper order
  int i;
  QStringList included;
  for (i = 0; i < m_listExcluded->count(); i++) {
    if (m_listExcluded->item(i)->isSelected()) {
      included += m_listExcluded->item(i)->text();
    }
  }

  // Add the included curves to the included list
  for (i = 0; i < included.count(); i++) {
    QString curveName = included.at (i);
    m_listIncluded->addItem (curveName);
  }

  // Perform backwards pass to remove the included curves from the excluded list
  QStringList excluded;
  for (i = m_listExcluded->count() - 1; i>= 0; i--) {
    QString curveName = m_listExcluded->item(i)->text();
    QListWidgetItem *item = m_listExcluded->item (i);
    if (included.contains (curveName)) {
      m_listExcluded->removeItemWidget (item);
      delete item;
    } else {
      excluded += item->text();
    }
  }

  m_modelExportAfter->setCurveNamesNotExported(excluded);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotListExcluded()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotListExcluded";

  updateControls();
  // Do not call updatePreview since this method changes nothing
}

void DlgSettingsExportFormat::slotListIncluded()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotListIncluded";

  updateControls();
  // Do not call updatePreview since this method changes nothing
}

void DlgSettingsExportFormat::slotOverrideCsvTsv(int)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotOverrideCsvTsv";

  m_modelExportAfter->setOverrideCsvTsv(m_chkOverrideCsvTsv->isChecked());
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotRelationsPointsEvenlySpaced()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotRelationsPointsEvenlySpaced";

  m_modelExportAfter->setPointsSelectionRelations(EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotRelationsPointsEvenlySpacedInterval(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotRelationsPointsEvenlySpacedInterval";

  m_modelExportAfter->setPointsIntervalRelations(m_editRelationsPointsEvenlySpacing->text().toDouble());
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotRelationsPointsEvenlySpacedIntervalUnits(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotRelationsPointsEvenlySpacedIntervalUnits";

  int index = m_cmbRelationsPointsEvenlySpacingUnits->currentIndex();
  ExportPointsIntervalUnits units = (ExportPointsIntervalUnits) m_cmbRelationsPointsEvenlySpacingUnits->itemData (index).toInt();

  m_modelExportAfter->setPointsIntervalUnitsRelations(units);
  updateIntervalConstraints(); // Call this before updateControls so constraint checking is updated for ok button
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotRelationsPointsRaw()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotRelationsPointsRaw";

  m_modelExportAfter->setPointsSelectionRelations(EXPORT_POINTS_SELECTION_RELATIONS_RAW);
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::slotSaveDefault()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotSaveDefault";

  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup (SETTINGS_GROUP_EXPORT);

  settings.setValue (SETTINGS_EXPORT_DELIMITER,
                     QVariant (m_modelExportAfter->delimiter()));
  settings.setValue (SETTINGS_EXPORT_HEADER,
                     QVariant (m_modelExportAfter->header()));
  settings.setValue (SETTINGS_EXPORT_LAYOUT_FUNCTIONS,
                     QVariant (m_modelExportAfter->layoutFunctions()));
  settings.setValue (SETTINGS_EXPORT_POINTS_INTERVAL_FUNCTIONS,
                     QVariant (m_modelExportAfter->pointsIntervalFunctions()));
  settings.setValue (SETTINGS_EXPORT_POINTS_INTERVAL_RELATIONS,
                     QVariant (m_modelExportAfter->pointsIntervalRelations()));
  settings.setValue (SETTINGS_EXPORT_POINTS_INTERVAL_UNITS_FUNCTIONS,
                     QVariant (m_modelExportAfter->pointsIntervalUnitsFunctions()));
  settings.setValue (SETTINGS_EXPORT_POINTS_INTERVAL_UNITS_RELATIONS,
                     QVariant (m_modelExportAfter->pointsIntervalUnitsRelations()));
  settings.setValue (SETTINGS_EXPORT_POINTS_SELECTION_FUNCTIONS,
                     QVariant (m_modelExportAfter->pointsSelectionFunctions()));
  settings.setValue (SETTINGS_EXPORT_POINTS_SELECTION_RELATIONS,
                     QVariant (m_modelExportAfter->pointsSelectionRelations()));
  settings.setValue (SETTINGS_EXPORT_X_LABEL,
                     QVariant (m_modelExportAfter->xLabel()));

  settings.endGroup ();
}

void DlgSettingsExportFormat::slotTabChanged (int)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotTabChanged";

  updatePreview();
}

void DlgSettingsExportFormat::slotXLabel(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExportFormat::slotXLabel";

  m_modelExportAfter->setXLabel (m_editXLabel->text());
  updateControls();
  updatePreview();
}

void DlgSettingsExportFormat::updateControls ()
{
  bool isGoodState = goodIntervalFunctions() &&
                     goodIntervalRelations();
  enableOk (isGoodState);

  m_listIncluded->sortItems (Qt::AscendingOrder);
  m_listExcluded->sortItems (Qt::AscendingOrder);

  int selectedForInclude = m_listExcluded->selectedItems().count();
  int selectedForExclude = m_listIncluded->selectedItems().count();
  int inInclude = m_listIncluded->count();

  m_btnInclude->setEnabled (selectedForInclude > 0); // Need at least one selection
  m_btnExclude->setEnabled ((selectedForExclude > 0) && (inInclude - selectedForExclude > 0)); // Need at least one selection, and one left after the move

  m_editFunctionsPointsEvenlySpacing->setEnabled (m_btnFunctionsPointsEvenlySpaced->isChecked ());
  m_editRelationsPointsEvenlySpacing->setEnabled (m_btnRelationsPointsEvenlySpaced->isChecked ());

  m_editXLabel->setEnabled (!m_btnHeaderNone->isChecked());
}

void DlgSettingsExportFormat::updateIntervalConstraints ()
{
  double functionsMin = (m_modelExportAfter->pointsIntervalUnitsFunctions() == EXPORT_POINTS_INTERVAL_UNITS_GRAPH ?
                           m_minIntervalGraph :
                           m_minIntervalScreen);
  double relationsMin = (m_modelExportAfter->pointsIntervalUnitsRelations() == EXPORT_POINTS_INTERVAL_UNITS_GRAPH ?
                           m_minIntervalGraph :
                           m_minIntervalScreen);

  if (m_tabWidget->currentIndex() == TAB_WIDGET_INDEX_FUNCTIONS) {

    if (m_modelExportAfter->pointsIntervalFunctions() < functionsMin) {

      m_editFunctionsPointsEvenlySpacing->setText (QString::number (functionsMin));

    }

    m_validatorFunctionsPointsEvenlySpacing->setBottom (functionsMin);

  } else {

    if (m_modelExportAfter->pointsIntervalRelations() < relationsMin) {

      m_editRelationsPointsEvenlySpacing->setText (QString::number (relationsMin));

    }

    m_validatorRelationsPointsEvenlySpacing->setBottom (relationsMin);
  }
}

void DlgSettingsExportFormat::updatePreview()
{
  // Save the scroll position for continuity before and after the preview update
  int scrollPosition = m_editPreview->verticalScrollBar()->value();

  QString exportedText;
  QTextStream str (&exportedText);

  if (mainWindow().transformation().transformIsDefined()) {

    // Transformaiton is defined so we can create a preview
    if (m_tabWidget->currentIndex() == TAB_WIDGET_INDEX_FUNCTIONS) {

      ExportFileFunctions exportStrategy;
      exportStrategy.exportToFile (*m_modelExportAfter,
                                   cmdMediator().document(),
                                   mainWindow().modelMainWindow(),
                                   mainWindow().transformation(),
                                   str);

    } else {

      ExportFileRelations exportStrategy;
      exportStrategy.exportToFile (*m_modelExportAfter,
                                   cmdMediator().document(),
                                   mainWindow().modelMainWindow(),
                                   mainWindow().transformation(),
                                   str);

    }
  } else {

    str << "Preview is unavailable until axis points are defined.";
  }

  m_editPreview->setText (exportedText);

  // Restore scroll position
  m_editPreview->verticalScrollBar()->setValue (scrollPosition);
}
