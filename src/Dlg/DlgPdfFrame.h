/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_PDF_FRAME_H
#define DLG_PDF_FRAME_H

#include <QDialog>
#include <QImage>
#include <QObject>

class PdfFrame;
namespace Poppler {
  class Document;
}
class QGraphicsPixmapItem;
class QGridLayout;
class QGraphicsScene;
class QRectF;
class QSpinBox;
class QString;
class QTimer;
class ViewPreview;

/// Dialog for selecting a page and frame on that page when importing an image from a pdf file
class DlgPdfFrame : public QDialog
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgPdfFrame(const Poppler::Document &document,
              int resolution);
  virtual ~DlgPdfFrame();

  /// Image that was selected. Value is null if loading failed
  QImage image () const;

  /// Do preparation before dialog is displayed.
  virtual void showEvent (QShowEvent *event);

private slots:

  /// Hide dialog.
  void slotCancel();

  /// Save changes entered in dialog.
  void slotOk ();

  /// Page number has changed
  void slotPage (int);

  /// Slow processing of pdf is performed asynchronously using a timer so event handlers are not slowed down
  void slotTimeout ();

private:
  DlgPdfFrame();

  void createPageSpinner (QGridLayout *layout,
                          int &row);
  void createPdfFrame ();
  void createPreview (QGridLayout *layout,
                      int &row);
  void createTimer ();
  void finishPanel (QWidget *subPanel);
  void initializeFrameGeometryAndPixmap ();
  QImage loadImage (int page1Based) const;

  /// Dialog layout constant that guarantees every widget has sufficient room
  static int MINIMUM_DIALOG_WIDTH;

  /// Dialog layout constant that guarantees preview has sufficent room
  static int MINIMUM_PREVIEW_HEIGHT;

  void saveGeometryToSettings ();
  void updatePreview ();

  QSpinBox *m_spinPage;
  QPushButton *m_btnCancel;
  QPushButton *m_btnOk;

  QTimer *m_timer;
  const Poppler::Document &m_document;
  int m_resolution;
  QImage m_image; // Needed so it can be passed to external code when this dialog has finished successfully
  QGraphicsPixmapItem *m_pixmap; // Needed so old image can be removed just before new one gets added

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;

  PdfFrame *m_pdfFrame;
};

#endif // DLG_PDF_FRAME_H
