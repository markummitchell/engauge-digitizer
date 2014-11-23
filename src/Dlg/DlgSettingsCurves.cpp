#include "CmdMediator.h"
#include "CmdSettingsCurves.h"
#include "DlgModelCurves.h"
#include "DlgSettingsCurves.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QListView>
#include <QMessageBox>
#include <QPushButton>
#include "QtToString.h"

DlgSettingsCurves::DlgSettingsCurves(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Curves", mainWindow)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsCurves::appendCurveName (const QString &curveNameNew,
                                         const QString &curveNameOriginal,
                                         int numPoints)
{
  Q_ASSERT (m_modelCurves != 0);

  int row = m_modelCurves->rowCount ();
  insertCurveName (row,
                   curveNameNew,
                   curveNameOriginal,
                   numPoints);
}

void DlgSettingsCurves::createButtons (QGridLayout *layout,
                                       int &row)
{
  m_btnNew = new QPushButton ("New...");
  m_btnNew->setWhatsThis (tr ("Adds a new curve to the curve list. The curve name can be edited in the curve name list.\n\n"
                              "If a curve is selected then the new curve will be inserted just before it, otherwise the new curve "
                              "will be added at the end.\n\n"
                              "Every curve name must be unique"));
  m_btnNew->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect (m_btnNew, SIGNAL (pressed ()), this, SLOT (slotNew()));
  layout->addWidget (m_btnNew, row, 1, 1, 1, Qt::AlignLeft);

  m_btnRemove = new QPushButton ("Remove");
  m_btnRemove->setWhatsThis (tr ("Removes the currently selected curve from the curve list.\n\n"
                                 "There must always be at least one curve"));
  m_btnRemove->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect (m_btnRemove, SIGNAL (pressed ()), this, SLOT (slotRemove()));
  layout->addWidget (m_btnRemove, row++, 2, 1, 1, Qt::AlignRight);
}

void DlgSettingsCurves::createListCurves (QGridLayout *layout,
                                          int &row)
{
  QLabel *label = new QLabel (tr ("Curve Names:"));
  layout->addWidget (label, row++, 1);

  m_modelCurves = new DlgModelCurves;

  // There is no Qt::ItemIsEditable flag for QListView, so instead we set that flag for the QListViewItems
  m_listCurves = new QListView;
  m_listCurves->setWhatsThis (tr ("List of the curves belonging to this document.\n\n"
                                  "Click on a curve name to edit it.\n\n"
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
  m_listCurves->setModel (m_modelCurves);
  layout->addWidget (m_listCurves, row++, 1, 1, 2);
  connect (m_modelCurves, SIGNAL (dataChanged (const QModelIndex &, const QModelIndex &, const QVector<int> &)),
           this, SLOT (slotDataChanged (const QModelIndex &, const QModelIndex &, const QVector<int> &)));
  connect (m_listCurves->selectionModel (), SIGNAL (selectionChanged (QItemSelection, QItemSelection)),
           this, SLOT (slotSelectionChanged (QItemSelection, QItemSelection)));
}

QWidget *DlgSettingsCurves::createSubPanel ()
{
  const int EMPTY_COLUMN_WIDTH = 30;
  const int EMPTY_ROW_HEIGHT = 40;

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

  layout->setRowStretch (0, 0); // Empty first row
  layout->setRowMinimumHeight (0, EMPTY_ROW_HEIGHT);
  layout->setRowStretch (row, 0); // Empty last row
  layout->setRowMinimumHeight (row, EMPTY_ROW_HEIGHT);

  return subPanel;
}

bool DlgSettingsCurves::endsWithNumber (const QString &str) const
{
  bool success = false;

  if (!str.isEmpty ()) {

      success = (str.right (1).at (0).digitValue() >= 0);
  }

  return success;
}

void DlgSettingsCurves::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurves::handleOk";

  CmdSettingsCurves *cmd = new CmdSettingsCurves (mainWindow (),
                                                  cmdMediator ().document(),
                                                  *m_modelCurves);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsCurves::insertCurveName (int row,
                                         const QString &curveNameNew,
                                         const QString &curveNameOriginal,
                                         int numPoints)
{
  if (m_modelCurves->insertRow (row)) {

    LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurves::insertCurveName curveName=" << curveNameNew.toLatin1 ().data ();

    DlgModelCurveEntry curveEntry (curveNameNew,
                                   curveNameOriginal,
                                   numPoints);

    m_modelCurves->setData (m_modelCurves->index (row, 0),
                            curveEntry.curveNameCurrent ());
    m_modelCurves->setData (m_modelCurves->index (row, 1),
                            curveEntry.curveNameOriginal ());
    m_modelCurves->setData (m_modelCurves->index (row, 2),
                            numPoints);

  } else {

    LOG4CPP_ERROR_S ((*mainCat)) << "DlgSettingsCurves::insertCurveName failed curveName=" << curveNameNew.toLatin1 ().data ();

  }
}

void DlgSettingsCurves::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurves::load";

  setCmdMediator (cmdMediator);

  // Remove any data from previous showing of dialog
  while (m_modelCurves->rowCount () > 0) {
    m_modelCurves->removeRow (0);
  }

  QStringList curveNames = cmdMediator.curvesGraphsNames ();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin (); itr != curveNames.end (); itr++) {
    QString curveName = *itr;
    appendCurveName (curveName,
                     curveName,
                     cmdMediator.curvesGraphsNumPoints (curveName));
  }
}

