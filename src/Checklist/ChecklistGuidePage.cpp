#include "ChecklistGuidePage.h"
#include "ChecklistLineEdit.h"
#include "Logger.h"
#include <QGridLayout>
#include <QLabel>
#include <QPalette>
#include <QRadioButton>
#include <QVBoxLayout>

const int MAX_LAYOUT_WIDTH = 300;

ChecklistGuidePage::ChecklistGuidePage(const QString &title) :
  m_row (0),
  m_checklineLineEditContainer (0),
  m_checklineLineEditLayout (0)
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

void ChecklistGuidePage::addLineEdit (ChecklistLineEdit *edit)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePage::addLineEdit";

  if (m_checklineLineEditContainer == 0) {

    // This is the first ChecklistLineEdit, so we create a container for it and any more that get added
    m_checklineLineEditLayout = new QVBoxLayout;
    m_checklineLineEditLayout->setSpacing (0); // This is the whole reason we wrap the ChecklineLineEdits in a container

    m_checklineLineEditContainer = new QWidget;
    m_checklineLineEditContainer->setLayout (m_checklineLineEditLayout);
    m_layout->addWidget (m_checklineLineEditContainer, m_row++, 0, 1, 2, Qt::AlignTop);
  }

  m_checklineLineEditLayout->addWidget (edit);
}
