#include "CmdMediator.h"
#include "DlgPreferencesPageCurves.h"
#include "Logger.h"
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QListView>
#include <QPushButton>

DlgPreferencesPageCurves::DlgPreferencesPageCurves(CmdMediator &cmdMediator,
                                                   QWidget *parent) :
  DlgPreferencesPageAbstractBase (cmdMediator,
                                  parent)
{
  const int EMPTY_COLUMN_WIDTH = 30;
  const int EMPTY_ROW_HEIGHT = 40;

  QGridLayout *layout = new QGridLayout (this);
  setLayout (layout);

  createButtons (layout);
  createListCurves (layout);

  layout->setColumnStretch (0, 0); // Empty first column
  layout->setColumnMinimumWidth (0, EMPTY_COLUMN_WIDTH);
  layout->setColumnStretch (1, 1); // New
  layout->setColumnStretch (2, 1); // Remove
  layout->setColumnStretch (3, 0); // Move Down
  layout->setColumnStretch (4, 0); // Empty last column
  layout->setColumnMinimumWidth (4, EMPTY_COLUMN_WIDTH);

  layout->setRowStretch (0, 0); // Empty first row
  layout->setRowMinimumHeight (0, EMPTY_ROW_HEIGHT);
  layout->setRowStretch (1, 0); // New
  layout->setRowStretch (2, 1); // Row above Move Up
  layout->setRowStretch (3, 0); // Move Up
  layout->setRowStretch (4, 0); // Move Down
  layout->setRowStretch (5, 1); // Row below Move Down
  layout->setRowStretch (6, 0); // Empty last row
  layout->setRowMinimumHeight (6, EMPTY_ROW_HEIGHT);

  updateControls ();
}

void DlgPreferencesPageCurves::appendCurveName (const QString &curveName)
{

}

void DlgPreferencesPageCurves::createButtons (QGridLayout *layout)
{
  m_btnNew = new QPushButton ("New...");
  m_btnNew->setWhatsThis (tr ("Adds a new curve to the curve list. The curve name can be edited in the curve name list.\n\n"
                              "If a curve is selected then the new curve will be inserted just before it, otherwise the new curve "
                              "will be added at the end.\n\n"
                              "Every curve name must be unique"));
  m_btnNew->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect (m_btnNew, SIGNAL (pressed ()), this, SLOT (slotNew()));
  layout->addWidget (m_btnNew, 1, 1, 1, 1, Qt::AlignLeft);

  m_btnRemove = new QPushButton ("Remove");
  m_btnRemove->setWhatsThis (tr ("Removes the currently selected curve from the curve list.\n\n"
                                 "There must always be at least one curve"));
  m_btnRemove->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect (m_btnRemove, SIGNAL (pressed ()), this, SLOT (slotRemove()));
  layout->addWidget (m_btnRemove, 1, 2, 1, 1, Qt::AlignRight);
}

void DlgPreferencesPageCurves::createListCurves (QGridLayout *layout)
{
  // There is no Qt::ItemIsEditable flag for QListView, so instead we set that flag for the QListViewItems
  m_listCurves = new QListView;
  m_listCurves->setWhatsThis (tr ("List of the curves belonging to this document.\n\n"
                                  "Click on a curve name to edit it.\n\n"
                                  "Reorder curves by dragging them around."));
  m_listCurves->setMinimumHeight (300);
  m_listCurves->setSelectionMode (QAbstractItemView::ExtendedSelection);
  m_listCurves->setDragDropMode (QAbstractItemView::InternalMove);
  layout->addWidget (m_listCurves, 2, 1, 4, 2);
  connect (m_listCurves, SIGNAL (itemSelectionChanged ()), this, SLOT (slotCurveSelectionChanged ()));

  QStringList curveNames = cmdMediator ().curvesGraphsNames ();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin (); itr != curveNames.end (); itr++) {
    QString curveName = *itr;
    appendCurveName (curveName);
  }
}

bool DlgPreferencesPageCurves::endsWithNumber (const QString &str) const
{
  bool success = false;

  if (!str.isEmpty ()) {

      success = (str.right (1).at (0).digitValue() >= 0);
  }

  return success;
}

void DlgPreferencesPageCurves::insertCurveName (int row,
                                                const QString &curveName)
{
}

QString DlgPreferencesPageCurves::nextCurveName () const
{
  const QString DASH_ONE ("-1"); // Nice value to start a new range at a lower level than the current level

  Q_ASSERT (m_listCurves != 0);

  QString curveNameNext ("Next");

  return curveNameNext;
}

int DlgPreferencesPageCurves::numberAtEnd (const QString &str) const
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

void DlgPreferencesPageCurves::slotCurveSelectionChanged ()
{
  updateControls ();
}

void DlgPreferencesPageCurves::slotNew ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageCurves::slotNew";

  QString curveNameSuggestion = nextCurveName ();

}

void DlgPreferencesPageCurves::slotRemove ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageCurves::slotRemove";
}

void DlgPreferencesPageCurves::updateControls ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageCurves::updateControls";

  Q_ASSERT (m_listCurves != 0);
}