QString DlgSettingsCurves::nextCurveName () const
{
  const QString DASH_ONE ("-1"); // Nice value to start a new range at a lower level than the current level

  Q_ASSERT (m_listCurves != 0);

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

    QModelIndex index = m_modelCurves->index (currentIndex - 1, 0);
    curveNameBefore = m_modelCurves->data (index).toString ();

  }

  if ((0 <= currentIndex) && (currentIndex < numItems)) {

    QModelIndex index = m_modelCurves->index (currentIndex, 0);
    curveNameAfter = m_modelCurves->data (index).toString ();

  }

  // New curve name
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

  } else if (!curveNameBefore.isEmpty () && endsWithNumber (curveNameBefore)) {

    // Pick a name after curveNameBefore, being sure to not match curveNameAfter
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
    } else {

      curveNameNext = curveNameBefore; // Better than nothing

    }
  }

  // At this point we have curveNameNext which does not conflict with curveNameBefore or
  // curveNameAfter, but it may in rare cases conflict with some other curve name. We keep
  // adding to the name until there is no conflict
  while (m_modelCurves->containsCurveNameCurrent (curveNameNext)) {
    curveNameNext += DASH_ONE;
  }

  return curveNameNext;
}

int DlgSettingsCurves::numberAtEnd (const QString &str) const
{
  Q_ASSERT (endsWithNumber (str));

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

void DlgSettingsCurves::removeSelectedCurves ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurves::removeSelectedCurves";

  for (int i = m_listCurves->selectionModel ()->selectedIndexes ().count () - 1; i >= 0; i--) {

    int row = m_listCurves->selectionModel ()->selectedIndexes ().at (i).row ();

    m_modelCurves->removeRow (row);
  }
}

void DlgSettingsCurves::slotDataChanged (const QModelIndex &topLeft,
                                         const QModelIndex &bottomRight,
                                         const QVector<int> &roles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurves::slotDataChanged"
                              << " topLeft=(" << topLeft.row () << "," << topLeft.column () << ")"
                              << " bottomRight=(" << bottomRight.row () << "," << bottomRight.column () << ")"
                              << " roles=" << rolesAsString (roles).toLatin1 ().data ();

  enableOk (true);
  updateControls ();
}

void DlgSettingsCurves::slotNew ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurves::slotNew";

  enableOk (true);

  const QString NO_ORIGINAL_CURVE_NAME;
  const int NO_POINTS = 0;

  QString curveNameSuggestion = nextCurveName ();

  if (m_listCurves->selectionModel ()->selectedIndexes ().count () == 1) {

    QModelIndex idx = m_listCurves->selectionModel ()->selectedIndexes ().at (0);
    insertCurveName (idx.row (),
                     curveNameSuggestion,
                     NO_ORIGINAL_CURVE_NAME,
                     NO_POINTS);

  } else {

    appendCurveName (curveNameSuggestion,
                     NO_ORIGINAL_CURVE_NAME,
                     NO_POINTS);

  }
}

void DlgSettingsCurves::slotRemove ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurves::slotRemove";

  enableOk (true);

  int numPoints = 0;
  for (int i = 0; i < m_listCurves->selectionModel ()->selectedIndexes ().count (); i++) {

    int row = m_listCurves->selectionModel ()->selectedIndexes ().at (i).row ();
    QModelIndex idx = m_modelCurves->index (row, COL_NUM_POINTS);
    int curvePoints = m_modelCurves->data (idx, Qt::DisplayRole).toInt ();

    numPoints += curvePoints;
  }

  int rtn = QMessageBox::Ok;
  if (numPoints > 0) {

    QString msg;
    if (m_listCurves->selectionModel ()->selectedIndexes ().count () == 1) {
      msg = QString ("Removing this curve will also remove %1 points. Continue?").arg (numPoints);
    } else {
      msg = QString ("Removing these curves will also remove %1 points. Continue?").arg (numPoints);
    }

    rtn = QMessageBox::warning (0,
                                "Curves With Points",
                                msg,
                                QMessageBox::Ok,
                                QMessageBox::Cancel);
  }

  if (rtn == QMessageBox::Ok) {
    removeSelectedCurves ();
  }
}

void DlgSettingsCurves::slotSelectionChanged (QItemSelection, QItemSelection)
{
  enableOk (true);
  updateControls ();
}

void DlgSettingsCurves::updateControls ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsCurves::updateControls";

  Q_ASSERT (m_listCurves != 0);

  int numSelectedItems = m_listCurves->selectionModel ()->selectedIndexes ().count ();
  int numItems = m_modelCurves->rowCount ();

  if (numSelectedItems < 2 ) {

    // Add or Insert is possible
    m_btnNew->setEnabled (true);
    m_btnNew->setText (numSelectedItems == 0 ? "Add" : "Insert");

  } else {

    // Placement of new curve would be ambigous
    m_btnNew->setEnabled (false);
  }

  // Leave at least one curve
  m_btnRemove->setEnabled ((numSelectedItems > 0) && (numSelectedItems < numItems));
}
