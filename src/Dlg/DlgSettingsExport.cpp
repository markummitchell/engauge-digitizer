#include "CmdMediator.h"
#include "CmdSettingsExport.h"
#include "DocumentModelExport.h"
#include "DlgSettingsExport.h"
#include "ExportFileFunctions.h"
#include "ExportFileRelations.h"
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
#include <QTextStream>
#include <QVBoxLayout>
#include "Transformation.h"

const int MIN_INDENT_COLUMN_WIDTH = 20;
const int MIN_EDIT_WIDTH = 110;
const int MAX_EDIT_WIDTH = 180;

const int TAB_WIDGET_INDEX_FUNCTIONS = 0;
const int TAB_WIDGET_INDEX_RELATIONS = 1;

const double INTERVAL_BOTTOM = 1; // In pixels

const QString EMPTY_PREVIEW;

DlgSettingsExport::DlgSettingsExport(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Export",
                           "DlgSettingsExport",
                           mainWindow),
  m_modelExportBefore (0),
  m_modelExportAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsExport::createCurveSelection (QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::createCurveSelection";

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

  m_btnExclude = new QPushButton (tr ("Exclude>"));
  m_btnExclude->setEnabled (false);
  m_btnExclude->setWhatsThis (tr ("Move the currently selected curve(s) from the included list"));
  layout->addWidget (m_btnExclude, row++, 1);
  connect (m_btnExclude, SIGNAL (released ()), this, SLOT (slotExclude()));

  row++;
}

void DlgSettingsExport::createDelimiters (QHBoxLayout *layoutMisc)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::createDelimiters";

  QGroupBox *groupDelimiters = new QGroupBox (tr ("Delimiters"));
  layoutMisc->addWidget (groupDelimiters, 1);

  QVBoxLayout *layoutDelimiters = new QVBoxLayout;
  groupDelimiters->setLayout (layoutDelimiters);

  m_btnDelimitersCommas = new QRadioButton (exportDelimiterToString (EXPORT_DELIMITER_COMMA));
  m_btnDelimitersCommas->setWhatsThis (tr ("Exported file will have commas between adjacent values"));
  layoutDelimiters->addWidget (m_btnDelimitersCommas);
  connect (m_btnDelimitersCommas, SIGNAL (released ()), this, SLOT (slotDelimitersCommas()));

  m_btnDelimitersSpaces = new QRadioButton (exportDelimiterToString (EXPORT_DELIMITER_SPACE));
  m_btnDelimitersSpaces->setWhatsThis (tr ("Exported file will have spaces between adjacent values"));
  layoutDelimiters->addWidget (m_btnDelimitersSpaces);
  connect (m_btnDelimitersSpaces, SIGNAL (released ()), this, SLOT (slotDelimitersSpaces()));

  m_btnDelimitersTabs = new QRadioButton (exportDelimiterToString (EXPORT_DELIMITER_TAB));
  m_btnDelimitersTabs->setWhatsThis (tr ("Exported file will have tabs between adjacent values"));
  layoutDelimiters->addWidget (m_btnDelimitersTabs);
  connect (m_btnDelimitersTabs, SIGNAL (released ()), this, SLOT (slotDelimitersTabs()));
}

void DlgSettingsExport::createFunctionsLayout (QHBoxLayout *layoutFunctions)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::createFunctionsLayout";

  QGroupBox *groupLayout = new QGroupBox (tr ("Layout"));
  layoutFunctions->addWidget (groupLayout, 1);

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

