/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MAIN_WINDOW_MODEL_H
#define MAIN_WINDOW_MODEL_H

#include "ColorPalette.h"
#include "DocumentModelAbstractBase.h"
#include "ImportCropping.h"
#include "MainTitleBarFormat.h"
#include <QLocale>
#include <QString>
#include "ZoomControl.h"
#include "ZoomFactorInitial.h"

class QTextStream;

extern bool DEFAULT_DRAG_DROP_EXPORT;
extern int DEFAULT_SIGNIFICANT_DIGITS;
extern bool DEFAULT_SMALL_DIALOGS;
extern bool DEFAULT_IMAGE_REPLACE_RENAMES_DOCUMENT;

/// Model for DlgSettingsMainWindow. Unlike the other models (DocumentModel*) this data is not saved and 
/// loaded within the document, so no xml or working with the Document class is involved. Also, there is
/// no associated Cmd. Instead, the settings are saved using QSettings. Methods involving xml/Document
/// (from DocumentModelAbstractBase) are stubbed out
class MainWindowModel : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  MainWindowModel();

  /// Copy constructor.
  MainWindowModel(const MainWindowModel &other);

  /// Assignment constructor.
  MainWindowModel &operator=(const MainWindowModel &other);

  /// Get method for drag and drop export
  bool dragDropExport () const;

  /// Get method for highlight opacity
  double highlightOpacity() const;

  /// Get method for image replaces renames document
  bool imageReplaceRenamesDocument () const;

  /// Get method for import cropping
  ImportCropping importCropping () const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Get method for locale
  QLocale locale() const;

  /// Get method for MainWindow titlebar filename format
  MainTitleBarFormat mainTitleBarFormat () const;

  /// Maximum number of grid lines
  int maximumGridLines () const;

  /// Get method for resolution of imported PDF files, in dots per inch
  int pdfResolution () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for drag and drop export
  void setDragDropExport (bool dragDropExport);

  /// Set method for highlight opacity
  void setHighlightOpacity (double highlightOpacity);

  /// Set method for image replace renames document
  void setImageReplaceRenamesDocument (bool imageReplaceRenamesDocument);

  /// Set method for import cropping
  void setImportCropping (ImportCropping importCropping);

  /// Set method for locale given attributes
  void setLocale (QLocale::Language language,
                  QLocale::Country country);

  /// Set method for locale given locale object
  void setLocale (const QLocale &locale);

  /// Set method for MainWindow titlebar filename format
  void setMainTitleBarFormat (MainTitleBarFormat mainTitleBarFormat);

  /// Set method for maximum number of grid lines
  void setMaximumGridLines (int maximumGridLines);

  /// Set method for resolution of imported PDF files, in dots per inch
  void setPdfResolution (int resolution);

  /// Set method for significant digits
  void setSignificantDigits (int significantDigits);

  /// Set method for small dialogs flag
  void setSmallDialogs (bool smallDialogs);

  /// Set method for zoom control
  void setZoomControl (ZoomControl zoomControl);

  /// Set method for initial zoom factor
  void setZoomFactorInitial (ZoomFactorInitial zoomFactorInitial);

  /// Get method for significant digits
  int significantDigits () const;

  /// Get method for small dialogs flag
  bool smallDialogs () const;

  /// Get method for zoom control
  ZoomControl zoomControl () const;

  /// Get method for initial zoom factor
  ZoomFactorInitial zoomFactorInitial () const;

private:

  QLocale m_locale;
  ZoomControl m_zoomControl;
  ZoomFactorInitial m_zoomFactorInitial;
  MainTitleBarFormat m_mainTitleBarFormat;
  int m_pdfResolution;
  ImportCropping m_importCropping;
  int m_maximumGridLines;
  double m_highlightOpacity;
  bool m_smallDialogs;
  bool m_dragDropExport;
  int m_significantDigits;
  bool m_imageReplaceRenamesDocument;
};

#endif // MAIN_WINDOW_MODEL_H
