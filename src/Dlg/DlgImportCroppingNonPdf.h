/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_IMPORT_CROPPING_NON_PDF_H
#define DLG_IMPORT_CROPPING_NON_PDF_H

#include <QDialog>
#include <QImage>
#include <QObject>

class QGraphicsPixmapItem;
class QGridLayout;
class QGraphicsScene;
class QRectF;
class QSpinBox;
class QString;
class ViewPreview;

/// Dialog for selecting a page and frame on that page when importing an image from a non-pdf file
class DlgImportCroppingNonPdf : public QDialog
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgImportCroppingNonPdf ();
  virtual ~DlgImportCroppingNonPdf ();

  /// Image that was selected. Value is null if loading failed
  QImage image () const;

  /// Do preparation before dialog is displayed.
  virtual void showEvent (QShowEvent *event);

private slots:

  /// Hide dialog.
  void slotCancel();

  /// Save changes entered in dialog.
  void slotOk ();

private:

  void createPreview (QGridLayout *layout,
                      int &row);
  void finishPanel (QWidget *subPanel);
  void initializeFrameGeometryAndPixmap ();
  QImage loadImage () const;

  /// Dialog layout constant that guarantees every widget has sufficient room
  static int MINIMUM_DIALOG_WIDTH;

  /// Dialog layout constant that guarantees preview has sufficent room
  static int MINIMUM_PREVIEW_HEIGHT;

  void saveGeometryToSettings ();
  void updatePreview ();

  QPushButton *m_btnCancel;
  QPushButton *m_btnOk;

  QImage m_image; // Needed so it can be passed to external code when this dialog has finished successfully
  QGraphicsPixmapItem *m_pixmap; // Needed so old image can be removed just before new one gets added

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;
};

#endif // DLG_IMPORT_CROPPING_NON_PDF_H