void DlgSettingsExport::createFunctionsPointsSelection (QHBoxLayout *layoutFunctions)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::createFunctionsPointsSelection";

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
  connect (m_btnFunctionsPointsAllCurves, SIGNAL (released()), this, SLOT (slotFunctionsPointsAllCurves()));

  m_btnFunctionsPointsFirstCurve = new QRadioButton (tr ("Interpolate Y's at X's from first curve"));
  m_btnFunctionsPointsFirstCurve->setWhatsThis (tr ("Exported file will have values at every unique X "
                                                    "value from the first curve. Y values will be linearly interpolated if necessary"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsFirstCurve, row++, 0, 1, 3);
  connect (m_btnFunctionsPointsFirstCurve, SIGNAL (released()), this, SLOT (slotFunctionsPointsFirstCurve()));

  m_btnFunctionsPointsEvenlySpaced = new QRadioButton (tr ("Interpolate Y's at evenly spaced X values."));
  m_btnFunctionsPointsEvenlySpaced->setWhatsThis (tr ("Exported file will have values at evenly spaced X values "
                                                      "starting with the first X value. If the last interval does not end at the last X value, "
                                                      "the last X value will be added. Y values will be linearly interpolated if necessary"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsEvenlySpaced, row++, 0, 1, 3);
  connect (m_btnFunctionsPointsEvenlySpaced, SIGNAL (released()), this, SLOT (slotFunctionsPointsEvenlySpaced()));

  QLabel *labelInterval = new QLabel ("Interval (pixels):");
  layoutPointsSelections->addWidget (labelInterval, row, 1, 1, 1, Qt::AlignRight);

  m_editFunctionsPointsEvenlySpacing = new QLineEdit;
  m_validatorFunctionsPointsEvenlySpacing = new QDoubleValidator;
  m_validatorFunctionsPointsEvenlySpacing->setBottom(INTERVAL_BOTTOM);
  m_editFunctionsPointsEvenlySpacing->setValidator (m_validatorFunctionsPointsEvenlySpacing);
  m_editFunctionsPointsEvenlySpacing->setMinimumWidth (MIN_EDIT_WIDTH);
  m_editFunctionsPointsEvenlySpacing->setMaximumWidth (MAX_EDIT_WIDTH);
  m_editFunctionsPointsEvenlySpacing->setWhatsThis (tr ("Interval, in pixels, between successive points in the X direction when "
                                                        "exporting at evenly spaced X values.\n\n"
                                                        "This parameter is specified in screen pixels rather than X units so "
                                                        "the intervals are evenly spaced for both linear and log scaling."));
  layoutPointsSelections->addWidget (m_editFunctionsPointsEvenlySpacing, row++, 2, 1, 1, Qt::AlignLeft);
  connect (m_editFunctionsPointsEvenlySpacing, SIGNAL (textChanged(const QString &)), this, SLOT (slotFunctionsPointsEvenlySpacedInterval(const QString &)));

  m_btnFunctionsPointsRaw = new QRadioButton (tr ("Raw X's and Y's"));
  m_btnFunctionsPointsRaw->setWhatsThis (tr ("Exported file will have only original X and Y values"));
  layoutPointsSelections->addWidget (m_btnFunctionsPointsRaw, row++, 0, 1, 3);
  connect (m_btnFunctionsPointsRaw, SIGNAL (released()), this, SLOT (slotFunctionsPointsRaw()));
}

void DlgSettingsExport::createHeader (QHBoxLayout *layoutMisc)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::createHeader";

  QGroupBox *groupHeader = new QGroupBox (tr ("Header"));
  layoutMisc->addWidget (groupHeader, 1);

  QVBoxLayout *layoutHeader = new QVBoxLayout;
  groupHeader->setLayout (layoutHeader);

  m_btnHeaderNone = new QRadioButton (exportHeaderToString (EXPORT_HEADER_NONE));
  m_btnHeaderNone->setWhatsThis (tr ("Exported file will have no header line"));
  layoutHeader->addWidget (m_btnHeaderNone);
  connect (m_btnHeaderNone, SIGNAL (released ()), this, SLOT (slotHeaderNone()));

  m_btnHeaderSimple = new QRadioButton (exportHeaderToString (EXPORT_HEADER_SIMPLE));
  m_btnHeaderSimple->setWhatsThis (tr ("Exported file will have simple header line"));
  layoutHeader->addWidget (m_btnHeaderSimple);
  connect (m_btnHeaderSimple, SIGNAL (released ()), this, SLOT (slotHeaderSimple()));

  m_btnHeaderGnuplot = new QRadioButton (exportHeaderToString (EXPORT_HEADER_GNUPLOT));
  m_btnHeaderGnuplot->setWhatsThis (tr ("Exported file will have gnuplot header line"));
  layoutHeader->addWidget (m_btnHeaderGnuplot);
  connect (m_btnHeaderGnuplot, SIGNAL (released()), this, SLOT (slotHeaderGnuplot()));
}

void DlgSettingsExport::createPreview(QGridLayout *layout, int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::createPreview";

  QLabel *label = new QLabel (tr ("Preview"));
  layout->addWidget (label, row++, 0, 1, 3);

  m_editPreview = new QTextEdit;
  m_editPreview->setReadOnly (true);
  m_editPreview->setWhatsThis (tr ("Preview window shows how current settings affect the exported file"));
  m_editPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_editPreview, row++, 0, 1, 3);
}

