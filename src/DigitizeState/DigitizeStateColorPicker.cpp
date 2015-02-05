#include "CmdMediator.h"
#include "CmdSettingsFilter.h"
#include "DigitizeStateContext.h"
#include "DigitizeStateColorPicker.h"
#include "DocumentModelFilter.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QBitmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>

DigitizeStateColorPicker::DigitizeStateColorPicker (DigitizeStateContext &context) :
  DigitizeStateAbstractBase (context)
{
}

DigitizeStateColorPicker::~DigitizeStateColorPicker ()
{
}

QString DigitizeStateColorPicker::activeCurve () const
{
  return context().mainWindow().selectedGraphCurve();
}

void DigitizeStateColorPicker::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::begin";

  setCursor();
  context().setDragMode(QGraphicsView::NoDrag);
  context().mainWindow().updateViewsOfSettings(activeCurve ());
}

QCursor DigitizeStateColorPicker::cursor() const
{
  // Hot point is at the point of the eye dropper
  const int HOT_X_IN_BITMAP = 8;
  const int HOT_Y_IN_BITMAP = 24;
  LOG4CPP_DEBUG_S ((*mainCat)) << "DigitizeStateColorPicker::cursor";

  QBitmap bitmap (":/engauge/img/cursor_eyedropper.xpm");
  QBitmap bitmapMask (":/engauge/img/cursor_eyedropper_mask.xpm");
  return QCursor (bitmap,
                  bitmapMask,
                  HOT_X_IN_BITMAP,
                  HOT_Y_IN_BITMAP);
}

void DigitizeStateColorPicker::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::end";
}

void DigitizeStateColorPicker::handleKeyPress (Qt::Key key)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleKeyPress key=" << QKeySequence (key).toString ().toLatin1 ().data ();
}

void DigitizeStateColorPicker::handleMousePress (QPointF /* posScreen */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleMousePress";
}

void DigitizeStateColorPicker::handleMouseRelease (QPointF posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::handleMouseRelease";

  QRgb rgb = context().cmdMediator().document().pixmap().toImage().pixel (posScreen.toPoint ());

  DocumentModelFilter modelFilterBefore = context().cmdMediator().document().modelFilter();
  DocumentModelFilter modelFilterAfter = transformFilter (rgb,
                                                          modelFilterBefore,
                                                          context().mainWindow().selectedGraphCurve());

  // Create command to change segment filter
  QUndoCommand *cmd = new CmdSettingsFilter (context ().mainWindow(),
                                             context ().cmdMediator ().document (),
                                             modelFilterBefore,
                                             modelFilterAfter);
  context().appendNewCmd(cmd);
}

DocumentModelFilter DigitizeStateColorPicker::transformFilter (const QRgb &rgb,
                                                               const DocumentModelFilter &modelFilterBefore,
                                                               const QString &curveName)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DigitizeStateColorPicker::transformFilter";

  DocumentModelFilter modelFilterAfter = modelFilterBefore;

  // The choice of which filter mode to use is determined, currently, by the selected pixel. This
  // could be maybe made smarter by looking at other pixels, or even the entire image
  int r = qRed (rgb);
  int g = qGreen (rgb);
  int b = qBlue (rgb);
  if (r == g && g == b) {

    // Pixel is gray scale, so we use intensity

  } else {

    // Pixel is not gray scale, so we use hue

  }

  return modelFilterAfter;
}
