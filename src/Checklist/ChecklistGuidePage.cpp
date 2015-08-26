#include "ChecklistGuidePage.h"
#include <QGridLayout>
#include <QPalette>
#include <QTextEdit>

const int TRANSPARENT_ALPHA = 0;

ChecklistGuidePage::ChecklistGuidePage(const QString &title) :
  m_edit (0)
{
  setTitle (title);

  m_edit = new QTextEdit (this);
  m_edit->setReadOnly (true);

  // Hide border and background of edit box
  QPalette palette = m_edit->palette ();
  palette.setColor (QPalette::Base, QColor (0, 0, 0, TRANSPARENT_ALPHA));
  m_edit->setPalette (palette);
  m_edit->setFrameStyle (QFrame::NoFrame);

  m_edit->setText ("<b>Test</b> html");

  QGridLayout *layout = new QGridLayout;
  setLayout (layout);
  layout->addWidget (m_edit);
}
