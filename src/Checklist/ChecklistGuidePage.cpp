/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ChecklistGuidePage.h"
#include "ChecklistLineEdit.h"
#include "Logger.h"
#include <QGridLayout>
#include <QLabel>
#include <QPalette>
#include <QRadioButton>
#include <QVBoxLayout>

ChecklistGuidePage::ChecklistGuidePage(const QString &title) :
  m_row (0),
  m_checklineLineEditContainer (nullptr),
  m_checklineLineEditLayout (nullptr)
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
  label->setWordWrap (true);

  m_layout->addWidget (label, m_row++, 0, 1, 2, Qt::AlignTop);
}

QRadioButton *ChecklistGuidePage::addLabelAndRadioButton (const QString &label,
                                                          const QString &whatsThis)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePage::addLabelAndRadioButton";

  QRadioButton *button = new QRadioButton;
  button->setWhatsThis (whatsThis);
  m_layout->addWidget (button, m_row, 0, 1, 1, Qt::AlignTop);

  QLabel *lbl = new QLabel (label);
  lbl->setWordWrap(true);
  m_layout->addWidget (lbl, m_row++, 1, 1, 1, Qt::AlignTop);

  return button;
}

void ChecklistGuidePage::addLineEdit (ChecklistLineEdit *edit,
                                      const QString &whatsThis)
{
  LOG4CPP_INFO_S ((*mainCat)) << "ChecklistGuidePage::addLineEdit";

  bool isFirst = false;

  if (m_checklineLineEditContainer == nullptr) {

    isFirst = true;

    // This is the first ChecklistLineEdit, so we create a container for it and any more that get added
    m_checklineLineEditLayout = new QVBoxLayout;
    m_checklineLineEditLayout->setSpacing (0); // This is the whole reason we wrap the ChecklineLineEdits in a container

    m_checklineLineEditContainer = new QWidget;
    m_checklineLineEditContainer->setLayout (m_checklineLineEditLayout);
    m_layout->addWidget (m_checklineLineEditContainer, m_row++, 0, 1, 2, Qt::AlignTop);
  }

  edit->setWhatsThis (whatsThis);
  m_checklineLineEditLayout->addWidget (edit);

  // Windows border is missing on left side so border is made complete here
  QString style = QString ("QLineEdit { "
                           "border-left : 1px solid gray; "
                           "border-right: 1px solid gray; "
                           "border-top:   %1px solid gray; "
                           "border-bottom:1px solid gray; }")
          .arg (isFirst ? 1 : 0);
  edit->setStyleSheet (style);
}