void DlgSettingsExport::createRelationsPointsSelection (QHBoxLayout *layoutRelations)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::createRelationsPointsSelection";

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
  connect (m_btnRelationsPointsEvenlySpaced, SIGNAL (released()), this, SLOT (slotRelationsPointsEvenlySpaced()));

  QLabel *labelInterval = new QLabel ("Interval (pixels):");
  layoutPointsSelections->addWidget (labelInterval, row, 1, 1, 1, Qt::AlignRight);

  m_editRelationsPointsEvenlySpacing = new QLineEdit;
  m_validatorRelationsPointsEvenlySpacing = new QDoubleValidator;
  m_validatorRelationsPointsEvenlySpacing->setBottom(INTERVAL_BOTTOM);
  m_editRelationsPointsEvenlySpacing->setValidator (m_validatorRelationsPointsEvenlySpacing);
  m_editRelationsPointsEvenlySpacing->setMinimumWidth (MIN_EDIT_WIDTH);
  m_editRelationsPointsEvenlySpacing->setMaximumWidth (MAX_EDIT_WIDTH);
  m_editRelationsPointsEvenlySpacing->setWhatsThis (tr ("Interval, in pixels, between successive points when "
                                                        "exporting at evenly spaced (X,Y) coordinates.\n\n"
                                                        "This parameter is specified in screen pixels rather than X and Y units so "
                                                        "the intervals are evenly spaced for both linear and log scaling."));
  layoutPointsSelections->addWidget (m_editRelationsPointsEvenlySpacing, row++, 2, 1, 1, Qt::AlignLeft);
  connect (m_editRelationsPointsEvenlySpacing, SIGNAL (textChanged(const QString &)), this, SLOT (slotRelationsPointsEvenlySpacedInterval(const QString &)));

  m_btnRelationsPointsRaw = new QRadioButton (tr ("Raw X's and Y's"));
  m_btnRelationsPointsRaw->setWhatsThis (tr ("Exported file will have only original X and Y values"));
  layoutPointsSelections->addWidget (m_btnRelationsPointsRaw, row++, 0, 1, 3);
  connect (m_btnRelationsPointsRaw, SIGNAL (released()), this, SLOT (slotRelationsPointsRaw()));
}

QWidget *DlgSettingsExport::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::createSubPanel";

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
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::createTabWidget";

  m_tabWidget = new QTabWidget;
  // This gets connected below, after the tabs have been added
  layout->addWidget (m_tabWidget, row++, 0, 1, 3);

  QWidget *widgetFunctions = new QWidget;
  int indexFunctions = m_tabWidget->addTab (widgetFunctions, tr ("Functions"));
  QWidget *tabFunctions = m_tabWidget->widget (indexFunctions);
  tabFunctions->setWhatsThis (tr ("Functions Tab\n\n"
                                  "Controls for specifying the format of functions during export"));
  layoutFunctions = new QHBoxLayout;
  widgetFunctions->setLayout (layoutFunctions);

  QWidget *widgetRelations = new QWidget;
  int indexRelations = m_tabWidget->addTab (widgetRelations, tr ("Relations"));
  QWidget *tabRelations = m_tabWidget->widget (indexRelations);
  tabRelations->setWhatsThis (tr ("Relations Tab\n\n"
                                  "Controls for specifying the format of relations during export"));
  layoutRelations = new QHBoxLayout;
  widgetRelations->setLayout (layoutRelations);

  // Now that the tabs have been added we can connect this signal
  connect (m_tabWidget, SIGNAL (currentChanged (int)), this, SLOT (slotTabChanged (int)));
}

void DlgSettingsExport::createXLabel (QHBoxLayout *layoutMisc)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::createXLabel";

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
  connect (m_editXLabel, SIGNAL (textChanged (const QString &)), this, SLOT (slotXLabel(const QString &)));
}

bool DlgSettingsExport::goodIntervalFunctions() const
{
  QString textFunctions = m_editFunctionsPointsEvenlySpacing->text();
  int posFunctions;

  return (m_validatorFunctionsPointsEvenlySpacing->validate (textFunctions, posFunctions) == QValidator::Acceptable);
}

bool DlgSettingsExport::goodIntervalRelations() const
{
  QString textRelations = m_editRelationsPointsEvenlySpacing->text();
  int posRelations;

  return (m_validatorRelationsPointsEvenlySpacing->validate (textRelations, posRelations) == QValidator::Acceptable);
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

  // Flush old data
  if (m_modelExportBefore != 0) {
    delete m_modelExportBefore;
  }
  if (m_modelExportAfter != 0) {
    delete m_modelExportAfter;
  }

  // Save new data
  m_modelExportBefore = new DocumentModelExport (cmdMediator.document());
  m_modelExportAfter = new DocumentModelExport (cmdMediator.document());

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

  ExportHeader header = m_modelExportAfter->header ();
  m_btnHeaderNone->setChecked (header == EXPORT_HEADER_NONE);
  m_btnHeaderSimple->setChecked (header == EXPORT_HEADER_SIMPLE);
  m_btnHeaderGnuplot->setChecked (header == EXPORT_HEADER_GNUPLOT);

  m_editXLabel->setText (m_modelExportAfter->xLabel());
  m_editFunctionsPointsEvenlySpacing->setText (QString::number (m_modelExportAfter->pointsIntervalFunctions()));
  m_editRelationsPointsEvenlySpacing->setText (QString::number (m_modelExportAfter->pointsIntervalRelations()));

  updateControls();
  enableOk (false); // Disable Ok button since there not yet any changes
  updatePreview();
}

