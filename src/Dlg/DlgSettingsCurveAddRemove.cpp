/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "CmdSettingsCurveAddRemove.h"
#include "CurveNameList.h"
#include "DlgSettingsCurveAddRemove.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QCheckBox>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QListView>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QSpacerItem>
#include "QtToString.h"
#include "Settings.h"
#include "SettingsForGraph.h"

DlgSettingsCurveAddRemove::DlgSettingsCurveAddRemove(MainWindow &mainWindow) :
  DlgSettingsAbstractBase (tr ("Curve Add/Remove"),
                           "DlgSettingsCurveAddRemove",
                           mainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::DlgSettingsCurveAddRemove";

  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

DlgSettingsCurveAddRemove::~DlgSettingsCurveAddRemove()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::~DlgSettingsCurveAddRemove";
}

void DlgSettingsCurveAddRemove::appendCurveName (const QString &curveNameNew,
                                             const QString &curveNameOriginal,
                                             int numPoints)
{
  ENGAUGE_CHECK_PTR (m_curveNameList);

  int row = m_curveNameList->rowCount ();
  insertCurveName (row,
                   curveNameNew,
                   curveNameOriginal,
                   numPoints);
}

void DlgSettingsCurveAddRemove::createButtons (QGridLayout *layout,
                                               int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::createButtons";

  m_btnAdd = new QPushButton (tr ("Add..."));
  m_btnAdd->setWhatsThis (tr ("Adds a new curve to the curve list. The curve name can be edited in the curve name list.\n\n"
                              "Every curve name must be unique"));
  m_btnAdd->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect (m_btnAdd, SIGNAL (released ()), this, SLOT (slotNew()));
  layout->addWidget (m_btnAdd, row, 1, 1, 1, Qt::AlignLeft);

  m_btnRemove = new QPushButton (tr ("Remove"));
  m_btnRemove->setWhatsThis (tr ("Removes the currently selected curve from the curve list.\n\n"
                                 "There must always be at least one curve"));
  m_btnRemove->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect (m_btnRemove, SIGNAL (released ()), this, SLOT (slotRemove()));
  layout->addWidget (m_btnRemove, row++, 2, 1, 1, Qt::AlignRight);
}

void DlgSettingsCurveAddRemove::createListCurves (QGridLayout *layout,
                                          int &row)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::createListCurves";

  QLabel *label = new QLabel (tr ("Curve Names:"));
  layout->addWidget (label, row++, 1);

  m_curveNameList = new CurveNameList;

  // There is no Qt::ItemIsEditable flag for QListView, so instead we set that flag for the QListViewItems
  m_listCurves = new QListView;
  m_listCurves->setWhatsThis (tr ("List of the curves belonging to this document.\n\n"
                                  "Click on a curve name to edit it. Each curve name must be unique.\n\n"
                                  "Reorder curves by dragging them around."));
  m_listCurves->setMinimumHeight (200);
  m_listCurves->setSelectionMode (QAbstractItemView::ExtendedSelection);
  m_listCurves->setDefaultDropAction (Qt::MoveAction);
  m_listCurves->setDragDropOverwriteMode (true);
  m_listCurves->setDragEnabled (true);
  m_listCurves->setDropIndicatorShown (true);
  m_listCurves->setDragDropMode (QAbstractItemView::InternalMove);
  m_listCurves->setViewMode (QListView::ListMode);
  m_listCurves->setMovement (QListView::Snap);
  m_listCurves->setModel (m_curveNameList);
  layout->addWidget (m_listCurves, row++, 1, 1, 2);
  connect (m_curveNameList, SIGNAL (dataChanged (const QModelIndex &, const QModelIndex &, const QVector<int> &)),
           this, SLOT (slotDataChanged (const QModelIndex &, const QModelIndex &, const QVector<int> &)));
  connect (m_listCurves->selectionModel (), SIGNAL (selectionChanged (QItemSelection, QItemSelection)),
           this, SLOT (slotSelectionChanged (QItemSelection, QItemSelection)));
}

void DlgSettingsCurveAddRemove::createOptionalSaveDefault (QHBoxLayout *layout)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::createOptionalSaveDefault";

  m_btnSaveDefault = new QPushButton (tr ("Save As Default"));
  m_btnSaveDefault->setWhatsThis (tr ("Save the curve names for use as defaults for future graph curves."));
  connect (m_btnSaveDefault, SIGNAL (released ()), this, SLOT (slotSaveDefault ()));
  layout->addWidget (m_btnSaveDefault, 0, Qt::AlignLeft);

  QSpacerItem *spacer = new QSpacerItem (40, 2);
  layout->addItem (spacer);
}

QWidget *DlgSettingsCurveAddRemove::createSubPanel ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::createSubPanel";

  const int EMPTY_COLUMN_WIDTH = 30;

  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  int row = 1;
  createListCurves (layout, row);
  createButtons (layout, row);

  layout->setColumnStretch (0, 0); // Empty first column
  layout->setColumnMinimumWidth (0, EMPTY_COLUMN_WIDTH);
  layout->setColumnStretch (1, 1); // New
  layout->setColumnStretch (2, 1); // Remove
  layout->setColumnStretch (3, 0); // Empty last column
  layout->setColumnMinimumWidth (3, EMPTY_COLUMN_WIDTH);

  return subPanel;
}

