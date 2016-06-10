/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MAIN_WINDOW_MODEL_H
#define MAIN_WINDOW_MODEL_H

#include "DocumentModelAbstractBase.h"
#include "MainTitleBarFormat.h"
#include <QLocale>
#include <QString>
#include "ZoomControl.h"
#include "ZoomFactorInitial.h"

class QTextStream;

/// Model for DlgSettingsMainWindow. Unlike the other models (DocumentModel*) this data is not saved and 
/// loaded within the document, so no xml or working with the Document class is involved. Also, there is
/// no associated Cmd. Instead, the settings are saved using QSettings. Method involving xml/Document 
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

  virtual void loadXml(QXmlStreamReader &reader);

  /// Get method for locale
  QLocale locale() const;

  /// Get method for MainWindow titlebar filename format
  MainTitleBarFormat mainTitleBarFormat () const;

  /// Get method for resolution of imported PDF files, in dots per inch
  int pdfResolution () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for locale given attributes
  void setLocale (QLocale::Language language,
                  QLocale::Country country);

  /// Set method for locale given locale object
  void setLocale (const QLocale &locale);

  /// Set method for MainWindow titlebar filename format
  void setMainTitleBarFormat (MainTitleBarFormat mainTitleBarFormat);

  /// Set method for resolution of imported PDF files, in dots per inch
  void setPdfResolution (int resolution);

  /// Set method for zoom control
  void setZoomControl (ZoomControl zoomControl);

  /// Set method for initial zoom factor
  void setZoomFactorInitial (ZoomFactorInitial zoomFactorInitial);

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

};

#endif // MAIN_WINDOW_MODEL_H
