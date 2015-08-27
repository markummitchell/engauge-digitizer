#include "ChecklistGuidePage.h"
#include "Logger.h"
#include <QGridLayout>
#include <QLabel>
#include <QPalette>
#include <QRadioButton>
#include <QTableWidget>
#include <QVariant>

const int MAX_LAYOUT_WIDTH = 300;
const int TRANSPARENT_ALPHA = 0;

ChecklistGuidePage::ChecklistGuidePage(const QString &title) :
  m_row (0)
{
  setTitle (title);

  m_layout = new QGridLayout;
  m_layout->setColumnStretch (0, 0);
  m_layout->setColumnStretch (1, 1);
  setLayout (m_layout);
}

void ChecklistGuidePage::addHtml (const QString &html)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePage::addHtml";

  QLabel *label = new QLabel (html);
  label->setMaximumWidth(MAX_LAYOUT_WIDTH);
  label->setWordWrap (true);

  m_layout->addWidget (label, m_row++, 0, 1, 2, Qt::AlignTop);
}

QRadioButton *ChecklistGuidePage::addLabelAndRadioButton (const QString &label)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePage::addLabelAndRadioButton";

  QRadioButton *button = new QRadioButton;
  m_layout->addWidget (button, m_row, 0, 1, 1, Qt::AlignTop);

  QLabel *lbl = new QLabel (label);
  lbl->setWordWrap(true);
  lbl->setMaximumWidth(MAX_LAYOUT_WIDTH);
  m_layout->addWidget (lbl, m_row++, 1, 1, 1, Qt::AlignTop);

  return button;
}

void ChecklistGuidePage::addTable (QTableWidget *table)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePage::addTable";

  m_layout->addWidget (table, m_row++, 0, 1, 2, Qt::AlignTop);
}