bool DlgSettingsCurveAddRemove::endsWithNumber (const QString &str) const
{
  bool success = false;

  if (!str.isEmpty ()) {

      success = (str.right (1).at (0).digitValue() >= 0);
  }

  return success;
}

void DlgSettingsCurveAddRemove::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::handleOk";

  CmdSettingsCurveAddRemove *cmd = new CmdSettingsCurveAddRemove (mainWindow (),
                                                                  cmdMediator ().document(),
                                                                  *m_curveNameList);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsCurveAddRemove::insertCurveName (int row,
                                             const QString &curveNameNew,
                                             const QString &curveNameOriginal,
                                             int numPoints)
{
  if (m_curveNameList->insertRow (row)) {

    LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::insertCurveName curveName=" << curveNameNew.toLatin1 ().data ();

    CurveNameListEntry curvesEntry (curveNameNew,
                                    curveNameOriginal,
                                    numPoints);

    m_curveNameList->setData (m_curveNameList->index (row, 0),
                              curvesEntry.curveNameCurrent ());
    m_curveNameList->setData (m_curveNameList->index (row, 1),
                              curvesEntry.curveNameOriginal ());
    m_curveNameList->setData (m_curveNameList->index (row, 2),
                              numPoints);

  } else {

    LOG4CPP_ERROR_S ((*mainCat)) << "DlgSettingsCurveAddRemove::insertCurveName failed curveName=" 
                                 << curveNameNew.toLatin1 ().data ();

  }
}

void DlgSettingsCurveAddRemove::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::load";

  setCmdMediator (cmdMediator);

  // Remove any data from previous showing of dialog
  while (m_curveNameList->rowCount () > 0) {
    m_curveNameList->removeRow (0);
  }

  QStringList curveNames = cmdMediator.curvesGraphsNames ();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin (); itr != curveNames.end (); itr++) {
    QString curveName = *itr;
    appendCurveName (curveName,
                     curveName,
                     cmdMediator.curvesGraphsNumPoints (curveName));
  }

  enableOk (false); // Disable Ok button since there not yet any changes
}

QString DlgSettingsCurveAddRemove::nextCurveName () const
{
  const QString DASH_ONE ("-1"); // Nice value to start a new range at a lower level than the current level

  ENGAUGE_CHECK_PTR (m_listCurves);

  int numSelectedItems = m_listCurves->selectionModel ()->selectedIndexes ().count ();
  int numItems = m_listCurves->model ()->rowCount ();

  // Determine index where new entry will be inserted
  int currentIndex = -1;
  if ((numSelectedItems == 0) &&
      (numItems > 0)) {

    // Append after list which has at least one entry
    currentIndex = numItems;

  } else if (numSelectedItems == 1) {

    // Insert before the selected index
    currentIndex = m_listCurves->selectionModel ()->selectedIndexes ().at (0).row ();

  }

  // Curves names of existing before/after curves
  QString curveNameBefore, curveNameAfter;
  if (currentIndex > 0) {

    QModelIndex index = m_curveNameList->index (currentIndex - 1, 0);
    curveNameBefore = m_curveNameList->data (index).toString ();

  }

  if ((0 <= currentIndex) && (currentIndex < numItems)) {

    QModelIndex index = m_curveNameList->index (currentIndex, 0);
    curveNameAfter = m_curveNameList->data (index).toString ();

  }

  // New curve name computed from previous curve name
  QString curveNameNext;
  if (curveNameBefore.isEmpty () && !curveNameAfter.isEmpty () && endsWithNumber (curveNameAfter)) {

    // Pick a name before curveNameAfter
    int numberAfter = numberAtEnd (curveNameAfter);
    int numberNew = numberAfter - 1;
    int pos = curveNameAfter.lastIndexOf (QString::number (numberAfter));
    if (pos >= 0) {

      curveNameNext = QString ("%1%2")
                      .arg (curveNameAfter.left (pos))
                      .arg (numberNew);

    } else {

      curveNameNext = curveNameAfter; // Better than nothing

    }

  } else if (curveNameBefore.isEmpty ()) {

    curveNameNext = DEFAULT_GRAPH_CURVE_NAME; // If necessary, this will be deconflicted below

  } else {

    curveNameNext = curveNameBefore; // This will be deconflicted below

    if (endsWithNumber (curveNameBefore)) {

      // Curve name ends with a number. Pick a name after curveNameBefore, being sure to not match curveNameAfter
      int numberBefore = numberAtEnd (curveNameBefore);
      int numberNew = numberBefore + 1;
      int pos = curveNameBefore.lastIndexOf (QString::number (numberBefore));
      if (pos >= 0) {

        curveNameNext = QString ("%1%2")
                        .arg (curveNameBefore.left (pos))
                        .arg (numberNew);
        if (curveNameNext == curveNameAfter) {

          // The difference between before and after is exactly one so we go to a lower level
          curveNameNext = QString ("%1%2")
                          .arg (curveNameBefore)
                          .arg (DASH_ONE);
        }
      }
    }
  }

  // Curve name from settings takes precedence
  SettingsForGraph settingsForGraph;
  int indexOneBasedNext = numItems + 1;
  curveNameNext = settingsForGraph.defaultCurveName (indexOneBasedNext,
                                                     curveNameNext);

  // At this point we have curveNameNext which does not conflict with curveNameBefore or
  // curveNameAfter, but it may in rare cases conflict with some other curve name. We keep
  // adding to the name until there is no conflict
  while (m_curveNameList->containsCurveNameCurrent (curveNameNext)) {
    curveNameNext += DASH_ONE;
  }

  return curveNameNext;
}

