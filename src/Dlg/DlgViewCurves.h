#ifndef DLG_VIEW_CURVES_H
#define DLG_VIEW_CURVES_H

#include <QListView>

class QWidget;

/// Make sure drags result in moves rather than just copies.
class DlgViewCurves : public QListView
{
  Q_OBJECT;

public:
  /// Single constructor.
  explicit DlgViewCurves(QWidget *parent = 0);

  /// Make sure we have move drags rather than copy drags
  virtual void dropEvent (QDropEvent *e);

  /// Change copy to move.
  virtual void startDrag (Qt::DropActions actions);

signals:

public slots:

};

#endif // DLG_VIEW_CURVES_H