void DlgSettingsExport::slotDelimitersCommas()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotDelimitersCommas";

  m_modelExportAfter->setDelimiter(EXPORT_DELIMITER_COMMA);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotDelimitersSpaces()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotDelimitersSpaces";

  m_modelExportAfter->setDelimiter(EXPORT_DELIMITER_SPACE);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotDelimitersTabs()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotDelimitersTabs";

  m_modelExportAfter->setDelimiter(EXPORT_DELIMITER_TAB);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotExclude ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotExclude";

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

void DlgSettingsExport::slotFunctionsLayoutAllCurves()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsLayoutAllCurves";

  m_modelExportAfter->setLayoutFunctions(EXPORT_LAYOUT_ALL_PER_LINE);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotFunctionsLayoutOneCurve()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsLayoutOneCurve";

  m_modelExportAfter->setLayoutFunctions(EXPORT_LAYOUT_ONE_PER_LINE);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotFunctionsPointsAllCurves()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsAllCurves";

  m_modelExportAfter->setPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotFunctionsPointsEvenlySpaced()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsEvenlySpaced";

  m_modelExportAfter->setPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotFunctionsPointsEvenlySpacedInterval(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsEvenlySpacedInterval";

  // Prevent infinite loop on empty and "-" values which get treated as zero interval
  if (goodIntervalFunctions()) {
    m_modelExportAfter->setPointsIntervalFunctions(m_editFunctionsPointsEvenlySpacing->text().toDouble());
    updateControls();
    updatePreview();
  } else {
    m_editPreview->setText(EMPTY_PREVIEW);
  }
}

void DlgSettingsExport::slotFunctionsPointsFirstCurve()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsFirstCurve";

  m_modelExportAfter->setPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotFunctionsPointsRaw()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotFunctionsPointsRaw";

  m_modelExportAfter->setPointsSelectionFunctions(EXPORT_POINTS_SELECTION_FUNCTIONS_RAW);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotHeaderGnuplot()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotHeaderGnuplot";

  m_modelExportAfter->setHeader(EXPORT_HEADER_GNUPLOT);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotHeaderNone()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotHeaderNone";

  m_modelExportAfter->setHeader(EXPORT_HEADER_NONE);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotHeaderSimple()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotHeaderSimple";

  m_modelExportAfter->setHeader(EXPORT_HEADER_SIMPLE);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotInclude ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotInclude";

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

void DlgSettingsExport::slotListExcluded()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotListExcluded";

  updateControls();
  // Do not call updatePreview since this method changes nothing
}

void DlgSettingsExport::slotListIncluded()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotListIncluded";

  updateControls();
  // Do not call updatePreview since this method changes nothing
}

void DlgSettingsExport::slotRelationsPointsEvenlySpaced()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotRelationsPointsEvenlySpaced";

  m_modelExportAfter->setPointsSelectionRelations(EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotRelationsPointsEvenlySpacedInterval(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotRelationsPointsEvenlySpacedInterval";

  // Prevent infinite loop on empty and "-" values which get treated as zero interval
  if (goodIntervalRelations()) {
    m_modelExportAfter->setPointsIntervalRelations(m_editRelationsPointsEvenlySpacing->text().toDouble());
    updateControls();
    updatePreview();
  } else {
    m_editPreview->setText (EMPTY_PREVIEW);
  }
}

void DlgSettingsExport::slotRelationsPointsRaw()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotRelationsPointsRaw";

  m_modelExportAfter->setPointsSelectionRelations(EXPORT_POINTS_SELECTION_RELATIONS_RAW);
  updateControls();
  updatePreview();
}

void DlgSettingsExport::slotTabChanged (int)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotTabChanged";

  updatePreview();
}

void DlgSettingsExport::slotXLabel(const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsExport::slotXLabel";

  m_modelExportAfter->setXLabel (m_editXLabel->text());
  updateControls();
  updatePreview();
}

void DlgSettingsExport::updateControls ()
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
}

void DlgSettingsExport::updatePreview()
{
  QString exportedText;
  QTextStream str (&exportedText);

  if (m_tabWidget->currentIndex() == TAB_WIDGET_INDEX_FUNCTIONS) {

    ExportFileFunctions exportStrategy;
    exportStrategy.exportToFile (*m_modelExportAfter,
                                 cmdMediator().document(),
                                 mainWindow().transformation(),
                                 str);

  } else {

    ExportFileRelations exportStrategy;
    exportStrategy.exportToFile (*m_modelExportAfter,
                                 cmdMediator().document(),
                                 mainWindow().transformation(),
                                 str);

  }

  m_editPreview->setText (exportedText);
}