int DlgSettingsCurveAddRemove::numberAtEnd (const QString &str) const
{
  ENGAUGE_ASSERT (endsWithNumber (str));

  // Go backward until the first nondigit
  int sign = +1;
  int ch = str.size () - 1;
  while (str.at (ch).digitValue() >= 0) {
    --ch;

    if (ch < 0) {
      break;
    }
  }
  ++ch;

  return sign * str.mid (ch).toInt ();
}

void DlgSettingsCurveAddRemove::removeSelectedCurves ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::removeSelectedCurves";

  for (int i = m_listCurves->selectionModel ()->selectedIndexes ().count () - 1; i >= 0; i--) {

    int row = m_listCurves->selectionModel ()->selectedIndexes ().at (i).row ();

    m_curveNameList->removeRow (row);
  }
}

void DlgSettingsCurveAddRemove::slotDataChanged (const QModelIndex &topLeft,
                                                 const QModelIndex &bottomRight,
                                                 const QVector<int> &roles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::slotDataChanged"
                              << " topLeft=(" << topLeft.row () << "," << topLeft.column () << ")"
                              << " bottomRight=(" << bottomRight.row () << "," << bottomRight.column () << ")"
                              << " roles=" << rolesAsString (roles).toLatin1 ().data ();

  updateControls ();
}

void DlgSettingsCurveAddRemove::slotNew ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::slotNew";

  const QString NO_ORIGINAL_CURVE_NAME;
  const int NO_POINTS = 0;

  QString curveNameSuggestion = nextCurveName ();

  appendCurveName (curveNameSuggestion,
                   NO_ORIGINAL_CURVE_NAME,
                   NO_POINTS);

  updateControls();
}

void DlgSettingsCurveAddRemove::slotRemove ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::slotRemove";

  int numPoints = 0;
  for (int i = 0; i < m_listCurves->selectionModel ()->selectedIndexes ().count (); i++) {

    int row = m_listCurves->selectionModel ()->selectedIndexes ().at (i).row ();
    QModelIndex idx = m_curveNameList->index (row, CurveNameListEntry::COL_NUM_POINTS ());
    int curvePoints = m_curveNameList->data (idx, Qt::DisplayRole).toInt ();

    numPoints += curvePoints;
  }

  int rtn = QMessageBox::Ok;
  if (numPoints > 0) {

    QString msg;
    if (m_listCurves->selectionModel ()->selectedIndexes ().count () == 1) {
      msg = QString ("%1 %2 %3")
            .arg (tr ("Removing this curve will also remove"))
            .arg (numPoints)
            .arg (tr ("points. Continue?"));
    } else {
      msg = QString ("%1 %2 %3")
            .arg (tr ("Removing these curves will also remove"))
            .arg (numPoints)
            .arg (tr ("points. Continue?"));
    }

    rtn = QMessageBox::warning (0,
                                tr ("Curves With Points"),
                                msg,
                                QMessageBox::Ok,
                                QMessageBox::Cancel);
  }

  if (rtn == QMessageBox::Ok) {
    removeSelectedCurves ();
  }

  updateControls();
}

void DlgSettingsCurveAddRemove::slotSaveDefault()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::slotSaveDefault";

  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);

  for (int row = 0; row < m_curveNameList->rowCount (); row++) {

    QModelIndex idxCurrent = m_curveNameList->index (row, 0);

    QString curveNameCurrent = m_curveNameList->data (idxCurrent).toString ();

    int indexOneBased = row + 1;

    SettingsForGraph settingsForGraph;
    QString groupName = settingsForGraph.groupNameForNthCurve (indexOneBased);

    settings.beginGroup (groupName);
    settings.setValue (SETTINGS_CURVE_NAME,
                       curveNameCurrent);
    settings.endGroup ();
  }
}

void DlgSettingsCurveAddRemove::slotSelectionChanged (QItemSelection, QItemSelection)
{
  updateControls ();
}

void DlgSettingsCurveAddRemove::updateControls ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurveAddRemove::updateControls";

  enableOk (true);

  ENGAUGE_CHECK_PTR (m_listCurves);

  int numSelectedItems = m_listCurves->selectionModel ()->selectedIndexes ().count ();
  int numItems = m_curveNameList->rowCount ();

  // Leave at least one curve
  m_btnRemove->setEnabled ((numSelectedItems > 0) && (numSelectedItems < numItems));
}
