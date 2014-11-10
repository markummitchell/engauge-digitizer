#include "DlgPreferencesPageCurves.h"
#include "Logger.h"
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

DlgPreferencesPageCurves::DlgPreferencesPageCurves(CmdMediator & /* cmdMediator */,
                                                   QWidget *parent) :
  QWidget (parent)
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
}

void DlgPreferencesPageCurves::createButtons (QGridLayout *layout)
{
  m_btnNew = new QPushButton ("New...");
  m_btnNew->setWhatsThis (tr ("Adds a new curve to the curve list. The curve name can be edited in the curve name list.\n\n"
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

  m_btnMoveUp = new QPushButton ("Move Up");
  m_btnMoveUp->setWhatsThis (tr ("Move the currently selected curve up in the curve list.\n\n"
                                 "Exported curves will be in the same order as displayed here"));
  m_btnMoveUp->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect (m_btnMoveUp, SIGNAL (pressed ()), this, SLOT (slotMoveUp()));
  layout->addWidget (m_btnMoveUp, 3, 3, 1, 1, Qt::AlignBottom);

  m_btnMoveDown = new QPushButton ("Move Down");
  m_btnMoveDown->setWhatsThis (tr ("Move the currently selected curve down in the curve list.\n\n"
                                   "Exported curves will be in the same order as displayed here"));
  m_btnMoveDown->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect (m_btnMoveDown, SIGNAL (pressed ()), this, SLOT (slotMoveDown()));
  layout->addWidget (m_btnMoveDown, 4, 3, 1, 1, Qt::AlignTop);
}

void DlgPreferencesPageCurves::createListCurves (QGridLayout *layout)
{
  m_listCurves = new QListWidget;
  m_listCurves->setWhatsThis (tr ("List of the curves belonging to this document"));
  m_listCurves->setMinimumHeight (300);
  layout->addWidget (m_listCurves, 2, 1, 4, 2);
}

void DlgPreferencesPageCurves::slotMoveDown ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageCurves::slotMoveDown";
}

void DlgPreferencesPageCurves::slotMoveUp ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageCurves::slotMoveUp";
}

void DlgPreferencesPageCurves::slotNew ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageCurves::slotNew";
}

void DlgPreferencesPageCurves::slotRename ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageCurves::slotRename";
}

void DlgPreferencesPageCurves::slotRemove ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageCurves::slotRemove";
}
