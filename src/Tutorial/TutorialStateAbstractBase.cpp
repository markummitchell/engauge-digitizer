#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "TutorialDlg.h"
#include "TutorialStateAbstractBase.h"
#include "TutorialStateContext.h"

const int DELTA_FONT_SIZE = 2;
const int TITLE_PADDING = 5;
const double Z_TITLE = 2.0; // On top of everything else

TutorialStateAbstractBase::TutorialStateAbstractBase(TutorialStateContext &context) :
  m_context (context)
{
}

TutorialStateAbstractBase::~TutorialStateAbstractBase()
{
}

int TutorialStateAbstractBase::buttonMargin () const
{
  return 10;
}

TutorialStateContext &TutorialStateAbstractBase::context ()
{
  return m_context;
}

QGraphicsPixmapItem *TutorialStateAbstractBase::createPixmapItem (const QString &resource,
                                                                  const QPoint &pos)
{
  QGraphicsPixmapItem *item = new QGraphicsPixmapItem (QPixmap (resource));
  item->setPos (pos);
  context().tutorialDlg().scene().addItem (item);

  return item;
}

QGraphicsTextItem *TutorialStateAbstractBase::createTextItem (const QString &text,
                                                              const QPoint &pos)
{
  QGraphicsTextItem *item = new QGraphicsTextItem (text);
  item->setPos (pos);
  context().tutorialDlg().scene().addItem (item);

  return item;
}

QGraphicsTextItem *TutorialStateAbstractBase::createTitle (const QString &text)
{
  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  QGraphicsTextItem *item = new QGraphicsTextItem (text);
  item->setZValue(Z_TITLE);
  item->setPos (backgroundSize.width() / 2.0 - item->boundingRect().width() / 2.0,
                TITLE_PADDING);
  context().tutorialDlg().scene().addItem (item);

  // Highlight the text
  QFont font = item->font();
  font.setBold (true);
//  font.setPixelSize (font.pixelSize() + DELTA_FONT_SIZE);
  item->setFont (font);
  return item;
}
